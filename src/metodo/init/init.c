#include <system.h>

#include <metodo/metodo.h>
#include <metodo/stop.h>

#include <metodo/hal/mm/memory.h>

#include <multiboot.h>

#include <buildid.h>
#include <vfs/vfs.h>
#include <initrd/initrd.h>
#include <string.h>

void InInitKernel(uint32_t magic, multiboot_info_t *multiboot)
{
	void *userland = NULL;
	void *ramdisk = NULL;
	fs_node_t *fs_root;
	//char *str = "Metodo " __DATE__ " " __TIME__ " " ARCH " " SCM_REV "\n";

	*mbd = *multiboot;

	HalInit();
	//HalDisplayString(str);

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		KrnlStop(STOP_BAD_MULTIBOOT_SIGNATURE, magic, 0, 0, 0);
	}

	/* mbd->flags */
	int i;
	module_t *module;
	if (mbd->flags>>3&1) {
		module = (module_t*)mbd->mods_addr;
		for (i = 0; i < mbd->mods_count; i++, module++) {
			printf("\nFound module.\n");
			printf("Module name: %s\n", module->string);
			if (strcmp((char*)(module->string), "/System/userland") >= 0){
				userland = (void*) module->mod_start;
				printf("\nUserland located at: 0x%x\n\n", userland);
				//asm("hlt");
			}
			if(strcmp((char*)(module->string), "/System/initrd.img") == 0){
				ramdisk = (void*) module->mod_start;
				printf("\nFound fs_root at: 0x%x\n\n", ramdisk);
			fs_root = initialise_initrd((uint32_t)module->mod_start);
                printf ("fs_root = 0x%x\n\n", fs_root);
			}
		}
	}
	char *panicmsg;
	printf("Beginning memory management test:\n");
	printf("First free frame:  %i\n", first_frame());
	printf("Allocating frame at %i\n", first_frame());
	set_frame(first_frame(), 1, 1);
	printf("First free frame is now %i\n", first_frame());
	printf("Finished memory management test\n\n");
	if (ramdisk != NULL) {
  	printf("Listing contents of initrd:\n");
	  i = 0;
  	struct dirent *node = 0;
  	while ( (node = readdir_fs(fs_root, i)) != 0)
  	{
      if ( strlen(node->name) == 0) {
        printf("Why did I find an empty filename?\n");
      } 
      else {
    		printf("Found file: %s\n", node->name);
    		fs_node_t *fsnode = finddir_fs(fs_root, node->name);

    		if((fsnode->flags&0x7) == FS_DIRECTORY)
    			printf("\tIt's a directory!\n");
  		  else
    		{
    			printf("\tContents: ");
    			char *buf;
    			uint32_t size = read_fs(fsnode, 0, 512, buf);
    			printf("%s\n", buf);
    		}
  		}
  		i++;
  	}
  	printf("fs_root test over\n");
  }

	printf("end_memory: %i (0x%x)\n", end_memory, end_memory);

	printf("mbd: %x; multiboot: %x\n", *mbd, *multiboot);

	/* Initialize pseudo-user mode */
	if (userland != NULL) {
		printf("Loading userland...\n");
		LoadUserland(userland);
		printf("Why yes, that is a black hole that flew out of userland...\n");
	}	else {
		printf("Interesting, no userland");
		//KrnlEasyStop(STOP_NO_USERLAND);
	}
	while(1);
}
