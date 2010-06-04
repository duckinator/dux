#include <lib/krnllib.h>
#include <system.h>

int main(int argc, char const* argv[]);

void _start(void)
{
	clear_screen();
	const char *argv[1] = {
		"user"
	};
	main(1, argv);
	return;
}

int main(int argc, char const* argv[])
{
	printf("Hi!\n%x\n%i\n", 1024, 1024);
	return 0;
}
