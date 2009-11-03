#ifndef KEYBOARD_H
#define KEYBOARD_H

#define SCROLL_LED 1
#define NUM_LED 2
#define CAPSLOCK_LED 4

typedef struct hal_key_info {
	int action;
	int scancode;
	char key;
} HalKeyInfo;

extern void HalKeyboardHandler(struct regs *r);
extern int HalKeyboardShift();
extern int HalKeyboardCapslock();
extern int HalKeyboardNumlock();
extern int HalKeyboardAlt();
extern int HalKeyboardCtrl();
extern char HalKeyboardHasInput();
extern HalKeyInfo HalKeyboardRead();
extern HalKeyInfo HalKeyboardReadLetter();
extern HalKeyInfo HalKeyboardResolveScancode(HalKeyInfo keyinfo);
extern HalKeyInfo HalKeyboardResolveScancode_shift(HalKeyInfo keyinfo);
extern void HalKeyboardInit();

extern void HalKeyboardTest();

#endif
