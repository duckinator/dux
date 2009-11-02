#ifndef TIMER_H
#define TIMER_H

extern void HalTimerHandler(struct regs *r);
extern unsigned int HalGetTicks();
extern void HalTimerInit();

#endif
