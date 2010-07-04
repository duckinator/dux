#ifndef MODULES_H
#define MODULES_H

#include <string.h>
#include <metodo/metodo.h>

// Kernel modules passed via grub

typedef struct Module_s {
	char *name;
	void *exe;
} Module;

Module *modules;

void *GetModule(char *name);

#endif
