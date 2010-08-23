#include <driver/driver.h>
#include <driver/i386/keyboard/keysym.h>

#define SCANCODE(x) ( (scancode == x) || (scancode == (x + 0x80))) // Does this match either the make or break code?
#define KEYINFO(x) keyinfo->x = x // KEYINFO(foo) is the same as keyinfo->foo=foo;

unsigned char buf[0x1000];
unsigned char *buffer;
unsigned char *origbuffer;
int shift_l = 0;
int shift_r = 0;
int capslock = 0;
int numlock = 0;
int alt_l = 0;
int alt_r = 0;
int ctrl_l = 0;
int ctrl_r = 0;
int escaped = 0;

int vt_visible = 0; // VT 0 is visible

void HalKeyboardHandler(UNUSED struct regs *r)
{
	unsigned int scancode = HalInPort(0x60);

	*++buffer = (unsigned char)scancode;
}

void HalKeyboardLeds(uint8_t status){
	while((HalInPort(0x64)&2)!=0){} //loop until zero
	HalOutPort(0x60,0xED);

	while((HalInPort(0x64)&2)!=0){} //loop until zero
	HalOutPort(0x60,status);
}

int HalKeyboardCapslock()
{
	return capslock;
}

int HalKeyboardNumlock()
{
	return numlock;
}

char HalKeyboardHasInput()
{
	return buffer > origbuffer;
}

HalKeyInfo *HalKeyboardRead()
{
	HalKeyInfo *keyinfo = kmalloc(sizeof(HalKeyInfo));
	int scancode;

	while (buffer <= origbuffer); // wait for input

	scancode = *buffer-- & 0xFF;

	keyinfo->scancode = scancode;
	keyinfo->key = (char)scancode;

	if ( scancode & 0x80 )
		// Released ("Break" code)
		keyinfo->action = 0;
	else
		// Pressed ("Make" code)
		keyinfo->action = 1;

	// Caps lock
	if (SCANCODE(CAPSLOCK))
		capslock = !capslock;

	// Left shift
	if (SCANCODE(SHIFT_LEFT))
		shift_l = keyinfo->action;

	// Right shift
	if (SCANCODE(SHIFT_RIGHT))
		shift_r = keyinfo->action;

	// Alt
	if (SCANCODE(ALT)) {
		if ( escaped )
			alt_r = keyinfo->action;
		else
			alt_l = keyinfo->action;
	}

	// Control
	if (SCANCODE(CONTROL)) {
		if ( escaped )
			ctrl_r = keyinfo->action;
		else
			ctrl_l = keyinfo->action;
	}

	if ( scancode == 0xe0 )
		escaped = 1;
	else
		escaped = 0;

	KEYINFO(shift_l);
	KEYINFO(shift_r);
	KEYINFO(alt_l);
	KEYINFO(alt_r);
	KEYINFO(ctrl_l);
	KEYINFO(ctrl_r);

	return keyinfo;
}

HalKeyInfo *HalKeyboardResolveScancode(HalKeyInfo *keyinfo)
{
	keyinfo->key = keysym_us[keyinfo->scancode & 0x7F];
	return keyinfo;
}
HalKeyInfo *HalKeyboardResolveScancode_shift(HalKeyInfo *keyinfo)
{
	keyinfo->key = keysym_us_shift[keyinfo->scancode & 0x7F];
	return keyinfo;
}

HalKeyInfo *HalKeyboardReadLetter()
{
	HalKeyInfo *keyinfo = kmalloc(sizeof(HalKeyInfo));
	keyinfo = HalKeyboardRead();
	if(keyinfo->shift_l || keyinfo->shift_r) {
		keyinfo = HalKeyboardResolveScancode_shift(keyinfo);
	} else {
		keyinfo = HalKeyboardResolveScancode(keyinfo);
	}
	return keyinfo;
}

void HalKeyboardInit()
{
	HalIrqHandler_Install(1, (void*)HalKeyboardHandler);
	// The compiler is convinced that unsigned char[0x1000] is not an
	// lvalue, so all these hacks are needed to compile.
	buffer = buf;
	origbuffer = buffer;
}

noreturn HalKeyboardTest()
{
	HalKeyInfo *keyinfo;
	printf("Initiating keyboard test...\n");
	while(1)
	{
		if ( HalKeyboardHasInput() ) {
			keyinfo = HalKeyboardReadLetter();
			if ( keyinfo->action == 0 ) {
				printf("%c", keyinfo->key);
			}
		}
	}
}
