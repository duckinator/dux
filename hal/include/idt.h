#ifndef IDT_H
#define IDT_H

struct HalIdtEntry {
	unsigned short offset_lo;
	unsigned short selector;
	unsigned char zero;
	unsigned char type;
	unsigned short offset_hi;
} __attribute__((packed));


struct HalIdtDesc {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

#endif
