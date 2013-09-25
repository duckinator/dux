#include <lib/krnllib.h>
#include <system.h>
#include <user/user.h>

void _start(void)
{
	//clear_screen();
	const char *argv[1] = {
		"user"
	};
	main(1, argv);
	return;
}

int main(UNUSED int argc, UNUSED char const* argv[])
{
	/*
	 * argc and argv are only passed to follow C conventions,
	 * but are not required, so we use the "UNUSED ARG FIX" to
	 * make the compilers be nice and not throw warnings about
	 * unused args.
	 */
	printf("Welcome to Dux's useless userland!\n(That really needs to change)\n");

	/*
	 * TODO: Implement APIs mentioned in user/user.c
	 * Unimplemented APIs:
	 *   Keyboard
	 *   Console
	 *   Image
	 *   Display
	 *   Network
	 *   VFS
	 * Pull the following out of the kernel, make more generic:
	 *   Text
	 *   CPU
	 */
	while(1) {
		__asm__ ("hlt");
	}

	return 0;
}
