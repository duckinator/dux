#include "detect.h"
#include "frame.h"
#include <system.h>

void mm_detect_alloc(unsigned int base_addr, unsigned int length)
{
	unsigned int i;
	for (i = 0; i < length/0x1000; i++) {
		mm_frame_alloc(base_addr+0x1000*i);
	}
}

void mm_detect_free(unsigned int base_addr, unsigned int length)
{
	unsigned int i;
	for (i = 0; i < length/0x1000; i++) {
		mm_frame_free(base_addr+0x1000*i);
	}
}

void mm_detect_grub(multiboot_info_t *mb_info)
{
	memory_map_t *cur_mmap = (memory_map_t*) mb_info->mmap_addr;

	/* allocate everything */
	mm_detect_alloc(0x0, 0xffffffff);

	if (mb_info->flags || 0x40) {
		cur_mmap = (memory_map_t*) mb_info->mmap_addr;

		while ((unsigned int) cur_mmap <
				mb_info->mmap_addr + mb_info->mmap_length) {
			if (cur_mmap->type == 1) {
				/* subtract one to get length starting from 0 */
				mm_detect_free(cur_mmap->base_addr_low,
						cur_mmap->length_low);
			}
			cur_mmap = (memory_map_t*) ((unsigned int) cur_mmap +
					cur_mmap->size + sizeof(unsigned int));
		}
	}
}
