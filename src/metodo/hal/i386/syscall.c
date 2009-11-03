// syscall.c -- Defines the implementation of a system call system.
// Based on code from JamesM's kernel development tutorials.

#include <stdint.h>
#include <system.h>
#include <metodo/metodo.h>

void HalSyscallShutdown(void)
{
	CoShutdown(SD_OFF);
}

void HalSyscallReboot(void)
{
	CoShutdown(SD_REBOOT);
}

void HalMonitorWriteStr(char *text)
{
	printf("%s", text);
}

void HalMonitorWriteHex(uint32_t text)
{
	printf("%x", text);
}

void HalMonitorWriteDec(uint32_t text)
{
	printf("%d", text);
}

DEFN_SYSCALL1(HalMonitorWriteStr, 0, const char*);
DEFN_SYSCALL1(HalMonitorWriteHex, 1, const uint32_t); // hex
DEFN_SYSCALL1(HalMonitorWriteDec, 2, const uint32_t); // dec

static void *syscalls[5] =
{
	&HalMonitorWriteStr,
	&HalMonitorWriteHex,
	&HalMonitorWriteDec,
	&HalSyscallShutdown,
	&HalSyscallReboot
};
int num_syscalls = 5;

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
