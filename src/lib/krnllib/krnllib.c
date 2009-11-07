/* krnllib.c for Dux */

#include <stdint.h>

void puts ( char *str )
{
	// Call syscall 0 (printk) with str as the arg
	__asm__ __volatile__ (" \
			mov $0, %%eax; \
			mov %0, %%ebx; \
			int $0x80; \
			" : : "m" (str) : "eax", "ebx");
}

void puthex ( uint32_t num )
{
	__asm__ __volatile__ (" \
			mov $1, %%eax; \
			mov %0, %%ebx; \
			int $0x80; \
			" : : "m" (num) : "eax", "ebx");
}

void putdec ( uint32_t num )
{
	__asm__ __volatile__ (" \
			mov $2, %%eax; \
			mov %0, %%ebx; \
			int $0x80; \
			" : : "m" (num) : "eax", "ebx");
}

void shutdown ()
{
	__asm__ __volatile__ (" \
			mov $3, %%eax; \
			int $0x80; \
			" : : : "eax");
}

void reboot ()
{
	__asm__ __volatile__ (" \
			mov $4, %%eax; \
			int $0x80; \
			" : : : "eax");
}

void clear_screen ()
{
	__asm__ __volatile__ (" \
			mov $5, %%eax; \
			int $0x80; \
			" : : : "eax");
}

void *malloc (unsigned int size, unsigned int flags)
{
	void *rval;
	__asm__ __volatile__ (" \
			mov $6, %%eax; \
			mov %0, %%ebx; \
			mov %1, %%ecx; \
			int $0x80; \
			mov %%eax, %2; \
			" : "=m" (rval) : "m" (size), "m" (flags) : "eax", "ebx", "ecx");
	return rval;
}

