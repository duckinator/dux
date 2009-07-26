#include <arch/display.h>
#include <stdint.h>

#define COLS (80)
#define ROWS (25)
#define VIDEO_MEMORY (0xb8000)

#define CLEAR (attr << 8 | ' ')
#define SPOT(n) (attr << 8 | (n))
#define PUTSPOT(n) VideoMemory[row*COLS + col] = SPOT(n);

static uint16_t *VideoMemory;

static uint8_t attr;
static uint8_t col;
static uint8_t row;
static uint8_t escape;
static uint8_t escape_attr;

void ArchDisplaySetAttr(uint8_t lattr)
{
	attr = lattr;
}

void ArchDisplayClear(void)
{
	int i;
	for (i = 0; i < COLS*ROWS; i++)
		VideoMemory[i] = CLEAR;
}

void ArchDisplayScroll(void)
{
	int i;
	if (row >= ROWS) {
		for (i = 0; i < COLS*(ROWS-1); i++) {
			VideoMemory[i] = VideoMemory[i + COLS];
		}
		for (COLS*(ROWS-1); i < COLS*ROWS; i++) {
			VideoMemory[i] = CLEAR;
		}
		row = ROWS-1;
		col = 0;
	}
}

void ArchDisplayChar(char c)
{
	if (c == 0x08) {
		/* Backspace */
		col--;
		PUTSPOT(' ');
	} else if (c == '\t') {
		/* Tab */
		col = ((col + 8 - 8) & ~(8 - 1)) + 8;
	} else if (c == '\r') {
		col = 0;
	} else if (c == '\n') {
		col = 0;
		row++;
	} else if (c >= ' ') {
		/* Printable */
		PUTSPOT(c);
		col++;
	} else if (c == 0x1b) {
		escape = 1;
	}

	if (escape) {
		if (c == '[') {
			escape_attr = 1;
		}
	}

	if (col >= COLS) {
		col = 0;
		row++;
	}
	ArchDisplayScroll();
}

void ArchDisplayString(char *s)
{
	do {
		ArchDisplayChar(*s);
	} while (*s++);
}

void ArchDisplaySpot(uint8_t s, uint8_t row, uint8_t col)
{
		PUTSPOT(s);
		col++;
}

void ArchDisplayInit(void)
{
	VideoMemory = (uint16_t*) VIDEO_MEMORY;
	col = 0;
	row = 0;
	attr = 0x1f;
	escape = 0;
	escape_attr = 0;
	ArchDisplayClear();
}
