// syscall.c -- Defines the implementation of a system call system.
// Based on code from JamesM's kernel development tutorials.

#include <stdint.h>
#include <system.h>
#include <metodo/metodo.h>
#include <config.h>

#define NUM_SYSCALLS 7

void ULShutdown(void)
{
	CoShutdown(SD_OFF);
}

void ULReboot(void)
{
	CoShutdown(SD_REBOOT);
}

void ULMonitorWriteChar(char c)
{
	printf("%c", c);
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

static void *syscalls[NUM_SYSCALLS] =
{
	ULMonitorWriteChar,
	ULMonitorWriteHex,
	ULMonitorWriteDec,
	ULShutdown,
	ULReboot,
	HalDisplayClear,
	malloc
};

void HalInitializeSyscalls()
{
	// Register our syscall handler.
	HalSetIDTGate(IA32_SYSCALL_INTERRUPT, (uint32_t) HalIsrSyscall, 0x08, 0x8E, 0, IDT_INTR32);
}

void HalSyscallHandler(struct regs *r)
{
	// Firstly, check if the requested syscall number is valid.
	// The syscall number is found in EAX.
	if (r->eax >= NUM_SYSCALLS)
		 return;

	void (*syscall)(int, int, int, int, int);

	syscall = syscalls[r->eax];
	syscall((int)r->edi, (int)r->esi, (int)r->edx, (int)r->ecx, (int)r->ebx);
}
