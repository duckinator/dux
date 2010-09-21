#ifndef STDLIB_H
#define STDLIB_H

/* Attempt to be compliant with Single UNIX Specification, Version 4 */

#include <stddef.h>
//#include <limits.h>
//#include <math.h>
//#include <sys/wait.h>

/*
 * We need sys/wait.h to have the following: WNOCHANG, WUNTRACED, WEXITSTATUS,
 * WIFEXITED, WIFSIGNALED, WIFSTOPPED, WSTOPSIG, WTERMSIG
 */

/* These are the same for all machines */
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define NULL ((void*)(0))

// Maximum value returned by rand(), at least 32767
#define RAND_MAX 32767

// MB_CUR_MAX returns value of maximum number of bytes in a character specified by the current locale
//#define MB_CUR_MAX

/* The following should be declared as functions/macros, uncomment as implemented

void _Exit(int);

long a64l(const char *);

void abort(void);
int abs(int);
int atexit(void (*)(void));
double atof(const char *);
int atoi(const char *);
long atol(const char *);
long long atoll(const char *);
void *bsearch(const void *, const void *, size_t, size_t,
int (*)(const void *, const void *));
void *calloc(size_t, size_t);
div_t div(int, int);

double drand48(void);
char *ecvt(double, int, int *restrict, int *restrict); (LEGACY )
double erand48(unsigned short[3]);

void exit(int);

char *fcvt(double, int, int *restrict, int *restrict); (LEGACY )

void free(void *);

char *gcvt(double, int, char *); (LEGACY )

char *getenv(const char *);

int getsubopt(char **, char *const *, char **);
int grantpt(int);
char *initstate(unsigned, char *, size_t);
long jrand48(unsigned short[3]);
char *l64a(long);

long labs(long);

void lcong48(unsigned short[7]);

ldiv_t ldiv(long, long);
long long llabs(long long);
lldiv_t lldiv(long long, long long);

long lrand48(void);
*/
void *malloc(size_t);
/*
int mblen(const char *, size_t);
size_t mbstowcs(wchar_t *restrict, const char *restrict, size_t);
int mbtowc(wchar_t *restrict, const char *restrict, size_t);

char *mktemp(char *); (LEGACY )
int  mkstemp(char *);
long mrand48(void);
long nrand48(unsigned short[3]);


int posix_memalign(void **, size_t, size_t);


int posix_openpt(int);
char *ptsname(int);
int putenv(char *);

void qsort(void *, size_t, size_t, int (*)(const void *,
           const void *));
int rand(void);

int rand_r(unsigned *);


long random(void);

void *realloc(void *, size_t);

char *realpath(const char *restrict, char *restrict);
unsigned short seed48(unsigned short[3]);


int setenv(const char *, const char *, int);


void setkey(const char *);
char *setstate(const char *);

void srand(unsigned);

void srand48(long);
void srandom(unsigned);

double strtod(const char *restrict, char **restrict);
float strtof(const char *restrict, char **restrict);
long strtol(const char *restrict, char **restrict, int);
long double strtold(const char *restrict, char **restrict);
long long strtoll(const char *restrict, char **restrict, int);
unsigned long strtoul(const char *restrict, char **restrict, int);
unsigned long long strtoull(const char *restrict, char **restrict, int);
int system(const char *);

int unlockpt(int);


int unsetenv(const char *);

size_t wcstombs(char *restrict, const wchar_t *restrict, size_t);
int wctomb(char *, wchar_t);

*/

#endif