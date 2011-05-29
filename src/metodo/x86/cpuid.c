#include <metodo/metodo.h>
#include <string.h>
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

size_t CPUIDMaxStandardLevel()
{
	size_t where[4];
	cpuid_string(CPUID_GETVENDORSTRING, where);
	return where[0];
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
	char *tmp = kmalloc(sizeof(char) * 13);
	char *lname = CPUIDBrand();
	char *ret;
	unsigned int size;

	memset(tmp, 0, sizeof(char)*13);

	if ((strcmp(lname, CPUID_VENDOR_OLDAMD) == 0) || (strcmp(lname, CPUID_VENDOR_AMD) == 0)) {
			strcpy(tmp, "AMD");
	} else if (strcmp(lname, CPUID_VENDOR_INTEL) == 0) {
			strcpy(tmp, "Intel");
	} else if (strcmp(lname, CPUID_VENDOR_VIA) == 0) {
			strcpy(tmp, "Via");
	} else if ((strcmp(lname, CPUID_VENDOR_OLDTRANSMETA) == 0) ||
	           (strcmp(lname, CPUID_VENDOR_TRANSMETA) == 0)) {
			strcpy(tmp, "Transmeta");
	} else if (strcmp(lname, CPUID_VENDOR_CYRIX) == 0) {
			strcpy(tmp, "Cyrix");
	} else if (strcmp(lname, CPUID_VENDOR_CENTAUR) == 0) {
			strcpy(tmp, "Centaur");
	} else if (strcmp(lname, CPUID_VENDOR_NEXGEN) == 0) {
			strcpy(tmp, "NexGen");
	} else if (strcmp(lname, CPUID_VENDOR_UMC) == 0) {
			strcpy(tmp, "UMC");
	} else if (strcmp(lname, CPUID_VENDOR_SIS) == 0) {
			strcpy(tmp, "SIS");
	} else if (strcmp(lname, CPUID_VENDOR_NSC) == 0) {
			strcpy(tmp, "NSC");
	} else if (strcmp(lname, CPUID_VENDOR_RISE) == 0) {
			strcpy(tmp, "Rise");
	} else {
			// Falls back to returning the full brand name.
			free(tmp);
			free(lname);
			return CPUIDBrand();
    }
	size = sizeof(char) * ((unsigned int)strlen(tmp) + 1);
	ret = kmalloc(size);
	memset(ret, 0, size);
	strcpy(ret, tmp);
	free(tmp);
	free(lname);
	return ret;
}

char *CPUIDFamily()
{
	// FIXME: Dummy CPUID functions
	char *ret = kmalloc(1);
	size_t where[4];
	cpuid_string(CPUID_GETFEATURES, where);
	return ret;
}

char *CPUIDModel()
{
	// FIXME: Dummy CPUID functions
	char *ret = kmalloc(1);
	return ret;
}

size_t CPUIDCount()
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

size_t CPUIDCacheSize()
{
	// FIXME: Dummy CPUID functions
	if(CPUIDMaxStandardLevel() >= 0x2) {
		// ?
	}
	return 0;
}

size_t CPUIDSerial()
{
	if(CPUIDMaxStandardLevel() >= 0x3) {
		size_t where[4];
		cpuid_string(CPUID_GETSERIAL, where);
		// Is this worthwhile?
		// See http://en.wikipedia.org/wiki/CPUID#EAX.3D3:_Processor_Serial_Number
	}
	return 0;
}
