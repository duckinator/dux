#ifndef SYSCALL_H
#define SYSCALL_H

#include <metodo/hal/isr.h>

extern void HalSyscallHandler(struct regs *r);
extern void HalIsrSyscall(void);

void HalInitializeSyscalls();

#endif
