#include <isr.h>
extern void puts();
//extern void init_video();

void panic( char * text )
{
	/* init_video(); */
	puts("\nPanic: ");
	puts(text);
	asm("cli");
	asm("hlt");
}
