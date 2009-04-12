#include <system.h>
#include <dux/mm/memory.h>

#define END_MEMORY 0x1000000

extern unsigned int end;
unsigned int placement;

/* malloc(size, flags)
 * Simple placement based allocator. This allocates off the end of the kernel.
 * Potential bugs: This has no bound, and does not check with the final heap allocator
 */
static unsigned int malloc(unsigned int size, unsigned int flags)
{
	unsigned int tmp;

	// Align on a page if needed.
	if ((flags & MALLOC_ALIGN) && (placement & 0xfffff000)) {
		placement &= 0xfffff000;
		placement += 0x1000;
	}

	// Return the address of allocation and increment the next placement address to whatever.
	tmp = placement;
	tmp += size;
	return placement;
}

static unsigned int *frames;

void set_frame(unsigned int addr)
{
	unsigned int frame = addr/0x1000;
	frames[frame/32] |= 0x1<<frame%32;
}

void clear_frame(unsigned int addr)
{
	unsigned int frame = addr/0x1000;
	frames[frame/32] &= ~(0x1<<frame%32);
}

unsigned int test_frame(unsigned int addr)
{
	unsigned int frame = addr/0x1000;
	return frames[frame/32] & (0x1<<frame%32);
}

void init_mm()
{
	placement = end;

	// Memory is assumed to be 16 MB.
	frames = (unsigned int*) malloc(END_MEMORY/0x1000, NULL);
	memset(frames, 0, END_MEMORY/0x1000/8);
}
