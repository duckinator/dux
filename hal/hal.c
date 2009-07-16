#include <buildnum.h>
#include <hal.h>

void HalInit(void (*receiver)(uint32_t msg))
{
	char c;

	// Start the console
	console_init();
	screen_setattr(0x0a, 0x0a);
	screen_clear();

	printk("Dux OS Build %d %d\n", BUILDNUM);

	// Enable interrupts
	HalIsrInstall();
	HalIrqInstall();
	HalTimerInstall();
	asm volatile ("sti");
	
	printk("You may type now...\n");
	char *input = "";
	while (1){
		c = console_readb();
		if (c != 0)
			console_writeb(c);

		switch(c) {
			case 'p':
				stop(0x10, 0x0);
				panic("User initialized");
				break;
			case 'b':
				HalBeep();
				break;
			case 't':
				printk("\nTicks: %i\n", HalGetTicks());
				break;
			case 'h':
				printk("\nHelp:\
	p: User initialized kernel panic\n\
	b: HalBeep();\n\
	t: Echo number of ticks since system start\n\
	h: This help message\n\
	Anything else is simply echoed\n");
				break;
			default:
				break;
		}
	}
}
