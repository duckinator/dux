// syscall.c -- Defines the implementation of a system call system.
// Based on code from JamesM's kernel development tutorials.

#include <stdint.h>
#include <system.h>
#include <metodo/metodo.h>

void ULShutdown(void)
{
	CoShutdown(SD_OFF);
}

void ULReboot(void)
{
	CoShutdown(SD_REBOOT);
}

void ULMonitorWriteStr(char *text)
{
	printf("%s", text);
}

void ULMonitorWriteHex(uint32_t text)
{
	printf("%x", text);
}

void ULMonitorWriteDec(uint32_t text)
{
	printf("%d", text);
}

void *malloc(unsigned int size, unsigned int flags)
{
	return kmalloc_int(size, flags);
}

DEFN_SYSCALL1(ULMonitorWriteStr, 0, const char*);
DEFN_SYSCALL1(ULMonitorWriteHex, 1, const uint32_t); // hex
DEFN_SYSCALL1(ULMonitorWriteDec, 2, const uint32_t); // dec
DEFN_SYSCALL0(ULShutdown,        3);
DEFN_SYSCALL0(ULReboot,          4);
DEFN_SYSCALL0(HalDisplayClear,   5);
DEFN_SYSCALL2(malloc, 6, unsigned int, unsigned int);
static void *syscalls[7] =
{
	&ULMonitorWriteStr,
	&ULMonitorWriteHex,
	&ULMonitorWriteDec,
	&ULShutdown,
	&ULReboot,
	&HalDisplayClear,
	&malloc
};
int num_syscalls = 7;

void HalInitializeSyscalls()
{
	// Register our syscall handler.
	//HalIdtSetEntry(0x80, (unsigned)HalIsrSyscall, 0x08, 0x8E);
	HalSetIDTGate(0x80, (uint32_t) HalIsrSyscall, 0x08, 0x8E, 0, IDT_INTR32);
}

void HalSyscallHandler(struct regs *r)
{
	// Firstly, check if the requested syscall number is valid.
	// The syscall number is found in EAX.
	if (r->eax >= num_syscalls)
		 return;

	// Get the required syscall location.
	void *location = syscalls[r->eax];

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
	" : "=a" (ret) : "r" (r->edi), "r" (r->esi), "r" (r->edx), "r" (r->ecx), "r" (r->ebx), "r" (location));
	r->eax = ret;
}
