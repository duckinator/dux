#include <hal.h>
#include <stdint.h>

static void HalPlayBuzz(uint32_t frequency)
{
	uint32_t div;
	uint8_t tmp;

	div = 1193180/frequency;
	HalOutPort(0x43, 0xb6);
	HalOutPort(0x42, (uint8_t)div);
	HalOutPort(0x42, (uint8_t)div>>8);

	tmp = HalInPort(0x61);
	if (tmp != (tmp | 3))
		HalOutPort(0x61, tmp | 3);
}

static void HalStopBuzz(void)
{
	HalOutPort(0x61, HalInPort(0x61) & 0xfc);
}

void HalBeep()
{
	HalPlayBuzz(1000);
	/* TODO: Use the timer to time this */
	HalStopBuzz();
}
