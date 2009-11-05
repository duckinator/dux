#include <system.h>
#include <metodo/debug.h>

void dprint(const char *msg, debug_type type)
{
	if (DEBUG_MODE == NONE)
		return;

	if (DEBUG_MODE == ALL || type == DEBUG_MODE)
		printf(msg);
}

void set_debug_mode(debug_type type)
{
	DEBUG_MODE = type;
}

debug_type get_debug_mode(void)
{
	return DEBUG_MODE;
}
