#ifndef HAL_UP0YTECP

#define HAL_UP0YTECP

#include <stdint.h>

void HalOutPort(uint16_t port, uint8_t data);
uint8_t HalInPort(uint16_t port);

void HalBeep(void);

#endif /* end of include guard: HAL_UP0YTECP */
