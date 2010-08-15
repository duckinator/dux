#ifndef HAL_I386_H
#define HAL_I386_H

#include <metodo/hal/i386/idt.h>

/* Interrupts */
void HalDisableInterrupts(void);
void HalEnableInterrupts(void);

void HalDisableNMI(void);
void HalEnableNMI(void);

#include <metodo/hal/i386/exceptions.h>
#include <metodo/hal/i386/ports.h>
#include <metodo/hal/i386/isr.h>
#include <metodo/hal/i386/syscall.h>
#include <metodo/hal/i386/mm/memory.h>

#include <driver/i386/timer.h>
#include <driver/i386/keyboard/keyboard.h>

#endif /* end of include guard: HAL_I386_H */
