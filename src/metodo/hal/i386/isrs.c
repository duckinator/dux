#include <metodo/metodo.h>
#include <metodo/hal/isr.h>
/*extern void panic();
extern void puts();
extern void HalIdtSetEntry();*/
/* handle interupts */
 
char *HalExceptions[32] = {
	"0 #DE Divide Error",
	"1 #DB RESERVED",
	"2 - NMI Interrupt",
	"3 #BP Breakpoint",
	"4 #OF Overflow",
	"5 #BR BOUND Range Exceeded",
	"6 #UD Invalid Opcode (Undefined Opcode)",
	"7 #NM Device Not Available (No Math Coprocessor)",
	"8 #DF Double Fault",
	"9   Coprocessor Segment Overrun (reserved)",
	"10 #TS Invalid TSS",
	"11 #NP Segment Not Present",
	"12 #SS Stack-Segment Fault",
	"13 #GP General Protection",
	"14 #PF Page Fault",
	"15 - (Intel reserved. Do not use.)",
	"16 #MF x87 FPU Floating-Point Error (Math Fault)",
	"17 #AC Alignment Check",
	"18 #MC Machine Check",
	"19 #XM SIMD Floating-Point Exception",
	"20 - Intel reserved. Do not use.",
	"21 - Intel reserved. Do not use.",
	"22 - Intel reserved. Do not use.",
	"23 - Intel reserved. Do not use.",
	"24 - Intel reserved. Do not use.",
	"25 - Intel reserved. Do not use.",
	"26 - Intel reserved. Do not use.",
	"27 - Intel reserved. Do not use.",
	"28 - Intel reserved. Do not use.",
	"29 - Intel reserved. Do not use.",
	"30 - Intel reserved. Do not use.",
	"31 - Intel reserved. Do not use."
};
//extern void HalSyscallHandler(struct regs *r);
void HalFaultHandler(struct regs *r)
{
	// No syscalls yet, but this looks useful ;D
	/*if (r->int_no == 0xffffff80) {
		HalSyscallHandler(r);
	}*/
	if(r->int_no == 3){
		printf("hai from HalFaultHandler()!\n");
	} else if(r->int_no < 32){
		panic(HalExceptions[r->int_no]);
	}
}

void HalIsrInstall(void)
{
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
