#ifndef HAL_H
#define HAL_H

#include <buildinfo.h>

#include <driver/generic/display.h>

#include <metodo/hal/mm/memory.h>

#ifdef DUX_I386
  #include <metodo/hal/i386.h>
#elif defined DUX_X86_64
  #include <metodo/hal/x86_64.h>
#endif

void HalInit(void);
void HalBreak(void);
void HalShutdown(void);
void HalReboot(void);

#endif /* end of include guard: HAL_H */
