#include <arch/shutdown.h>

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
