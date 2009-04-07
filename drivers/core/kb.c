#include <dux/drivers/core/ports.h>
#include <dux/drivers/core/console.h>

#include <isr.h>

static void kb_irq_handler()
{
	unsigned int scancode = inb(0x60);
	console_writeb(scancode);
}

void kb_init()
{
	irq_install_handler(1, kb_irq_handler);
}
