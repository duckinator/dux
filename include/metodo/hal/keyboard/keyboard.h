#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <metodo/hal/keyboard/keysym.h>

extern void HalKeyboardHandler(struct regs *r);
extern int HalKeyboardShift();
extern int HalKeyboardCapslock();
extern int HalKeyboardNumlock();
extern int HalKeyboardAlt();
extern int HalKeyboardCtrl();
extern char HalKeyboardHasInput();
extern char HalKeyboardRead();
extern char HalKeyboardRead();
extern char HalKeyboardResolveScancode(int scancode);
extern char HalKeyboardResolveScancode_shift(int scancode);
extern void HalKeyboardInit();

extern void HalKeyboardTest();

#endif
