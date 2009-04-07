#include <dux/drivers/core/console.h>
#include <dux/drivers/core/screen.h>

static unsigned char x, y;

void console_write(char c)
{
	if (c == 0x08) {
		if (x > 0)
			screen_writechar(x-1, y, screen_getattr().attr, c);
		else
			screen_writechar(79, y-1, screen_getattr().attr, c);
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

char console_read()
{
	screen_showcursor(block);
	screen_hidecursor();
	return 0x0;
}

void console_init()
{
	screen_init();
	x = 0;
	y = 0;
}
