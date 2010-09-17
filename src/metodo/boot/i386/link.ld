ENTRY(_start)

SECTIONS {
	. = 0x100000;
	start = .;

	.debug_info : {
		debug_info_start = .;
		*(.debug_info)
		debug_info_end = .;
	}

	.text : ALIGN (0x1000) {
		*(.mboot)
		*(.text)
	}

	.rodata ALIGN (0x1000) : {
		*(.rodata)
	}

	.data ALIGN (0x1000) : {
		*(.data)
		start_initial_tests = .;
		*(initial_tests)
		end_initial_tests = .;
		start_other_tests = .;
		*(other_tests*)
		end_other_tests = .;
	}

	.bss ALIGN (0x1000) : {
		sbss = .;
		*(COMMON)
		*(.bss)
		ebss = .;
	}

	end = .;
}
