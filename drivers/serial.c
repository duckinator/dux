#include <system.h>
#define PORT 0x3f8

void serial_init()
{
	outportb(PORT+1, 0x00);
	outportb(PORT+3, 0x80);
	outportb(PORT+0, 0x03);
	outportb(PORT+1, 0x00);
	outportb(PORT+3, 0x03);
	outportb(PORT+2, 0xc7);
	outportb(PORT+4, 0x08);
}

int serial_received()
{
	return inportb(PORT+5) & 1;
}

char read_serial()
{
	while (serial_received() == 0);

	return inportb(PORT);
}

int is_transmit_empty()
{
	return inportb(PORT+5) & 0x20;
}

void write_serial(char a)
{
	while (is_transmit_empty() == 0);

	outportb(PORT, a);
}
