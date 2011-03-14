#ifndef PANIC_H
#define PANIC_H

#include <stdarg.h>

#define STOP_MSG "A problem has been detected and Dux has been shut down to prevent damage\nto your computer.\n\n"

struct stack_frame {
	struct stack_frame *next;
	void *addr; 
};

void panic_dump_hex(unsigned int *stack);
char *stop_getmsg(int error);
void stop_dump_stack(void);
void stack_dump(void);
void register_dump(void);

noreturn _stop(const char *text, int error, const char *function, const char *filename, int line, const char *code);

void panic_setup_stop_table();

/* Stop */
#define stop(error) _stop("", error, __FUNCTION__, __FILE__, __LINE__, "")

/* Assert */
#define assert(a) if (!(a)) _stop("", 0x01, __FUNCTION__, __FILE__, __LINE__, #a)

/* Panic */
#define panic(message) _stop(message, 0, __FUNCTION__, __FILE__, __LINE__, "")
/*
#define STOP_ASSERTION_FAILED     0x01
#define STOP_BAD_BOOTLOADER_MAGIC 0x02
#define STOP_NO_USERLAND          0x03
#define STOP_USERLAND_EXITED      0x04
#define STOP_UNKNOWN              0x10
#define STOP_END_OF_KERNEL        0x11
#define STOP_USER_INITIALIZED     0x12
*/
enum STOP_MESSAGES {
	STOP_ASSERTION_FAILED = 1,
	STOP_CODER_FAILED,
	STOP_BAD_BOOTLOADER_MAGIC,
	STOP_NO_USERLAND,
	STOP_USERLAND_EXITED,
	
	STOP_UNKNOWN,
	STOP_USER_INITIALIZED,
	STOP_END_OF_KERNEL,

	// Add new messages here

	__STOP_NUM_MESSAGES
};

#endif /* end of include guard: PANIC_H */
