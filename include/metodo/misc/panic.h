#ifndef PANIC_H
#define PANIC_H

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

void panic_dump_hex(unsigned int *stack);
char *stop_getmsg(int error);
void stop(int error, int argc, ...);
void stop_dump_stack(void);
void stack_dump(void);
void register_dump(void);

void panic_setup_stop_table();

/* Assert */
void assert_dowork(const char *function, const char *file, int line, const char *code);
#define assert(a) if (!(a)) assert_dowork(__FUNCTION__, __FILE__, __LINE__, #a)

/* Panic */
void _panic(char *text, const char *function, const char *filename, int line);
#define panic(message) _panic(message, __FUNCTION__, __FILE__, __LINE__)

#endif /* end of include guard: PANIC_H */
