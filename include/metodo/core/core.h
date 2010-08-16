#ifndef CORE_H
#define CORE_H

/* Interrupt Priority Level */
typedef uint8_t IPL, *PIPL;

#define IPL_PASSIVE 0x00
#define IPL_HWINTERRUPT 0x01
#define IPL_EXCEPTION 0x02
#define IPL_UNINITIALIZED 0xff

void CoRaiseIpl(IN IPL NewIpl, OUT PIPL OldIpl);
void CoLowerIpl(IN IPL NewIpl);
IPL CoGetIpl(void);

/* Shutdown */
#define SD_REBOOT 1
#define SD_OFF 2
#define SD_WAIT 3

void CoShutdown(int mode);

#include <text.h>

#include <metodo/core/memory.h>

#endif /* end of include guard: CORE_H */
