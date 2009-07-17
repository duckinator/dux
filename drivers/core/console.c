#include <dux/drivers/core/console.h>
#include <dux/drivers/core/screen.h>
#include <dux/drivers/core/kb.h>

#include "keysym.h"

static unsigned char x, y, tab_start;

void console_tab_start(char start)
{
	tab_start = start;
}

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
		x = ((x + 8 - tab_start) & ~(8 - 1)) + tab_start;
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
	int tmp, shift;
	
	tmp = kb_read();
	//printk("\n%i shift: %i alt: %i ctrl: %i... ", tmp, kb_shift(), kb_alt(), kb_ctrl());
	if (!(tmp & 0x80))
	{
		if (kb_alt())
		{
			
		}
		
		if (kb_ctrl())
		{
			
		}
		
		if (kb_shift())
			return keysym_us_shift[tmp];
		else
			return keysym_us[tmp];
	}
	//if (tmp & 0x80)
	return 0;
	//return keysym_us[tmp];
}

void console_clear()
{
	x = 0;
	y = 0;
	screen_clear();
}

void console_init()
{
	screen_init();
	x = 0;
	y = 0;
	tab_start = 0;

	kb_init();
}
