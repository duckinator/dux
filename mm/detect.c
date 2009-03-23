#include "detect.h"
#include "frame.h"

void mm_detect_grub(multiboot_info_t *mb_info)
{
	memory_map_t *cur_mmap = (memory_map_t*) mb_info->mmap_addr;
	if (mb_info->flags || 0x40) {
		cur_mmap = (memory_map_t*) mb_info->mmap_addr;

		while ((unsigned int) cur_mmap <
				mb_info->mmap_addr + mb_info->mmap_length) {
			if (cur_mmap->type == 1)
				mm_detect_alloc(cur_mmap->base_addr_low, cur_mmap->length_low);
			cur_mmap = (memory_map_t*) ((unsigned int) cur_mmap +
					cur_mmap->size + sizeof(unsigned int));
		}
	}
}

void mm_detect_alloc(unsigned int base_addr, unsigned int length)
{
	unsigned int i;
	unsigned int cur_addr;

	for (i = 0; i < length/0x1000; i++) {
		cur_addr = base_addr+0x1000*i;
		if (!(cur_addr % 0x1000)) {
			mm_frame_alloc(cur_addr);
		} else {
			printk("error allocating 0x%x\n", cur_addr);
		}
	}
}
