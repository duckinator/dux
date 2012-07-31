#include <metodo/misc/modules.h>

void *GetModule(const char *name)
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

