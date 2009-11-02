#include <metodo/hal/hal.h>
#include <metodo/metodo.h>
#include <metodo/hal/i386.h>
#include <metodo/hal/isr.h>
#include <metodo/hal/timer/timer.h>

unsigned int ticks = 0;

void HalTimerHandler(struct regs *r)
{
	//printf("Ticks: %i", ticks);
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
