#include <dux/drivers/core/ports.h>
#include <dux/drivers/core/console.h>

#include <isr.h>

unsigned char buf[0x1000];
unsigned char *buffer;
unsigned char *origbuffer;
int shift_l = 0;
int shift_r = 0;
int capslock = 0;
int numlock = 0;
int alt = 0;
int ctrl = 0;

static void kb_irq_handler()
{
	unsigned int scancode = inb(0x60);

	*++buffer = scancode;
}

int kb_shift()
{
	return shift_l || shift_r;
}

int kb_capslock()
{
	return capslock;
}

int kb_numlock()
{
	return numlock;
}

int kb_alt()
{
	return alt;
}

int kb_ctrl()
{
	return ctrl;
}

char kb_read()
{
	int tmp;
start:
	if (buffer > origbuffer) {
			
		tmp = *buffer-- & 0xFF;
		//printk("\n'%x'\n", tmp);
		
		// Left shift
		if (tmp == 0x2A)
			shift_l = 1;
		else if (tmp == 0xAA)
			shift_l = 0;
		
		// Right shift
		if (tmp == 0x36)
			shift_r = 1;
		else if (tmp == 0xB6)
			shift_r = 0;
		
		// Alt
		if (tmp == 0x38)
			alt = 1;
		else if (tmp == 0xB8)
			alt = 0;
		
		// Control
		if (tmp == 0x1D)
			ctrl = 1;
		else if (tmp == 0x9D)
			ctrl = 0;
			
		return (char)tmp;
	} else {
		// Goto is usually frowned upon, but it is truly the most
		// understandable method here. We could also use a while loop.
		goto start;
	}
}

void kb_init()
{
	HalIrqHandler_Install(1, kb_irq_handler);
	// The compiler is convinced that unsigned char[0x1000] is not an
	// lvalue, so all these hacks are needed to compile.
	buffer = buf;
	origbuffer = buffer;
}
