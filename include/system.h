#ifndef __SYSTEM_H
#define __SYSTEM_H

/* kernel/misc.c */

extern void outportb(unsigned short _port, unsigned char data);
extern unsigned char inportb(unsigned short _port);

extern void *malloc(int size);
extern void *memcpy(void *dest, void *src, unsigned int count);
extern void *memset(void *dest, unsigned char val, unsigned int count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned int count);
extern int strlen(const char *str);

extern void cls();
extern void putch(char c);
extern void puts(char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();

extern void timer_sleep();

extern void panic();

int printk(const char *fmt, ...);

#endif
