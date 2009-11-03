#ifndef KRNLLIB_H
#define KRNLLIB_H

#include <stdint.h>

void puts ( char *str );
void puthex ( uint32_t num );
void putdec ( uint32_t num );
void shutdown ();
void reboot ();
void clear_screen ();

#endif
