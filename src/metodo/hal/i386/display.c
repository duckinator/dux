#include <metodo/metodo.h>

#define COLS (80)
#define ROWS (25)
#define VIDEO_MEMORY (0xb8000)

#define CLEAR (attr << 8 | ' ')
#define SPOT(n) (attr << 8 | (n))
#define PUTSPOT(n) VideoMemory[row*COLS + col] = SPOT(n);

static uint16_t *VideoMemory;

static uint8_t disp_init = 0;
static uint8_t attr;
static uint8_t col;
static uint8_t row;
static uint8_t escape;
static uint8_t escape_attr;

void HalDisplaySetAttr(uint8_t lattr)
{
	attr = lattr;
}

void HalDisplayClear(void)
{
	int i;
	for (i = 0; i < COLS*ROWS; i++)
		VideoMemory[i] = CLEAR;
}

void HalDisplayScroll(void)
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

void HalDisplayChar(char c)
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
	}

	if (col >= COLS) {
		col = 0;
		row++;
	}
	HalDisplayScroll();
}

void HalDisplayString(char *s)
{
	do {
		HalDisplayChar(*s);
	} while (*s++);
}

void HalDisplaySpot(uint8_t s, uint8_t row, uint8_t col)
{
		PUTSPOT(s);
		col++;
}

void HalDisplayHideCursor()
{
	HalOutPort(0x3d4, 0x0a);
	HalOutPort(0x3d5, 1 << 5);
}

void HalInitDisplay(void)
{
	VideoMemory = (uint16_t*) VIDEO_MEMORY;
	col = 0;
	row = 0;
	attr = 0x1f;
	escape = 0;
	escape_attr = 0;
	disp_init = 1;
	HalDisplayHideCursor();
	HalDisplayClear();
}

void HalDisableDisplay(void)
{
	disp_init = 0;
}

int HalIsDisplayOn(void)
{
	return (int) disp_init ? 1 : 0;
}
