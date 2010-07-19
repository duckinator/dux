#include <system.h>

#include <metodo/metodo.h>
#include <metodo/misc/stop.h>

#include <metodo/hal/mm/memory.h>
#include <metodo/init/tests.h>

#include <multiboot.h>

#include <buildid.h>
#include <string.h>

#include <metodo/bochs.h>

#include <metodo/colpa/debug.h>

#include <metodo/init/elfloader.h>

#include <metodo/misc/modules.h>

void InitKernel(uint32_t magic, multiboot_info_t *multiboot)
{
	void *userland = NULL;

	*mbd = *multiboot;

	memory_map_t *mmap = (memory_map_t*)mbd->mmap_addr;

	HalInit();

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		KrnlStop(STOP_BAD_MULTIBOOT_SIGNATURE, magic, 0, 0, 0);
	}

	/* mbd->flags */
	int i, len;
	module_t *module;
	int current_module = 0;
	modules = (Module*)kmalloc(sizeof(Module) * 1024);
	if (mbd->flags>>3&1) {
		module = (module_t*)mbd->mods_addr;
		printf("We have %i modules.\n", mbd->mods_count);
		for (i = 0; i < mbd->mods_count; i++, module++) {
			printf("\nFound module.\n");
			printf("Module located at 0x%x-0x%x\n", module->mod_start, module->mod_end);
			printf("Module name: %s\n", (char*)module->string);

			len = sizeof(char) * strlen((char*)module->string)+1;
			modules[current_module].name = (char*)kmalloc(len);
			memcpy(modules[current_module].name, (char*)(module->string), len);
			modules[current_module].exe = (void*) module->mod_start;
			printf("Found executable %s at 0x%x\n", modules[current_module].name, modules[current_module].exe);
			current_module++;
		}
	}

	SystemTests();

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
		type: %i\n",
		mmap->size, mmap->base_addr_low, mmap->base_addr_high,
		mmap->length_low, mmap->length_high, mmap->type);*/
	}

	userland = GetModule("/System/userland.exe");

	/* Initialize pseudo-user mode */
	if (userland != NULL) {
		printf("Loading userland...\n");
		//HalSwitchToUserMode();
		LoadUserland(userland);
		printf("\nWhy yes, that is a black hole that flew out of userland...\n(Userland exited unexpectedly)\n");
	} else {
	  panic("No userland");
		printf("No userland\n");
		HalBreak();
		//KernDebug();
		//KrnlEasyStop(STOP_NO_USERLAND);
	}
	while(1);
}
