#ifndef DISPLAY_OLOJ4A8Q
#define DISPLAY_OLOJ4A8Q
void HalDisplaySetAttr(uint8_t lattr);
void HalDisplayClear(void);
void HalDisplayScroll(void);
void HalDisplayChar(char c);
void HalDisplayString(char *s);
void HalDisplaySpot(uint8_t s, uint8_t row, uint8_t col);
void HalInitDisplay(void);
void HalDisableDisplay(void);
int HalIsDisplayOn(void);
#endif
