#include <dux/drivers/core/ports.h>
#include <dux/drivers/core/console.h>

#include <isr.h>

unsigned char buf[0x1000];
unsigned char *buffer;
unsigned char *origbuffer;
int shift_l = 0;
int shift_r = 0;
int capslock = 0;
int numlock = 0;
int alt = 0;

static void kb_irq_handler()
{
	unsigned int scancode = inb(0x60);

	*++buffer = scancode;
}

int kb_shift()
{
	if ( shift_l || shift_r )
		return 1;
}

int kb_capslock()
{
	return capslock;
}

int kb_numlock()
{
	return numlock;
}

int kb_alt()
{
	return alt;
}

char kb_read()
{
	char tmp;
start:
	if (buffer > origbuffer) {
		
		// Left shift
		if (tmp == 0x2A)
			shift_l = 1;
		else if (tmp == 0xFFFFFFAA)
			shift_l = 0;
		
		// Right shift
		if (tmp == 0x36)
			shift_r = 1;
		else if (tmp == 0xFFFFFFB6)
			shift_r = 0;
			
		//printk("\n'%x'\n", tmp);
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
