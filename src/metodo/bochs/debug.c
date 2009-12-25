/* Scott: Thanks ;D */

#include <metodo/metodo.h>

/* read http://bochs.sourceforge.net/doc/docbook/development/iodebug.html */

/*
 * this function drops to the debugger in bochs, like a breakpoint
 * only works if you compile bochs with --enable-iodebug and
 * --enable-debugger, which is incompatible with --enable-gdb-stub
 */
void BochsBreak()
{
	printf("Enabling bochs iodebug module... ");
	HalOutPortWord(0x8A00,0x8A00); /* enable the bochs iodebug module */
	printf("Done!\nDropping to debugger prompt... ");
	HalOutPortWord(0x8A00,0x8AE0); /* drop to debugger prompt */
	printf("Continuing.\n\n");
}
