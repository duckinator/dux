#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include <system.h>
#include <hal/isr.h>

void HalTimerHandler(UNUSED struct regs *r);
unsigned int HalGetTicks();
void HalTimerInit();

#endif /* end of include guard: HAL_TIMER_H */
