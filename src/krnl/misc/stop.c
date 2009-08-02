#include <stdint.h>

#include <arch/display.h>
#include <arch/shutdown.h>

#include <krnl/stop.h>

static int in_stop = 0;

void KrnlStop(uint32_t error, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4)
{
	if (in_stop) {
		/* Its recursive! */
		ArchShutdown();
	}
	in_stop = 1;

	ArchDisplayInit();
	ArchDisplaySetAttr(0x4f);
	ArchDisplayClear();

	ArchDisplayString("An error has occured and Dux has been shutdown to prevent damage.\n\n");

	printf("STOP: %#x (%#x, %#x, %#x, %#x)\n",
			error, arg1, arg2, arg3, arg4);

#ifdef DEBUG
	ArchDisplayString("BREAK\n");
	ArchBreak();
#else
	ArchShutdown();
#endif
}
