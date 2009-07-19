#include <dux/drivers/core/console.h>
#include <dux/drivers/core/screen.h>
#include <dux/drivers/core/kb.h>

#include "keysym.h"

static unsigned char x, y;

void console_writeb(char c)
{

	if (c == 0x08) {
		if (x > 0) {
			x--;
			screen_writechar(x, y, screen_getattr().attr, ' ');
		} else {
			x = 79;
			y--;
			screen_writechar(x, y, screen_getattr().attr, ' ');
		}
	}
	else if (c == 0x09) {
		x = (x+8) & ~(8-1);
	}
	else if (c == '\r') {
		x = 0;
	}
	else if (c == '\n') {
		y++;
		x = 0;
	}
	else if (c >= 0x20) {
		screen_writechar(x, y, screen_getattr().attr, c);
		x++;
	}

	if (x > 80) {
		x = 0;
		y++;
	}

	screen_scroll(&x, &y);
}

void console_write(char *buf, unsigned int count)
{
	unsigned int i;
	for (i = 0; i < count; i++)
		console_writeb(buf[i]);
}

char console_readb()
{
	char tmp;
	tmp = kb_read();
	if (tmp & 0x80)
		return 0;
	return keysym_us[tmp];
}

void console_init()
{
	screen_init();
	screen_setattr(0x1f, 0x1f);
	screen_clear();
	x = 0;
	y = 0;

	kb_init();
}
