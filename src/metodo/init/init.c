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
		printf("\nWhy yes, that is a black hole that flew out of userland...\n(Userland exited unexpectedly)\n");
	} else {
//		printf("No userland\n");
//		HalBreak();
		//KernDebug();
		stop(STOP_NO_USERLAND);
	}
	while(1);
}
