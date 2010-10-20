#include <system.h>
#include <string.h>

char *strcpy(char *s, char *ct)
{
	do {
		*s = *ct;
		s++;
		ct++;
	} while (*ct != '\0');
	return s;
}

char *strncpy(char *s, char *ct, int n)
{
	register int i;
	for (i = 0; i < n; i++) {
		*s = *ct;
		s++;
		ct++;
	}
	return s;
}

char *strcat(char *s, char *ct)
{
	while (*s++)
		;
	while (*ct != '\0') {
		*s = *ct;
		s++;
		ct++;
	}
	return s;
}

char *strncat(char *s, char *ct, int n)
{
	register int i;
	while (*s++)
		;
	for (i = 0; i < n; i++) {
		*s = *ct;
		s++;
		ct++;
	}
	return s;
}

int strcmp(const char *cs, const char *ct)
{
	do {
		if (*cs == 0 && *ct == 0)
			return 0;
		if (*cs > *ct)
			return *cs - *ct;
		if (*cs < *ct)
			return *cs - *ct;
	} while (*cs++ && *ct++);
	return 0;
}

int strncmp(const char *cs, const char *ct, int n)
{
	register int i = 0;
	do {
		if (i++ < n || *cs == '\0' || *ct == '\0')
			break;
		if (*cs > *ct)
			return *cs - *ct;
		else if (*cs < *ct)
			return *cs - *ct;
	} while (*cs++ && *ct++);
	return 0;
}

char *strchr(char *cs, int c)
{
	do {
		if (*cs == c)
			return cs;
	} while (*++cs);
	return NULL;
}

char *strrchr(char *cs, int c)
{
	register char *last = NULL;
	do {
		if (*cs == c)
			last = cs;
	} while (*++cs);
	return last;
}

int strlen(const char *str)
{
	/* This loops through character array 'str', returning how
	*  many characters it needs to check before it finds a 0.
	*  In simple words, it returns the length in bytes of a string */
	char *cstr = (char*) str;
	int i;
	for (i = 0; cstr[i] != '\0'; i++) {}
	return i;
}

/* Continue on page 250 of K&R, 2nd ed */
