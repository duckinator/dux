#include <metodo/metodo.h>
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

char *CPUIDBrand()
{
    char *ret = kmalloc(sizeof(char) * 13); // on x86, length is always 13
    size_t where[4];
    cpuid_string(CPUID_GETVENDORSTRING, where);
    sprintf(ret, "%c%c%c%c%c%c%c%c%c%c%c%c",
           (char) where[1], (char) (where[1] >> 8), (char) (where[1] >> 16), (char) (where[1] >> 24),
           (char) where[3], (char) (where[3] >> 8), (char) (where[3] >> 16), (char) (where[3] >> 24),
           (char) where[2], (char) (where[2] >> 8), (char) (where[2] >> 16), (char) (where[2] >> 24));
    return ret;
}

char *CPUIDShortBrand()
{
	// FIXME: Dummy CPUID functions
	char *ret = kmalloc(1);
	return ret;
}

char *CPUIDFamily()
{
	// FIXME: Dummy CPUID functions
	char *ret = kmalloc(1);
	return ret;
}

char *CPUIDModel()
{
	// FIXME: Dummy CPUID functions
	char *ret = kmalloc(1);
	return ret;
}

int CPUIDCount()
{
	return 0;
}

/*
CPU_features_t *CPUIDFeatures()
{
	CPU_features_t *ret = kmalloc(sizeof(CPU_features_t));
	return ret;
}
*/

int CPUIDCacheSize()
{
    // FIXME: Dummy CPUID functions
	return 0;
}

char *CPUIDSerial()
{
	// FIXME: Dummy CPUID functions
	char *ret = kmalloc(1);
	return ret;
}
