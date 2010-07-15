#ifndef INIT_H
#define INIT_H

#include <multiboot.h>

void InitKernel(uint32_t magic, multiboot_info_t *mbd);

#endif /* end of include guard: INIT_H */
