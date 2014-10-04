#include <kernel.h>
#include <system.h>

unsigned int stack;
int in_panic = 0;

const char *stop_table[__STOP_NUM_MESSAGES] = {
	"Assertion failed",
	"Coder failed",
	"Bad bootloader magic",
	"No userland",
	"Userland exited",
	"Unknown error",
	"User initialized",
	"Reached end of kernel",
};

void panic_dump_hex(unsigned int *stack)
{
	unsigned int orig_stack = (unsigned int) stack;
	printf("\nStack dump:\n");
	while ((unsigned int) stack < ((orig_stack+0x1000) & (unsigned int)(~(0x1000-1)))) {
		printf("0x%x: 0x%x\n", stack, *stack);
		if ( *stack == 0x0 )
			break;
		stack++;
	}
}

char *stop_getmsg(int error)
{
/*	int i;
	int index;
 
	/ * Loop through the table, stopping at every other entry to see if it
	 * matches. If so, record it. * /
	for (i = 0; stop_table[i] != 0x0; i+=2) {
		if ((int)stop_table[i] == error) {
			index = i;
			break;
		}
	}
 
	return (char*)stop_table[index+1];*/
	if (error > __STOP_NUM_MESSAGES)
		error = STOP_CODER_FAILED;
	return (char*)stop_table[error];
}

noreturn _stop(const char *text, int error, const char *function, const char *filename, int line, const char *code)
{

	if (in_panic) {
		/* Something is causing a recursive panic, so
		 * just kill the machine. */
		HalShutdown();
	}
	in_panic = 1;

	DisplayInit();
	DisplaySetAttr(0x4f);
	DisplayClear();

	printf(STOP_MSG);
	if(error == STOP_ASSERTION_FAILED) {
		// Failed assertion
		printf("Assertion failed in %s at %s:%d\n\n", function, filename, line);
		printf("Failed assertion: %s\n\n", code);
	} else if(error == 0) {
		// panic()
		printf("%s\n\n", text);
	} else {
		// Everything else
		printf("STOP: 0x%x (%s)\n\n", error, stop_getmsg(error));
		printf("Function: %s\nFile: %s\nLine: %d\n", function, filename, line);
	}

	stack_dump();

	HalShutdown();

	// Should not get this far
	while(1)
		;
}

