#include <lib/krnllib.h>
#include <system.h>
#include <user/user.h>

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
	/*
	 * argc and argv are only passed to follow C conventions,
	 * but are not required, so we use the "UNUSED ARG FIX" to
	 * make the compilers be nice and not throw warnings about
	 * unused args.
	 */
	argc = argc; // UNUSED ARG FIX
	argv = argv; // UNUSED ARG FIX
	printf("Hi!\n%x\n%i\n", 1024, 1024);
	return 0;
}
