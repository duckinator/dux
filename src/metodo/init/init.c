#include <metodo/init/init.h>

noreturn InitKernel(uint32_t magic, void *arg)
{
	void *userland = NULL;

	InitDetectBootloader(magic, arg); // Detect bootloader
	MMapSetup(arg);    // Set up memory map first
	HalInit();         // Start HAL (GDT, Display, IDT, etc)
	ColpaInit();       // System tests that only return success/failure status

	InitLoadModules(); // Load all kernel modules

	SystemTests();     // Run system tests

	MMapPrint();       // Print memory map information

	userland = GetModule("/System/userland.exe");

	/* Initialize pseudo-user mode */
	if (userland != NULL) {
		printf("Loading userland...\n");
		//HalSwitchToUserMode();
		LoadUserland(userland);
		stop(STOP_USERLAND_EXITED);
	} else {
		//HalBreak();
		stop(STOP_NO_USERLAND);
	}
	stop(STOP_END_OF_KERNEL);
}
