#include <metodo/metodo.h>

void HalBreak(void)
{
	__asm__ __volatile__ ("int $3");
}

noreturn HalShutdown(void)
{
	while (1) {
		__asm__ __volatile__ ("cli");
		__asm__ __volatile__ ("hlt");
	}
}

// FIXME: HalReboot() causess a SIMD Floating Point Exception
noreturn HalReboot(void)
{
	uint8_t good = 0x02;
	HalDisableInterrupts();

	while ((good & 0x02) != 0)
		good = HalInPort(0x64);
	HalOutPort(0x64, 0xFE);

	HalShutdown();
}
