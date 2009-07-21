#include <dux/drivers/core/ports.h>
#include <dux/drivers/core/console.h>

#include "keysym.h" // Scan codes

#include <isr.h>

unsigned char buf[0x1000];
unsigned char *buffer;
unsigned char *origbuffer;
int shift_l = 0;
int shift_r = 0;
int capslock = 0;
int numlock = 0;
int alt = 0;
int ctrl = 0;

int vt_visible = 0; // VT 0 is visible

static void kb_irq_handler()
{
	unsigned int scancode = inb(0x60);

	*++buffer = scancode;
}

int kb_shift()
{
	return shift_l || shift_r;
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

int kb_ctrl()
{
	return ctrl;
}

char kb_has_input()
{
	return buffer > origbuffer;
}

char kb_read()
{
	int scancode, i;
	
	while (buffer <= origbuffer); // wait for input

	scancode = *origbuffer & 0xFF;
	//printk("\n0x%x\n", scancode);
	
	for (i = 0; i < (buffer - origbuffer); i++)
		origbuffer[i] = origbuffer[i + 1];
	
	buffer--;	
	
	// Left shift
	if (scancode == 0x2A)
		shift_l = 1;
	else if (scancode == 0xAA)
		shift_l = 0;
	
	// Right shift
	if (scancode == 0x36)
		shift_r = 1;
	else if (scancode == 0xB6)
		shift_r = 0;
	
	// Alt
	if (scancode == 0x38)
		alt = 1;
	else if (scancode == 0xB8)
		alt = 0;
	
	// Control
	if (scancode == 0x1D)
		ctrl = 1;
	else if (scancode == 0x9D)
		ctrl = 0;
	
	if (ctrl && alt && (scancode == 0x53))
	{ // Ctrl-Alt-Delete
		stop(0x11, 0x0);
	}
		
	return (char)scancode;
}

char kb_resolve_scancode(int scancode)
{
	return keysym_us[scancode & 0x7F];
}
char kb_resolve_scancode_shift(int scancode)
{
	return keysym_us_shift[scancode & 0x7F];
}

void kb_init()
{
	HalIrqHandler_Install(1, kb_irq_handler);
	// The compiler is convinced that unsigned char[0x1000] is not an
	// lvalue, so all these hacks are needed to compile.
	buffer = buf;
	origbuffer = buffer;
}
