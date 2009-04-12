#include <system.h>
#include <isr.h>

#include <dux/drivers/core/console.h>
#include <dux/mm/memory.h>

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

	// Initialize memory.
	init_mm();

	int i;
	for (i = 0; i < 0x1000000; i += 0x1000) {
		printk("Memory at 0x%x, is %s.\n", i, test_frame(i) ? "allocated" : "free");
	}

	PageTableEntry page1, page2, page3, page4;
	alloc_frame(&page1, 1, 1);
	printk("Allocated %x\n", page1.address<<12);
	alloc_frame(&page2, 1, 1);
	printk("Allocated %x\n", page2.address<<12);
	alloc_frame(&page3, 1, 1);
	printk("Allocated %x\n", page3.address<<12);
	free_frame(&page1);
	alloc_frame(&page4, 1, 1);
	printk("Allocated %x\n", page4.address<<12);

	// Let them eat cake.
	printk("You may type now...\n");
	while (1)
		console_writeb(console_readb());
}
