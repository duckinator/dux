#ifndef SYSTEM_H
#define SYSTEM_H

#include <metodo/metodo.h>
#include <macros.h>

extern void *memcpy(void *dest, void *src, unsigned int count);
extern void *memset(void *dest, unsigned char val, unsigned int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned int count);
extern int strlen(const char *str);

extern void putch(unsigned int c);
extern void puts(char *str);

extern void monitor_clear();
extern void monitor_switch_pages(unsigned int a, unsigned int b);
extern unsigned int monitor_get_cursor_x();
extern unsigned int monitor_get_cursor_y();
extern void monitor_set_cursor(unsigned int x, unsigned int y);

/*extern void HalTimerSleep();
extern void sleep();
extern void usleep();*/


/* Handle awesome kernel panic implementation */
void _panic(char *text, char *filename, int line);
#define panic(message) _panic(message, __FILE__, __LINE__)

void stop(int error, int argc, ...);
#define assert(a) if (!(a)) assert_dowork(__FILE__, __LINE__)

#endif /* end of include guard: SYSTEM_H */
