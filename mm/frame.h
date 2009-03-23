#ifndef MM_FRAME_H
#define MM_FRAME_H

int mm_frame_state(unsigned int frame_addr);
void mm_frame_alloc(unsigned int frame_addr);
void mm_frame_free(unsigned int frame_addr);
unsigned int mm_frame_find();

#endif
