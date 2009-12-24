#ifndef METODO_IIXETUDY

#define METODO_IIXETUDY

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/* Define pseudo argument modifiers. */
#define IN
#define OUT
#define OPTIONAL
#define NOTHING

/* Define pseudo function modifiers. */
#define DEPRECIATED

#include <metodo/hal/hal.h>

#include <metodo/init.h>
#include <metodo/core.h>

#include <metodo/misc.h>

#include <multiboot.h>

multiboot_info_t *mbd;

#endif /* end of include guard: METODO_IIXETUDY */
