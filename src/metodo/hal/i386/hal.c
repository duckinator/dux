#include <metodo/metodo.h>

void HalInit(void)
{
	HalInitGDT();
	HalInitIDT();
}
