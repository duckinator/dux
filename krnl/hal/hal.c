#include <hal.h>
#include <dux/drivers/fdd.h>

void HalInit(void (*receiver)(uint32_t msg))
{
	
	// Enable interrupts
	HalIsrInstall();
	HalIrqInstall();
	HalTimerInstall();
	FDD_install();
	asm volatile ("sti");
	dux_intro();

	user_console();

}
