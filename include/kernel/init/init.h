#ifndef INIT_H
#define INIT_H

#include <system.h>

#include <kernel.h>
#include <kernel/misc/panic.h>

#include <kernel/init/tests.h>
#include <kernel/init/memory_map.h>
#include <kernel/init/load_modules.h>

#include <string.h>

#include <kernel/bochs.h>

#include <kernel/colpa/debug.h>
#include <kernel/colpa/tests.h>

#include <kernel/init/elfloader.h>

#include <dwarf2.h>

void InitKernel(uint32_t magic, void *args);

#endif /* end of include guard: INIT_H */
