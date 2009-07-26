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

void puthex( uint32_t num )
{
	__asm__ __volatile__ (" \
			mov $1, %%eax; \
			mov %0, %%ebx; \
			int $0x80; \
			" : : "m" (num) : "eax", "ebx");
}

void putdec( uint32_t num )
{
	__asm__ __volatile__ (" \
			mov $2, %%eax; \
			mov %0, %%ebx; \
			int $0x80; \
			" : : "m" (num) : "eax", "ebx");
}
