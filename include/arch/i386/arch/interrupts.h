#ifndef INTERRUPTS_UTQLFFV0

#define INTERRUPTS_UTQLFFV0

#include <arch/arch.h>

void ArchDisableInterrupts(void);
void ArchEnableInterrupts(void);

void ArchDisableNMI(void);
void ArchEnableNMI(void);

#endif /* end of include guard: INTERRUPTS_UTQLFFV0 */
