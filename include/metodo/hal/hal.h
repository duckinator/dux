#ifndef HAL_H
#define HAL_H

#include <driver/generic/display.h>

#if I386
#include <metodo/hal/i386.h>
#endif

void HalInit(void);
void HalBreak(void);
void HalShutdown(void);
void HalReboot(void);

#endif /* end of include guard: HAL_H */
