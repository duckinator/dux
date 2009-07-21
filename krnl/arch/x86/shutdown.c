#include <arch/shutdown.h>

void ArchShutdown(void)
{
	while (1) {
		__asm__ __volatile__ ("cli");
		__asm__ __volatile__ ("hlt");
	}
}
