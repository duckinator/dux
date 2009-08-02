#include <dux/krnl.h>

#include <buildid.h>

void kmain(void)
{
	CoLowerIpl(IPL_PASSIVE);

	HalInit(NULL);

	ArchDisplayInit();
	printf("Dux Operating System Version 0.0.3\n");
	printf("Built from Git revision %s (%s/%s)\n\n", SCM_REV,
			ARCH, DEBUG ? "DEBUG" : "RELEASE");

	CoShutdown(SD_WAIT);
}
