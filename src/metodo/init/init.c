#include <metodo/metodo.h>
#include <metodo/hal/mm/memory.h>
#include <buildid.h>

void InInitKernel(void)
{
	char *str = "Metodo " __DATE__ " " __TIME__ " " ARCH " " SCM_REV "\n";

	HalInit();

	HalDisplayString(str);
	init_mm();
	printf("First free frame:  %i\n", first_frame());	
	set_frame(first_frame(), 1, 1);
	printf("Allocating frame at %i\n", first_frame());
	printf("First free frame is now %i\n", first_frame());
	HalKeyboardInit();
	HalKeyboardTest();
	//asm volatile ("int $0");
}
