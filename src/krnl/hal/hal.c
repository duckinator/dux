#include <hal.h>
#include <dux/drivers/fdd.h>

void HalInit(void (*receiver)(uint32_t msg))
{
	// Enable interrupts
	HalIsrInstall();
	HalIrqInstall();
	HalTimerInstall();
	HalInitializeSyscalls();
	FDD_install();
	asm volatile ("sti");
}
