global _start		; making entry point visible to linker
global _stacktop
extern init_kernel	; Defined in init/init.c

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

; reserve initial kernel stack space
STACKSIZE equ 0x4000			; that's 16k.

extern stop
_start:
	mov esp, _stacktop	; set up the stack
	push ebx			; argument to kmain
	push eax			; provided by multiboot compliant bootloaders
	call  init_kernel			; call kernel proper
	cli				; stop interrupts
	hlt				; halt machine should kernel return

section .bss
align 32
	resb STACKSIZE			; reserve 16k stack on a quadword boundary
_stacktop:
