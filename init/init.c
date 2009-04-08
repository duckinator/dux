#include <system.h>
#include <isr.h>

#include <dux/drivers/core/console.h>

/* Main loop! */
void kmain()
{
	// Start the console
	console_init();
	printk("Dux OS Kernel Starting...\n");

	// Enable interrupts
	isr_install();
	irq_install();
	asm volatile ("sti");

	// Let them eat cake.
	printk("You may type now...\n");
	while (1)
		console_writeb(console_readb());
}
