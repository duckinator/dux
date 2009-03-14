OUTPUT_FORMAT(elf32-i386)
 
ENTRY(loader)
 
SECTIONS {
	. = 0x100000;
 
	.text : {
		code = .;
		*(.text)
		. = ALIGN(4096);
	}
 
	.rodata : {
		*(.rodata)
		. = ALIGN(4096);
	}
 
	.data : {
		*(.data)
		. = ALIGN(4096);
	}
 
	.bss : {
		bss = .;
		*(.bss)
		. = ALIGN(4096);
	}
 
	end = .;
}
