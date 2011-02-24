#ifndef HAL_X86_64_H
#define HAL_X86_64_H

#include <metodo/hal/x86_64/idt.h>

/* Interrupts */
void HalDisableInterrupts(void);
void HalEnableInterrupts(void);

void HalDisableNMI(void);
void HalEnableNMI(void);

#include <metodo/hal/x86_64/exceptions.h>
#include <metodo/hal/x86_64/ports.h>
#include <metodo/hal/x86_64/isr.h>
#include <metodo/hal/x86_64/syscall.h>

#include <driver/x86_64/timer.h>
#include <driver/x86_64/keyboard/keyboard.h>

#endif /* end of include guard: HAL_X86_64_H */
