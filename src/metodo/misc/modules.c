#include <metodo/misc/modules.h>

void *GetModule(const char *name)
{
	int i;
	for(i=0; i < sizeof(modules); i++) {
		if(strcmp(modules[i].name, name) == 0) {
		  printf("Loading module %s\n", name);
			return modules[i].exe;
		}
	}
	return NULL;
}

