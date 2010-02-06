#ifndef VGA_H
#define VGA_H

#include <metodo/metodo.h>

void VgaDisplaySetAttr(uint8_t lattr);
void VgaDisplayClear(void);
static void VgaDisplayScroll(void);
void VgaDisplayChar(char c);
void VgaDisplaySpot(uint8_t s, uint8_t row, uint8_t col);
void VgaDisplayHideCursor();
void VgaDisplayCursorPosition(int _row, int _col);
void VgaInitDisplay(void);
void VgaDisableDisplay(void);
int VgaIsDisplayOn(void);

#endif
