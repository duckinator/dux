#ifndef API_CPU_H
#define API_CPU_H

#if defined(DUX_I386) || defined(DUX_AMD64)
	#include <metodo/x86/hal/cpuid.h>
#endif

typedef struct {
	char family[15]; // Brand and such: "Intel P4", "AMD K8", etc
} CPUInfo_t;

typedef struct {
} CPU_features_t;

char *CPUBrand();
char *CPUShortBrand();
char *CPUFamily();
char *CPUModel();
size_t CPUCount();
CPU_features_t *CPUFeatures();
size_t CPUCacheSize();
size_t CPUSerial();

#endif  /* end of include guard: API_CPU_H */
