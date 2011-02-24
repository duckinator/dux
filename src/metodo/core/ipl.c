#include <metodo/core/ipl.h>

static IPL m_ipl = IPL_UNINITIALIZED;

void CoRaiseIpl(IN IPL NewIpl, OUT PIPL OldIpl)
{
	if (m_ipl <= NewIpl) {
		*OldIpl = m_ipl;
		m_ipl = NewIpl;
	} else {
		/* TODO: Implement some kind of error system. Unresolvable. Somehow stop. */
		CoShutdown(SD_WAIT);
	}
}

void CoLowerIpl(IN IPL NewIpl)
{
	/* You can always lower IPL, even if lowering results in IPL
	 * being higher. This has no chance of causing problems. */
	m_ipl = NewIpl;
}

IPL CoGetIpl(void)
{
	return m_ipl;
}
