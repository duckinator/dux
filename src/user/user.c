#include <lib/krnllib.h>
#include <system.h>

void _start(void)
{
	const char *argv[1] = {
		"user"
	};
	main(1, argv);
	while (1)
		;
}

int main(int argc, char const* argv[])
{
     clear_screen();
     puts("So yes. Hi.\n");
     malloc(30,1);

	puthex(1024);
	puts("\n");
	putdec(1024);
	puts("\n");
	puts("ohi");
	return 0;
}
