#ifndef HAL_H
#define HAL_H

#include <buildinfo.h>

#include <api/display.h>

#include <kernel/hal/mm/memory.h>

#include <hal/idt.h>

#include <hal/timer.h>
#include <hal/exceptions.h>
#include <hal/ports.h>
#include <hal/isr.h>
#include <hal/irqs.h>
#include <hal/syscall.h>

/* Interrupts */
void HalDisableInterrupts(void);
void HalEnableInterrupts(void);

void HalDisableNMI(void);
void HalEnableNMI(void);

#include <hal/shutdown.h>

//#include <driver/timer.h>
//#include <driver/keyboard/keyboard.h>

void HalInit(void);

#endif /* end of include guard: HAL_H */
