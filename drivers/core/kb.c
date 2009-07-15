#include <dux/drivers/core/ports.h>
#include <dux/drivers/core/console.h>

#include <isr.h>

unsigned char buf[0x1000];
unsigned char *buffer;
unsigned char *origbuffer;

static void kb_irq_handler()
{
	unsigned int scancode = inb(0x60);

	*++buffer = scancode;
}

char kb_read()
{
	char tmp;
start:
	if (buffer > origbuffer) {
		tmp = *buffer--;
		return tmp;
	} else {
		// Goto is usually frowned upon, but it is truly the most
		// understandable method here. We could also use a while loop.
		goto start;
	}
}

void kb_init()
{
	HalIrqHandler_Install(1, kb_irq_handler);
	// The compiler is convinced that unsigned char[0x1000] is not an
	// lvalue, so all these hacks are needed to compile.
	buffer = buf;
	origbuffer = buffer;
}
