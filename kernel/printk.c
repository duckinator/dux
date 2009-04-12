#include <system.h>

#include <dux/drivers/core/console.h>

#ifndef __GNUC__
#error I want gcc!
#endif

#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)
typedef __builtin_va_list va_list;

static void printn(unsigned int n, unsigned int base)
{
	char *numbers = "0123456789abcdefghijklmnopqrstuvwxyz";
	// always false
//	if (n < 0) {
//		putch('-');
//		n = -n;
//	}
	if (n / base)
		printn(n/base, base);
	console_writeb(numbers[n % base]);
}

void printk(char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	char cval;
	unsigned int ival;
	unsigned long long lval;
	unsigned int process_long = 0;
	//double dval; /* for %f */

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			console_writeb(*p);
			continue;
		}

reset:
		switch(*++p) {
			case 'i':
			case 'd':
				ival = va_arg(ap, unsigned int);
				printn(ival, 10);
				break;
			case 'c':
				cval = va_arg(ap, unsigned int);
				console_writeb(cval);
				break;
			case 's':
				sval = va_arg(ap, char*);
				while (*sval)
					console_writeb(*sval++);
				break;
			case 'x':
				if (process_long) {
					lval = va_arg(ap, unsigned long long);
					printn((unsigned int)lval, 16);
				} else {
					ival = va_arg(ap, unsigned int);
					printn(ival, 16);
				}
				break;
			case 'l':
				process_long = 1;
				goto reset;
				break;
			default:
				console_writeb(*p);
				break;
		}
	}
	va_end(ap);
}
