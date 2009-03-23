#include "frame.h"
#include <system.h>

static unsigned char table[0x100000];

int mm_frame_state(unsigned int frame_addr)
{
	unsigned int frame = frame_addr/0x1000;
	return (table[frame/8] >> (frame-(frame/8)*8) & 1);
}

void mm_frame_alloc(unsigned int frame_addr)
{
	unsigned int frame = frame_addr/0x1000;
	table[frame/8] |= 0x1 << (frame % 8);
}

void mm_frame_free(unsigned int frame_addr)
{
	unsigned int frame = frame_addr/0x1000;
	table[frame/8] &= ~(0x1 << (frame % 8));
}

unsigned int mm_frame_find()
{
	unsigned int cur_test = 0x0;

	for (; cur_test < 0xffffffff; cur_test += 0x1000) {
		if (!(mm_frame_state(cur_test))) {
			mm_frame_alloc(cur_test);
			return cur_test;
		}
	}

	panic("could not find free frame");
	/* no, compiler, actually control does not reach end of non-void
	 * function because panic is going to stop the system, but just to
	 * satisfy your needs, I'll add 7 extra bytes to the code */
	return 0;
}
