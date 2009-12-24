#include <system.h>

#include <metodo/metodo.h>
#include <metodo/stop.h>

#include <metodo/hal/mm/memory.h>
#include <metodo/tests.h>

#include <multiboot.h>

#include <buildid.h>
#include <vfs/vfs.h>
#include <initrd/initrd.h>
#include <string.h>

void InInitKernel(uint32_t magic, multiboot_info_t *multiboot)
{
	void *userland = NULL;
	void *ramdisk = NULL;
	//char *str = "Metodo " __DATE__ " " __TIME__ " " ARCH " " SCM_REV "\n";

	*mbd = *multiboot;

	HalInit();

	//HalDisplayString(str);

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		KrnlStop(STOP_BAD_MULTIBOOT_SIGNATURE, magic, 0, 0, 0);
	}

	/* mbd->flags */
	int i;
	module_t *module;
	if (mbd->flags>>3&1) {
		module = (module_t*)mbd->mods_addr;
		for (i = 0; i < mbd->mods_count; i++, module++) {
			printf("\nFound module.\n");
			printf("Module name: %s\n", module->string);
			if (strcmp((char*)(module->string), "/System/userland") >= 0){
				userland = (void*) module->mod_start;
				printf("\nUserland located at: 0x%x\n\n", userland);
			}
			if(strcmp((char*)(module->string), "/System/initrd.img") == 0){
				ramdisk = (void*) module->mod_start;
				printf("\nFound fs_root at: 0x%x\n\n", ramdisk);
			}
		}
	}

	SystemTests(&ramdisk);

	/* Initialize pseudo-user mode */
	if (userland != NULL) {
		printf("Loading userland...\n");
		LoadUserland(userland);
		printf("Why yes, that is a black hole that flew out of userland...\n");
	}	else {
		printf("Interesting, no userland");
		//KrnlEasyStop(STOP_NO_USERLAND);
	}
	while(1);
}
