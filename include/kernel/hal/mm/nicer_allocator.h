#ifndef HAL_MM_NICER_ALLOCATOR
#define HAL_MM_NICER_ALLOCATOR

#include <kernel/hal/mm/frames.h>

typedef long Align;

union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;

#define NALLOC 4096-sizeof(Header)

void *kmalloc(unsigned int nbytes);
void free(void *ap);

#endif /* HAL_MM_NICER_ALLOCATOR */
