#include <system.h>
#include <dux/mm/memory.h>

#define END_MEMORY 0x1000000

extern unsigned int end;
unsigned int placement;

/* malloc(size, flags)
 * Simple placement based allocator. This allocates off the end of the kernel.
 * Potential bugs: This has no bound, and does not check with the final heap allocator
 */
static unsigned int kmalloc_int(unsigned int size, unsigned int flags)
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

/* set_frame(addr)
 * Allocates a frame in the frames array. It is assumed to be large enough to
 * hold whatever address you are allocating!
 */
void set_frame(unsigned int addr)
{
	unsigned int frame = addr/0x1000;
	frames[frame/32] |= 0x1<<frame%32;
}

/* clear_frame(addr)
 * Clears a frame in the frames array. It is assumed to be large enough to
 * hold whatever address you are clearing!
 */
void clear_frame(unsigned int addr)
{
	unsigned int frame = addr/0x1000;
	frames[frame/32] &= ~(0x1<<frame%32);
}

/* test_frame(addr)
 * Returns 0 if a frame is free or anything else if a frame is not free. It
 * will not cause data loss is frames is not large enough, but will produce
 * erratic results.
 */
unsigned int test_frame(unsigned int addr)
{
	unsigned int frame = addr/0x1000;
	return frames[frame/32] & (0x1<<frame%32);
}

unsigned int first_frame()
{
	unsigned int i;

	for (i = 0; i < END_MEMORY; i+=0x1000) {
		if (!test_frame(i)) {
			return i;
		}
	}

	// Control does not reach end in this function, unless you count
	// The infinite loop that panic will enter. So compiler, I have a
	// message for you: "You are stupid."
	panic("No free frames.\n");

	// I also added the extra 7 bytes (on IA-32 anyway) to shut you up:
	return 0;
}

/* alloc_frame(page, is_kernel, is_writable)
 * Obtains a physical frame and allocates it to the page table given.
 */
unsigned int alloc_frame(PageTableEntry *page, int is_kernel, int is_writable)
{
	unsigned int addr;

	// Was the frame already allocated?
	if (page->address != 0)
		return -1;

	addr = first_frame();
	set_frame(addr);

	page->present = 1;
	page->usersupervisor = is_kernel ? 0 : 1;
	page->readwrite = is_writable ? 1 : 0;
	page->address = addr>>12;
	return 0;
}

/* free_frame(page)
 * Clears the allocation on the physical frame
 */
void free_frame(PageTableEntry *page)
{
	clear_frame(page->address<<12);
	page->address = 0x0;
}

void init_mm()
{
	placement = end;

	// Memory is assumed to be 16 MB.
	frames = (unsigned int*) kmalloc_int(END_MEMORY/0x1000, NULL);
	memset(frames, 0, END_MEMORY/0x1000/8);
}
