#include <dux/drivers/core/ports.h>
#include <dux/drivers/core/screen.h>

static unsigned short *vidmem = (unsigned short*) 0xb8000;
static CursorPos cp;

/*
 * Writing characters
 * Goes from hard to use to easy to use
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
	cp.type = none;
}

void screen_showcursor(CursorStyle type)
{
	cp.type = type;
}

void screen_drawcursor(unsigned char x, unsigned char y)
{
	// Column 80 needs to be on column 80, the other columns need to be one column after
	// the printed text.
	if (cp.type != none) {
		if (x == 79) {
			x = 0;
			y++;
			switch (cp.type) {
				case block:
					vidmem[80*y+x] = cp.cattr << 8 | (vidmem[80*y+x] & 0xff);
					break;
				default:
					break;
			}
		} else {
			x = x+1;
			switch (cp.type) {
				case block:
					vidmem[80*y+x] = cp.cattr << 8 | (vidmem[80*y+x] & 0xff);
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

void screen_setattr(unsigned char attr, unsigned char cattr)
{
	cp.attr = attr;
	cp.cattr = cattr;
}

void screen_clear()
{
	int i;
	for (i = 0; i < 80*25; i++) {
		vidmem[i] = cp.attr << 8 | ' ';
	}
}

void screen_init()
{
	// Hide cursor.
	// I'll handle the cursor myself, thankyouverymuch.
	outb(0x3d4, 0x0a);
	outb(0x3d5, 1 << 5);

	cp.x = 0;
	cp.y = 0;
	cp.attr = 0x80;
	cp.cattr = 0xf0;
	cp.type = block;

	screen_clear();
}
