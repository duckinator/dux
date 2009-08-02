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
	ArchOutPort(0x70, ArchInPort(0x70)|0x80);
}

void ArchEnableNMI(void)
{
	ArchOutPort(0x70, ArchInPort(0x70)&0x7f);
}
