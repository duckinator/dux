#include <dux/drivers/ports.h>

void outb(unsigned short port, unsigned char data)
{
	asm volatile ("outb %1, %0" :: "dN" (port), "a" (data));
}

unsigned char inb(unsigned short port)
{
	unsigned char ret;
	asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

unsigned short inw(unsigned short port)
{
	unsigned short ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}
