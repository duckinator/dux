#include <system.h>
#include <keyboard.h>

extern unsigned int timer_install();
extern unsigned int isr_install();
extern unsigned int irq_install();
extern unsigned int gdt_install();

static unsigned int enable_interrupts(void){
	__asm__ __volatile__ ("sti");
	return 0;
}

static void startitem(unsigned int (*func)(void), char *what)
{
	puts("Initializing ");
	puts(what);
	puts("... ");
 
	switch (func()) {
		case 0:
			puts("Done\n");
			return;
		default:
			puts("Failure\n");
			while (1);
	}
}


#include <dux/drivers/screen.h>

/* Main loop! */
void kmain()
{
	asm volatile ("cli");
	asm volatile ("hlt");

	startitem(timer_install, "timer");
	startitem(isr_install, "ISRs");
	startitem(irq_install, "IRQs");
	startitem(keyboard_install, "keyboard");
	startitem(enable_interrupts, "interrupts");

	while (1) {
		asm volatile ("cli");
		asm volatile ("hlt");
	}

	//detect_floppy_drives(); 
	//putch(floppy_read_data(0x3f0));
	/* This reboots, I think.
	 * outportb(0x60, 0xED);
	 * outportb(0x60, 0x00);*/
}
