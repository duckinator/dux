#ifndef __SYSTEM_H
#define __SYSTEM_H

/* kernel/misc.c */

extern void outportb(unsigned short _port, unsigned char data);
extern unsigned char inportb(unsigned short _port);

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

extern void timer_sleep();

extern void panic();

void printk(char *fmt, ...);

#define NULL 0

#endif
