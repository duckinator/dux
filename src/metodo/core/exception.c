#include <metodo/metodo.h>

void CoException(void)
{
	char *str = "The system crashed. I don't know why.";

	HalDisplayString(str);

	while (1)
		;
}
