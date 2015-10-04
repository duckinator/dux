#ifndef MATH_H
#define MATH_H

// Values of pi and e truncated to 20 decimal places
#define M_PI 3.14159265358979323846
#define M_E  2.71828182845904523536

/* abs(n): return absolute value of n as a integer */
int abs(int);
/* labs(n): return absolute value of n as a long */
long labs(long);
/* llabs(n): return absolute value of n as a long long */
long long llabs(long long);

/* div(n, d): return struct containing quotient and remainder of n/d -- .quot and .rem are integers */
//div_t div(int, int);
/* ldiv(n, d): return struct containing quotient and remainder of n/d -- .quot and .rem are longs */
//ldiv_t ldiv(long, long);
/* lldiv(n, d): return struct containing quotient and remainder of n/d -- .quot and .rem are long longs */
//lldiv_t lldiv(long long, long long);

#endif

