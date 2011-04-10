#ifndef HAL_X86_H
#define HAL_X86_H

/* Interrupts */
void HalDisableInterrupts(void);
void HalEnableInterrupts(void);

void HalDisableNMI(void);
void HalEnableNMI(void);

#include <metodo/x86/hal/shutdown.h>

#include <driver/x86/timer.h>
#include <driver/x86/keyboard/keyboard.h>

#endif /* end of include guard: HAL_X86_H */
