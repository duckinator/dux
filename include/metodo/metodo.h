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

#include <metodo/hal/display.h>
#include <metodo/hal/hal.h>
#if I386
#include <metodo/hal/i386.h>
#endif

#include <metodo/init.h>
#include <metodo/core.h>

#include <metodo/misc.h>

#endif /* end of include guard: METODO_IIXETUDY */
