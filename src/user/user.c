#include <lib/krnllib.h>
#include <system.h>

void _start(void)
{
	clear_screen();
	puts("Hi from userland");
	const char *argv[1] = {
		"user"
	};
	main(1, argv);
	while (1)
		;
}

int main(int argc, char const* argv[])
{
     shutdown();
	clear_screen();
	puthex(1024);
	puts("\n");
	putdec(1024);
	puts("\n");
	puts("ohi");
	return 0;
}
