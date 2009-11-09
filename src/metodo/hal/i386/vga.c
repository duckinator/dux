
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

void VgaDisplaySetAttr(uint8_t lattr)
{
	attr = lattr;
}

void VgaDisplayClear(void)
{
	int i;
	VgaDisplayCursorPosition(0, 0);
	for (i = 0; i < COLS*ROWS; i++)
		VideoMemory[i] = CLEAR;
}

static void VgaDisplayScroll(void)
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

void VgaDisplayChar(char c)
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
	VgaDisplayScroll();
}

void VgaDisplaySpot(uint8_t s, uint8_t row, uint8_t col)
{
	PUTSPOT(s);
	col++;
}

void VgaDisplayHideCursor()
{
	HalOutPort(0x3d4, 0x0a);
	HalOutPort(0x3d5, 1 << 5);
}

void VgaDisplayCursorPosition(int _row, int _col)
{
	col = _col;
	row = _row;
}

void VgaInitDisplay(void)
{
	VideoMemory = (uint16_t*) VIDEO_MEMORY;
	col = 0;
	row = 0;
	attr = 0x1f;
	escape = 0;
	escape_attr = 0;
	disp_init = 1;
	VgaDisplayHideCursor();
	VgaDisplayClear();
}

void VgaDisableDisplay(void)
{
	disp_init = 0;
}

int VgaIsDisplayOn(void)
{
	return (int) disp_init ? 1 : 0;
}

struct DisplayDevice VgaDisplayDevice = {
	.Init		= VgaInitDisplay,
	.DisplayChar	= VgaDisplayChar,
	.DisplayClear	= VgaDisplayClear,
};
