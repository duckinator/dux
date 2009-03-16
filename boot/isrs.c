#include <isr.h>
extern void panic();
extern void puts();
extern void idt_set_entry();
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
void fault_handler(struct regs *r)
{
	if(r->int_no == 3){
		puts("hai from fault_handler()!\n");
	} else if(r->int_no < 32){
		panic(exceptions[r->int_no]);
	}
}

void isr_install()
{
	idt_set_entry(0, (unsigned)isr0, 0x08, 0x8E);
	idt_set_entry(1, (unsigned)isr1, 0x08, 0x8E);
	idt_set_entry(2, (unsigned)isr2, 0x08, 0x8E);
	idt_set_entry(3, (unsigned)isr3, 0x08, 0x8E);
	idt_set_entry(4, (unsigned)isr4, 0x08, 0x8E);
	idt_set_entry(5, (unsigned)isr5, 0x08, 0x8E);
	idt_set_entry(6, (unsigned)isr6, 0x08, 0x8E);
	idt_set_entry(7, (unsigned)isr7, 0x08, 0x8E);
	idt_set_entry(8, (unsigned)isr8, 0x08, 0x8E);
	idt_set_entry(9, (unsigned)isr9, 0x08, 0x8E);
	idt_set_entry(10, (unsigned)isr10, 0x08, 0x8E);
	idt_set_entry(11, (unsigned)isr11, 0x08, 0x8E);
	idt_set_entry(12, (unsigned)isr12, 0x08, 0x8E);
	idt_set_entry(13, (unsigned)isr13, 0x08, 0x8E);
	idt_set_entry(14, (unsigned)isr14, 0x08, 0x8E);
	idt_set_entry(15, (unsigned)isr15, 0x08, 0x8E);
	idt_set_entry(16, (unsigned)isr16, 0x08, 0x8E);
	idt_set_entry(17, (unsigned)isr17, 0x08, 0x8E);
	idt_set_entry(18, (unsigned)isr18, 0x08, 0x8E);
	idt_set_entry(19, (unsigned)isr19, 0x08, 0x8E);
	idt_set_entry(20, (unsigned)isr20, 0x08, 0x8E);
	idt_set_entry(21, (unsigned)isr21, 0x08, 0x8E);
	idt_set_entry(22, (unsigned)isr22, 0x08, 0x8E);
	idt_set_entry(23, (unsigned)isr23, 0x08, 0x8E);
	idt_set_entry(24, (unsigned)isr24, 0x08, 0x8E);
	idt_set_entry(25, (unsigned)isr25, 0x08, 0x8E);
	idt_set_entry(26, (unsigned)isr26, 0x08, 0x8E);
	idt_set_entry(27, (unsigned)isr27, 0x08, 0x8E);
	idt_set_entry(28, (unsigned)isr28, 0x08, 0x8E);
	idt_set_entry(29, (unsigned)isr29, 0x08, 0x8E);
	idt_set_entry(30, (unsigned)isr30, 0x08, 0x8E);
	idt_set_entry(31, (unsigned)isr31, 0x08, 0x8E);

}
