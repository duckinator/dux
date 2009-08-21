#ifndef CORE_DY5608B7

#define CORE_DY5608B7

/* Interrupt Priority Level */
typedef uint8_t IPL, *PIPL;

#define IPL_PASSIVE 0x00
#define IPL_HWINTERRUPT 0x01
#define IPL_EXCEPTION 0x02
#define IPL_UNINITIALIZED 0xff

void CoRaiseIpl(IN IPL NewIpl, OUT PIPL OldIpl);
void CoLowerIpl(IN IPL NewIpl);
IPL CoGetIpl(void);

/* Shutdown */
#define SD_REBOOT 1
#define SD_OFF 2
#define SD_WAIT 3

void CoShutdown(int mode);

/* Text Formatting */
#define TF_ALTERNATE 1
#define TF_ZEROPAD 2
#define TF_LEFT 4
#define TF_SPACE 8
#define TF_SIGN 16
#define TF_SMALL 32
#define TF_PLUS 64
/*
int m_printn(OUT char *str, IN int maxlen, IN int len, IN int n,
		IN int base, IN int size, IN int flags, IN int precision);
int printf(IN const char *fmt, ...);
int sprintf(OUT char *str, IN const char *fmt, ...);
int snprintf(OUT char *str, IN size_t size, IN const char *fmt, ...);
int vprintf(IN const char *fmt, va_list ap);
int vsprintf(OUT char *str, IN const char *fmt, va_list ap);
int vsnprintf(OUT char *str, IN size_t size, IN const char *fmt,
		IN va_list ap);*/

#endif /* end of include guard: CORE_DY5608B7 */
