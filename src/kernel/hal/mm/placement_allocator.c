#include <kernel.h>
#include <kernel/hal/mm/placement_allocator.h>

unsigned int placement = 0;

/* malloc(size, flags)
 * Simple placement based allocator. This allocates off the end of the kernel.
 * Potential bugs: This has no bound, and does not check with the final heap allocator
 */
void *kmalloc_int(unsigned int size, unsigned int flags)
{
	if (placement == 0) // Initialize if needed.
		placement = (unsigned int)end;
	else // Otherwise, increment to next placement address.
		placement += size;

	// Align on a page if needed.
/* The following line was this, but meteger said to invert the bitmask in the check:
 *	if ((flags & MALLOC_ALIGN) && (placement & 0xfffff000)) {
*/
	if ((flags & MALLOC_ALIGN) && ((placement) & 0x0fff)) {
		placement &= 0xfffff000;
		placement += 0x1000;
	}

	return (void*) placement;
}
