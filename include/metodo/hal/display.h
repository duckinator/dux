#ifndef HAL_DISPLAY_H
#define HAL_DISPLAY_H

struct DisplayDevice {
	void (*Init) ();
	void (*Disable) ();
	void (*DisplayChar) (char c);
	void (*DisplayClear) ();
	void (*DisplaySetAttr) (uint8_t lattr);
	void (*DisplayHideCursor) ();
};

void HalDisplaySetAttr(uint8_t lattr);
void HalDisplayClear(void);
void HalDisplayScroll(void);
void HalDisplayChar(char c);
void HalDisplayString(char *s);
void HalDisplaySpot(uint8_t s, uint8_t row, uint8_t col);
void HalInitDisplay(void);
void HalDisableDisplay(void);
int HalIsDisplayOn(void);
void HalDisplayHideCursor();
void HalDisplayCursorPosition(int _row, int _col);
#endif /* end of include guard: HAL_DISPLAY_H */
