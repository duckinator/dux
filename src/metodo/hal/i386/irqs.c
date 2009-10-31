#include <metodo/metodo.h>
#include <metodo/hal/isr.h>

void HalIrqHandler(struct regs *r)
{
	if(r->int_no > 31){
		printf("Irq %i\n", r->int_no);
	}
}

void HalIrqInstall(void)
{
	HalSetIDTGate(0, (uint32_t) HalIrq0, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(1, (uint32_t) HalIrq1, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(2, (uint32_t) HalIrq2, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(3, (uint32_t) HalIrq3, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(4, (uint32_t) HalIrq4, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(5, (uint32_t) HalIrq5, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(6, (uint32_t) HalIrq6, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(7, (uint32_t) HalIrq7, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(8, (uint32_t) HalIrq8, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(9, (uint32_t) HalIrq9, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(10, (uint32_t) HalIrq10, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(11, (uint32_t) HalIrq11, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(12, (uint32_t) HalIrq12, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(13, (uint32_t) HalIrq13, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(14, (uint32_t) HalIrq14, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(15, (uint32_t) HalIrq15, 0x8, 0, 0, IDT_INTR32);
}
