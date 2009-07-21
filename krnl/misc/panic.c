//#include <isr.h>
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

void stop_dump_stack(void);

#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)
typedef __builtin_va_list va_list;

char *stop_msg = "A problem has been detected and Dux has been shut down to prevent damage\nto your computer.\n\n";

char *stop_table[9] = {
	(char*)0x01, "ASSERTION_FAILED",
	(char*)0x02, "NO_MULTIBOOT",
	(char*)0x10, "USER_INITIALIZED",
	(char*)0x11, "DUX_SECURITY",
	(char*)0x0
};

char *stop_getmsg(int error)
{
	int i;
	int index;

	/* Loop through the table, stopping at every other entry to see if it
	 * matches. If so, record it. */
	for (i = 0; stop_table[i] != 0x0; i+=2) {
		if ((int)stop_table[i] == error) {
			index = i;
			break;
		}
	}

	return stop_table[index+1];
}

void stop(int error, int argc, ...)
{
	va_list ap;
	int i;
	int arg;

	if (in_panic) {
		/* Something is causing a recursive stop, so
		 * just kill the machine. */
		asm volatile("cli");
		asm volatile("hlt");
	}
	in_panic = 1;

	console_init();
	screen_setattr(0x4f, 0x4f);
	screen_clear();

	printk(stop_msg);
	printk("%s\n\n", stop_getmsg(error));

	printk("STOP: 0x%x (", error);

	/* Print all the arguments. */
	va_start(ap, argc);
	for (i = 0; i < argc; i++) {
		arg = va_arg(ap, unsigned int);
		printk("0x%x, ", arg);
	}

	/* \x08 is backspace, so it doesn't have an extra ", " at the end. */
	if (argc != 0)
		printk("\x08\x08)\n\n");
	else
		printk(")\n\n");

	va_end(ap);

	printk("Stack Dump:\n\n");

	stop_dump_stack();

	asm volatile("cli");
	asm volatile("hlt");
}

void assert_dowork(char *file, int line)
{
	printk("Asserton failed in %s:%d", file, line);
	stop(0x01, 0x2, file, line);
}

struct stack_frame {
	struct stack_frame *next;
	void *addr;

};

unsigned int stack;
void stop_dump_stack(void)
{
	struct stack_frame *frame;

	asm volatile ("movl %%ebp, %0" : "=rm" (frame));

	while ((unsigned int)frame < stack) {
		printk("addr: 0x%x, frame: 0x%x\n", frame->addr, frame);
		frame = frame->next;
	}
}