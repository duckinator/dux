#ifndef MODIFIERS_H
#define MODIFIERS_H

/* Define pseudo argument modifiers. */
#define IN
#define OUT
#define OPTIONAL
#define NOTHING

/* Define function modifiers. */
#define DEPRECATED __attribute__((deprecated))

#define noreturn __attribute__((noreturn)) void // Specify that a function doesn't return

/* Define argument modifiers */
#define UNUSED __attribute__((unused))

#endif /* end of include guard: MODIFIERS_H */
