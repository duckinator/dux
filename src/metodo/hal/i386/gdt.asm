bits 32

global HalInitGDT

extern _start

section .text

HalInitGDT:
	; This lets us check that the stack is still valid. Its not
	; foolproof, but I believe it is enough to gurantee we can keep
	; running.
	mov ebx, [esp]

	; 0x8 is the new code segment.
	lgdt [gdt_desc]
	jmp 0x8:.flushcs

	; 0x10 is the new data segment.
	.flushcs:
		mov eax, 0x10
		mov ds, eax
		mov es, eax
		mov fs, eax
		mov gs, eax
		mov ss, eax

	; Check if the stack is still valid.
	cmp ebx, [esp]
	jne _start

	ret

section .data

gdt:

gdt_null:
	dq 0x0

gdt_code:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0

gdt_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

gdt_user_code:
	dw 0xffff
	dw 0x0
	db 0x0
	db 11111010b
	db 11001111b
	db 0x0

gdt_user_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 11110010b
	db 11001111b
	db 0x0

gdt_end:

gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt
