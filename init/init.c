#include <system.h>

#include <dux/drivers/core/console.h>
#include <dux/mm/memory.h>

#include <hal.h>
#include <dux/message_handler.h>

#include <buildnum.h>
#include <multiboot.h>

/* Main loop! */
void kmain(multiboot_t *mbd)
{
	// Start the console
	console_init();
	printk("Dux OS Build %d %d\n", BUILDNUM);

	/* mbd->flags */
	int i;
	struct mods_t *module;
	if (mbd->flags>>3&1) {
		module = (mods_t*)mbd->mods_addr;
		while (i < mbd->mods_count) {
			printk("mod_start: %i\n", module->mod_start);
			i++;
			//module = module + sizeof(mods_t);
			module++;
		}
	}

	// Init the Hal
	HalInit((*MessageReceiver));

}
