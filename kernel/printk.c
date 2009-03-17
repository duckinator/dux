#include <system.h>

#ifndef __GNUC__
#error I want gcc!
#endif

#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)
typedef __builtin_va_list va_list;

static void printn(int n, int base)
{
	char *numbers = "0123456789abcdefghijklmnopqrstuvwxyz";
	if (n < 0) {
		putch('-');
		n = -n;
	}
	if (n / base)
		printn(n/base, base);
	putch(numbers[n % base]);
}

void printk(char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	char cval;
	int ival;
	double dval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putch(*p);
			continue;
		}

		switch(*++p) {
			case 'd':
				ival = va_arg(ap, int);
				printn(ival, 10);
				break;
			case 'c':
				cval = va_arg(ap, int);
				putch(cval);
				break;
			case 's':
				sval = va_arg(ap, char*);
				while (*sval)
					putch(*sval++);
				break;
			case 'x':
				ival = va_arg(ap, int);
				printn(ival, 16);
				break;
			default:
				putch(*p);
				break;
		}
	}
	va_end(ap);
}
