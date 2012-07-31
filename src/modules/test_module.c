#include <lib/krnllib.h>
#include <system.h>

void _start(void)
{
	clear_screen();
	
	TestInit();
	return;
}

int TestInit()
{
	printf("This is a test module.\n");
	return 0;
}

