#ifndef API_DISPLAY_H
#define API_DISPLAY_H

#include <stdint.h>

void DisplaySetAttr(uint8_t lattr);
void DisplayClear(void);
void DisplayScroll(void);
void DisplayChar(const char c);
void DisplayString(const char *s);
void DisplaySpot(uint8_t s, uint8_t row, uint8_t col);
void DisplayInit(void);
void DisableDisplay(void);
int  DisplayIsOn(void);
void DisplayHideCursor();
void DisplayCursorPosition(uint8_t _row, uint8_t _col);

#endif /* end of include guard: API_DISPLAY_H */

