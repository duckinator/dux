#ifndef MISC_MODULES_H
#define MISC_MODULES_H

#include <string.h>
#include <kernel.h>

// Kernel modules passed via grub

typedef struct Module_s {
	char *name;
	void *exe;
} Module;

Module *modules;

void *get_module(const char *name);
int register_module_callback(void *callback, const char *name, ...);

#endif /* end of include guard: MISC_MODULES_H */
