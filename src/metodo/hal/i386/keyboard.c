#include <metodo/hal/hal.h>
#include <metodo/metodo.h>
#include <metodo/hal/i386.h>
#include <metodo/hal/isr.h>
#include <metodo/hal/keyboard/keyboard.h>
 
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
 
void HalKeyboardHandler(struct regs *r)
{
	//printf("In HalKeyboardHandler()\n");
	unsigned int scancode = HalInPort(0x60);
 
	*++buffer = scancode;
}
 
int HalKeyboardShift()
{
	return shift_l || shift_r;
}
 
int HalKeyboardCapslock()
{
	return capslock;
}
 
int HalKeyboardNumlock()
{
	return numlock;
}
 
int HalKeyboardAlt()
{
	return alt;
}
 
int HalKeyboardCtrl()
{
	return ctrl;
}
 
char HalKeyboardHasInput()
{
	return buffer > origbuffer;
}
 
char HalKeyboardRead()
{
	int scancode;
 
	while (buffer <= origbuffer); // wait for input
 
	scancode = *buffer-- & 0xFF;
	//printk("\n'%x'\n", scancode);
 
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
		panic("User initialized");
	}
 
	return (char)scancode;
}
 
char HalKeyboardResolveScancode(int scancode)
{
	return keysym_us[scancode & 0x7F];
}
char HalKeyboardResolveScancode_shift(int scancode)
{
	return keysym_us_shift[scancode & 0x7F];
}
 
void HalKeyboardInit()
{
	HalIrqHandler_Install(1, (void*)HalKeyboardHandler);
	// The compiler is convinced that unsigned char[0x1000] is not an
	// lvalue, so all these hacks are needed to compile.
	buffer = buf;
	origbuffer = buffer;
}

void HalKeyboardTest()
{
	printf("Initiating keyboard test...\n");
	while(1) {
		if ( HalKeyboardHasInput() ) {
			printf("\nHalKeyboardRead(): '%s'\n", HalKeyboardRead());
		}
	}
}
