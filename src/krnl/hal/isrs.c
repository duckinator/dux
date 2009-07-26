#include <isr.h>
extern void panic();
extern void puts();
extern void HalIdtSetEntry();
/* handle interupts */

char *exceptions[32] = {
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
extern void HalSyscallHandler(struct regs *r);
void HalFaultHandler(struct regs *r)
{
	if (r->int_no == 0xffffff80) {
		HalSyscallHandler(r);
	}
	if(r->int_no == 3){
		puts("hai from HalFaultHandler()!\n");
	} else if(r->int_no < 32){
		panic(exceptions[r->int_no]);
	}
}

unsigned int HalIsrInstall(void)
{
	HalIdtSetEntry(0, (unsigned)HalIsr0, 0x08, 0x8E);
	HalIdtSetEntry(1, (unsigned)HalIsr1, 0x08, 0x8E);
	HalIdtSetEntry(2, (unsigned)HalIsr2, 0x08, 0x8E);
	HalIdtSetEntry(3, (unsigned)HalIsr3, 0x08, 0x8E);
	HalIdtSetEntry(4, (unsigned)HalIsr4, 0x08, 0x8E);
	HalIdtSetEntry(5, (unsigned)HalIsr5, 0x08, 0x8E);
	HalIdtSetEntry(6, (unsigned)HalIsr6, 0x08, 0x8E);
	HalIdtSetEntry(7, (unsigned)HalIsr7, 0x08, 0x8E);
	HalIdtSetEntry(8, (unsigned)HalIsr8, 0x08, 0x8E);
	HalIdtSetEntry(9, (unsigned)HalIsr9, 0x08, 0x8E);
	HalIdtSetEntry(10, (unsigned)HalIsr10, 0x08, 0x8E);
	HalIdtSetEntry(11, (unsigned)HalIsr11, 0x08, 0x8E);
	HalIdtSetEntry(12, (unsigned)HalIsr12, 0x08, 0x8E);
	HalIdtSetEntry(13, (unsigned)HalIsr13, 0x08, 0x8E);
	HalIdtSetEntry(14, (unsigned)HalIsr14, 0x08, 0x8E);
	HalIdtSetEntry(15, (unsigned)HalIsr15, 0x08, 0x8E);
	HalIdtSetEntry(16, (unsigned)HalIsr16, 0x08, 0x8E);
	HalIdtSetEntry(17, (unsigned)HalIsr17, 0x08, 0x8E);
	HalIdtSetEntry(18, (unsigned)HalIsr18, 0x08, 0x8E);
	HalIdtSetEntry(19, (unsigned)HalIsr19, 0x08, 0x8E);
	HalIdtSetEntry(20, (unsigned)HalIsr20, 0x08, 0x8E);
	HalIdtSetEntry(21, (unsigned)HalIsr21, 0x08, 0x8E);
	HalIdtSetEntry(22, (unsigned)HalIsr22, 0x08, 0x8E);
	HalIdtSetEntry(23, (unsigned)HalIsr23, 0x08, 0x8E);
	HalIdtSetEntry(24, (unsigned)HalIsr24, 0x08, 0x8E);
	HalIdtSetEntry(25, (unsigned)HalIsr25, 0x08, 0x8E);
	HalIdtSetEntry(26, (unsigned)HalIsr26, 0x08, 0x8E);
	HalIdtSetEntry(27, (unsigned)HalIsr27, 0x08, 0x8E);
	HalIdtSetEntry(28, (unsigned)HalIsr28, 0x08, 0x8E);
	HalIdtSetEntry(29, (unsigned)HalIsr29, 0x08, 0x8E);
	HalIdtSetEntry(30, (unsigned)HalIsr30, 0x08, 0x8E);
	HalIdtSetEntry(31, (unsigned)HalIsr31, 0x08, 0x8E);
	return 0;
}
