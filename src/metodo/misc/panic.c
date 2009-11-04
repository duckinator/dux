#include <metodo/metodo.h>

void panic(char *text)
{
	HalInitDisplay();
	HalDisplaySetAttr(0x4f);
	HalDisplayClear();
	printf("Dux quacked!\n%s\n\n", text);
	CoShutdown(SD_WAIT);
}
