#ifndef HAL_MM_PAGING_H
#define HAL_MM_PAGING_H

#include <kernel/hal/mm/placement_allocator.h>

void clear_page_directory(PageDirEntry* page_directory);
void idmap_page_table(PageTableEntry* page_table, unsigned int address);
void InitMMPaging();

#endif /* HAL_MM_PAGING_H */
