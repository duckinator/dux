#include <system.h>

#include <dux/drivers/core/console.h>
#include <dux/krnl/core.h>

static const char *numbers = "0123456789abcdefghijklmnopqrstuvwxyz";

static void printn(unsigned int n, unsigned int base)
{
	if (n / base)
		printn(n/base, base);
	console_writeb(numbers[n % base]);
}

DEPRECIATED void printk(const char *fmt, ...)
{
	va_list ap;
	const char *p, *sval;
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

static void printna(unsigned int n, unsigned int base)
{
	if (n / base)
		printna(n/base, base);
	ArchDisplayChar(numbers[n % base]);
}


void printka(const char *fmt, ...)
{
	va_list ap;
	const char *p, *sval;
	char cval;
	unsigned int ival;
	unsigned long long lval;
	unsigned int process_long = 0;
	//double dval; /* for %f */

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			ArchDisplayChar(*p);
			continue;
		}

reset:
		switch(*++p) {
			case 'i':
			case 'd':
				ival = va_arg(ap, unsigned int);
				printna(ival, 10);
				break;
			case 'c':
				cval = va_arg(ap, unsigned int);
				ArchDisplayChar(cval);
				break;
			case 's':
				sval = va_arg(ap, char*);
				while (*sval)
					ArchDisplayChar(*sval++);
				break;
			case 'x':
				if (process_long) {
					lval = va_arg(ap, unsigned long long);
					printna((unsigned int)lval, 16);
				} else {
					ival = va_arg(ap, unsigned int);
					printna(ival, 16);
				}
				break;
			case 'l':
				process_long = 1;
				goto reset;
				break;
			default:
				ArchDisplayChar(*p);
				break;
		}
	}
	va_end(ap);
}
