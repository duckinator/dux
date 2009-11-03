#ifndef HAL_VP4F7OUG

#define HAL_VP4F7OUG

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

#endif /* end of include guard: HAL_VP4F7OUG */
