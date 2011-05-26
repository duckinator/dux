#include <metodo/metodo.h>
#include <api/cpu.h>

char *CPUBrand()
{
	return CPUIDBrand();
}

char *CPUShortBrand()
{
	return CPUIDShortBrand();
}

char *CPUFamily()
{
	return CPUIDFamily();
}

char *CPUModel()
{
	return CPUIDModel();
}

int CPUCount()
{
	return CPUIDCount();
}

CPU_features_t *CPUFeatures()
{
	CPU_features_t *ret = kmalloc(sizeof(CPU_features_t));
	return ret;
}

int CPUCacheSize()
{
	return CPUIDCacheSize();
}

char *CPUSerial()
{
	return CPUIDSerial();
}
