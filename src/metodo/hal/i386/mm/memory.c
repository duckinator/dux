#include <system.h>
#include <metodo/metodo.h>
#include <metodo/hal/mm/memory.h>
#include <metodo/misc.h>

extern unsigned int end;
unsigned int placement = 0;

/* malloc(size, flags)
 * Simple placement based allocator. This allocates off the end of the kernel.
 * Potential bugs: This has no bound, and does not check with the final heap allocator
 */
void *kmalloc_int(unsigned int size, unsigned int flags)
{
	unsigned int tmp;

	printf("\n\n&end: %i\n\n", &end);

	// Initialize if needed.
	if (placement == 0)
		placement = &end;

	// Align on a page if needed.
/* The following line was this, but meteger said to invert the bitmask in the check:
 *	if ((flags & MALLOC_ALIGN) && (placement & 0xfffff000)) {
*/
	if ((flags & MALLOC_ALIGN) && (placement & 0x0fff)) {
		placement &= 0xfffff000;
		placement += 0x1000;
	}

	// Return the address of allocation and increment the next placement address to whatever.
	tmp = placement;
	placement += size;
	return (void*) placement;
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
 * will not cause data loss if frame is not large enough, but will produce
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

	for (i = 0; i < end_memory; i+=0x1000) {
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
	clear_frame(page->address<<12);
	page->address = 0x0;
}

PageDirEntry *cur_page_directory;

/* clear_page_directory(page_directory)
 * Clears the page directory given.
 */
void clear_page_directory(PageDirEntry* page_directory)
{
	unsigned int i;
	for (i = 0; i < 1024; i++) {
		page_directory[i].present = 0;
		page_directory[i].readwrite = 1;
		page_directory[i].user = 0;
	}
}

/* idmap_page_table(page_table, address)
 * Identity maps the page table given to address.
 */
void idmap_page_table(PageTableEntry* page_table, unsigned int address)
{
	unsigned int i;
	for (i = 0; i < 1024; i++, address += 0x1000) {
		page_table[i].address = address >> 12;
		page_table[i].present = 1;
		page_table[i].readwrite = 1;
		page_table[i].user = 0;
	}
}

void init_mm()
{
	PageTableEntry* page_table;

	end_memory = mbd->mem_upper*1024;
	
	// Memory is assumed to be 16 MB.
	// TODO: Double check if kmalloc_int(end_memory/0x1000, NULL) is correct. Assumed it's not at the moment
	frames = (unsigned int*) kmalloc_int(end_memory/0x1000, 0);
	memset(frames, 0, end_memory/0x1000/8);

	// Create page directory
	cur_page_directory = (PageDirEntry*) kmalloc_int(sizeof(PageDirEntry)*1024, MALLOC_ALIGN);
	clear_page_directory(cur_page_directory);

	// Create a page table.
	page_table = (PageTableEntry*) kmalloc_int(sizeof(PageTableEntry)*1024, MALLOC_ALIGN);
	idmap_page_table(page_table, 0);

	// Add that page table to the page directory.
	cur_page_directory[0].address = (unsigned int) page_table >> 12;
	cur_page_directory[0].present = 1;
	cur_page_directory[0].readwrite = 1;
	cur_page_directory[0].user = 0;

	// Enable paging.
	asm volatile("mov %0, %%cr3":: "b"(cur_page_directory));
	unsigned int cr0;
	asm volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= 0x80000000;
	asm volatile("mov %0, %%cr0":: "b"(cr0));
}

