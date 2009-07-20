[bits 32]

[global HalLoadIdt]

; the IDT descriptor to load
[extern idtp]

[section .text]

HalLoadIdt:
	; load the IDT
	lidt [idtp]

	ret
