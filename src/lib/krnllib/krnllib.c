/* krnllib.c for Dux */

#include <stdint.h>
#include <config.h>

void putc ( char c )
{
	// Call syscall 0 (HalDisplayChar) with c as the arg
	__asm__ __volatile__ (" \
			mov $0, %%eax; \
			mov %0, %%ebx; \
			int $" IA32_SYSCALL_INTERRUPT_STR "; \
			" : : "m" (c) : "eax", "ebx");
}

void puts ( char *s )
{
	do {
		putc(*s);
	} while (*s++);
}

void puthex ( uint32_t num )
{
	__asm__ __volatile__ (" \
			mov $1, %%eax; \
			mov %0, %%ebx; \
			int $" IA32_SYSCALL_INTERRUPT_STR "; \
			" : : "m" (num) : "eax", "ebx");
}

void putdec ( uint32_t num )
{
	__asm__ __volatile__ (" \
			mov $2, %%eax; \
			mov %0, %%ebx; \
			int $" IA32_SYSCALL_INTERRUPT_STR "; \
			" : : "m" (num) : "eax", "ebx");
}

void shutdown ()
{
	__asm__ __volatile__ (" \
			mov $3, %%eax; \
			int $" IA32_SYSCALL_INTERRUPT_STR "; \
			" : : : "eax");
}

void reboot ()
{
	__asm__ __volatile__ (" \
			mov $4, %%eax; \
			int $" IA32_SYSCALL_INTERRUPT_STR "; \
			" : : : "eax");
}

void clear_screen ()
{
	__asm__ __volatile__ (" \
			mov $5, %%eax; \
			int $" IA32_SYSCALL_INTERRUPT_STR "; \
			" : : : "eax");
}

void *malloc (unsigned int size, unsigned int flags)
{
	void *rval;
	__asm__ __volatile__ (" \
			mov $6, %%eax; \
			mov %0, %%ebx; \
			mov %1, %%ecx; \
			int $" IA32_SYSCALL_INTERRUPT_STR "; \
			mov %%eax, %2; \
			" : "=m" (rval) : "m" (size), "m" (flags) : "eax", "ebx", "ecx");
	return rval;
}

