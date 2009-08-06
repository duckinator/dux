#include <metodo/metodo.h>

#define HALSETIDT(n) HalSetIDTGate(n, (uint32_t) isrn, 0x8, 0, 0, IDT_INTR32);

void HalInit(void)
{
	PIDTG idt;

	HalInitGDT();
	HalInitIDT();

	HalSetIDTGate(0, (uint32_t) isr0, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(1, (uint32_t) isr1, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(2, (uint32_t) isr2, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(3, (uint32_t) isr3, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(4, (uint32_t) isr4, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(5, (uint32_t) isr5, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(6, (uint32_t) isr6, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(7, (uint32_t) isr7, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(8, (uint32_t) isr8, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(9, (uint32_t) isr9, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(10, (uint32_t) isr10, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(11, (uint32_t) isr11, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(12, (uint32_t) isr12, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(13, (uint32_t) isr13, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(14, (uint32_t) isr14, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(15, (uint32_t) isr15, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(16, (uint32_t) isr16, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(17, (uint32_t) isr17, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(18, (uint32_t) isr18, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(19, (uint32_t) isr19, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(20, (uint32_t) isr20, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(21, (uint32_t) isr21, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(22, (uint32_t) isr22, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(23, (uint32_t) isr23, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(24, (uint32_t) isr24, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(25, (uint32_t) isr25, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(26, (uint32_t) isr26, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(27, (uint32_t) isr27, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(28, (uint32_t) isr28, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(29, (uint32_t) isr29, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(30, (uint32_t) isr30, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(31, (uint32_t) isr31, 0x8, 0, 0, IDT_INTR32);
}
