#include <lib/krnllib.h>
#include <system.h>

void _start(void)
{
	clear_screen();
	const char *argv[1] = {
		"user"
	};
	main(1, argv);
	while (1)
		;
}

int main(int argc, char const* argv[])
{
	printf("Hi!\n%x\n%i", 1024, 1024);
	return 0;
}
