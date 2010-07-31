#ifndef HAL_VGA_H
#define HAL_VGA_H

#include <metodo/metodo.h>

void VgaDisplaySetAttr(uint8_t lattr);
void VgaDisplayClear(void);
static void VgaDisplayScroll(void);
void VgaDisplayChar(char c);
void VgaDisplaySpot(uint8_t s, uint8_t row, uint8_t col);
void VgaDisplayHideCursor();
void VgaDisplayCursorPosition(uint8_t _row, uint8_t _col);
void VgaInitDisplay(void);
void VgaDisableDisplay(void);
int VgaIsDisplayOn(void);

#endif /* end of include guard: HAL_VGA_H */
