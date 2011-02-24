#ifndef METODO_H
#define METODO_H

#include <system.h>

#include <metodo/hal.h>

#include <metodo/init/init.h>
#include <metodo/core/core.h>

#include <multiboot.h>

#include <macros.h>

#include <metodo/misc/panic.h>

multiboot_info_t *mbd;
memory_map_t *mmaps[100];

#endif /* end of include guard: METODO_H */
