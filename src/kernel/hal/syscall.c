// syscall.c -- Defines the implementation of a system call system.
// Based on code from JamesM's kernel development tutorials.

#include <stdint.h>
#include <system.h>
#include <kernel.h>
#include <kernel/core/shutdown.h>
#include <config.h>

#define NUM_SYSCALLS 6

void ULShutdown(UNUSED uint32_t ebx, UNUSED uint32_t ecx, UNUSED uint32_t edx,
	UNUSED uint32_t esi, UNUSED uint32_t edi)
{
	CoShutdown(SD_OFF);
}

void ULReboot(UNUSED uint32_t ebx, UNUSED uint32_t ecx, UNUSED uint32_t edx,
	UNUSED uint32_t esi, UNUSED uint32_t edi)
{
	CoShutdown(SD_REBOOT);
}

void ULMonitorWriteChar(uint32_t ebx, UNUSED uint32_t ecx, UNUSED uint32_t edx,
	UNUSED uint32_t esi, UNUSED uint32_t edi)
{
	printf("%c", (char)ebx);
}

void ULMonitorWriteHex(uint32_t ebx, UNUSED uint32_t ecx, UNUSED uint32_t edx,
	UNUSED uint32_t esi, UNUSED uint32_t edi)
{
	printf("%x", ebx);
}

void ULMonitorWriteDec(uint32_t ebx, UNUSED uint32_t ecx, UNUSED uint32_t edx,
	UNUSED uint32_t esi, UNUSED uint32_t edi)
{
	printf("%d", ebx);
}

void ULDisplayClear(UNUSED uint32_t ebx, UNUSED uint32_t ecx, UNUSED uint32_t edx,
	UNUSED uint32_t esi, UNUSED uint32_t edi)
{
	DisplayClear();
}

static void (*syscalls[NUM_SYSCALLS])(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) = 
{
	ULMonitorWriteChar,
	ULMonitorWriteHex,
	ULMonitorWriteDec,
	ULShutdown,
	ULReboot,
	ULDisplayClear,
};

void HalInitializeSyscalls()
{
	// Register our syscall handler.
	HalSetIDTGate(SYSCALL_INTERRUPT, (uint32_t) HalIsrSyscall, 0x08, 0x8E, 0, IDT_INTR32);
}

void HalSyscallHandler(struct regs *r)
{
	// Firstly, check if the requested syscall number is valid.
	// The syscall number is found in EAX.
	if (r->eax >= NUM_SYSCALLS)
		 return;

	void (*syscall)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

	syscall = syscalls[r->eax];
	syscall((uint32_t)r->ebx, (uint32_t)r->ecx, (uint32_t)r->edx, (uint32_t)r->esi, (uint32_t)r->edi);
}
