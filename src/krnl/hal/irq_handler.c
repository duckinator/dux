#include <isr.h>

extern void puts(char *s);
extern void HalIdtSetEntry();

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/* This installs a custom IRQ handler for the given IRQ */
unsigned int HalIrqHandler_Install(int irq, void (*handler)(struct regs *r))
{
	irq_routines[irq] = handler;
	return 0;
}

/* This clears the handler for a given IRQ */
void HalIrqHandler_Uninstall(int irq)
{
	irq_routines[irq] = 0;
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time HalIrq0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make HalIrq0 to 15 be remapped to IDT entries 32 to
*  47 */
void HalIrqRemap(void)
{
	HalOutPort(0x20, 0x11);
	HalOutPort(0xA0, 0x11);
	HalOutPort(0x21, 0x20);
	HalOutPort(0xA1, 0x28);
	HalOutPort(0x21, 0x04);
	HalOutPort(0xA1, 0x02);
	HalOutPort(0x21, 0x01);
	HalOutPort(0xA1, 0x01);
	HalOutPort(0x21, 0x0);
	HalOutPort(0xA1, 0x0);
}

/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
unsigned int HalIrqInstall(void)
{
	HalIrqRemap();

	HalIdtSetEntry(32, (unsigned)HalIrq0, 0x08, 0x8E);
	HalIdtSetEntry(33, (unsigned)HalIrq1, 0x08, 0x8E);
	HalIdtSetEntry(34, (unsigned)HalIrq2, 0x08, 0x8E);
	HalIdtSetEntry(35, (unsigned)HalIrq3, 0x08, 0x8E);
	HalIdtSetEntry(36, (unsigned)HalIrq4, 0x08, 0x8E);
	HalIdtSetEntry(37, (unsigned)HalIrq5, 0x08, 0x8E);
	HalIdtSetEntry(38, (unsigned)HalIrq6, 0x08, 0x8E);
	HalIdtSetEntry(39, (unsigned)HalIrq7, 0x08, 0x8E);
	HalIdtSetEntry(40, (unsigned)HalIrq8, 0x08, 0x8E);
	HalIdtSetEntry(41, (unsigned)HalIrq9, 0x08, 0x8E);
	HalIdtSetEntry(42, (unsigned)HalIrq10, 0x08, 0x8E);
	HalIdtSetEntry(43, (unsigned)HalIrq11, 0x08, 0x8E);
	HalIdtSetEntry(44, (unsigned)HalIrq12, 0x08, 0x8E);
	HalIdtSetEntry(45, (unsigned)HalIrq13, 0x08, 0x8E);
	HalIdtSetEntry(46, (unsigned)HalIrq14, 0x08, 0x8E);
	HalIdtSetEntry(47, (unsigned)HalIrq15, 0x08, 0x8E);
	
	return 0;
}

/* Each of the IRQ ISRs point to this function, rather than
*  the 'HalFaultHandler' in 'isrs.c'. The IRQ Controllers need
*  to be told when you are done servicing them, so you need
*  to send them an "End of Interrupt" command (0x20). There
*  are two 8259 chips: The first exists at 0x20, the second
*  exists at 0xA0. If the second controller (an IRQ from 8 to
*  15) gets an interrupt, you need to acknowledge the
*  interrupt at BOTH controllers, otherwise, you only send
*  an EOI command to the first controller. If you don't send
*  an EOI, you won't raise any more IRQs */
void HalIrqHandler(struct regs *r)
{
	/* This is a blank function pointer */
	void (*handler)(struct regs *r);

	/* Find out if we have a custom handler to run for this
	*  IRQ, and then finally, run it */
	handler = irq_routines[r->int_no - 32];
	if (handler)
	{
		handler(r);
	}

	/* We need to send an EOI to the
	*  interrupt controllers too */
	if(r->int_no > 8){ /* Only send EOI to slave controller if it's involved (irqs 9 and up) */
		HalOutPort(0xA0, 0x20);
	}
	HalOutPort(0x20, 0x20);
}
