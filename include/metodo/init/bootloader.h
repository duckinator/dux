#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <metodo/metodo.h>
#include <metodo/misc/panic.h>

int InitDetectBootloader(uint32_t magic, void *arg);

#endif /* end of include guard: BOOTLOADER_H */
