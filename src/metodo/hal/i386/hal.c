#include <metodo/metodo.h>

void HalInit(void)
{
	PIDTG idt;

	HalInitGDT();
	HalInitDisplay();
	HalInitIDT();
	HalIsrInstall();
}
