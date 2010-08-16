#include <metodo/core/memory.h>

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
	for (i = 0; i < count; i++) cdest[i] = (char)val;
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

