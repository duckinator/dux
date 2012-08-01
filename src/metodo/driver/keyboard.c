#include <driver/driver.h>
#include <driver/keyboard/keysym.h>

int shift_l  = 0,
	shift_r  = 0,
	capslock = 0,
	numlock  = 0,
	alt_l	= 0,
	alt_r	= 0,
	ctrl_l   = 0,
	ctrl_r   = 0,
	shift	= 0,
	alt	  = 0,
	ctrl	 = 0,
	escaped  = 0;

HalKeyboardEventQueue *HalKeyboardEventQueue_head = NULL;
HalKeyboardEventQueue *HalKeyboardEventQueue_tail = NULL;

void HalKeyboardHandler(UNUSED struct regs *r)
{
	uint8_t keyCode = HalInPort(0x60);

	HalKeyboardEvent *event = kmalloc(sizeof(HalKeyboardEvent));

	if (keyCode & 0x80) {
		event->type = HalKeyboardEventType_up;
		keyCode = keyCode & ~0x80;
	} else {
		event->type = HalKeyboardEventType_down;
	}

	event->code = keyCode;
	event->character = (shift_l || shift_r) ? keysym_us_shift[keyCode] : keysym_us[keyCode];
	event->shift_l = shift_l;
	event->shift_r = shift_r;
	event->shift = shift_l || shift_r;
	event->ctrl_l = ctrl_l;
	event->ctrl_r = ctrl_r;
	event->ctrl = ctrl;
	event->alt_l = alt_l;
	event->alt_r = alt_r;
	event->alt = alt;

	switch (event->code)
	{
	case 0x2A:
		shift_l = !event->type;
		break;
	case 0x36:
		shift_r = !event->type;
		break;
	case 0x1D:
		// TODO: Handle LCtrl/RCtrl separately.
		ctrl = ctrl_l = ctrl_r = !event->type;
		break;
	case 0x38:
		// TODO: Handle LAlt/RAlt separately.
		alt = alt_l = alt_r = !event->type;
		break;
	}

	HalKeyboardEventQueue_enqueue(event);
}

void HalKeyboardLeds(uint8_t status){
	while((HalInPort(0x64)&2)!=0){} //loop until zero
	HalOutPort(0x60,0xED);

	while((HalInPort(0x64)&2)!=0){} //loop until zero
	HalOutPort(0x60,status);
}

int HalKeyboardCapslock()
{
	return capslock;
}

int HalKeyboardNumlock()
{
	return numlock;
}

void HalKeyboardEventQueue_enqueue(HalKeyboardEvent *event)
{
	HalKeyboardEventQueue *new = kmalloc(sizeof(HalKeyboardEventQueue));
	new->event = event;
	new->previous = NULL;
	if (HalKeyboardEventQueue_tail)
	{
		HalKeyboardEventQueue_tail->previous = new;
		HalKeyboardEventQueue_tail = new;
	}
	else
	{
		HalKeyboardEventQueue_head = new;
		HalKeyboardEventQueue_tail = new;
	}
}


HalKeyboardEvent *HalKeyboardEventQueue_dequeue()
{
	if (!HalKeyboardEventQueue_head)
		return NULL;
	HalKeyboardEventQueue *head = HalKeyboardEventQueue_head;
	HalKeyboardEvent *event = head->event;
	HalKeyboardEventQueue_head = head->previous;
	if (HalKeyboardEventQueue_tail == head)
		HalKeyboardEventQueue_tail = NULL;

	free(head);
	return event;
}

HalKeyboardEvent *HalKeyboardGetEvent(int blocking)
{
	// Curtis' version uses Threading_yield(). We don't have Threading_yield() :(
	if (blocking)
		while (!HalKeyboardEventQueue_head)
						__asm__("hlt");

	return HalKeyboardEventQueue_dequeue();
}

HalKeyboardEvent *HalKeyboardReadLetter(int echo)
{
	HalKeyboardEvent *event = HalKeyboardGetEvent(1);
	while (!event || !event->character || event->type == HalKeyboardEventType_up) {
		free(event);
		event = HalKeyboardGetEvent(1);
	}
	char character = event->character;
	if (echo)
		DisplayChar(character);
	free(event);
	return character;
}

void HalKeyboardInit()
{
	HalIrqHandler_Install(1, (void*)HalKeyboardHandler);
}

