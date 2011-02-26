#include <metodo/init/load_modules.h>

void InitLoadModules()
{
	/* mbd->flags */
	unsigned int i, len;
	module_t *module;
	int current_module = 0;
	modules = (Module*)kmalloc(sizeof(Module) * 1024);
	if (mbd->flags>>3&1) {
		module = (module_t*)mbd->mods_addr;
		printf("We have %i modules.\n", mbd->mods_count);
		for (i = 0; i < mbd->mods_count; i++, module++) {
			printf("Module located at 0x%x-0x%x\n", module->mod_start, module->mod_end);
			printf("Module name: %s\n", (char*)module->string);

			len = sizeof(char) * ((unsigned int)strlen((char*)module->string))+1;
			modules[current_module].name = (char*)kmalloc(len);
			memcpy(modules[current_module].name, (char*)(module->string), len);
			modules[current_module].exe = (void*) module->mod_start;
			printf("Found executable %s at 0x%x\n", modules[current_module].name, modules[current_module].exe);
			current_module++;

			if (strncmp((char*)module->string, (char*)"/Drivers/", 9) == 0) {
				printf("Loading driver: %s\n", (char*)module->string);
				//LoadExe((void*)module->mod_start);
				//while(1){}
			}
		}
	}
}
