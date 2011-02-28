#include <metodo/metodo.h>

extern unsigned int end;
unsigned int placement = 0;

/* malloc(size, flags)
 * Simple placement based allocator. This allocates off the end of the kernel.
 * Potential bugs: This has no bound, and does not check with the final heap allocator
 */
void *kmalloc_int(unsigned int size, unsigned int flags)
{
	unsigned int tmp;

	// Initialize if needed.
	if (placement == 0)
		placement = end;

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

typedef long Align;

union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

#define NALLOC 4096-sizeof(Header)

void free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1; /* point to block header */
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break; /* freed block at start or end of arena */

	if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) { /* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

/* Maybe it would be better to allocate in more than units of pages? */
static Header *morecore(unsigned nu)
{
	char *cp;
	Header *up;

	if (nu <= NALLOC)
		nu = NALLOC;
	else
		return NULL;

	cp = (void*) first_frame();
	/* first_frame() can't fail. */
	up = (Header *) cp;
	up->s.size = nu;
	free((void *)(up+1));
	return freep;
}

void *kmalloc(unsigned int nbytes)
{
	Header *p, *prevp;
	unsigned nunits;

	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) +1;
	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) { /* big enough */
			if (p->s.size == nunits) /* exactly */
				prevp->s.ptr = p->s.ptr;
			else { /* allocate tail end */
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if (p == freep) /* wrapper around free list */
			if ((p = morecore(nunits)) == NULL)
				return NULL; /* none left */
	}
}

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

	// Control does not reach end in this function, unless you count
	// The infinite loop that panic will enter. So compiler, I have a
	// message for you: "You are stupid."
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
	__asm__ volatile("mov %0, %%cr3":: "b"(cur_page_directory));
	unsigned int cr0;
	__asm__ volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= 0x80000000;
	__asm__ volatile("mov %0, %%cr0":: "b"(cr0));
}

