#ifndef MULTIBOOT_4EA2YWHA

#define MULTIBOOT_4EA2YWHA

#include <stdint.h>

typedef struct multiboot_t {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	char *cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;
	union {
		struct {
			uint32_t tabsize;
			uint32_t strsize;
			uint32_t addr;
			uint32_t reserved;
		} aout;
		struct {
			uint32_t num;
			uint32_t size;
			uint32_t addr;
			uint32_t shndx;
		} elf;
	} syms;
	uint32_t mmap_length;
	uint32_t mmap_addr;
	uint32_t drives_length;
	uint32_t drives_addr;
	uint32_t config_table;
	char *boot_loader_name;
	uint32_t apm_table;
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_len;
} multiboot_t;

typedef struct mods_t {
	uint32_t mod_start;
	uint32_t mod_end;
	char *string;
	uint32_t reserved;
} mods_t;

#endif /* end of include guard: MULTIBOOT_4EA2YWHA */
