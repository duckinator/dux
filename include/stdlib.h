#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>
//#include <limits.h>
//#include <math.h>
//#include <sys/wait.h>

/* These are the same for all machines */
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define NULL ((void*)(0))

/* atexit(fn): run fn() at exit */
//int atexit(void (*)(void));
/* exit(n): exit with status code of n */
//void exit(int);

void *malloc(size_t);
//void *calloc(size_t, size_t);
//void *realloc(void *, size_t);
void free(void *);


/* Char array to number conversion */

/* atof(str): return a double containing the numeric equivalent of str */
//double atof(const char *);
/* atoi(str): return an integer containing the numeric equivalent of str */
//int atoi(const char *);
/* atol(str): return a long containing the numeric equivalent of str */
//long atol(const char *);
/* atoll(str): return a long long containing the numeric equivalent of str */
//long long atoll(const char *);

/* String to number conversion */

//double strtod(const char *, char **);
//float strtof(const char *, char **);
//long strtol(const char *, char **, int);
//long double strtold(const char *, char **);
//long long strtoll(const char *, char **, int);
//unsigned long strtoul(const char *, char **, int);
//unsigned long long strtoull(const char *, char **, int);

#endif /* end of include guard: STDLIB_H */

