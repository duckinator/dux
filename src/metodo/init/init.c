#include <system.h>

#include <metodo/metodo.h>
#include <metodo/misc/stop.h>

#include <metodo/hal/mm/memory.h>
#include <metodo/init/tests.h>

#include <multiboot.h>
#include <beef.h>

#include <buildinfo.h>
#include <string.h>

#include <metodo/bochs.h>

#include <metodo/colpa/debug.h>

#include <metodo/init/elfloader.h>

#include <metodo/misc/modules.h>

#include <dwarf2.h>

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

	/* mbd->flags */
	unsigned int i, len;
	module_t *module;
	int current_module = 0;
	modules = (Module*)kmalloc(sizeof(Module) * 1024);
	if (mbd->flags>>3&1) {
		module = (module_t*)mbd->mods_addr;
		printf("We have %i modules.\n", mbd->mods_count);
		for (i = 0; i < mbd->mods_count; i++, module++) {
			printf("Module located at 0x%x-0x%x\n", module->mod_start, module->mod_end);
			printf("Module name: %s\n", (char*)module->string);

			len = sizeof(char) * ((unsigned int)strlen((char*)module->string))+1;
			modules[current_module].name = (char*)kmalloc(len);
			memcpy(modules[current_module].name, (char*)(module->string), len);
			modules[current_module].exe = (void*) module->mod_start;
			printf("Found executable %s at 0x%x\n", modules[current_module].name, modules[current_module].exe);
			current_module++;

			if (strncmp((char*)module->string, (char*)"/Drivers/", 9) == 0) {
				printf("Loading driver: %s\n", (char*)module->string);
				//LoadExe((void*)module->mod_start);
				//while(1){}
			}
		}
	}

	SystemTests();

	printf("Memory map:\n");
	printf("\
          |      base addr      |       length\n\
   size   |   low    |   high   |   low    |   high   |   type\n");
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
		HalBreak();
		//KernDebug();
		//KrnlEasyStop(STOP_NO_USERLAND);
	}
	while(1);
}
