#ifndef HAL_I386_H
#define HAL_I386_H

#include <metodo/i386/hal/idt.h>

/* Interrupts */
void HalDisableInterrupts(void);
void HalEnableInterrupts(void);

void HalDisableNMI(void);
void HalEnableNMI(void);

#include <metodo/i386/hal/exceptions.h>
#include <metodo/i386/hal/ports.h>
#include <metodo/i386/hal/isr.h>
#include <metodo/i386/hal/syscall.h>

#include <driver/i386/timer.h>
#include <driver/i386/keyboard/keyboard.h>

#endif /* end of include guard: HAL_I386_H */
