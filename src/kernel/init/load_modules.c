#include <init/elfloader.h>
#include <init/load_modules.h>

void InitLoadModules()
{
	/* mbd->flags */
	unsigned int i, len;
	module_t *module;
	int current_module = 0;
	modules = (Module*)kmalloc(sizeof(Module) * 1024);
	void *module_ptr = NULL;

	if (mbd->flags>>3&1) {
		module = (module_t*)mbd->mods_addr;
		printf("Found %i modules.\n", mbd->mods_count);
		for (i = 0; i < mbd->mods_count; i++, module++) {
      if(module->mod_start == 0x0 && module->mod_end == 0x0) {
        // If we get here, it's not really a module.
        current_module++;
        
        if(current_module >= 5) {
          // Arbitrary number. Give up to avoid an endless loop.
          printf("BUG: Found 5 modules at 0x0-0x0.\n");
          printf("Giving up on loading modules.\n");
          return;
        } else {
          printf("BUG: Found module at 0x0-0x0.\n");
          continue;
        }
      }
      
			//printf("Module located at 0x%x-0x%x\n", module->mod_start, module->mod_end);
			//printf("Module name: %s\n", (char*)module->string);

			printf("Found module: %s\n", (char*)module->string);
			len = sizeof(char) * ((unsigned int)strlen((char*)module->string))+1;
			modules[current_module].name = (char*)kmalloc(len);
			memcpy(modules[current_module].name, (char*)(module->string), len);
			modules[current_module].exe = (void*) module->mod_start;
			//printf("Found module %s at 0x%x\n", modules[current_module].name, modules[current_module].exe);
			current_module++;

			module_ptr = get_module((char*)(module->string));

			if (module_ptr != NULL && (strncmp((char*)(module->string), "/Modules/", 10) == 0)) {
				printf("Initalizing %s...\n", (char*)(module->string));
				LoadExe(module_ptr);
			}
		}
	}
}
