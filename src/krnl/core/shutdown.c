#include <dux/krnl.h>

#include <arch/display.h>

void CoShutdown(int mode)
{
	if (!ArchDisplayIsInit()) {
		ArchDisplayInit();
	}

	printf("Shutting down.\n");
	printf("Done.\n");

	switch (mode) {
	case SD_WAIT:
		while (1)
			;
		break;
	case SD_OFF:
		ArchShutdown();
		break;
	case SD_REBOOT:
		printf("Rebooting is unimplemented.\n");
		while (1)
			;
		break;
	default:
		while (1)
			;
		break;
	}
}
