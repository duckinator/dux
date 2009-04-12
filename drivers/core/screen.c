#include <dux/drivers/core/ports.h>
#include <dux/drivers/core/screen.h>

static unsigned short *vidmem = (unsigned short*) 0xb8000;
static Cursor cs;

/*
 * Writing characters
 */

void screen_writechar(unsigned char x, unsigned char y, unsigned char attr, char c)
{
	unsigned short pos = 80*y+x;

	vidmem[pos] = attr << 8 | c;
}

/*
 * Software cursor
 */

void screen_hidecursor()
{
	cs.type = none;
}

void screen_showcursor(CursorStyle type)
{
	cs.type = type;
}

void screen_drawcursor(unsigned char x, unsigned char y)
{
	// Column 80 needs to be on column 80, the other columns need to be one column after
	// the printed text.
	if (cs.type != none) {
		if (x == 79) {
			x = 0;
			y++;
			switch (cs.type) {
				case block:
					vidmem[80*y+x] = cs.cattr << 8 | (vidmem[80*y+x] & 0xff);
					break;
				default:
					break;
			}
		} else {
			x = x+1;
			switch (cs.type) {
				case block:
					vidmem[80*y+x] = cs.cattr << 8 | (vidmem[80*y+x] & 0xff);
					break;
				default:
					break;
			}
		}
	}
}

/*
 * Misc
 */

void screen_scroll(unsigned char *x, unsigned char *y)
{
	unsigned int i;

	if (*y > 24) {
		for (i = 0; i < 80*24; i++)
			vidmem[i] = vidmem[i+80];

		for (i = 80*24; i < 80*25; i++)
			vidmem[i] = cs.attr << 8 | 0x20;
		*y = 24;
		*x = 0;
	}
}

void screen_setattr(unsigned char attr, unsigned char cattr)
{
	cs.attr = attr;
	cs.cattr = cattr;
}

Cursor screen_getattr()
{
	return cs;
}

void screen_clear()
{
	int i;
	for (i = 0; i < 80*25; i++) {
		vidmem[i] = cs.attr << 8 | ' ';
	}
}

void screen_init()
{
	// Hide cursor.
	// I'll handle the cursor myself, thankyouverymuch.
	outb(0x3d4, 0x0a);
	outb(0x3d5, 1 << 5);

	// Clear cursor structures.
	cs.attr = 0x80;
	cs.cattr = 0xf0;
	cs.type = block;

	screen_clear();
}
