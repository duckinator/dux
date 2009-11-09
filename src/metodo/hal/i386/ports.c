#include <metodo/metodo.h>

void HalOutPort(uint16_t port, uint8_t val)
{
	__asm volatile("outb %0, %1" : : "a"(val), "d" (port));
}

uint8_t HalInPort(uint16_t port)
{
	uint8_t val;
	__asm volatile("inb %1, %0" : "=a" (val) : "d" (port));
	return val;
}
