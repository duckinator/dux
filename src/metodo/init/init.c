#include <metodo/init/init.h>

noreturn InitKernel(uint32_t magic, void *arg)
{
	void *userland = NULL;
	int i;
	memory_map_t *mmap;

	switch(magic) {
		case MULTIBOOT_BOOTLOADER_MAGIC:
			mbd = arg;
			bootloader = BOOTLOADER_MULTIBOOT;
			//mmap = (memory_map_t*)mbd->mmap_addr;

			break;
		case BEEF_BOOTLOADER_MAGIC:
			bootloader = BOOTLOADER_BEEF;
			mbd = NULL;

			HalInit();
			panic("Successfully booted with beef. No clue what to do now.");
			break;
		default:
			HalInit();
			KrnlStop(STOP_BAD_MULTIBOOT_SIGNATURE, magic, 0, 0, 0);
	}


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
		//panic("No userland");
		printf("No userland\n");
//		HalBreak();
		//KernDebug();
		//KrnlEasyStop(STOP_NO_USERLAND);
	}
	while(1);
}
