#include <metodo/metodo.h>

void InInitKernel(void)
{
	uint16_t *vidmem = (uint16_t*)0xb8000;
	HalInit();
	vidmem[0] = 0x1f << 8 | 'B';
}
