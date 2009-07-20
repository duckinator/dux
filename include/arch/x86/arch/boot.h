#ifndef BOOT_LXW94HGB

#define BOOT_LXW94HGB

#include <stdint.h>

typedef struct mboot_t {
	uint32_t magic;
	uint32_t flags;
	uint32_t check;
} mboot_t;

/* Surpress warnings about alignment issues. */
mboot_t *_mboot __attribute__((aligned(1)));
void _start();
void _halt();
uint32_t *_stacksize;
void *_stack;

#endif /* end of include guard: BOOT_LXW94HGB */
