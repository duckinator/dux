#ifndef METODO_H
#define METODO_H

#include <system.h>

#include <metodo/hal/hal.h>

#include <metodo/init/init.h>
#include <metodo/core/core.h>

#include <metodo/misc/misc.h>

#include <multiboot.h>

#include <macros.h>

#include <metodo/misc/panic.h>

extern void monitor_clear();
extern void monitor_switch_pages(unsigned int a, unsigned int b);
extern unsigned int monitor_get_cursor_x();
extern unsigned int monitor_get_cursor_y();
extern void monitor_set_cursor(unsigned int x, unsigned int y);

//extern void HalTimerSleep();

multiboot_info_t *mbd;
memory_map_t *mmaps[100];

#endif /* end of include guard: METODO_H */
