#include <idt.h>

extern void load_idt();

struct idt_entry idt[256];
struct idt_desc idtp;

void idt_init()
{
	// make a descriptor
	idtp.base = (unsigned int) &idt;
	idtp.limit = sizeof(idt) - 1;

	// zero the IDT
	unsigned int i;
	for (i = 0; i < sizeof(idt); i++)
		*((unsigned char *) idt + i) = 0;

	// use an assembly helper function to load the IDT
	load_idt();
}

void idt_set_entry(unsigned char n, unsigned int offset, unsigned short selector, unsigned char type)
{
	idt[n].offset_lo = offset & 0xFFFF;
	idt[n].selector = selector;
	idt[n].zero = 0;
	idt[n].type = type;
	idt[n].offset_hi = (offset >> 16) & 0xFFFF;
}