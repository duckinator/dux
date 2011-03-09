#ifndef METODO_H
#define METODO_H

#include <system.h>

#include <metodo/hal.h>

#include <metodo/core/memory.h>

#include <bootloaders.h>

#include <metodo/misc/panic.h>

multiboot_info_t *mbd;
memory_map_t *mmaps[100];

uint8_t bootloader;

extern unsigned int *start;
extern unsigned int *end;

extern unsigned int *debug_info_start;
extern unsigned int *debug_info_end;

extern unsigned int *start_tests;
extern unsigned int *end_tests;

#endif /* end of include guard: METODO_H */
