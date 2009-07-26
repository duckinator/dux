#include <krnl/stop.h>

void panic(char *text)
{
	KrnlEasyStop(STOP_UNKNOWN);
}

void stop(int error, int argc, ...)
{
	KrnlEasyStop(STOP_UNKNOWN);
}
