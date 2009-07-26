#include <dux/drivers/core/console.h>
#include <dux/drivers/core/screen.h>
#include <dux/shutdown.h>

#include <arch/display.h>
#include <arch/shutdown.h>

void DuxShutdown(void)
{
	ArchDisplayInit();
	ArchDisplayClear();
	ArchDisplayString("Shutting down...\n");
	ArchDisplayString("It is now safe to turn off your computer.\n");

	ArchShutdown();
}
