#include <metodo/colpa/dprint.h>

void dprint(debug_type type, char *str, const char *fmt, ...)
{
	if (DEBUG_MODE == NONE)
		return;

	if (DEBUG_MODE == ALL || type == DEBUG_MODE) {
		va_list args;
		int i;

		va_start(args, fmt);
		i = vsnprintf(str, 0, fmt, args);
		va_end(args);

		va_start(args, fmt);
		i = vsnprintf(str, i+1, fmt, args);
		va_end(args);
	}
}

void set_debug_mode(debug_type type)
{
	DEBUG_MODE = type;
}

debug_type get_debug_mode(void)
{
	return DEBUG_MODE;
}
