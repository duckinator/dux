#include <metodo/metodo.h>

void InInitKernel(void)
{
	char *name = "Metodo";
	uint16_t *vidmem = (uint16_t*) 0xb8000;

	while (*name)
		*vidmem++ = *name++ | 0x1f << 8;
}
