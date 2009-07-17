#ifndef __size_t_defined
typedef signed int size_t;
#define __size_t_defined
#endif

void *memcpy(void *dest, void *src, unsigned int count);
void *memset(void *dest, unsigned char val, unsigned int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned int count);
int strlen(const char *str);

char *strcpy(char *s, char *ct);
char *strncpy(char *s, char *ct, int n);
char *strcat(char *s, char *ct);
char *strncat(char *s, char *ct, int n);
int strcmp(char *cs, char *ct);
int strncmp(char *cs, char *ct, int n);
char *strchr(char *cs, char c);
//char *strrchr(char *cs, char c);
