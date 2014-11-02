#include <stddef.h>
#include <stdint.h>

#include <elf.h>
#include <multiboot.h>

#include <kernel.h> 
#include <kernel/init/elfloader.h>

void *load_elf_exe(void *exe)
{
	int i;

	Elf32_Ehdr *ehdr;
	Elf32_Phdr *phdr;

	ehdr = exe;

	/* Is this even an elf file? */
	if (!(ehdr->e_ident[EI_MAG0] == ELFMAG0
			&& ehdr->e_ident[EI_MAG1] == ELFMAG1
			&& ehdr->e_ident[EI_MAG2] == ELFMAG2
			&& ehdr->e_ident[EI_MAG3] == ELFMAG3))
		return NULL;

	/* Is it executable? */
	if (ehdr->e_type != ET_EXEC)
		return NULL;

	/* Is there a program header? */
	if (ehdr->e_phoff == 0)
		return NULL;

	phdr = (Elf32_Phdr*) ((uint32_t) exe + (uint32_t) ehdr->e_phoff);

	for (i = 0; i < ehdr->e_phnum; i++, phdr++) {
		if (phdr->p_type == PT_LOAD) {
			memset((void*) phdr->p_vaddr, 0, phdr->p_memsz);
			memcpy((void*) phdr->p_vaddr,
					(void*) ((uint32_t) exe + (uint32_t) phdr->p_offset),
					phdr->p_filesz);
		}
	}

	return (void*) ehdr->e_entry;
}

void run_elf_exe(void *exe)
{
	void (*start)(void);

	start = (void (*)(void))load_elf_exe(exe);
	start();
}

