#include <metodo/metodo.h>

void CoException(void)
{
	char *str = "The system crashed. I don't know why.";
	uint16_t *vidmem = (uint16_t*)0xb80a0;
	int i = 0;

	while (i < 80)
		vidmem[i] = 0x1f << 8 | str[i++];

	while (1)
		;
}
