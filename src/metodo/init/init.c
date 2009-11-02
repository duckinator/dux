#include <metodo/metodo.h>

#include <buildid.h>

void InInitKernel(void)
{
	char *str = "Metodo " __DATE__ " " __TIME__ " " ARCH " " SCM_REV "\n";

	HalInit();

	HalDisplayString(str);
	
	HalKeyboardTest();
	
	//asm volatile ("int $0");
}
