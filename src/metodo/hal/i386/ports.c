#include <metodo/metodo.h>

inline void HalOutPort(uint16_t port, uint8_t val)
{
	asm volatile("outb %0, %1" : : "a"(val), "Nd" (port));
}

inline uint8_t HalInPort(uint16_t port)
{
	uint8_t val;
	asm volatile("inb %1, %0" : "=a" (val) : "Nd" (port));
	return val;
}
