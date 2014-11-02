#include <kernel/init/modules.h>

void *get_module(const char *name)
{
	size_t i;
	for(i=0; i < sizeof(modules); i++) {
		if(strcmp(modules[i].name, (char*)name) == 0) {
			//printf("Loading module: %s\n", name);
			return modules[i].exe;
		}
	}
	return NULL;
}

int register_module_callback(void *callback, const char *name, ...) {
  return 0;
}
