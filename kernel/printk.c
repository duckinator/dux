#include <stdarg.h>
#include <string.h>

#include <system.h>

extern int vsprintf(char *buf, const char *fmt, va_list args);

static char buf[1024];

int printk(const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i=vsprintf(buf,fmt,args);
	va_end(args);
	puts(buf);
	return i;
}

