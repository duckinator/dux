#include <system.h>

#include <metodo/metodo.h>
#include <metodo/stop.h>

#include <multiboot.h>

#include <buildid.h>

#include <string.h>

void InInitKernel(uint32_t magic, multiboot_info_t *mbd)
{
	void *userland = NULL;
	//char *str = "Metodo " __DATE__ " " __TIME__ " " ARCH " " SCM_REV "\n";

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
		}
	}

	printf("Beginning memory management test:\n");
	printf("First free frame:  %i\n", first_frame());	
	set_frame(first_frame(), 1, 1);
	printf("Allocating frame at %i\n", first_frame());
	printf("First free frame is now %i\n", first_frame());
	printf("Finished memory management test\n\n");
	
	/* Initialize pseudo-user mode */
	printf("Loading userland...\n");
	if (userland != NULL)
		LoadUserland(userland);
	else
		KrnlEasyStop(STOP_NO_USERLAND);
}
