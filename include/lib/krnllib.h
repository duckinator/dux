#ifndef KRNLLIB_H
#define KRNLLIB_H

#include <stdint.h>

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

#endif
