#ifndef INIT_H
#define INIT_H

#include <system.h>

#include <metodo/metodo.h>
#include <metodo/misc/stop.h>

#include <metodo/init/tests.h>
#include <metodo/init/memory_map.h>

#include <string.h>

#include <metodo/bochs.h>

#include <metodo/colpa/debug.h>
#include <metodo/colpa/tests.h>

#include <metodo/init/elfloader.h>

#include <dwarf2.h>

void InitKernel(uint32_t magic, void *args);

#endif /* end of include guard: INIT_H */
