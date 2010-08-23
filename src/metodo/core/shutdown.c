#include <metodo/metodo.h>

void CoShutdown(int mode)
{
	if (!DisplayIsOn()) {
		DisplayInit();
	}

	DisplayString("Shutting down.\n");
	DisplayString("Done.\n");

	switch (mode) {
	case SD_WAIT:
		while (1)
			;
	case SD_OFF:
		HalShutdown();
		break;
	case SD_REBOOT:
		HalReboot();
		while (1)
			;
	default:
		while (1)
			;
	}
}
