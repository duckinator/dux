#include <stddef.h>
#include <stdint.h>

#include <dux/mm.h>

uint32_t *frames;
uint32_t nframes;

void MMPhysicalSet(size_t page)
{
	uint32_t frame = page/0x1000;
	frames[frame/(8*4)] |= 0x1 << frame%(8*4);
}

void MMPhysicalUnset(size_t page)
{
	uint32_t frame = page/0x1000;
	frames[frame/(8*4)] &= ~(0x1 << frame%(8*4));
}

uint32_t MMPhysicalCheck(size_t page)
{
	uint32_t frame = page/0x1000;
	return frames[frame/(8*4)] & (0x1 << frame%(8*4));
}

uint32_t MMPhysicalFind(void)
{
	uint32_t i, j;

	for (i = 0; i < nframes/(8*4); i++) {
		if (frames[i] == 0xffffffff) {
			return;
		} else {
			for (j = 0; j < 8*4; j++) {
				if (!MMPhysicalCheck(((i*8*4)+j)*0x1000)) {
					MMPhysicalSet(((i*8*4)+j)*0x1000);
					return ((i*8*4)+j)*0x1000;
				}
			}
		}
	}
}

void MMPageAlloc(struct MMPage *page, int kernel, int write)
{
	uint32_t frame;

	/* Already allocated. */
	if (page->frame != 0) {
		return;
	} else {
		frame = MMPhysicalFind();
		page->present = 1;
		page->write = write ? 1 : 0;
		page->user = kernel ? 0 : 1;
		page->frame = frame/0x1000;
	}
}

void MMPageFree(struct MMPage *page)
{
	uint32_t frame;

	frame = page->frame * 0x1000;
	if (frame == 0) {
		return;
	} else {
		MMPhysicalUnset(frame);
		page->present = 0;
		page->frame = 0;
	}
}
