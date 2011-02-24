#ifndef METODO_H
#define METODO_H

#include <system.h>

#include <metodo/hal.h>

#include <metodo/core/memory.h>

#include <bootloaders.h>

#include <metodo/misc/panic.h>

multiboot_info_t *mbd;
memory_map_t *mmaps[100];

extern unsigned int debug_info_start;
extern unsigned int debug_info_end;
extern unsigned int debug_abbrev_start;
extern unsigned int debug_abbrev_end;

#endif /* end of include guard: METODO_H */
