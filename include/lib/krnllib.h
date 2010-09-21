#ifndef KRNLLIB_H
#define KRNLLIB_H

#include <system.h>
#include <modifiers.h>


void putc ( char c );
void puts ( char *str );
void puthex ( uint32_t num );
void putdec ( uint32_t num );
void shutdown ();
void reboot ();
void clear_screen ();

#endif /* end of include guard: KRNLLIB_H */
