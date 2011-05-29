#include <metodo/init/tests.h>

void SystemTests()
{
	MemorySizeTest();
	MMTest();
	KernelSizeTest();
	UsedFrameTest();
}

void KernelSizeTest()
{
	printf("Kernel size is approximately %i bytes (start: 0x%08x, end: 0x%08x)\n", &end-&start, &start, &end);
}

void MemorySizeTest()
{
	unsigned long int bytes = mbd->mem_upper*1024;
	char *ext = kmalloc(sizeof(char) * 6);
	unsigned long int last;
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
		strcpy(ext, " bytes");
		break;
	case 3:
		strcpy(ext, "KB");
		break;
	case 6:
		strcpy(ext, "MB");
		break;
	case 9:
		strcpy(ext, "GB");
		break;
	}
	printf("We have %d%s of RAM\n", bytes, ext);
	free(ext);
}

void MMTest()
{
	printf("Beginning memory management test:\n");
	printf("\tFirst free frame:  %i\n", first_frame());
	printf("\tAllocating frame at %i\n", first_frame());
	set_frame(first_frame());
	printf("\tFirst free frame is now %i\n", first_frame());
	printf("Finished memory management test\n\n");
}

void UsedFrameTest()
{
	unsigned int i;
	for(i=0; i < end_memory; i += 0x1000) {
		if(test_frame(i)) {
			printf("Frame %u (%u-%u) is used.\n", i, i, i+0x0111);
		}
	}
}
