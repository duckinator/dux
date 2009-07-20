#include <idt.h>

extern void HalLoadIdt();

struct HalIdtEntry idt[256];
struct HalIdtDesc idtp;

void HalIdtInit()
{
	// make a descriptor
	idtp.base = (unsigned int) &idt;
	idtp.limit = sizeof(idt) - 1;

	// zero the IDT
	unsigned int i;
	for (i = 0; i < sizeof(idt); i++)
		*((unsigned char *) idt + i) = 0;

	// use an assembly helper function to load the IDT
	HalLoadIdt();
}

void HalIdtSetEntry(unsigned char n, unsigned int offset, unsigned short selector, unsigned char type)
{
	idt[n].offset_lo = offset & 0xFFFF;
	idt[n].selector = selector;
	idt[n].zero = 0;
	idt[n].type = type;
	idt[n].offset_hi = (offset >> 16) & 0xFFFF;
}
