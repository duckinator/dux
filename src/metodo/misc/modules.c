#include <metodo/misc/modules.h>

void *GetModule(char *name)
{
	int i;
	printf("name: %s\n",name);
	for(i=0; i < sizeof(modules); i++) {
		if(strcmp(modules[i].name, name) == 0) {
			return modules[i].exe;
		}
	}
	return NULL;
}

