#include <hal/isr.h>
#include <hal/irqs.h>

int irq_t = 1;

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void (*irq_routines[27])(struct regs *r) =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/* This installs a custom IRQ handler for the given IRQ */
void HalIrqHandler_Install(int irq, void (*handler)(struct regs *r))
{
	if (HalGetTicks() > 0) {
		if ( irq_routines[irq] ) {
			printf("Replacing IRQ Handler #%i\n", irq);
		} else {
			printf("Installing IRQ Handler #%i\n", irq);
		}
	}
	irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void HalIrqHandler_Uninstall(int irq)
{
	if (HalGetTicks() > 0) {
		printf("Uninstalling IRQ Handler #%i\n", irq);
	}
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
	HalOutPort(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence
	HalOutPort(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	HalOutPort(PIC1_DATA, 0x20);                    // define the PIC vectors
	HalOutPort(PIC2_DATA, 0x28);
	HalOutPort(PIC1_DATA, 4);                       // continue initialization sequence
	HalOutPort(PIC2_DATA, 2);
 
	HalOutPort(PIC1_DATA, ICW4_8086);
	HalOutPort(PIC2_DATA, ICW4_8086);
 
	HalOutPort(PIC1_DATA, 0x0);   // Unmask all interrupts on PIC1
	HalOutPort(PIC2_DATA, 0x0);   // Unmask all interrupts on PIC2

/*	HalOutPort(0x20, 0x11);
	HalOutPort(0xA0, 0x11);
	HalOutPort(0x21, 0x20);
	HalOutPort(0xA1, 0x28);
	HalOutPort(0x21, 0x04);
	HalOutPort(0xA1, 0x02);
	HalOutPort(0x21, 0x01);
	HalOutPort(0xA1, 0x01);
	HalOutPort(0x21, 0x0);
	HalOutPort(0xA1, 0x0);*/
}

/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void HalIrqInstall(void)
{
	HalIrqRemap();

	HalSetIDTGate(32, (uint32_t) HalIrq0, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(33, (uint32_t) HalIrq1, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(34, (uint32_t) HalIrq2, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(35, (uint32_t) HalIrq3, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(36, (uint32_t) HalIrq4, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(37, (uint32_t) HalIrq5, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(38, (uint32_t) HalIrq6, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(39, (uint32_t) HalIrq7, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(40, (uint32_t) HalIrq8, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(41, (uint32_t) HalIrq9, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(42, (uint32_t) HalIrq10, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(43, (uint32_t) HalIrq11, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(44, (uint32_t) HalIrq12, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(45, (uint32_t) HalIrq13, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(46, (uint32_t) HalIrq14, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(47, (uint32_t) HalIrq15, 0x8, 0, 0, IDT_INTR32);
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

/* Disables a particular IRQ */
void HalIrqSetMask(uint8_t irq)
{
	uint16_t port;
	uint8_t value;

    if(irq < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		/* Silly gcc 4.5, clang can handle this flawlessly:
		 * irq -= 8;
		 */
		irq = (uint8_t)(irq - 8);
	}

	value = HalInPort(port) | (uint8_t)(1 << irq);
	HalOutPort(port, value);    
}

/* Enables a particular IRQ */
void HalIrqUnsetMask(uint8_t irq)
{
	uint16_t port;
	uint8_t value;

	if(irq < 8) {
		port = PIC1_DATA;
	} else {
		port = PIC2_DATA;
		/* Silly gcc 4.5, clang can handle this flawlessly:
		 * irq -= 8;
		 */
		irq = (uint8_t)(irq - 8);
	}

	value = HalInPort(port) & (uint8_t)(~(1 << irq));
	HalOutPort(port, value);
}
