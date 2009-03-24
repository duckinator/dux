#include "tui.h"
#include "serial.h"

#include <keyboard.h>

#define SERIAL

unsigned consend(unsigned char c)
{
#ifdef TUI
	tui_write_char(c);
#endif

#ifdef SERIAL
	write_serial(c);
#endif
}

unsigned char conrecv()
{
	unsigned char c;
#ifdef TUI
	c = keyboard_getchar();
#endif

#ifdef SERIAL
	c = read_serial();
	consend(c);
#endif

	return c;
}
