#ifndef DRIVER_VGA_H
#define DRIVER_VGA_H

#include <driver/driver.h>

void VgaDisplaySetAttr(uint8_t lattr);
void VgaDisplayClear(void);
static void VgaDisplayScroll(void);
void VgaDisplayChar(char c);
void VgaDisplaySpot(uint8_t s, uint8_t row, uint8_t col);
void VgaDisplayHideCursor();
void VgaDisplayCursorPosition(uint8_t _row, uint8_t _col);
void VgaDisplayInit(void);
void VgaDisableDisplay(void);
int VgaIsDisplayOn(void);

#endif /* end of include guard: HAL_VGA_H */
