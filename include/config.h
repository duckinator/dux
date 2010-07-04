#ifndef CONFIG_H
#define CONFIG_H

/* The following line, if defined, has printf() and friends use memory management.
 * If commented, they will not use memory management at all
 */
//#define PRINTF_USE_MM

/* Interrupt for syscalls:
 *   default is 0x2F
 *   used to use 0x80 (got the idea from Linux)
 * This must also be changed in HalIsrSyscall - line 15 in
 * src/metodo/hal/i386/exceptions.asm
 *
 * Why the syscall interrupt is 0x2F:
 *   - 0x00 through 0x1F are exceptions
 *   - 0x20 through 0x2E are IRQs
 *   this leaves 0x2F through 0xFF (0xFF being the last interrupt)
 */
#define IA32_SYSCALL_INTERRUPT 0x2F

#endif
