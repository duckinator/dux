#ifndef HAL_MM_MEMORY_H
#define HAL_MM_MEMORY_H

#include <stdlib.h>

typedef struct {
	unsigned int present : 1;
	unsigned int readwrite : 1;
	unsigned int user : 1;
	unsigned int writethrough : 1;
	unsigned int cachedisable : 1;
	unsigned int accessed : 1;
	unsigned int dirty : 1;
	unsigned int attributeindex : 1;
	unsigned int global : 1;
	unsigned int reserved : 3;
	unsigned int address : 20;
} PageTableEntry;

typedef struct {
	unsigned int present : 1;
	unsigned int readwrite : 1;
	unsigned int user : 1;
	unsigned int writethrough : 1;
	unsigned int cachedisable : 1;
	unsigned int accessed : 1;
	unsigned int available : 1;
	unsigned int pagesize : 1;
	unsigned int global : 1;
	unsigned int reserved : 3;
	unsigned int address : 20;
} PageDirEntry;

#define MALLOC_ALIGN 1

#include <kernel/hal/mm/placement_allocator.h>
#include <kernel/hal/mm/nicer_allocator.h>
#include <kernel/hal/mm/frames.h>
#include <kernel/hal/mm/paging.h>

void *kmalloc_int(unsigned int size, unsigned int flags);
void *kmalloc(unsigned int nbytes);

void HalMMInit();
unsigned int test_frame(unsigned int addr);
void set_frame(unsigned int addr);
unsigned int first_frame();

unsigned int end_memory;

#endif /* HAL_MM_MEMORY_H */
