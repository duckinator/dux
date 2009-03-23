#ifndef MM_DETECT_H
#define MM_DETECT_H

typedef struct aout_symbol_table {
	unsigned int tabsize;
	unsigned int strsize;
	unsigned int addr;
	unsigned int reserved;
} aout_symbol_table_t;

typedef struct elf_section_header_table {
	unsigned int num;
	unsigned int size;
	unsigned int addr;
	unsigned int shndx;
} elf_section_header_table_t;

typedef struct multiboot_info {
	unsigned int flags;
	unsigned int mem_lower;
	unsigned int mem_upper;
	unsigned int boot_device;
	unsigned int cmdline;
	unsigned int mods_count;
	unsigned int mods_addr;
	union {
		aout_symbol_table_t aout_sym;
		elf_section_header_table_t elf_sec;
	} u;
	unsigned long mmap_length;
	unsigned long mmap_addr;
} multiboot_info_t;

typedef struct memory_map {
	unsigned int size;
	unsigned int base_addr_low;
	unsigned int base_addr_high;
	unsigned int length_low;
	unsigned int length_high;
	unsigned int type;
} memory_map_t;

void mm_detect_grub(multiboot_info_t *mb_info);
void mm_detect_alloc(unsigned int base_addr, unsigned int length);

#endif
