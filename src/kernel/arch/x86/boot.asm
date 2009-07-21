bits 32

global _mboot
global _start
global _halt
global _stacksize
global _stack

extern kmain

MBOOT_MAGIC equ 0x1badb002
MBOOT_FLAGS equ 1<<0 | 1<<1
MBOOT_CHECK equ -(MBOOT_MAGIC+MBOOT_FLAGS)

STACKSIZE equ 0x4000

section .mboot

_mboot:
	dd MBOOT_MAGIC
	dd MBOOT_FLAGS
	dd MBOOT_CHECK

section .text

_start:
	xor ebp, ebp
	mov esp, _stack+STACKSIZE

	jmp kmain

_halt:
	cli
	.halt:
		hlt
		jmp .halt

section .data

_stacksize: dd STACKSIZE

section .bss

_stack:
resb STACKSIZE
