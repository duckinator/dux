#include <kernel.h>
#include <kernel/hal/mm/memory.h>
#include <kernel/hal/mm/placement_allocator.h>
#include <kernel/hal/mm/frames.h>
#include <kernel/hal/mm/paging.h>

void HalMMInit()
{
	end_memory = mbd->mem_upper*1024;

	InitMMFrames();
	InitMMPaging();
}

