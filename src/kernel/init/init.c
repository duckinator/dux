#include <kernel/init/init.h>

noreturn InitKernel(uint32_t magic, void *arg)
{
	void *userland = NULL;

	mbd = arg; // In kernel.h.

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		HalInit();
		stop(STOP_BAD_BOOTLOADER_MAGIC);
	}

	MMapSetup(mbd);    // Set up memory map first
	HalInit();         // Start HAL (GDT, Display, IDT, etc).
	TestInit();        // Configure tests.

	TestRunAll();      // Run tests.

	InitLoadModules(); // Load all kernel modules

	userland = GetModule("/System/userland.exe");

	/* Initialize pseudo-user mode */
	if (userland != NULL) {
		printf("Loading userland...\n");
		HalSwitchToUserMode();
		LoadUserland(userland);
		printf("\n\nUserland exited unexpectedly.\n");
		HalBreak();
		stop(STOP_USERLAND_EXITED);
	} else {
		HalBreak();
		stop(STOP_NO_USERLAND);
	}
}
