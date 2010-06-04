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

static void *syscalls[7] =
{
	ULMonitorWriteChar,
	ULMonitorWriteHex,
	ULMonitorWriteDec,
	ULShutdown,
	ULReboot,
	HalDisplayClear,
	malloc
};
int num_syscalls = 7;

void HalInitializeSyscalls()
{
	// Register our syscall handler.
	HalSetIDTGate(0x80, (uint32_t) HalIsrSyscall, 0x08, 0x8E, 0, IDT_INTR32);
}

void HalSyscallHandler(struct regs *r)
{
	// Firstly, check if the requested syscall number is valid.
	// The syscall number is found in EAX.
	if (r->eax >= num_syscalls)
		 return;

	void (*syscall)(int, int, int, int, int);

	syscall = syscalls[r->eax];
	syscall((int)r->edi, (int)r->esi, (int)r->edx, (int)r->ecx, (int)r->ebx);
}
