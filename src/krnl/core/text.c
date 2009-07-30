#include <dux/krnl/core.h>

static int m_printn(IN char *str, IN size_t size, IN int curLength,
		IN int upper, IN int base, IN int n);

static const char *m_lowerNumbers = "0123456789abcdefghijklmnopqrstuvwxyz";
static const char *m_upperNumbers = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static int m_printn(IN char *str, IN size_t size, IN int curLength,
		IN int upper, IN int base, IN int n)
{
	int dividend = n;
	int divisor = base;
	const char *numbers = m_lowerNumbers;

	if (upper)
		numbers = m_upperNumbers;

	/* Is the number negative. */
	if (n < 0)
		if (curLength < size)
			str[curLength++] = '-';
		else
			curLength++;

	/* Just some commentary on the algorithm. First divide a
	 * dividend by the base, if the result isn't zero, the new
	 * dividend is the original number divided by the divisor. After
	 * that the divisor is multiplied by the base.
	 *
	 * So for the number 1234:
	 * 1234 % 10 = 4 not 0, so 1234/10 = 123
	 *  123 % 10 = 3 not 0, so 1234/100 = 12
	 *   12 % 10 = 2 not 0, so 1234/1000 = 1
	 *    1 % 10 = 1 not 0, so 1234/10000 = 0
	 *    0 % 10 = 0 not 0, so 1234/100000 = 0
	 *
	 * Next take one order of magnitude off the divisor for every
	 * loop until the divisor is 1. The number dividied by the
	 * divisor mod zero is the index.
	 *
	 * 1234/1000%0 = 1
	 *  1234/100%0 = 2
	 *   1234/10%0 = 3
	 *    1234/1%0 = 4
	 *
	 * To convert the index into ASCII, the number is looked up in
	 * an array. */

	/* Find how long the number is. */
	while (dividend%base != 0) {
		dividend = n/divisor;
		divisor *= base;
	}

	/* Undo effects of testing in previous loop. */
	divisor /= base*base;

	/* Print the number to a string. */
	while (divisor > 0) {
		if (curLength < size)
			str[curLength++] = numbers[(n/divisor%base)];
		else
			curLength++;
		divisor /= base;
	}

	return curLength;
}

int snprintf(IN char *str, IN size_t size, IN const char *format, ...)
{
	va_list args;
	int i;
	
	va_start(args, format);
	i = vsnprintf(str, size, format, args);
	va_end(args);
	return i;
}

int sprintf(IN char *str, IN const char *format, ...)
{
	va_list args;
	int i;
	
	va_start(args, format);
	i = vsnprintf(str, 0, format, args);
	va_end(args);

	/* Add one here to leave space for the null byte. */
	va_start(args, format);
	i = vsnprintf(str, i+1, format, args);
	va_end(args);
	return i;
}

int printf(IN const char *format, ...)
{
	/* TODO: Use real memory management here. */
#if 0
	char *str;
#endif
	char str[1024];
	va_list args;
	int i;

#if 0
	va_start(args, format);
	i = vsnprintf(NULL, 0, format, args);
	va_end(args);

	str = malloc(i+1);
	
	/* Add one here to leave space for the null byte. */
	va_start(args, format);
	i = vsnprintf(str, i+1, format, args);
	va_end(args);
#endif

	va_start(args, format);
	i = vsnprintf(str, 1024, format, args);
	va_end(args);

	ArchDisplayString(str);
#if 0
	free(str);
#endif
	return i;
}

int vsnprintf(IN char *str, IN size_t size, IN const char *format,
		IN va_list args)
{
	int len = 0;
	const char *p;
	char cval;
	signed int dval;
	const char *sval;
	unsigned int uval;

	/* The algorithm here is rather simple. Loop through the format
	 * string looking for %s. When a % is found, take appropriate
	 * action. */

	for (p = format; *p; p++) {
		if (*p != '%') {
			if (len < size)
				str[len++] = *p;
			else
				len++;
			continue;
		}

		switch (*++p) {
			case 'I':
			case 'D':
				dval = va_arg(args, int);
				len = m_printn(str, size, len, 1,
						10, dval);
				break;
			case 'i':
			case 'd':
				dval = va_arg(args, int);
				len = m_printn(str, size, len, 0,
						10, dval);
				break;
			case 'U':
				uval = va_arg(args, unsigned int);
				len = m_printn(str, size, len, 1,
						10, uval);
				break;
			case 'u':
				uval = va_arg(args, unsigned int);
				len = m_printn(str, size, len, 0,
						10, uval);
				break;
			case 'O':
				uval = va_arg(args, unsigned int);
				len = m_printn(str, size, len, 1,
						8, uval);
				break;
			case 'o':
				uval = va_arg(args, unsigned int);
				len = m_printn(str, size, len, 0,
						8, uval);
				break;
			case 'X':
				uval = va_arg(args, unsigned int);
				len = m_printn(str, size, len, 1,
						16, uval);
				break;
			case 'x':
				uval = va_arg(args, unsigned int);
				len = m_printn(str, size, len, 0,
						16, uval);
				break;
			case 'c':
				cval = va_arg(args, int);
				if (len < size)
					str[len++] = cval;
				else
					len++;
				break;
			case 's':
				sval = va_arg(args, char*);
				while (*sval)
					if (len < size) {
						str[len++] = *sval++;
					} else {
						/* sval has to increase
						 * if we want to get out
						 * of this. */
						sval++;
						len++;
					}
				break;
			default:
				/* Assume something has been placed on
				 * the stack. */
				va_arg(args, void);
				if (len < size)
					str[len++] = '%';
				else
					len++;
				if (len < size)
					str[len++] = *p;
				else
					len++;
		}
	}

	/* If len is less than size, we need to print at the end of the
	 * string. If len is greater than size we need to print it
	 * wherever the real cutoff point is. Also make sure size is
	 * greater than zero before writing anything. */
	if (size > 0)
		if (len < size)
			str[len] = '\0';
		else
			str[size-1] = '\0';
	return len;
}
