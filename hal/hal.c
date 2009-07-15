#include <hal.h>

void HalInit(void (*receiver)(uint32_t msg))
{
	char c;

	// Enable interrupts
	HalIsrInstall();
	HalIrqInstall();
	HalTimerInstall();
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
