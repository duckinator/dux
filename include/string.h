#ifndef __size_t_defined
typedef signed int size_t;
#define __size_t_defined
#endif

void *memcpy(void *dest, void *src, unsigned int count);
void *memset(void *dest, unsigned char val, unsigned int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned int count);
int strlen(const char *str);

