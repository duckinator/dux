#include <system.h>
#include <isr.h>

extern void puts();
extern void idt_set_entry();

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
	irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq)
{
	irq_routines[irq] = 0;
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void irq_remap(void)
{
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xA1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);
}

/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void irq_install()
{
	irq_remap();

	idt_set_entry(32, (unsigned)irq0, 0x08, 0x8E);
	idt_set_entry(33, (unsigned)irq1, 0x08, 0x8E);
	idt_set_entry(34, (unsigned)irq2, 0x08, 0x8E);
	idt_set_entry(35, (unsigned)irq3, 0x08, 0x8E);
	idt_set_entry(36, (unsigned)irq4, 0x08, 0x8E);
	idt_set_entry(37, (unsigned)irq5, 0x08, 0x8E);
	idt_set_entry(38, (unsigned)irq6, 0x08, 0x8E);
	idt_set_entry(39, (unsigned)irq7, 0x08, 0x8E);
	idt_set_entry(40, (unsigned)irq8, 0x08, 0x8E);
	idt_set_entry(41, (unsigned)irq9, 0x08, 0x8E);
	idt_set_entry(42, (unsigned)irq10, 0x08, 0x8E);
	idt_set_entry(43, (unsigned)irq11, 0x08, 0x8E);
	idt_set_entry(44, (unsigned)irq12, 0x08, 0x8E);
	idt_set_entry(45, (unsigned)irq13, 0x08, 0x8E);
	idt_set_entry(46, (unsigned)irq14, 0x08, 0x8E);
	idt_set_entry(47, (unsigned)irq15, 0x08, 0x8E);
}

/* Each of the IRQ ISRs point to this function, rather than
*  the 'fault_handler' in 'isrs.c'. The IRQ Controllers need
*  to be told when you are done servicing them, so you need
*  to send them an "End of Interrupt" command (0x20). There
*  are two 8259 chips: The first exists at 0x20, the second
*  exists at 0xA0. If the second controller (an IRQ from 8 to
*  15) gets an interrupt, you need to acknowledge the
*  interrupt at BOTH controllers, otherwise, you only send
*  an EOI command to the first controller. If you don't send
*  an EOI, you won't raise any more IRQs */
void irq_handler(struct regs *r)
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
		outportb(0xA0, 0x20);
	}
	outportb(0x20, 0x20);
}
