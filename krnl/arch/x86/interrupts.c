#include <hal.h>
#include <arch/interrupts.h>
#include <arch/port.h>

void ArchDisableInterrupts(void)
{
	__asm__ __volatile__ ("cli");
}

void ArchEnableInterrupts(void)
{
	__asm__ __volatile__ ("sti");
}

void ArchDisableNMI(void)
{
	HalOutPort(0x70, HalInPort(0x70)|0x80);
}

void ArchEnableNMI(void)
{
	HalOutPort(0x70, HalInPort(0x70)&0x7f);
}
