#ifndef HAL_KEYBOARD_H
#define HAL_KEYBOARD_H

#define SCROLL_LED 1
#define NUM_LED 2
#define CAPSLOCK_LED 4

typedef enum
{
    HalKeyboardEventType_down,
    HalKeyboardEventType_up
} HalKeyboardEventType;

typedef struct HalKeyboardEvent {
	HalKeyboardEventType type;
	int ctrl_l, ctrl_r;
	int alt_l, alt_r;
	int shift_l, shift_r;
  int alt, shift, ctrl;
	uint32_t code;
	char character;
	char unused[3]; // Fix alignment
} HalKeyboardEvent;

typedef struct HalKeyboardEventQueue
{
    HalKeyboardEvent *event;
    struct HalKeyboardEventQueue *previous;
} HalKeyboardEventQueue;

void HalKeyboardHandler(struct regs *r);
int HalKeyboardCapslock();
int HalKeyboardNumlock();
void HalKeyboardEventQueue_enqueue(HalKeyboardEvent *event);
HalKeyboardEvent *HalKeyboardEventQueue_dequeue();
HalKeyboardEvent *HalKeyboardGetEvent(int blocking);
char HalKeyboardReadLetter();
void HalKeyboardInit();

#endif /* end of include guard: HAL_KEYBOARD_H */
