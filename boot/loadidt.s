[bits 32]

[global load_idt]

; the IDT descriptor to load
[extern idtp]

[section .text]

load_idt:
	; load the IDT
	lidt [idtp]

	ret