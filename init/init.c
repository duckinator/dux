#include <system.h>
#include <isr.h>

#include <dux/drivers/core/console.h>
#include <dux/mm/memory.h>

#include <buildnum.h>

/* Main loop! */
void kmain()
{
	char c;
	// Start the console
	console_init();
	printk("Dux OS Build %d\n", BUILDNUM);

	// Enable interrupts
	isr_install();
	irq_install();
	asm volatile ("sti");

	// Initialize memory.
	init_mm();

	// Let them eat cake.
	printk("You may type now...\n");
	while (1){
		c = console_readb();
		if (c != 0)
			console_writeb(c);
		if (c == 'p') {
			stop(0x10, 0x0);
			panic("User initialized");
		}
	}
}
