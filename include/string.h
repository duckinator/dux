#include <stddef.h>

#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

extern int strlen(const char *str);

extern char *strcpy(char *s, char *ct);
extern char *strncpy(char *s, char *ct, int n);

extern char *strcat(char *s, char *ct);
extern char *strncat(char *s, char *ct, int n);

extern int strcmp(char *cs, char *ct);
extern int strncmp(char *cs, char *ct, int n);

extern char *strchr(char *cs, int c);
extern char *strrchr(char *cs, int c);

#endif /* end of include guard: __STRING_H */

