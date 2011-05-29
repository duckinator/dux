#include <metodo/metodo.h>
#include <api/cpu.h>

#if defined(DUX_X86_32) || defined(DUX_X86_64)
	#include <metodo/x86/hal/cpuid.h>
#endif

char *CPUBrand()
{
	return HalCPUBrand();
}

unsigned int CPUShortBrand()
{
	return HalCPUShortBrand();
}

char *CPUShortBrandString()
{
	char *ret,
	     *brand_str = kmalloc(13);
	unsigned int len,
	             brand_num = CPUShortBrand();

	memset(brand_str, 0, 13);

	switch(brand_num) {
	case CPU_VENDOR_UNKNOWN:
		strcpy(brand_str, "Unknown");
		break;
	case CPU_VENDOR_AMD:
		strcpy(brand_str, "AMD");
		break;
	case CPU_VENDOR_INTEL:
		strcpy(brand_str, "Intel");
		break;
	case CPU_VENDOR_VIA:
		strcpy(brand_str, "VIA");
		break;
	case CPU_VENDOR_TRANSMETA:
		strcpy(brand_str, "Transmeta");
		break;
	case CPU_VENDOR_CYRIX:
		strcpy(brand_str, "Cyrix");
		break;
	case CPU_VENDOR_CENTAUR:
		strcpy(brand_str, "Centaur");
		break;
	case CPU_VENDOR_NEXGEN:
		strcpy(brand_str, "NexGen");
		break;
	case CPU_VENDOR_UMC:
		strcpy(brand_str, "UMC");
		break;
	case CPU_VENDOR_SIS:
		strcpy(brand_str, "SiS");
		break;
	case CPU_VENDOR_NSC:
		strcpy(brand_str, "NSC");
		break;
	case CPU_VENDOR_RISE:
		strcpy(brand_str, "Rise");
		break;
	}
	len = strlen(brand_str);
	ret = kmalloc(len + 1);
	memset(ret, 0, len + 1);
	strcpy(ret, brand_str);
	free(brand_str);
	return ret;
}

char *CPUFamily()
{
	return HalCPUFamily();
}

char *CPUModel()
{
	return HalCPUModel();
}

size_t CPUCount()
{
	return HalCPUCount();
}

CPU_features_t *CPUFeatures()
{
	CPU_features_t *ret = kmalloc(sizeof(CPU_features_t));
	return ret;
}

size_t CPUCacheSize()
{
	return HalCPUCacheSize();
}

size_t CPUSerial()
{
	return HalCPUSerial();
}
