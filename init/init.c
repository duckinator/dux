#include <system.h>

extern unsigned int timer_install();
extern unsigned int isr_install();
extern unsigned int irq_install();
extern unsigned int gdt_install();
extern unsigned int keyboard_install();
extern void detect_floppy_drives();
extern unsigned char floppy_read_cmd();

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


void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outportb(0x43, 0x36);             /* Set our command byte 0x36 */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

void prompt(char *prompt){
	puts(prompt);
}

/* Main loop! */
void kmain(void* mb_info)
{
	settextcolor(0xf, 0x1);
	init_video();
	timer_phase(100); /* 100Hz timer */
	/*timer_install();
	isr_install();
	irq_install();
	keyboard_install();*/
	startitem(timer_install, "timer");
	startitem(isr_install, "ISRs");
	startitem(irq_install, "IRQs");
	startitem(keyboard_install, "keyboard");
	__asm__ __volatile__ ("sti"); 

	puts("TEST!\n");
	//detect_floppy_drives(); 
	//putch(floppy_read_data(0x3f0));
	outportb(0x60, 0xED);
	/*outportb(0x60, 0x00);*/

	for(;;) asm("hlt"); /* Until we get processes/threads/multitasking working... */
}
