#include <system.h>
 
unsigned short *vidmem = (unsigned short*) 0xb8000;
 
unsigned int cursor_x;
unsigned int cursor_y;
 
unsigned int attribute = 0x0f;
 
static void move_cursor()
{
	// Find the linear cursor position.
	unsigned short position = cursor_y * 80 + cursor_x;
 
	// Send the low cursor byte.
	outportb(0x3d4, 0x0f);
	outportb(0x3d5, position & 0xff);
 
	// Send the high cursor byte.
	outportb(0x3d4, 0x0e);
	outportb(0x3d5, (position >> 8) & 0xff);
}
 
static void scroll()
{
	// Keep in mind that scroll does not move the hardware cursor.
	if (cursor_y >= 25) {
		unsigned short i;
 
		// Move the last 24 lines up 1 line.
		for (i = 0; i < 80*24; i++)
			vidmem[i] = vidmem[i+80];
 
		// Blank the last line.
		for (i = 80*24; i < 80*25; i++)
			vidmem[i] = 0x20 | attribute << 8;
 
		// The cursor should be on the last line.
		cursor_y = 24;
	}
}
 
void monitor_set_attribute(unsigned int attr)
{
	attribute = attr;
}
 
void monitor_clear()
{
	// Sets the entire video memory to white on black spaces.
	unsigned short i;
	for (i = 0; i < 80*25; i++)
		vidmem[i] = 0x20 | attribute << 8;
 
	// Put the cursor in the upper left hand corner.
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}
 
void monitor_put_char(unsigned int c)
{
	// Put the character on the screen at the current cursor position with
	// white on black attributes.
 
	// Backspace
	if (c == 0x08) {
		cursor_x--;
		monitor_put_char(' ');
		cursor_x--;
	}
	// Tab
	else if (c == 0x09) {
		cursor_x = (cursor_x + 8) & ~(8-1);
	}
	// Carriage return
	else if (c == '\r') {
		cursor_x = 0;
	}
	// New line
	else if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	}
	// Space
	else if (c == 0x20) {
		vidmem[cursor_y * 80 + cursor_x] = 0x20 | attribute << 8;
		cursor_x++;
	}
	// Other character.
	else if (c > 0x20) {
		vidmem[cursor_y * 80 + cursor_x] = c | attribute << 8;
		cursor_x++;
	}
 
	// If the x cursor is past column 80, loop around to the next line.
	if (cursor_x > 80) {
		cursor_y++;
		cursor_x = 0;
	}
 
	scroll();
	move_cursor();
}

void putch(unsigned int c)
{
	consend(c);
}

void puts(char *str)
{
	while(*str)
		putch(*str++);
}

void monitor_switch_pages(unsigned int a, unsigned int b)
{
	// There are no pages after 8 (7).
	if ((a > 8) || (b > 8))
		return;
 
	// Pointers to video memory.
	unsigned short *ap = (unsigned short*) 0xb8000 + (a * 4000);
	unsigned short *bp = (unsigned short*) 0xb8000 + (b * 4000);
 
	// Buffer to store ap.
	unsigned short temp[4000];
 
	// Switch the pages.
	unsigned short i;
	for (i = 0; i < 4000; i++) {
		temp[i] = ap[i];
	}
	for (i = 0; i < 4000; i++) {
		ap[i] = bp[i];
	}
	for (i = 0; i < 4000; i++) {
		bp[i] = temp[i];
	}
 
	// Cursor handling after a page switch does not belong here.
}
 
unsigned int monitor_get_cursor_x()
{
	return cursor_x;
}
 
unsigned int monitor_get_cursor_y()
{
	return cursor_y;
}
 
void monitor_set_cursor(unsigned int x, unsigned int y)
{
	cursor_x = x;
	cursor_y = y;
	move_cursor();
}
