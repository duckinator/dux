#include <kernel.h>
#include <kernel/hal/mm/memory.h>

void HalMMInit()
{
	end_memory = mbd->mem_upper*1024;

	InitMMFrames();
	InitMMPaging();
}

