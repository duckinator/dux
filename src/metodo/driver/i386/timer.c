#include <driver/driver.h>
#include <driver/i386/timer.h>
#include <metodo/core/scheduler.h>

unsigned int ticks = 0;

void HalTimerHandler(struct regs *r)
{
	r = r; // UNUSED ARG FIX
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
