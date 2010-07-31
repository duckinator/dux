#include <metodo/metodo.h>
#include <system.h>

void stop_dump_stack(void);

#define STOP_MSG "A problem has been detected and Dux has been shut down to prevent damage\nto your computer.\n\n"

#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)
//typedef __builtin_va_list va_list;

struct stack_frame {
	struct stack_frame *next;
	void *addr; 
};
unsigned int stack;

void stack_dump(void);
void register_dump(void);

char *stop_table[7] = {
	(char*)0x01, "ASSERTION_FAILED",
	(char*)0x02, "NO_MULTIBOOT",
	(char*)0x10, "USER_INITIALIZED",
	(char*)0x0
};

int in_panic = 0;

void _panic(char *text, const char *filename, int line)
{
	if (in_panic) {
		/* Something is causing a recursive panic, so
		 * just kill the machine. */
		asm volatile("cli");
		asm volatile("hlt");
	}
	in_panic = 1;
 
	HalInitDisplay();
	HalDisplaySetAttr(0x4f);
	HalDisplayClear();
	printf("\n**** UDUDD ***\n\n%s\n\n", text);
	printf("File: %s\nLine: %d\n\n", filename, line);
	stack_dump();
	asm("cli");
	asm("hlt");
}
 
void panic_dump_hex(unsigned int *stack)
{
	unsigned int orig_stack = (unsigned int) stack;
	printf("\nBecause I stack-traced it!\n");
	while ((unsigned int) stack < ((orig_stack+0x1000) & ~(0x1000-1))) {
		printf("0x%x: 0x%x\n", stack, *stack);
		if ( *stack == 0x0 )
			break;
		stack++;
	}
}

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
	unsigned int arg;

	if (in_panic) {
		/* Something is causing a recursive stop, so
		 * just kill the machine. */
		asm volatile("cli");
		asm volatile("hlt");
	}
	in_panic = 1;

	HalInitDisplay();
	HalDisplaySetAttr(0x4f);
	HalDisplayClear();

	printf(STOP_MSG);
	printf("%s\n\n", stop_getmsg(error));

	printf("STOP: 0x%x (", error);

	/* Print all the arguments. */
	va_start(ap, argc);
	for (i = 0; i < argc; i++) {
		arg = va_arg(ap, unsigned int);
		printf("0x%x, ", arg);
	}

	/* \x08 is backspace, so it doesn't have an extra ", " at the end. */
	if (argc != 0)
		printf("\x08\x08)\n\n");
	else
		printf(")\n\n");

	va_end(ap);

	printf("Stack Dump:\n\n");

	stop_dump_stack();

	asm volatile("cli");
	asm volatile("hlt");
}

void assert_dowork(char *file, int line)
{
	printf("Asserton failed in %s:%d", file, line);
	stop(0x01, 0x2, file, line);
}

void stop_dump_stack(void)
{
	struct stack_frame *frame;
 
	asm volatile ("movl %%ebp, %0" : "=rm" (frame));
 
	while ((unsigned int)frame < stack) {
		printf("addr: 0x%x, frame: 0x%x\n", frame->addr, frame);
		frame = frame->next;
	}
}
