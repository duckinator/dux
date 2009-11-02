#include <metodo/metodo.h>

unsigned int ticks = 0;

void HalTimerHandler(struct regs *r)
{
	//Increment ticks
	ticks++;
}

unsigned int HalGetTicks()
{
	return ticks;
}

void HalTimerInit()
{
	HalIrqHandler_Install(0, (void*)HalTimerHandler);
}
