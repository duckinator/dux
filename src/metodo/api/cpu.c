#include <metodo/metodo.h>
#include <api/cpu.h>

char *CPUBrand()
{
	// FIXME: Dummy CPU API
	char *ret = kmalloc(1);
	return ret;
}

char *CPUShortBrand()
{
	// FIXME: Dummy CPU API
	char *ret = kmalloc(1);
	return ret;
}

char *CPUFamily()
{
	// FIXME: Dummy CPU API
	char *ret = kmalloc(1);
	return ret;
}

char *CPUModel()
{
	// FIXME: Dummy CPU API
	char *ret = kmalloc(1);
	return ret;
}

int CPUCount()
{
	return 0;
}

CPU_features_t *CPUFeatures()
{
	CPU_features_t *ret = kmalloc(sizeof(CPU_features_t));
	return ret;
}

int CPUCacheSize()
{
	return 0;
}

char *CPUSerial()
{
	// FIXME: Dummy CPU API
	char *ret = kmalloc(1);
	return ret;
}
