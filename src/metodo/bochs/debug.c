#include <metodo/metodo.h>

void BochsBreak()
{
	printf("Enabling bochs iodebug module... ");
	HalOutPortWord(0x8A00,0x8A00); /* enable the bochs iodebug module */
	printf("Done!\nDropping to debugger prompt... ");
	HalOutPortWord(0x8A00,0x8AE0); /* drop to debugger prompt */
	printf("Continuing.\n\n");
}
