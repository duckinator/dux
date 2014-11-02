#include <system.h>
#include <api/display.h>

#define COLS (80)
#define ROWS (25)
#define VIDEO_MEMORY (0xb8000)

#define CLEAR (uint16_t)(attr << 8 | ' ')
#define SPOT(n) (uint16_t)(attr << 8 | (n))
#define PUTSPOT(n) VideoMemory[row*COLS + col] = SPOT(n);

static uint16_t *VideoMemory;

static uint8_t disp_init = 0;
static uint8_t attr;
static uint8_t col;
static uint8_t row;
static uint8_t escape;
static uint8_t escape_attr;

void DisplaySetAttr(uint8_t lattr)
{
	attr = lattr;
}

void DisplayClear(void)
{
	int i;
	DisplayCursorPosition(0, 0);
	for (i = 0; i < COLS*ROWS; i++)
		VideoMemory[i] = CLEAR;
}

void DisplayScroll(void)
{
	int i;
	if (row >= ROWS) {
		for (i = 0; i < COLS*(ROWS-1); i++) {
			VideoMemory[i] = VideoMemory[i + COLS];
		}
		for (i = COLS*(ROWS-1); i < COLS*ROWS; i++) {
			VideoMemory[i] = CLEAR;
		}
		row = ROWS-1;
		col = 0;
	}
}

void DisplayChar(char c)
{
	if (c == 0x08) {
		/* Backspace */
		// TODO: Add test for DisplayChar() backspacing from column 0 to previous line. Row 0, as well as a higher row.
		if (col == 0) {
			// If it's row 0, col 0, we merely ignore it.
			if (row != 0) {
				/* This stupid gcc fail *AGAIN*?! come on now.
				 * clang can handle this:
				 * 	  row -= 1;
				 */
				row = (uint8_t)(row - 1);
				col = COLS-1;
			}
		} else {
			col--;
		}
		PUTSPOT(' ');
	} else if (c == '\t') {
		/* Tab */
		col = (uint8_t)(((col + 8 - 8) & ~(8 - 1)) + 8);
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
	DisplayScroll();
}

void DisplayString(const char *s)
{
	for(; *s; s++)
		DisplayChar(*s);
}

void DisplaySpot(uint8_t s, uint8_t row, uint8_t col)
{
	PUTSPOT(s);
	col++;
}

void DisplayHideCursor()
{
	HalOutPort(0x3d4, 0x0a);
	HalOutPort(0x3d5, 1 << 5);
}

void DisplayCursorPosition(uint8_t _row, uint8_t _col)
{
	col = _col;
	row = _row;
}

void DisplayInit(void)
{
	VideoMemory = (uint16_t*) VIDEO_MEMORY;
	col = 0;
	row = 0;
	attr = 0x1f;
	escape = 0;
	escape_attr = 0;
	disp_init = 1;
	DisplayHideCursor();
	DisplayClear();
}

void DisableDisplay(void)
{
	disp_init = 0;
}

int DisplayIsOn(void)
{
	return (int) disp_init ? 1 : 0;
}

