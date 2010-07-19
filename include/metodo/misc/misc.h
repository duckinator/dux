#ifndef MISC_H
#define MISC_H

void *memcpy(void *dest, void *src, unsigned int count);
extern void *memset(void *dest, unsigned char val, unsigned int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned int count);
int strlen(const char *str);
#endif /* end of include guard: MISC_H */
