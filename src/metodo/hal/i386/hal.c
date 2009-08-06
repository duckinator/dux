#include <metodo/metodo.h>

void HalInit(void)
{
	HalInitGDT();
	HalInitDisplay();
	HalInitIDT();
	HalLoadIDT();
}
