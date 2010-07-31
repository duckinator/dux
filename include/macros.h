#ifndef MACROS_H
#define MACROS_H

#define STRING(x) #x
#define MACRO_STRING(x) STRING(x)

#define noreturn __attribute__((noreturn)) void // Specify that a function doesn't return

#endif /* end of include guard: MACROS_H */
