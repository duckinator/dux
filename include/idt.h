#ifndef IDT_H
#define IDT_H

struct idt_entry {
	unsigned short offset_lo;
	unsigned short selector;
	unsigned char zero;
	unsigned char type;
	unsigned short offset_hi;
} __attribute__((packed));


struct idt_desc {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

#endif