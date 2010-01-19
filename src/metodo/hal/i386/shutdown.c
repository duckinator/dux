#include <metodo/metodo.h>

void HalBreak(void)
{
	__asm__ __volatile__ ("int $3");
}

void HalShutdown(void)
{
	while (1) {
		__asm__ __volatile__ ("cli");
		__asm__ __volatile__ ("hlt");
	}
}

void HalReboot(void)
{
	unsigned char good = 0x02;
	HalDisableInterrupts();
	__asm__ __volatile__ ("int $0x13");

	while ((good & 0x02) != 0)
		good = HalInPort(0x64);
	HalOutPort(0x64, 0xFE);

	HalShutdown();
}
