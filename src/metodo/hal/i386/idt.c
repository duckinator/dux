#include <metodo/metodo.h>

IDTD idtd;
IDTG idt[256];

void HalInitIDT(void)
{
	idtd.offset = (uint32_t) idt;
	idtd.size = sizeof(IDTG)*256 - 1;

	ZeroMemory(idt, idtd.size);
}

void HalLoadIDT(void)
{
	__asm__ __volatile__ ("lidt %0" : : "m" (idtd));
}

void HalSetIDTGate(OUT PIDTG idtg, IN uint32_t offset, IN uint16_t selector, IN uint8_t priv, IN uint8_t sys, IN uint8_t gatetype)
{
	idtg->offset_1 = offset & 0xffff;
	idtg->selector = selector;
	idtg->zero = 0;
	idtg->type = 0x80 | (priv << 5 & 0x3) | (sys << 4 & 0x1) | (gatetype & 0xf);
	idtg->offset_2 = offset >> 16 & 0xffff;
}
