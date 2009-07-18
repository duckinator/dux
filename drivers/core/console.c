#include <dux/drivers/core/console.h>
#include <dux/drivers/core/screen.h>
#include <dux/drivers/core/kb.h>

//#include "keysym.h"

static unsigned char cursor_x, cursor_y, tab_start;

void console_tab_start(char start)
{
	tab_start = start;
}

void console_writeb(char c)
{

	if (c == 0x08) {
		if (cursor_x > 0) {
			cursor_x--;
			screen_writechar(cursor_x, cursor_y, screen_getattr().attr, ' ');
		} else {
			cursor_x = 79;
			cursor_y--;
			screen_writechar(cursor_x, cursor_y, screen_getattr().attr, ' ');
		}
	}
	else if (c == 0x09) {
		cursor_x = ((cursor_x + 8 - tab_start) & ~(8 - 1)) + tab_start;
	}
	else if (c == '\r') {
		cursor_x = 0;
	}
	else if (c == '\n') {
		cursor_y++;
		cursor_x = 0;
	}
	else if (c >= 0x20) {
		screen_writechar(cursor_x, cursor_y, screen_getattr().attr, c);
		cursor_x++;
	}

	if (cursor_x > 80) {
		cursor_x = 0;
		cursor_y++;
	}

	screen_scroll(&cursor_x, &cursor_y);
	update_cursor(cursor_y, cursor_x);
}

void console_write(char *buf, unsigned int count)
{
	unsigned int i;
	for (i = 0; i < count; i++)
		console_writeb(buf[i]);
}

char console_readb()
{
	int scancode = kb_read();
	//printk("\n%i shift: %i alt: %i ctrl: %i... ", scancode, kb_shift(), kb_alt(), kb_ctrl());
	if (!(scancode & 0x80))
	{
		if (kb_alt())
		{
			
		}
		
		if (kb_ctrl())
		{
			
		}
		
		return console_resolve_scancode(scancode);
	}
	//if (scancode & 0x80)
	return 0;
}

char console_resolve_scancode(int scancode)
{
	if (kb_shift())
		return kb_resolve_scancode_shift(scancode);
	else
		return kb_resolve_scancode(scancode);
}

void console_clear()
{
	cursor_x = 0;
	cursor_y = 0;
	screen_clear();
}

void console_init()
{
	screen_init();
	cursor_x = 0;
	cursor_y = 0;
	tab_start = 0;

	kb_init();
}

unsigned int console_get_cursor_x()
{
	return cursor_x;
}
 
unsigned int console_get_cursor_y()
{
	return cursor_y;
}
 
void console_set_cursor(unsigned int x, unsigned int y)
{
	cursor_x = x;
	cursor_y = y;
        //move_cursor();
}
