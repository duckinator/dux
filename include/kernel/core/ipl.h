#ifndef IPL_H
#define IPL_H

#include <kernel/core/shutdown.h>

/* Interrupt Priority Level */
typedef uint8_t IPL, *PIPL;

#define IPL_PASSIVE 0x00
#define IPL_HWINTERRUPT 0x01
#define IPL_EXCEPTION 0x02
#define IPL_UNINITIALIZED 0xff

void CoRaiseIpl(IN IPL NewIpl, OUT PIPL OldIpl);
void CoLowerIpl(IN IPL NewIpl);
IPL CoGetIpl(void);

#endif /* end of include guard: IPL_H */
