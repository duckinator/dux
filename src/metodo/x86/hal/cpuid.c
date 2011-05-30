#include <metodo/metodo.h>
#include <string.h>
#include <metodo/x86/hal/cpuid.h>

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

size_t HalCPUMaxStandardLevel()
{
	size_t where[4];
	cpuid_string(CPUID_GETVENDORSTRING, where);
	return where[0];
}

char *HalCPUBrand()
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

size_t HalCPUShortBrand()
{
	char *lname = HalCPUBrand();
	size_t ret;

	if ((strcmp(lname, CPUID_VENDOR_OLDAMD) == 0) || (strcmp(lname, CPUID_VENDOR_AMD) == 0)) {
			ret = CPU_VENDOR_AMD;
	} else if (strcmp(lname, CPUID_VENDOR_INTEL) == 0) {
			ret = CPU_VENDOR_INTEL;
	} else if (strcmp(lname, CPUID_VENDOR_VIA) == 0) {
			ret = CPU_VENDOR_VIA;
	} else if ((strcmp(lname, CPUID_VENDOR_OLDTRANSMETA) == 0) ||
	           (strcmp(lname, CPUID_VENDOR_TRANSMETA) == 0)) {
			ret = CPU_VENDOR_TRANSMETA;
	} else if (strcmp(lname, CPUID_VENDOR_CYRIX) == 0) {
			ret = CPU_VENDOR_CYRIX;
	} else if (strcmp(lname, CPUID_VENDOR_CENTAUR) == 0) {
			ret = CPU_VENDOR_CENTAUR;
	} else if (strcmp(lname, CPUID_VENDOR_NEXGEN) == 0) {
			ret = CPU_VENDOR_NEXGEN;
	} else if (strcmp(lname, CPUID_VENDOR_UMC) == 0) {
			ret = CPU_VENDOR_UMC;
	} else if (strcmp(lname, CPUID_VENDOR_SIS) == 0) {
			ret = CPU_VENDOR_SIS;
	} else if (strcmp(lname, CPUID_VENDOR_NSC) == 0) {
			ret = CPU_VENDOR_NSC;
	} else if (strcmp(lname, CPUID_VENDOR_RISE) == 0) {
			ret = CPU_VENDOR_RISE;
	} else {
			ret = CPU_VENDOR_UNKNOWN;
    }
	free(lname);
	return ret;
}

char *HalCPUFamily()
{
	char *tmp = kmalloc(20),
	     *ret;
	size_t len,
	       where[4];

	cpuid_string(CPUID_GETFEATURES, where);
	sprintf(tmp, "%hx", (short)(where[0] >> 8));
	len = strlen(tmp);
	ret = kmalloc(len + 1);
	memset(ret, 0, len + 1);
	strcpy(ret, tmp);
	return ret;
}

char *HalCPUModel()
{
	// FIXME: Dummy CPUID functions
	char *ret = kmalloc(1);
	return ret;
}

size_t HalCPUCount()
{
	size_t where[4];
	uint8_t tmp;

	cpuid_string(CPUID_GETFEATURES, where);
	tmp = (uint8_t)(where[1] >> 16);

	// If it reports 0 processors, assume 1 instead of 0
	if(tmp == 0)
		tmp = 1;
	
	return (size_t)tmp;
}

/*
CPU_features_t *HalCPUFeatures()
{
	CPU_features_t *ret = kmalloc(sizeof(CPU_features_t));
	return ret;
}
*/

size_t HalCPUCacheSize()
{
	// FIXME: Dummy CPUID functions
	if(HalCPUMaxStandardLevel() >= 0x2) {
		// ?
	}
	return 0;
}

size_t HalCPUSerial()
{
	if(HalCPUMaxStandardLevel() >= 0x3) {
		size_t where[4];
		cpuid_string(CPUID_GETSERIAL, where);
		// Is this worthwhile?
		// See http://en.wikipedia.org/wiki/CPUID#EAX.3D3:_Processor_Serial_Number
	}
	return 0;
}
