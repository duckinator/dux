#include <metodo/metodo.h>
#include <metodo/hal/keyboard/keysym.h>

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

void HalKeyboardHandler(struct regs *r)
{
	unsigned int scancode = HalInPort(0x60);

	*++buffer = scancode;
}

void HalKeyboardLeds(uint8_t status){
 	while((HalInPort(0x64)&2)!=0){} //loop until zero
 	HalOutPort(0x60,0xED);

 	while((HalInPort(0x64)&2)!=0){} //loop until zero
 	HalOutPort(0x60,status);
 }

int HalKeyboardShift_l()
{
	return shift_l;
}

int HalKeyboardShift_r()
{
	return shift_r;
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

int HalKeyboardAlt_l()
{
	return alt_l;
}

int HalKeyboardAlt_r()
{
	return alt_r;
}

int HalKeyboardAlt()
{
	return alt_l || alt_r;
}

int HalKeyboardCtrl_l()
{
	return ctrl_l;
}

int HalKeyboardCtrl_r()
{
	return ctrl_r;
}

int HalKeyboardCtrl()
{
	return ctrl_l || ctrl_r;
}

char HalKeyboardHasInput()
{
	return buffer > origbuffer;
}

HalKeyInfo HalKeyboardRead()
{
	HalKeyInfo keyinfo = {0};
	int scancode;

	while (buffer <= origbuffer); // wait for input

	scancode = *buffer-- & 0xFF;

	// Caps lock
	if (scancode == 0xBA) {
		if ( capslock ) {
			capslock = 0;
		} else {
			capslock = 1;
		}
	}

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
	if (scancode == 0x38) {
		if ( escaped ) {
			alt_r = 1;
		} else {
			alt_l = 1;
		}
	} else if (scancode == 0xB8) {
		if ( escaped ) {
			alt_r = 0;
		} else {
			alt_l = 0;
		}
	}

	// Control
	if (scancode == 0x1D) {
		if ( escaped ) {
			ctrl_r = 1;
		} else {
			ctrl_l = 1;
		}
	} else if (scancode == 0x9D) {
		if ( escaped ) {
			ctrl_r = 0;
		} else {
			ctrl_l = 0;
		}
	}

	if ( escaped ) {
		escaped = 0;
	} else if ( scancode == 0xe0 ) {
		escaped = 1;
	}

	if (HalKeyboardCtrl() && HalKeyboardAlt() && (scancode == 0x53))
	{ // Ctrl-Alt-Delete
		panic("User initialized");
	}
	
	if ( scancode & 0x80 ) {
		// Released ("Break" code)
		keyinfo.action = 0;
	} else {
		// Pressed ("Make" code)
		keyinfo.action = 1;
	}
	
	keyinfo.scancode = scancode;
	keyinfo.key = (char)scancode;
	return keyinfo;
}

HalKeyInfo HalKeyboardResolveScancode(HalKeyInfo keyinfo)
{
	keyinfo.key = keysym_us[keyinfo.scancode & 0x7F];
	return keyinfo;
}
HalKeyInfo HalKeyboardResolveScancode_shift(HalKeyInfo keyinfo)
{
	keyinfo.key = keysym_us_shift[keyinfo.scancode & 0x7F];
	return keyinfo;
}

HalKeyInfo HalKeyboardReadLetter()
{
	HalKeyInfo keyinfo = {0};
	keyinfo = HalKeyboardRead();
	if(shift_l || shift_r) {
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

void HalKeyboardTest()
{
	HalKeyInfo keyinfo;
	printf("Initiating keyboard test...\n");
	while(1)
	{
		if ( HalKeyboardHasInput() ) {
			keyinfo = HalKeyboardReadLetter();
			if ( keyinfo.action == 0 ) {
				printf("%c", keyinfo.key);
			}
		}
	}
}
