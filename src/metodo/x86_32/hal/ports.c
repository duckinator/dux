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

void HalOutPortWord(uint16_t port, uint16_t val)
{
	__asm volatile("outw %0, %1" : : "a"(val), "d" (port));
}

uint16_t HalInPortWord(uint16_t port)
{
	uint16_t val;
	__asm volatile("inw %1, %0" : "=a" (val) : "d" (port));
	return val;
}

void HalOutPortLong(uint16_t port, uint32_t val)
{
	__asm volatile("outl %0, %1" : : "a"(val), "d" (port));
}

uint32_t HalInPortLong(uint16_t port)
{
	uint32_t val;
	__asm volatile("inl %1, %0" : "=a" (val) : "d" (port));
	return val;
}

// HalIOWait() is in the ports.h, since it's inline.
