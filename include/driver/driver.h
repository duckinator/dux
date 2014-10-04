#ifndef DRIVER_H
#define DRIVER_H

#include <kernel.h>

#define DRIVER_INIT(func) void _start(void) { ##func (); }

#endif
