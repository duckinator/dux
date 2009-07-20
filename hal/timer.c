#include <hal.h>
#include <isr.h>

/* This will keep track of how many ticks that the system
*  has been running for */
int HalTimerTicks = 0;

int HalGetTicks(void)
{
	return HalTimerTicks;
}

/* Handles the timer. In this case, it's very simple: We
*  increment the 'timer_ticks' variable every time the
*  timer fires. By default, the timer fires 18.222 times
*  per second. Why 18.222Hz? Some engineer at IBM must've
*  been smoking something funky */
void HalTimerHandler(struct regs *r)
{
	r=r;
	HalTimerTicks++;
}

void HalTimerPhase(int hz)
{
	int divisor = 1193180 / hz;
	HalOutPort(0x43, 0x36);
	HalOutPort(0x40, divisor & 0xFF);
	HalOutPort(0x40, divisor >> 8);
}

void HalTimerInstall(void)
{
	HalIrqHandler_Install(0, HalTimerHandler);
	HalTimerPhase(1000);
}

void HalTimerSleep(int ticks)
{
	long eticks;

	eticks = HalTimerTicks + ticks;
	while(HalTimerTicks < eticks);
}

void usleep(int milliseconds)
{
	HalTimerSleep(milliseconds);
}

void sleep(int seconds)
{
	HalTimerSleep((seconds * 1000));
}
