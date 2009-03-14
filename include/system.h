#ifndef __SYSTEM_H
#define __SYSTEM_H

/* MAIN.C */

void outportb(unsigned short _port, unsigned char data);
unsigned char inportb(unsigned short _port);

extern void cls();
extern void putch(char c);
extern void puts(char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();

extern void timer_sleep();

extern void panic();

int printk(const char *fmt, ...);

#endif
