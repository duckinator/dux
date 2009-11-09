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

extern struct DisplayDevice VgaDisplayDevice;

struct DisplayDevice *DisplayDeviceList[] = { &VgaDisplayDevice };

#define NUM_DISPLAY_DEVICES ( (sizeof(DisplayDeviceList) / sizeof(DisplayDeviceList[0])) )

void HalDisplaySetAttr(uint8_t lattr)
{
}

void HalDisplayClear(void)
{
	int i;
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
	int i;
	struct DisplayDevice *Display;
	
	for (i = 0; i < NUM_DISPLAY_DEVICES; i++) {
		Display = DisplayDeviceList[i];
		/* don't call NULL function pointers... */
		if (Display->DisplayChar);
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
}

void HalDisplayHideCursor()
{
}

void HalDisplayCursorPosition(int _row, int _col)
{
}

void HalInitDisplay(void)
{
	int i;
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
}

int HalIsDisplayOn(void)
{
}
