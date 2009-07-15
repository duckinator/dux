// syscall.c -- Defines the implementation of a system call system.
// Written for JamesM's kernel development tutorials.

#include <system.h>
#include <syscall.h>
#include <isr.h>

/* #include "monitor.h" */

void HalMonitorWriteHex(char *text){
	printk("%x", text); /* Todo: Figure out wtf "%x" should be */
}
void HalMonitorWriteDec(char *text){
	printk("%i", text);
}

DEFN_SYSCALL1(printk, 0, const char*);
DEFN_SYSCALL1(HalMonitorWriteHex, 1, const char*); // hex
DEFN_SYSCALL1(HalMonitorWriteDec, 2, const char*); // dec

static void HalSyscallHandler(registers_t *regs);

static void *syscalls[3] =
{
	&printk,
	&HalMonitorWriteHex,
	&HalMonitorWriteDec,
};
int num_syscalls = 3;

void HalInitializeSyscalls()
{
	// Register our syscall handler.
	//HalIrqHandler_Install (0x80, &HalSyscallHandler);
}

void HalSyscallHandler(registers_t *regs)
{
	// Firstly, check if the requested syscall number is valid.
	// The syscall number is found in EAX.
	if (regs->eax >= num_syscalls)
		 return;

	// Get the required syscall location.
	void *location = syscalls[regs->eax];

	// We don't know how many parameters the function wants, so we just
	// push them all onto the stack in the correct order. The function will
	// use all the parameters it wants, and we can pop them all back off afterwards.
	int ret;
	asm volatile (" \
		push %1; \
		push %2; \
		push %3; \
		push %4; \
		push %5; \
		call *%6; \
		pop %%ebx; \
		pop %%ebx; \
		pop %%ebx; \
		pop %%ebx; \
		pop %%ebx; \
	" : "=a" (ret) : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx), "r" (location));
	regs->eax = ret;
}
