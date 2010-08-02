#ifndef DRIVER_H
#define DRIVER_H

#include <metodo/metodo.h>

#define DRIVER_INIT(func) void _start(void) { ##func (); }

#endif
