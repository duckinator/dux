#ifndef CONFIG_H
#define CONFIG_H

/* The following line, if defined, has printf() and friends use memory management.
 * If commented, they will not use memory management at all
 */
//#define PRINTF_USE_MM

/* Interrupt for syscalls:
 *   default is 0x20
 *   used to use 0x80 (got the idea from Linux)
 */
#define IA32_SYSCALL_INTERRUPT 0x20

#endif
