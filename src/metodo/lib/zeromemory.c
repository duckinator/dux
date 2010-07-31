#include <metodo/metodo.h>

void *ZeroMemory(IN void *ptr, IN uint32_t len)
{
	unsigned int i;
	uint8_t *mem = ptr;

	for (i = 0; i < len; i++) 
	{
		mem[i] = 0;
	}

	return mem;
}
