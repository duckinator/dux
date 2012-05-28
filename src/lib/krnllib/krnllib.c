/* krnllib.c for Dux */

#include <stddef.h>
#include <stdint.h>
#include <config.h>
#include <macros.h>
#include <lib/krnllib.h>

void putc ( char c )
{
	// Call syscall 0 (DisplayChar) with c as the arg
	__asm__ __volatile__ (" \
			mov $0, %%eax; \
			mov %0, %%ebx; \
			int $" MACRO_STRING(SYSCALL_INTERRUPT) "; \
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
			int $" MACRO_STRING(SYSCALL_INTERRUPT) "; \
			" : : "m" (num) : "eax", "ebx");
}

void putdec ( uint32_t num )
{
	__asm__ __volatile__ (" \
			mov $2, %%eax; \
			mov %0, %%ebx; \
			int $" MACRO_STRING(SYSCALL_INTERRUPT) "; \
			" : : "m" (num) : "eax", "ebx");
}

void shutdown ()
{
	__asm__ __volatile__ (" \
			mov $3, %%eax; \
			int $" MACRO_STRING(SYSCALL_INTERRUPT) "; \
			" : : : "eax");
}

void reboot ()
{
	__asm__ __volatile__ (" \
			mov $4, %%eax; \
			int $" MACRO_STRING(SYSCALL_INTERRUPT) "; \
			" : : : "eax");
}

void clear_screen ()
{
	__asm__ __volatile__ (" \
			mov $5, %%eax; \
			int $" MACRO_STRING(SYSCALL_INTERRUPT) "; \
			" : : : "eax");
}

void *malloc (size_t size)
{
	// FIXME: Dummy userland malloc()
	return NULL;
}

void free(void *ptr)
{
	// FIXME: Dummy userland free()
}
