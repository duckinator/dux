#ifndef STOP_NB3QO831

#define STOP_NB3QO831

#include <stdint.h>

#define STOP_UNKNOWN 0x1
#define STOP_BAD_MULTIBOOT_SIGNATURE 0x2
#define STOP_NO_USERLAND 0x3
#define STOP_IPL_NOT_GREATER_OR_EQUAL 0x4

void KrnlStop(uint32_t error, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);
#define KrnlEasyStop(error) KrnlStop(error, 0, 0, 0, 0);

#endif /* end of include guard: STOP_NB3QO831 */
