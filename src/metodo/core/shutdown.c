#include <metodo/metodo.h>

void CoShutdown(int mode)
{
	if (!HalDisplayIsInit()) {
		HalDisplayInit();
	}

	HalDisplayString("Shutting down.\n");
	HalDisplayString("Done.\n");

	switch (mode) {
	case SD_WAIT:
		while (1)
			;
		break;
	case SD_OFF:
		HalShutdown();
		break;
	case SD_REBOOT:
		HalReboot();
		while (1)
			;
		break;
	default:
		while (1)
			;
		break;
	}
}
