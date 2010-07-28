#ifndef INIT_H
#define INIT_H

#include <multiboot.h>

void InitKernel(uint32_t magic, multiboot_info_t *mbd);

extern unsigned int debug_info_start;
extern unsigned int debug_info_end;
extern unsigned int debug_abbrev_start;
extern unsigned int debug_abbrev_end;

#endif /* end of include guard: INIT_H */
