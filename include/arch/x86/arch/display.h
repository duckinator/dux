#ifndef DISPLAY_B4NZ5MOB

#define DISPLAY_B4NZ5MOB

#include <stdint.h>

void ArchDisplaySetAttr(uint8_t lattr);
void ArchDisplayClear(void);
void ArchDisplayScroll(void);
void ArchDisplayChar(char c);
void ArchDisplayString(char *s);
void ArchDisplaySpot(uint8_t s, uint8_t row, uint8_t col);
void ArchDisplayInit(void);
void ArchDisplayUnInit(void);
int ArchDisplayIsInit(void);

#endif /* end of include guard: DISPLAY_B4NZ5MOB */
