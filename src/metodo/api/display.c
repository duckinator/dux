#include <api/api.h>
#include <api/display.h>

static uint8_t disp_init = 0;

extern struct DisplayDevice VgaDisplayDevice;
//extern struct DisplayDevice UartDisplayDevice;

struct DisplayDevice *DisplayDeviceList[] = { &VgaDisplayDevice,
/*								&UartDisplayDevice*/ };

#define NUM_DISPLAY_DEVICES ( (sizeof(DisplayDeviceList) / sizeof(DisplayDeviceList[0])) )

void DisplaySetAttr(uint8_t lattr)
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

void DisplayClear(void)
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

void DisplayChar(const char c)
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

void DisplayString(const char *s)
{
	do {
		DisplayChar(*s);
	} while (*s++);
}

void DisplaySpot(uint8_t s, uint8_t row, uint8_t col)
{
	// To stop gcc from whining...
	s = s;
	row = row;
	col = col;
}

void DisplayHideCursor()
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

void DisplayCursorPosition(int _row, int _col)
{
	// To stop gcc from whining, again...
	_row = _row;
	_col = _col;
}

void DisplayInit(void)
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

void DisableDisplay(void)
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

int DisplayIsOn(void)
{
	return disp_init;
}
