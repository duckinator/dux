#ifndef HAL_IRQS_H
#define HAL_IRQS_H

#include <metodo/metodo.h>
#include <metodo/i386/hal/isr.h>
#include <metodo/i386/hal/ports.h>

#define PIC1            0x20     /* IO base address for master PIC */
#define PIC2            0xA0     /* IO base address for slave PIC */
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)

#define PIC_EOI         0x20     /* End-of-interrupt command code */

#define ICW1_ICW4       0x01     /* ICW4 (not) needed */
#define ICW1_SINGLE     0x02     /* Single (cascade) mode */
#define ICW1_INTERVAL4  0x04     /* Call address interval 4 (8) */
#define ICW1_LEVEL      0x08     /* Level triggered (edge) mode */
#define ICW1_INIT       0x10     /* Initialization - required! */
 
#define ICW4_8086       0x01     /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO       0x02     /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE  0x08     /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C     /* Buffered mode/master */
#define ICW4_SFNM       0x10     /* Special fully nested (not) */

void HalIrqSetMask(uint8_t irq);
void HalIrqUnsetMask(uint8_t irq);

extern void HalIrqInstall(void);
extern void HalIrqHandler(struct regs *r);
extern void HalIrqHandler_Install(int irq, void (*handler)(struct regs *r));
extern void HalIrqHandler_Uninstall(int irq);

/* These are own isrs that point to our special IRQ handler
*  instead of the regular 'HalFaultHandler' function */
extern void HalIrq0();
extern void HalIrq1();
extern void HalIrq2();
extern void HalIrq3();
extern void HalIrq4();
extern void HalIrq5();
extern void HalIrq6();
extern void HalIrq7();
extern void HalIrq8();
extern void HalIrq9();
extern void HalIrq10();
extern void HalIrq11();
extern void HalIrq12();
extern void HalIrq13();
extern void HalIrq14();
extern void HalIrq15();

#endif
