#include <metodo/metodo.h>

void HalBreak(void)
{
	__asm__ __volatile__ ("int $3");
}

noreturn HalHalt(void)
{
	__asm__ __volatile__ ("hlt");
	/* Yes, hlt does in fact not return.
	 * Too bad clang/gcc/etc can't figure this out. */
	while(1)
		;
}

noreturn HalShutdown(void)
{
	while (1) {
		HalDisableInterrupts();
		HalHalt();
	}
}

noreturn HalReboot(void)
{
	uint8_t good = 0x02;
	HalDisableInterrupts();

	while ((good & 0x02) != 0)
		good = HalInPort(0x64);
	HalOutPort(0x64, 0xFE);

	HalHalt();
}
