#ifndef HAL_X86_64_H
#define HAL_X86_64_H

#include <metodo/amd64/hal/idt.h>

/* Interrupts */
void HalDisableInterrupts(void);
void HalEnableInterrupts(void);

void HalDisableNMI(void);
void HalEnableNMI(void);

#include <metodo/amd64/hal/exceptions.h>
#include <metodo/amd64/hal/ports.h>
#include <metodo/amd64/hal/isr.h>
#include <metodo/amd64/hal/syscall.h>

#include <driver/x86_64/timer.h>
#include <driver/x86_64/keyboard/keyboard.h>

#endif /* end of include guard: HAL_X86_64_H */
