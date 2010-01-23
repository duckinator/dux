#include <metodo/tests.h>

extern unsigned int start;
extern unsigned int end;

void SystemTests(void *ramdisk)
{
	MemorySizeTest();
	MMTest();
	RamdiskTest(ramdisk);
	KernelSizeTest();
}

void KernelSizeTest()
{
	printf("Kernel size is approximately %i bytes (start: 0x%08x, end: 0x%08x)\n", &end-&start, &start, &end);
}

void MemorySizeTest()
{
	int bytes = mbd->mem_upper*1024;
	char *ext;
	int last;
	int exp = 0;
	while(1) {
		if ( bytes >= 1 ) {
			exp += 3;
			last = bytes;
			bytes /= 1024;
		} else {
			bytes = last;
			exp -= 3;
			break;
		}
	}

	switch(exp) {
	case 0:
		ext = " bytes";
		break;
	case 3:
		ext = "KB";
		break;
	case 6:
		ext = "MB";
		break;
	case 9:
		ext = "GB";
		break;
	}
	printf("We have %d%s of RAM\n", bytes, ext);
}

void MMTest()
{
	printf("Beginning memory management test:\n");
	printf("\tFirst free frame:  %i\n", first_frame());
	printf("\tAllocating frame at %i\n", first_frame());
	set_frame(first_frame(), 1, 1);
	printf("\tFirst free frame is now %i\n", first_frame());
	printf("Finished memory management test\n\n");
}

void RamdiskTest(void *ramdisk)
{
	char *buf = {0};
	int i;
	uint32_t size;
	fs_node_t *fs_root = {0};

	if (ramdisk != NULL) {
		printf("Beginning ramdisk/fs_root test:\n");
		fs_root = initialize_initrd((uint32_t)ramdisk);
		printf ("\tfs_root = 0x%x\n\n", fs_root);

		printf("\tListing contents of initrd:\n");
		i = 0;
		struct dirent *node = 0;
		while ( (node = readdir_fs(fs_root, i)) != 0) {
			if ( strlen(node->name) == 0) {
				printf("\t\tWhy did I find an empty filename?\n");
			} else {
				printf("\t\tFound file: %s\n", node->name);
				fs_node_t *fsnode = finddir_fs(fs_root, node->name);

				printf("fs_root->flags&0x7: 0x%02x\n", fs_root->flags&0x7);
    		if((fsnode->flags&0x7) == FS_DIRECTORY) {
					printf("\t\t\tIt's a directory!\n");
				} else {
					printf("fsnode->flags&0x7: 0x%02x", fsnode->flags&0x7);
					printf("\t\tContents: ");
					//size = read_fs(fsnode, 0, 512, buf);
					printf("%s\n", buf);
				}
			}
			i++;
		}
		printf("Finished ramdisk/fs_root test\n\n");
	}
}
