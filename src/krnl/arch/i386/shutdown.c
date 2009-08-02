#include <arch/shutdown.h>
#include <arch/interrupts.h>

void ArchBreak(void)
{
	__asm__ __volatile__ ("int $0x3");
}

void ArchShutdown(void)
{
	while (1) {
		__asm__ __volatile__ ("cli");
		__asm__ __volatile__ ("hlt");
	}
}

void ArchReboot(void)
{
	unsigned char good = 0x02;
	ArchDisableInterrupts();
	__asm__ __volatile__ ("int $0x13");

	while ((good & 0x02) != 0)
		good = ArchInPort(0x64);
	ArchOutPort(0x64, 0xFE);

	ArchShutdown();
}
