#include <dux/drivers/core/console.h>
#include <dux/drivers/core/screen.h>
#include <dux/shutdown.h>

void DuxShutdown(void)
{
	console_init();
	screen_setattr(0x1f, 0x1f);
	screen_clear();
	printk("Shutting down...\n");
	printk("It is now safe to turn off your computer.\n");
	while (1);
}
