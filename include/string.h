#include <stddef.h>

#ifndef __STRING_H
#define __STRING_H

#include <stddef.h>

int strlen(const char *str);

char *strcpy(char *s, char *ct);
char *strncpy(char *s, char *ct, int n);

char *strcat(char *s, char *ct);
char *strncat(char *s, char *ct, int n);

int strcmp(char *cs, char *ct);
int strncmp(char *cs, char *ct, int n);

char *strchr(char *cs, int c);
char *strrchr(char *cs, int c);

#endif /* end of include guard: __STRING_H */

