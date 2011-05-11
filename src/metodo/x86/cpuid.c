#include <metodo/x86/cpuid.h>

/* cpuid() and cpuid_string() are from Clicker, which is in the public domain */

/** issue a single request to CPUID. Fits 'intel features', for instance
 *  note that even if only "eax" and "edx" are of interrest, other registers
 *  will be modified by the operation, so we need to tell the compiler about it.
 */
static inline void cpuid(int code, size_t *eax, size_t *ebx, size_t *ecx, size_t *edx) {
  __asm__ volatile("cpuid":"=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx):"0"(code):"ecx","ebx", "ecx", "edx");
}
 
/** issue a complete request, storing general registers output as a string
 */
static inline int cpuid_string(int code, size_t where[4]) {
  int highest;
  __asm__ volatile("cpuid":"=a"(*where),"=b"(*(where+1)),
               "=c"(*(where+2)),"=d"(*(where+3)):"0"(code));
  return highest;
}
