#include <metodo/metodo.h>

#include <buildid.h>

void InInitKernel(void)
{
	char *str = "Metodo " __DATE__ " " __TIME__ " " ARCH " " SCM_REV;
	uint16_t *vidmem = (uint16_t*)0xb8000;
	int i = 0;

	HalInit();

/*	while (i < 80)
		vidmem[i++] = 0x1f << 8 | *str++;*/
	HalDisplayString(str);

	asm volatile ("int $0");
}
