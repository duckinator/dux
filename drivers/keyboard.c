#include <system.h>
#include <keyboard.h>
#include <isr.h>
#include <lb.h>

static lb_t *first;

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

void keyboard_handler(struct regs *r)
{
	unsigned char *s;
	unsigned int scancode;

	r=r;

	scancode = inportb(0x60);

	if (scancode & 0x80) { /* a key was released */
		scancode -= 0x80;
	} else { /* a key was pressed */
		s = malloc(1);
		*s = kbdus[scancode];
		lb_add(first, 1, s);
	}
}

char keyboard_getchar()
{
	char c;

	if (first->next != NULL) {
		c = *(first->next->buf);
		free(first->next->buf);
		lb_del(first, first->next);
	} else {
		c = 0;
	}
	return c;
}

unsigned int keyboard_install(void)
{
	first = lb_init();
	irq_install_handler(1, keyboard_handler);
	return 0;
}
