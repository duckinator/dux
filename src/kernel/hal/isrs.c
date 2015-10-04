#include <kernel.h>
//#include <kernel/debugger/debug.h>
#include <config.h>

/* handle interupts */
int isr_t = 0;
const char *HalExceptions[32] = {
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

void HalIsrHandler(struct regs *r)
{
	if (r->int_no == SYSCALL_INTERRUPT) {
		HalSyscallHandler(r);
	} else if(r->int_no == 3) {
		//KernDebug();
	} else if(r->int_no < 32){
		panic((char*)HalExceptions[r->int_no]);
	}
}

void HalIsrInstall(void)
{
	HalSetIDTGate(0, (uint32_t) HalIsr0, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(1, (uint32_t) HalIsr1, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(2, (uint32_t) HalIsr2, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(3, (uint32_t) HalIsr3, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(4, (uint32_t) HalIsr4, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(5, (uint32_t) HalIsr5, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(6, (uint32_t) HalIsr6, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(7, (uint32_t) HalIsr7, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(8, (uint32_t) HalIsr8, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(9, (uint32_t) HalIsr9, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(10, (uint32_t) HalIsr10, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(11, (uint32_t) HalIsr11, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(12, (uint32_t) HalIsr12, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(13, (uint32_t) HalIsr13, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(14, (uint32_t) HalIsr14, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(15, (uint32_t) HalIsr15, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(16, (uint32_t) HalIsr16, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(17, (uint32_t) HalIsr17, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(18, (uint32_t) HalIsr18, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(19, (uint32_t) HalIsr19, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(20, (uint32_t) HalIsr20, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(21, (uint32_t) HalIsr21, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(22, (uint32_t) HalIsr22, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(23, (uint32_t) HalIsr23, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(24, (uint32_t) HalIsr24, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(25, (uint32_t) HalIsr25, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(26, (uint32_t) HalIsr26, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(27, (uint32_t) HalIsr27, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(28, (uint32_t) HalIsr28, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(29, (uint32_t) HalIsr29, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(30, (uint32_t) HalIsr30, 0x8, 0, 0, IDT_INTR32);
	HalSetIDTGate(31, (uint32_t) HalIsr31, 0x8, 0, 0, IDT_INTR32);
}
