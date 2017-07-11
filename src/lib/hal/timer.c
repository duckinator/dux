#include <hal/timer.h>
#include <kernel/core/scheduler.h>

unsigned int ticks = 0;

void HalTimerHandler(UNUSED struct regs *r)
{
	ticks++;

	if (HalIsSchedulerEnabled())
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
