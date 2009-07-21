#include <arch/port.h>

inline void ArchOutPort(uint16_t port, uint8_t data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

inline uint8_t ArchInPort(uint16_t port)
{
	register volatile uint8_t data;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (data) : "dN" (port));
	return data;
}
