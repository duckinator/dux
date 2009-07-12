#include <system.h>
#include <isr.h>

#include <dux/drivers/core/console.h>
#include <dux/mm/memory.h>

#include <buildnum.h>
#include <multiboot.h>

/* Main loop! */
void kmain(multiboot_t *mbd)
{

	char c;
	// Start the console
	console_init();
	printk("Dux OS Build %d %d\n", BUILDNUM);

	/* mbd->flags */
	int i;
	struct mods_t *module;
	if (mbd->flags>>3&1) {
		module = mbd->mods_addr;
		while (i < mbd->mods_count) {
			printk("mod_start: %i\n", module->mod_start);
			i++;
			//module = module + sizeof(mods_t);
			module++;
		}
	}
	// Enable interrupts
	isr_install();
	irq_install();
	asm volatile ("sti");

	printk("You may type now...\n");
	while (1){
		c = console_readb();
		if (c != 0)
			console_writeb(c);
#if 0
		if (c == 'p') {
			stop(0x10, 0x0);
			panic("User initialized");
		}
#endif
	}
}
