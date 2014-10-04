#ifndef COLPA_DPRINT_H
#define COLPA_DPRINT_H

#include <system.h>
#include <kernel.h>

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

#endif /* end of include guard: COLPA_DPRINT_H */
