#include <kernel/init/init.h>

noreturn init_kernel(uint32_t magic, void *arg)
{
	void *userland = NULL;

	mbd = arg; // In kernel.h.

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
		hal_init();
		stop(STOP_BAD_BOOTLOADER_MAGIC);
	}

	mmap_init(mbd);    // Set up memory map first
	hal_init();         // Start HAL (GDT, Display, IDT, etc).
	TestInit();//test_init();        // Configure tests.

	TestRunAll();//test_run_all();      // Run tests.

	InitLoadModules();//load_modules(); // Load all kernel modules

	userland = get_module("/System/userland.exe");

	/* Initialize pseudo-user mode */
	if (userland != NULL) {
		printf("Loading userland...\n");
		//switch_to_user_mode();
		LoadUserland(userland);//load_userland(userland);
		printf("\n\nUserland exited unexpectedly.\n");
		//hal_break();
		stop(STOP_USERLAND_EXITED);
	} else {
		//hal_break();
		stop(STOP_NO_USERLAND);
	}
}
