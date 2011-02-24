#include <metodo/init/init.h>

noreturn InitKernel(uint32_t magic, void *arg)
{
	void *userland = NULL;
	memory_map_t *mmap;

	switch(magic) {
		case MULTIBOOT_BOOTLOADER_MAGIC:
			mbd = arg;
			mmap = (memory_map_t*)mbd->mmap_addr;

			break;
		case BEEF_BOOTLOADER_MAGIC:
			HalInit();
			printf("SUCCESS");
			while(1)
				;
			/*mbd = NULL;
			mmap = (memory_map_t*)arg;

			break;*/
		default:
			HalInit();
			KrnlStop(STOP_BAD_MULTIBOOT_SIGNATURE, magic, 0, 0, 0);
	}


	HalPreInit(); // HAL-related things that must be started before drivers
	DisplayInit();
	printf("Metodo " DUX_ARCH " " DUX_BUILDTYPE " build.\nCompiled at " __TIME__ " " __DATE__ "\nRevision " SCM_REV "\n\n");
	HalInit(); // Rest of HAL
	ColpaInit(); // System tests that only return success/failure status

	MMapSetup();

	SystemTests();

	printf("Memory map:\n");
	printf("\
          |      base addr      |       length\n\
   size   |   low    |   high   |   low    |   high   |   type\n");
	int i;
	for (i = 0; mmap < (memory_map_t*)(mbd->mmap_addr + mbd->mmap_length); i++,mmap++) {
		// Store all memory maps in mmaps (see metodo.h)
		mmaps[i] = mmap;
		// Print info about current memory map
/*		printf("mmap:\n\
		size: %i\n\
		base_addr_low: 0x%x\n\
		base_addr_high: 0x%x\n\
		length_low: %i\n\
		length_high: %i\n\
		type: %i\n",*/
		printf(" %8x | %8x | %8x | %8x | %8x | %8x\n",
		mmap->size, mmap->base_addr_low, mmap->base_addr_high,
		mmap->length_low, mmap->length_high, mmap->type);
	}

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
