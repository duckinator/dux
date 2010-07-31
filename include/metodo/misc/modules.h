#ifndef MISC_MODULES_H
#define MISC_MODULES_H

#include <string.h>
#include <metodo/metodo.h>

// Kernel modules passed via grub

typedef struct Module_s {
	char *name;
	void *exe;
} Module;

Module *modules;

void *GetModule(const char *name);

#endif /* end of include guard: MISC_MODULES_H */
