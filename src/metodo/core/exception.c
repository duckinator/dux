#include <metodo/metodo.h>

void CoException(int ss, int gs, int fs, int es, int ds)
{
	char *str = "The system crashed. I don't know why.\n";

	HalDisplayString(str);
	printf("ss: 0x%x\ngs: 0x%x\nfs: 0x%x\nes: 0x%x\nds: 0x%x",
		ss,
		gs,
		fs,
		es,
		ds);

	CoShutdown(SD_WAIT);
}
