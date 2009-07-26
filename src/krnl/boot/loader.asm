global loader		; making entry point visible to linker
extern kmain		; kmain is defined elsewhere
extern HalIdtInit		; HalIdtInit is defined elsewhere

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
	db 11001111b ; ganular, last 3 bits of segment limiter
	db 0         ; final 8 bits of base address
 
gdt_data:
	dw 0xFFFF
	dw 0		; first 16 bits of base address
	db 0		; next 8 bits of base address
	db 10010010b	; data segment, writable, extends downwards
	db 11001111b	; big
	db 0		; final 8 bits of base address
 
gdt_end:
 
gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt

; reserve initial kernel stack space
STACKSIZE equ 0x4000			; that's 16k.

extern stop
loader:
	mov esp, stacktop	; set up the stack

	lgdt [gdt_desc]
	jmp 0x08:.flush
	.flush:
		mov ax, 0x10
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax
		mov ss, ax
		mov esp, stacktop
		jmp 0x08:gdt_return
gdt_return:
	call  HalIdtInit			; initialize IDT
	push ebx			; argument to kmain
	push 0x2badb002
	call  kmain			; call kernel proper
	cli				; stop interrupts
	hlt				; halt machine should kernel return

section .bss
align 32
	resb STACKSIZE			; reserve 16k stack on a quadword boundary
stacktop:
