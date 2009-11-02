#include <metodo/misc.h>

//TODO: Figure out where these should go
void *memcpy(void *dest, void *src, unsigned int count)
{
	/* Add code here to copy 'count' bytes of data from 'src' to
	*  'dest', finally return 'dest' */
	char *cdest = (char*) dest;
	char *csrc = (char*) src;
	unsigned int i;
	for (i = 0; i < count; i++) cdest[i] = csrc[i];
	return cdest;
}

void *memset(void *dest, unsigned char val, unsigned int count)
{
	/* Add code here to set 'count' bytes in 'dest' to 'val'.
	*  Again, return 'dest' */
	char *cdest = (char*) dest;
	unsigned int i;
	for (i = 0; i < count; i++) cdest[i] = val;
	return cdest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned int count)
{
	/* Same as above, but this time, we're working with a 16-bit
	*  'val' and dest pointer. Your code can be an exact copy of
	*  the above, provided that your local variables if any, are
	*  unsigned short */
	unsigned int i;
	for (i = 0; i < count; i++) dest[i] = val;
	return dest;
}

int strlen(const char *str)
{
	/* This loops through character array 'str', returning how
	*  many characters it needs to check before it finds a 0.
	*  In simple words, it returns the length in bytes of a string */
	char *cstr = (char*) str;
	int i;
	for (i = 0; cstr[i] != '\0'; i++) {}
	return i;
}

