#ifndef API_CPU_H
#define API_CPU_H

#include <system.h>
#include <string.h>

enum {
	CPU_VENDOR_UNKNOWN = 0,
	CPU_VENDOR_AMD,
	CPU_VENDOR_INTEL,
	CPU_VENDOR_VIA,
	CPU_VENDOR_TRANSMETA,
	CPU_VENDOR_CYRIX,
	CPU_VENDOR_CENTAUR,
	CPU_VENDOR_NEXGEN,
	CPU_VENDOR_UMC,
	CPU_VENDOR_SIS,
	CPU_VENDOR_NSC,
	CPU_VENDOR_RISE,
};

typedef struct {
	char family[15]; // Brand and such: "Intel P4", "AMD K8", etc
} CPUInfo_t;

typedef struct {
} CPU_features_t;

char *CPUBrand();
size_t CPUShortBrand();
char *CPUShortBrandString();
char *CPUFamily();
char *CPUModel();
size_t CPUCount();
CPU_features_t *CPUFeatures();
size_t CPUCacheSize();
size_t CPUSerial();

#endif  /* end of include guard: API_CPU_H */
