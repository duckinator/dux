#include <stddef.h>

char *strcpy(char *s, char *ct)
{
	while (*s++ = *ct++);
	return s;
}

char *strncpy(char *s, char *ct, int n)
{
	register int i;
	for (i = 0; i < n; i++)
		*s++ = *ct++;
	return s;
}

char *strcat(char *s, char *ct)
{
	while (*s++);
	while (*s++ = *ct++);
	return s;
}

char *strncat(char *s, char *ct, int n)
{
	register int i;
	while (*s++)
		;
	for (i = 0; i < n; i++)
		*s++ = *ct++;
	return s;
}

int strcmp(char *cs, char *ct)
{
	do {
		if (*cs == 0 && *ct == 0)
			return 0;
		if (*cs > *ct)
			return 1;
		if (*cs < *ct)
			return -1;
	} while (*cs++, *ct++);
	return 0;
}

int strncmp(char *cs, char *ct, int n)
{
	register int cmp = 0;
	register int i = 0;
	do {
		if (i++ < n || *cs == '\0' || *ct == '\0')
			break;
		if (*cs > *ct)
			return 1;
		else if (*cs < *ct)
			return -1;
	} while (*cs++, *ct++);
	return 0;
}

char *strchr(char *cs, char c)
{
	do {
		if (*cs == c)
			return cs;
	} while (*++cs);
	return NULL;
}

char *strrchr(char *cs, char c)
{
	register char *last = NULL;
	do {
		if (*cs == c)
			last = cs;
	} while (*++cs);
	return last;
}

/* Continue on page 250 of K&R, 2nd ed */
