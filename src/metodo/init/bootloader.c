#include <metodo/init/bootloader.h>

int InitDetectBootloader(uint32_t magic, void *arg)
{
	switch(magic) {
		case MULTIBOOT_BOOTLOADER_MAGIC:
			mbd = arg;
			bootloader = BOOTLOADER_MULTIBOOT;
			break;
		case BEEF_BOOTLOADER_MAGIC:
			bootloader = BOOTLOADER_BEEF;
			mbd = NULL;

			HalInit();
			panic("Successfully booted with beef. No clue what to do now.");
		default:
			HalInit();
			stop(STOP_BAD_BOOTLOADER_MAGIC);
	}
	return bootloader;
}
