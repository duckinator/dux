#include <system.h>

#include <dux/drivers/core/console.h>
#include <dux/mm/memory.h>

#include <krnl/stop.h>
#include <stdint.h>

#include <hal.h>
#include <dux/message_handler.h>

#include <multiboot.h>

/* Main loop! */
void kmain(uint32_t magic, multiboot_info_t *mbd)
{
	void *userland = NULL;
	// Start the console
	console_init();
	screen_setattr(0x0a, 0x0a);
	screen_clear();

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		KrnlStop(STOP_BAD_MULTIBOOT_SIGNATURE, magic, 0, 0, 0);
	}

	/* mbd->flags */
	int i;
	module_t *module;
	if (mbd->flags>>3&1) {
		module = (module_t*)mbd->mods_addr;
		for (i = 0; i < mbd->mods_count; i++, module++) {
			printk("\nModule name: %s\n", module->string);
			if (strcmp(module->string, "/System/userland") >= 0){
				userland = (void*) module->mod_start;
				printk("\nUserland: %x\n", userland);
			}
		}
	}
	
	// Init the Hal
	HalInit((*MessageReceiver));

	/* Initialize pseudo-user mode */
	//user_console();
	if (userland != NULL)
		LoadUserland(userland);
	else {
		KrnlEasyStop(STOP_NO_USERLAND);
	}
}
