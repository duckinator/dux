bits 32

global HalInitGDT
extern _stacktop

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

	; Load the TSS
	push esi
	push eax
	mov esi, tss_begin
	add esi, 0x4
	mov dword [ds:esi], _stacktop
	mov ax, 0x28
	ltr ax
	pop esi
	pop eax

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
	db 01001111b
	db 0x0

gdt_tss:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10001001b
	db 10001111b
	db 0x0

gdt_end:

gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt

tss_begin:
	dw 0x0 ;LINK
	dw 0x0
	dd 0x0 ;ESP0 (will be location of stacktop)
	dw 0x10 ;SS0 (descriptor for SS)
	dw 0x0
	dd 0x0 ;ESP1
	dw 0x0 ;SS1
	dw 0x0
	dd 0x0 ;ESP2
	dw 0x0 ;SS2
	dw 0x0
	dd 0x0 ;CR3
	dd 0x0 ;EIP
	dd 0x0 ;EFLAGS
	dd 0x0 ;EAX
	dd 0x0 ;ECX
	dd 0x0 ;EDX
	dd 0x0 ;EBX
	dd 0x0 ;ESP
	dd 0x0 ;EBP
	dd 0x0 ;ESI
	dd 0x0 ;EDI
	dw 0x0 ;ES
	dw 0x0
	dw 0x0 ;CS
	dw 0x0
	dw 0x0 ;SS
	dw 0x0
	dw 0x0 ;DS
	dw 0x0
	dw 0x0 ;FS
	dw 0x0
	dw 0x0 ;GS
	dw 0x0
	dw 0x0 ;LDTR
	dw 0x0
	dw 104 ;IOPB offset (the sizeof the TSS)
tss_end:
