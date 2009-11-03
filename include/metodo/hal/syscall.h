#ifndef SYSCALL_H
#define SYSCALL_H

#include <metodo/hal/isr.h>

extern void HalSyscallHandler(struct regs *r);
extern void HalIsrSyscall(void);

void HalInitializeSyscalls();

#define DECL_SYSCALL0(fn) int HalSyscall_##fn();
#define DECL_SYSCALL1(fn,p1) int HalSyscall_##fn(p1);
#define DECL_SYSCALL2(fn,p1,p2) int HalSyscall_##fn(p1,p2);
#define DECL_SYSCALL3(fn,p1,p2,p3) int HalSyscall_##fn(p1,p2,p3);
#define DECL_SYSCALL4(fn,p1,p2,p3,p4) int HalSyscall_##fn(p1,p2,p3,p4);
#define DECL_SYSCALL5(fn,p1,p2,p3,p4,p5) int HalSyscall_##fn(p1,p2,p3,p4,p5);

#define DEFN_SYSCALL0(fn, num) \
int HalSyscall_##fn() \
{ \
 int a; \
 asm volatile("int $0x80" : "=a" (a) : "0" (num)); \
 return a; \
}

#define DEFN_SYSCALL1(fn, num, P1) \
int HalSyscall_##fn(P1 p1) \
{ \
 int a; \
 asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1)); \
 return a; \
}

#define DEFN_SYSCALL2(fn, num, P1, P2) \
int HalSyscall_##fn(P1 p1, P2 p2) \
{ \
 int a; \
 asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2)); \
 return a; \
}

#define DEFN_SYSCALL3(fn, num, P1, P2, P3) \
int HalSyscall_##fn(P1 p1, P2 p2, P3 p3) \
{ \
 int a; \
 asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2), "d" ((int)p3)); \
 return a; \
}

#define DEFN_SYSCALL4(fn, num, P1, P2, P3, P4) \
int HalSyscall_##fn(P1 p1, P2 p2, P3 p3, P4 p4) \
{ \
 int a; \
 asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2), "d" ((int)p3), "e" ((int)p4)); \
 return a; \
}

#define DEFN_SYSCALL5(fn, num, P1, P2, P3, P4, P5) \
int HalSyscall_##fn(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) \
{ \
 int a; \
 asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2), "d" ((int)p3), "e" ((int)p4), "f" ((int)p5)); \
 return a; \
}

DECL_SYSCALL1(ULMonitorWrite, const char*)
DECL_SYSCALL1(ULMonitorWriteHex, const uint32_t)
DECL_SYSCALL1(ULMonitorWriteDec, const uint32_t) 
DECL_SYSCALL0(ULShutdown)
DECL_SYSCALL0(ULReboot)
DECL_SYSCALL0(HalDisplayClear)

void HalSyscallDebug();

#endif
