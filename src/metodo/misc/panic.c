#include <metodo/metodo.h>

void panic(char *text)
{
	HalInitDisplay();
	HalDisplaySetAttr(0x4f);
	HalDisplayClear();
	printf("PANIC: %s\n\n", text);
	CoShutdown(SD_WAIT);
}
