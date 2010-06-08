global _start		; making entry point visible to linker
global _stacktop
extern InInitKernel	; Defined in init/init.c

; setting up the Multiboot header - see GRUB docs for details
MODULEALIGN equ  1<<0			; align loaded modules on page boundaries
MEMINFO     equ  1<<1			; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO 	; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002		; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)	; checksum required

section .text
align 4
MultiBootHeader:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

gdt:

gdt_null:
	dq 0

gdt_code:
	dw 0xFFFF    ; first 16 bits of segment limiter
	dw 0         ; first 16 bits of base address
	db 0         ; next 8 bits of base address
	db 10011010b ; code segment, readable, nonconforming
	db 11001111b ; ganular, last 4 bits of segment limiter
	db 0         ; final 8 bits of base address

gdt_data:
	dw 0xFFFF
	dw 0		; first 16 bits of base address
	db 0		; next 8 bits of base address
	db 10010010b	; data segment, writable, extends downwards
	db 11001111b	; big
	db 0		; final 8 bits of base address

gdt_user_code:   ; user mode code segment
    dw 0xFFFF
    dw 0
    db 0
    db 11111010b
    db 11001111b
    db 0

gdt_user_data:   ; user mode data segment
    dw 0xFFFF
    dw 0
    db 0
    db 11110010b
    db 11001111b
    db 0

gdt_end:

gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt

; reserve initial kernel stack space
STACKSIZE equ 0x4000			; that's 16k.

extern stop
_start:
	mov esp, _stacktop	; set up the stack
	push ebx			; argument to kmain
	push eax			; provided by multiboot compliant bootloaders
	call  InInitKernel			; call kernel proper
	cli				; stop interrupts
	hlt				; halt machine should kernel return

section .bss
align 32
	resb STACKSIZE			; reserve 16k stack on a quadword boundary
_stacktop:
