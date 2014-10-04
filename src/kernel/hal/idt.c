#include <kernel.h>

IDTD idtd;
IDTG idt[256];

static void HalLoadIDT(void);

void HalInitIDT(void)
{
	idtd.offset = (uint32_t) idt;
	idtd.size = sizeof(IDTG)*256 - 1;

	memset(idt, 0, idtd.size);

	HalLoadIDT();
}

static void HalLoadIDT(void)
{
	__asm__ __volatile__ ("lidt %0" : : "m" (idtd));
}

void HalSetIDTGate(IN size_t n, IN uint32_t offset, IN uint16_t selector, IN uint8_t priv, IN uint8_t sys, IN uint8_t gatetype)
{
	idt[n].offset_1 = offset & 0xffff;
	idt[n].selector = selector;
	idt[n].zero = 0;
	idt[n].type = (uint8_t)(0x80 | (priv << 5 & 0x3) | (sys << 4 & 0x1) | (gatetype & 0xf));
	idt[n].offset_2 = (uint16_t)(offset >> 16 & 0xffff);
}
