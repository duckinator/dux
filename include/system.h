#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <text.h>
#include <macros.h>
#include <modifiers.h>

/*void sleep();
void usleep();*/

#define assert(a) if (!(a)) assert_dowork(__FILE__, __LINE__)

#endif /* end of include guard: SYSTEM_H */
