#include <metodo/metodo.h>

#include <buildid.h>

void InInitKernel(void)
{
	char *str = "Metodo " __DATE__ " " __TIME__ " " ARCH " " SCM_REV "\n";

	HalInit();

	HalDisplayString(str);
	
	HalKeyboardInit();
	while(1)
	{
		char character = HalKeyboardResolveScancode(HalKeyboardRead());
		printf("%c", character);
	}
	
	//asm volatile ("int $0");
}
