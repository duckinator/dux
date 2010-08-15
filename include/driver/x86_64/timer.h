#ifndef HAL_TIMER_H
#define HAL_TIMER_H

extern void HalTimerHandler(struct regs *r);
extern unsigned int HalGetTicks();
extern void HalTimerInit();

#endif /* end of include guard: HAL_TIMER_H */
