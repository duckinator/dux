#include <metodo/tests.h>

extern unsigned int start;
extern unsigned int end;

void SystemTests()
{
	MemorySizeTest();
	MMTest();
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
