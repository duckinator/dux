#include <kernel.h>
#include <kernel/hal/mm/frames.h>

static unsigned int *frames;

/* set_frame(addr)
 * Allocates a frame in the frames array. It is assumed to be large enough to
 * hold whatever address you are allocating!
 */
void set_frame(unsigned int addr)
{
	unsigned int frame = addr/0x1000;
	frames[frame/32] |= (unsigned int)0x1<<frame%32;
}

/* clear_frame(addr)
 * Clears a frame in the frames array. It is assumed to be large enough to
 * hold whatever address you are clearing!
 */
void clear_frame(unsigned int addr)
{
	unsigned int frame = addr/0x1000;
	frames[frame/32] &= ~((unsigned int)0x1<<frame%32);
}

/* test_frame(addr)
 * Returns 0 if a frame is free or anything else if a frame is not free. It
 * will not cause data loss if frame is not large enough, but will produce
 * erratic results.
 */
unsigned int test_frame(unsigned int addr)
{
	unsigned int frame = addr/0x1000;
	return frames[frame/32] & ((unsigned int)0x1<<frame%32);
}

unsigned int first_frame()
{
	unsigned int i;

	for (i = 0; i < end_memory; i+=0x1000) {
		if (!test_frame(i)) {
			return i;
		}
	}

	panic((char*)"No free frames.\n");
}

/* alloc_frame(page, is_kernel, is_writable)
 * Obtains a physical frame and allocates it to the page table given.
 */
int alloc_frame(PageTableEntry *page, int is_kernel, int is_writable)
{
	unsigned int addr;

	// Was the frame already allocated?
	if (page->address != 0)
		return -1;

	addr = first_frame();
	set_frame(addr);

	assert((addr>>12) < 1048576); // (addr>>12) < 2^20

	page->present = 1;
	page->user = is_kernel ? 0 : 1;
	page->readwrite = is_writable ? 1 : 0;
	page->address = addr>>12;
	return 0;
}

/* free_frame(page)
 * Clears the allocation on the physical frame
 */
void free_frame(PageTableEntry *page)
{
	clear_frame((unsigned int)page->address<<12);
	page->address = 0x0;
}

/* setup_frames()
 */
void InitMMFrames()
{
	// Memory is assumed to be 16 MB.
	frames = (unsigned int*) kmalloc_int(end_memory/0x1000, 0);
	memset(frames, 0, end_memory/0x1000/8);
}
