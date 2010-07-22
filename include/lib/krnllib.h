#ifndef KRNLLIB_H
#define KRNLLIB_H

#include <stdint.h>
#include <stddef.h>

#define IN
#define OUT
#define OPTIONAL
#define NOTHING


void putc ( char c );
void puts ( char *str );
void puthex ( uint32_t num );
void putdec ( uint32_t num );
void shutdown ();
void reboot ();
void clear_screen ();
void *malloc (size_t size);
void free(void *ptr);

#endif /* end of include guard: KRNLLIB_H */
