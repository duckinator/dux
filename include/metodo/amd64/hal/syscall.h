#ifndef HAL_SYSCALL_H
#define HAL_SYSCALL_H

#include <metodo/amd64/hal/isr.h>

extern void HalSyscallHandler(struct regs *r);
extern void HalIsrSyscall(void);

void HalInitializeSyscalls();

#endif /* end of include guard: HAL_SYSCALL_H */
