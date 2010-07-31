#include <metodo/metodo.h>
#include <metodo/hal/hal.h>

#define COLS (80)
#define ROWS (25)
#define VIDEO_MEMORY (0xb8000)

#define CLEAR (attr << 8 | ' ')
#define SPOT(n) (attr << 8 | (n))
#define PUTSPOT(n) VideoMemory[row*COLS + col] = SPOT(n);

static uint8_t disp_init = 0;

extern struct DisplayDevice VgaDisplayDevice;
extern struct DisplayDevice UartDisplayDevice;

struct DisplayDevice *DisplayDeviceList[] = { &VgaDisplayDevice,
								&UartDisplayDevice };

#define NUM_DISPLAY_DEVICES ( (sizeof(DisplayDeviceList) / sizeof(DisplayDeviceList[0])) )

void HalDisplaySetAttr(uint8_t lattr)
{
	unsigned int i;
	struct DisplayDevice *Display;

	for (i = 0; i < NUM_DISPLAY_DEVICES; i++) {
		Display = DisplayDeviceList[i];
		/* don't call NULL function pointers... */
		if (Display->DisplaySetAttr)
			Display->DisplaySetAttr(lattr);
	}
}

void HalDisplayClear(void)
{
	unsigned int i;
	struct DisplayDevice *Display;
	
	for (i = 0; i < NUM_DISPLAY_DEVICES; i++) {
		Display = DisplayDeviceList[i];
		/* don't call NULL function pointers... */
		if (Display->DisplayClear)
			Display->DisplayClear();
	}
}

void HalDisplayChar(char c)
{
	unsigned int i;
	struct DisplayDevice *Display;
	
	for (i = 0; i < NUM_DISPLAY_DEVICES; i++) {
		Display = DisplayDeviceList[i];
		/* don't call NULL function pointers... */
		if (Display->DisplayChar)
			Display->DisplayChar(c);
	}
}

void HalDisplayString(char *s)
{
	do {
		HalDisplayChar(*s);
	} while (*s++);
}

void HalDisplaySpot(uint8_t s, uint8_t row, uint8_t col)
{
	// To stop gcc from whining...
	s = s;
	row = row;
	col = col;
}

void HalDisplayHideCursor()
{
	unsigned int i;
	struct DisplayDevice *Display;
	
	for (i = 0; i < NUM_DISPLAY_DEVICES; i++) {
		Display = DisplayDeviceList[i];
		/* don't call NULL function pointers... */
		if (Display->DisplayHideCursor)
			Display->DisplayHideCursor();
	}
}

void HalDisplayCursorPosition(int _row, int _col)
{
	// To stop gcc from whining, again...
	_row = _row;
	_col = _col;
}

void HalInitDisplay(void)
{
	unsigned int i;
	struct DisplayDevice *Display;
	
	for (i = 0; i < NUM_DISPLAY_DEVICES; i++) {
		Display = DisplayDeviceList[i];
		/* don't call NULL function pointers... */
		if (Display->Init)
			Display->Init();
	}
}

void HalDisableDisplay(void)
{
	unsigned int i;
	struct DisplayDevice *Display;
	
	for (i = 0; i < NUM_DISPLAY_DEVICES; i++) {
		Display = DisplayDeviceList[i];
		/* don't call NULL function pointers... */
		if (Display->Disable)
			Display->Disable();
	}
}

int HalIsDisplayOn(void)
{
	return disp_init;
}
