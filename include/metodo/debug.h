#ifndef __DEBUG_H
#define __DEBUG_H

/* debug.c */

typedef enum {
  NONE,
	ALL,
	FILESYSTEM,
	MEMORY,
	CONSOLE
} debug_type;

debug_type DEBUG_MODE = NONE;

void dprint(const char *msg, debug_type type);
void set_debug_mode(debug_type type);
debug_type get_debug_mode(void);

#endif
