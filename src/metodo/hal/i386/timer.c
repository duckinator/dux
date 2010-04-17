#include <metodo/metodo.h>
#include <metodo/scheduler.h>

unsigned int ticks = 0;

void HalTimerHandler(struct regs *r)
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
