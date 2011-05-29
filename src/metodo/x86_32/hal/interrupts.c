#include <metodo/metodo.h>

void HalDisableInterrupts(void)
{
	__asm__ __volatile__ ("cli");
}

void HalEnableInterrupts(void)
{
	__asm__ __volatile__ ("sti");
}

void HalDisableNMI(void)
{
	HalOutPort(0x70, HalInPort(0x70)|0x80);
}

void HalEnableNMI(void)
{
	HalOutPort(0x70, HalInPort(0x70)&0x7f);
}
