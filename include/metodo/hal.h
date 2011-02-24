#ifndef HAL_H
#define HAL_H

#include <buildinfo.h>

#include <api/display.h>

#include <metodo/x86/mm/memory.h>

#ifdef DUX_I386
  #include <metodo/i386/hal.h>
#elif defined DUX_AMD64
  #include <metodo/amd64/hal.h>
#endif

void HalPreInit(void);
void HalInit(void);
void HalBreak(void);
void HalShutdown(void);
void HalReboot(void);

#endif /* end of include guard: HAL_H */
