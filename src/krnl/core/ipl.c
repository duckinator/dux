#include <stdint.h>

#include <arch/interrupts.h>

#include <dux/krnl/core.h>
#include <krnl/stop.h>

static IPL m_ipl = IPL_UNINITIALIZED;

void CoRaiseIpl(IN IPL NewIpl, OUT PIPL OldIpl)
{
	if (m_ipl <= NewIpl) {
		*OldIpl = m_ipl;
		m_ipl = NewIpl;
	} else {
		KrnlEasyStop(STOP_IPL_NOT_LESS_OR_EQUAL);
	}
}

void CoLowerIpl(IN IPL NewIpl)
{
	ArchDisableInterrupts();
	/* You can always lower IPL, even if lowering results in IPL
	 * being higher. This has no chance of causing problems. */
	m_ipl = NewIpl;
	ArchEnableInterrupts();
}

IPL CoGetIpl(void)
{
	return m_ipl;
}
