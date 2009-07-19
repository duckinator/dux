#ifndef HAL_UP0YTECP

#define HAL_UP0YTECP

#include <stdint.h>

void HalInit(void (*receiver)(uint32_t msg));
void HalOutPort(uint16_t port, uint8_t data);
uint8_t HalInPort(uint16_t port);

void HalBeep(void);

void usleep(int milliseconds);
void sleep(int seconds);

#endif /* end of include guard: HAL_UP0YTECP */
