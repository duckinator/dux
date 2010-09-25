#include <math.h>

/* abs(n): return absolute value of n as a integer */
int abs(int n)
{
  if (n >= 0)
    return n;
  else
    return -n;
}

/* labs(n): return absolute value of n as a long */
long labs(long n)
{
  if (n >= 0)
    return n;
  else
    return -n;
}

/* llabs(n): return absolute value of n as a long long */
long long llabs(long long n)
{
  if (n >= 0)
    return n;
  else
    return -n;
}

/* div(n, d): return struct containing quotient and remainder of n/d -- .quot and .rem are integers */
//div_t div(int, int);
/* ldiv(n, d): return struct containing quotient and remainder of n/d -- .quot and .rem are longs */
//ldiv_t ldiv(long, long);
/* lldiv(n, d): return struct containing quotient and remainder of n/d -- .quot and .rem are long longs */
//lldiv_t lldiv(long long, long long);