#include <kernel.h>
#include <kernel/init/memory_map.h>

void mmap_init(void *arg)
{
	int i;
	memory_map_t *mmap;
	memory_map_t *first_empty_mmap;

	mmap = (memory_map_t*)mbd->mmap_addr;
	first_empty_mmap = (memory_map_t*)(mbd->mmap_addr + mbd->mmap_length);

	for (i = 0; mmap < first_empty_mmap; i++, mmap++)
		mmaps[i] = mmap;

	for (i++, mmap++; i < 100; i++, mmap++)
		mmaps[i] = NULL;
}

void mmap_print() {
	int i;
	printf("Memory map:\n");
	printf("\
          |      base addr      |       length\n\
   size   |   low    |   high   |   low    |   high   |   type\n");
	for (i = 0; mmaps[i] != NULL; i++) {
		printf(" %8x | %8x | %8x | %8x | %8x | %8x\n",
		mmaps[i]->size, mmaps[i]->base_addr_low, mmaps[i]->base_addr_high,
		mmaps[i]->length_low, mmaps[i]->length_high, mmaps[i]->type);
	}
}
