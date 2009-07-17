#include <buildnum.h>
#include <hal.h>

void HalInit(void (*receiver)(uint32_t msg))
{

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

	user_console();

}
