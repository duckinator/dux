#include <system.h>

#include <metodo/metodo.h>
#include <metodo/misc/stop.h>

#include <metodo/hal/mm/memory.h>
#include <metodo/init/tests.h>

#include <multiboot.h>
#include <beef.h>

#include <buildid.h>
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

	HalInit();

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
				LoadExe((void*)module->mod_start);
			}
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

/*	printf("debug: 0x%x-0x%x\n", &debug_abbrev_start, &debug_abbrev_end);
	printf("debug: %s\n", &debug_abbrev_start);*/

// I'm only committing this so other people can play with it if they want, but leaving it commented out by default
/*
	printf("debug: 0x%x-0x%x\n", &debug_info_start, &debug_info_end);

	DWARF_Compilation_Unit_H* dwarf_comp_unit;
	unsigned int ui;
	i=0;
//	for (i = 0; i < 0x100000+0x007294; i++) {
printf("%i\n", &debug_info_end);
	for (ui = 0; ui <= &debug_info_end; ui++,i++) {
		dwarf_comp_unit = (DWARF_Compilation_Unit_H*)&debug_info_start+ui;
		if(dwarf_comp_unit->version == 2) {
			printf("%i (0x%x):\n", ui, ui);
			printf("    length:  0x%x (%u)\n", dwarf_comp_unit->length, dwarf_comp_unit->length);
			printf("    version: %u\n", dwarf_comp_unit->version, dwarf_comp_unit->version);
			printf("    offset:  0x%x (%u)\n", dwarf_comp_unit->offset, dwarf_comp_unit->offset);
			printf("    size:    0x%x (%u)\n", dwarf_comp_unit->size, dwarf_comp_unit->size);
			if(i==2)
			  break;
		}
	}*/

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
