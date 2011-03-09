#include <driver/driver.h>
#include <driver/x86/timer.h>
#include <metodo/core/scheduler.h>

unsigned int ticks = 0;

void HalTimerHandler(UNUSED struct regs *r)
{
	//Increment ticks
	ticks++;

	// Scheduler
	if ( HalIsSchedulerEnabled() )
		CoSchedulerHandler();
}

unsigned int HalGetTicks()
{
	return ticks;
}

void HalTimerInit()
{
	HalIrqHandler_Install(0, (void*)HalTimerHandler);
}
