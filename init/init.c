#include <system.h>

extern void timer_install();
extern void isr_install();
extern void irq_install();
extern void gdt_install();
extern void keyboard_install();
extern void detect_floppy_drives();
extern unsigned char floppy_read_cmd();

void *NULL = 0x0;

char *freebase = (char*) 0x400000; // 4 MB
char *freeend = (char*) 0x500000; // 5 MB
void *malloc(int size)
{
	if ((freebase + size) > freeend) {
		return NULL;
	} else {
		freebase = freebase + size;
		return freebase - size;
	}
	return NULL;
}

void *memcpy(void *dest, void *src, unsigned int count)
{
	/* Add code here to copy 'count' bytes of data from 'src' to
	*  'dest', finally return 'dest' */
	char *cdest = (char*) dest;
	char *csrc = (char*) src;
	unsigned int i;
	for (i = 0; i < count; i++) cdest[i] = csrc[i];
	return cdest;
}

void *memset(void *dest, unsigned char val, unsigned int count)
{
	/* Add code here to set 'count' bytes in 'dest' to 'val'.
	*  Again, return 'dest' */
	char *cdest = (char*) dest;
	unsigned int i;
	for (i = 0; i < count; i++) cdest[i] = val;
	return cdest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, unsigned int count)
{
	/* Same as above, but this time, we're working with a 16-bit
	*  'val' and dest pointer. Your code can be an exact copy of
	*  the above, provided that your local variables if any, are
	*  unsigned short */
	unsigned int i;
	for (i = 0; i < count; i++) dest[i] = val;
	return dest;
}

int strlen(const char *str)
{
	/* This loops through character array 'str', returning how
	*  many characters it needs to check before it finds a 0.
	*  In simple words, it returns the length in bytes of a string */
	char *cstr = (char*) str;
	int i;
	for (i = 0; cstr[i] != '\0'; i++) {}
	return i;
}

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}


void timer_phase(int hz)
{
    int divisor = 1193180 / hz;       /* Calculate our divisor */
    outportb(0x43, 0x36);             /* Set our command byte 0x36 */
    outportb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    outportb(0x40, divisor >> 8);     /* Set high byte of divisor */
}

void prompt(char *prompt){
	puts(prompt);
}

/* Main loop! */
void kmain(void* mb_info)
{
	timer_phase(100); /* 100Hz timer */
	timer_install();
	isr_install();
	irq_install();
	//gdt_install();
	keyboard_install();
	__asm__ __volatile__ ("sti"); 
	settextcolor(0xf, 0x1);
	init_video();

	puts("TEST!\n");
	//detect_floppy_drives(); 
	//putch(floppy_read_data(0x3f0));
	outportb(0x60, 0xED);
	/*outportb(0x60, 0x00);*/

	for(;;) asm("hlt"); /* Until we get processes/threads/multitasking working... */
}
