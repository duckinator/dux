#ifndef MM_DVWOFTDE

#define MM_DVWOFTDE

#include <stddef.h>
#include <stdint.h>

void MMPhysicalSet(size_t page);
void MMPhysicalUnset(size_t page);
uint32_t MMPhysicalCheck(size_t page);
uint32_t MMPhysicalFind(void);

struct MMPage {
	uint32_t present : 1;
	uint32_t write : 1;
	uint32_t user : 1;
	uint32_t writethrough : 1;
	uint32_t disablecache : 1;
	uint32_t accessed : 1;
	uint32_t dirty : 1;
	uint32_t fourmbpage : 1;
	uint32_t global : 1;
	uint32_t avail : 2;
	uint32_t frame : 20;
};

#endif /* end of include guard: MM_DVWOFTDE */
