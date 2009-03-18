#include <system.h>
#include <isr.h>

int alt = 0; // Alt released
int ctrl = 0; // Ctrl released
int shift_l = 0; // Left Shift released
int shift_r = 0; // Right Shift released
int capslock = 0; // Caps lock off
int vt_visible = 0; // VT 0 is visible

/* KBDUS means US Keyboard Layout. This is a scancode table
*  used to layout a standard US keyboard. I have left some
*  comments in to give you an idea of what key is what, even
*  though I set it's array index to 0. You can change that to
*  whatever you want using a macro, if you wish! */
unsigned char kbdus[128] =
{
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8',		/* 9 */
	'9', '0', '-', '=', '\b',	/* Backspace */
	'\t',				/* Tab */
	'q', 'w', 'e', 'r',		/* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
	0,							/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	'\'', '`',   0,						/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	'm', ',', '.', '/',   0,				/* Right shift */
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',

	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};

unsigned char kbdus_shift[128] =
{
	0,  27, '!', '@', '#', '$', '%', '^', '&', '*',		/* 9 */
	'(', ')', '_', '+', '\b',	/* Backspace */
	'\t',				/* Tab */
	'Q', 'W', 'E', 'R',		/* 19 */
	'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',		/* Enter key */
	0,							/* 29   - Control */
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
	'"', '~',   0,						/* Left shift */
	'|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
	'M', '<', '>', '?',   0,				/* Right shift */
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',

	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};

/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
	r=r;
	unsigned char scancode;

	/* Read from the keyboard's data buffer */
	scancode = inportb(0x60);

	/* If the top bit of the byte we read from the keyboard is
	*  set, that means that a key has just been released */
	if (scancode & 0x80)
	{
		/* You can use this one to see if the user released the
		*  shift, alt, or control keys... */
		puts("KEY RELEASED\n");
		if(scancode == 29) ctrl = 0; // ctrl released
		if(scancode == 56) alt = 0; // alt released
		
		if(scancode == 42) shift_l = 0; // left shift released
		if(scancode == 54) shift_r = 0; // right shift released
	}
	else
	{
		/* Here, a key was just pressed. Please note that if you
		*  hold a key down, you will get repeated key press
		*  interrupts. */

		/* Just to show you how this works, we simply translate
		*  the keyboard scancode into an ASCII value, and then
		*  display it to the screen. You can get creative and
		*  use some flags to see if a shift is pressed and use a
		*  different layout, or you can add another 128 entries
		*  to the above layout to correspond to 'shift' being
		*  held. If shift is held using the larger lookup table,
		*  you would add 128 to the scancode when you look for it */
		if(scancode == 29) ctrl = 1; // ctrl pressed
		if(scancode == 56) alt = 1; // alt pressed
		
		if(scancode == 42) shift_l = 1; // left shift pressed
		if(scancode == 54) shift_r = 1; // right shift pressed
		
		if(scancode == 58 && capslock == 1){
			capslock = 0; // caps lock disabled
		} else {
			capslock = 1; // caps lock enabled
		}
		
		if(scancode == 59){
			// F1 pressed
			vt_visible = 1;
		}
		if(scancode == 60){
			// F2 Pressed
			vt_visible = 2;
		}
		if(scancode == 61){
			// F3 pressed
			vt_visible = 3;
		}
		if(scancode == 62){
			// F4 pressed
			vt_visible = 4;
		}
		if(scancode == 63){
			// F5 pressed
			vt_visible = 5;
		}
		if(scancode == 64){
			// F6 pressed
			vt_visible = 6;
		}
		if(scancode == 65){
			// F7 pressed
			vt_visible = 7;
		}
		if(scancode == 66){
			// F8 pressed
			vt_visible = 8;
		}
		if(scancode == 67){
			// F9 pressed
		}
		if(scancode == 68){
			// F10 pressed
		}
		if(scancode == 87){
			// F11 pressed
		}
		if(scancode == 88){
			// F12 pressed
		}
		if(scancode >= 59 && scancode <= 66){
			monitor_switch_pages(0, vt_visible);
		}
		
		if( (shift_l == 1) || (shift_r == 1) || (capslock == 1) ){
			putch(kbdus_shift[scancode]);
		} else {
			putch(kbdus[scancode]);
		}
		//printk("[%d]", scancode);
	}
}

/* Sets up the keyboard by installing the keyboard handler
*  into IRQ1 */
unsigned int keyboard_install(void)
{
	/* Installs 'keyboard_handler' to IRQ1 */
	irq_install_handler(1, keyboard_handler);
	return 0;
}
