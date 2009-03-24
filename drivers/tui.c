#include "tui.h"

#include <system.h>
#include <string.h>

static unsigned short doublebuf[0x780];
static unsigned short changedbuf[0x780];
static unsigned short *vidmem = (unsigned short*) 0xb8000;

static unsigned char x = 0;
static unsigned char y = 0;

static unsigned char attr = 0x0f;

static void scroll();

void tui_init()
{
	memcpy(doublebuf, 0, 0xf00);
	memcpy(changedbuf, 0, 0x1e0);
}

static void set_hwcursor()
{
	unsigned short position = y * 80 + x;
 
	// Send the low cursor byte.
	outportb(0x3d4, 0x0f);
	outportb(0x3d5, position & 0xff);
 
	// Send the high cursor byte.
	outportb(0x3d4, 0x0e);
	outportb(0x3d5, (position >> 8) & 0xff);
}

static void scroll()
{
	unsigned int i;

	if (y >= 25) {
		/* Move the last 24 lines up 1 line */
		for (i = 0; i < 80*24; i++)
			doublebuf[i] = doublebuf[i+80];

		/* Blank the last line */
		for (i = 80*24; i < 80*25; i++)
			doublebuf[i] = 0x20 | attr << 8;

		/* Set the cursor to the last line */
		y = 24;
	}
}

void tui_set_attr(unsigned char a)
{
	attr = a;
}

void tui_write_char(unsigned char c)
{
	if (c == 0x08) { /* Backspace */
		x--;
		doublebuf[y*80+x] = ' ' | attr << 8;
		x--;
	}
	else if (c == 0x09) { /* Tab */
		x = (x + 8) & ~(8-1);
	}
	else if (c == '\r') { /* Carriage return */
		x = 0;
	}
	else if (c == '\n') { /* New line */
		x = 0;
		y++;
	}
	else if (c == 0x20) { /* Space */
		doublebuf[y*80+x] = ' ' | attr << 8;
		x++;
	}
	else if (c > 0x20) {
		doublebuf[y*80+x] = c | attr << 8;
		x++;
	}

	if (x > 80) {
		y++;
		x = 0;
	}

	scroll();
}

void tui_update_hw()
{
	unsigned int i;

	for (i = 0; i < 80*24; i++)
		vidmem[i] = doublebuf[i];

	set_hwcursor();
}
