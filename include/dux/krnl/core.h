#ifndef CORE_DY5608B7

#define CORE_DY5608B7

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/* Declare function argument identifiers. */
#define IN
#define OUT

/* Interrupt Priority Level */
typedef uint8_t IPL, *PIPL;

#define IPL_PASSIVE 0x00
#define IPL_HWINTERRUPT 0x01
#define IPL_EXCEPTION 0x02
#define IPL_UNINITIALIZED 0xff

void CoRaiseIpl(IN IPL NewIpl, OUT PIPL OldIpl);
void CoLowerIpl(IN IPL NewIpl);
IPL CoGetIpl(void);

/* Text Formatting */
int snprintf(char *str, size_t size, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int printf(const char *format, ...);
int vsnprintf(char *str, size_t size, const char *format, va_list args);

#endif /* end of include guard: CORE_DY5608B7 */
