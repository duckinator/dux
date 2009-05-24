#include <isr.h>
#include <system.h>

void stack_dump(void);
void register_dump(void);

int in_panic = 0;

void panic(char *text)
{
	if (in_panic) {
		/* Something is causing a recursive panic, so
		 * just kill the machine. */
		asm volatile("cli");
		asm volatile("hlt");
	}
	in_panic = 1;
		
	printk("\nPanic: %s", text);
	stack_dump();
	asm("cli");
	asm("hlt");
}

void panic_dump_hex(unsigned int *stack)
{
	unsigned int orig_stack = (unsigned int) stack;
	printk("\nStack Contents\n");
	while ((unsigned int) stack < ((orig_stack+0x1000) & ~(0x1000-1))) {
		printk("0x%x: 0x%x\n", stack, *stack);
		stack++;
	}
}
