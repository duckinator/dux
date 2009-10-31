#include <metodo/metodo.h>

void panic(char *text)
{
	printf("\n\nPANIC: %s\n\n", text);
	CoShutdown(SD_WAIT);
}
