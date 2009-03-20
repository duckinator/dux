#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <isr.h>

typedef struct {
	unsigned int alt;
	unsigned int ctrl;
	unsigned int shift_l;
	unsigned int shift_r;
	unsigned int capslock;
} keyboard_status_t;

unsigned int keyboard_install(void);
char keyboard_getchar();
keyboard_status_t keyboard_getstatus();

#endif
