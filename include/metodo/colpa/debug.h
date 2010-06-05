#ifndef DEBUG_H
#define DEBUG_H

#include <system.h>
#include <metodo/metodo.h>
#include <metodo/hal/keyboard/keyboard.h>

typedef enum {
  NONE,
	ALL,
	FILESYSTEM,
	MEMORY,
	CONSOLE
} debug_type;
 
static debug_type DEBUG_MODE = NONE;

void dprint(debug_type type, char *str, const char *fmt, ...);
void set_debug_mode(debug_type type);
debug_type get_debug_mode(void);

void KernDebug();


#endif
