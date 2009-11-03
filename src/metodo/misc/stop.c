#include <stdint.h>
 
#include <metodo/metodo.h>
/*
#include <metodo/display.h>
#include <metodo/shutdown.h>
 */
#include <metodo/stop.h>
 
static int in_stop = 0;
 
void KrnlStop(uint32_t error, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
	if (in_stop) {
		/* Its recursive! */
		HalShutdown();
	}
	in_stop = 1;

	HalInitDisplay();
	HalDisplaySetAttr(0x4f);
	HalDisplayClear();

	HalDisplayString("An error has occured and Dux has been shutdown to prevent damage.\n\n");

	printf("STOP: %x (%x, %x, %x, %x)\n", error, arg1, arg2, arg3, arg4);
 
#ifdef DEBUG
	HalDisplayString("BREAK\n");
	HalBreak();
#else
	HalShutdown();
#endif
}
