#include <buildnum.h>
#include <hal.h>

void HalInit(void (*receiver)(uint32_t msg))
{

	// Enable interrupts
	HalIsrInstall();
	HalIrqInstall();
	HalTimerInstall();
	asm volatile ("sti");

	user_console();

}
