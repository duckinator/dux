#ifndef HAL_H
#define HAL_H

#include <metodo/hal/display.h>
#include <metodo/hal/hal.h>
#if I386
#include <metodo/hal/i386.h>
#endif

#include <metodo/hal/isr.h>

#include <metodo/hal/timer/timer.h>

#include <metodo/hal/syscall.h>

#include <metodo/hal/mm/memory.h>

#include <metodo/hal/keyboard/keyboard.h>

void HalInit(void);
void HalBreak(void);
void HalShutdown(void);
void HalReboot(void);
int HalIsDisplayOn(void);
void HalDisplayChar(char c);

#endif /* end of include guard: HAL_H */
