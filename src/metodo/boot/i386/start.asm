bits 32

global _start

extern InInitKernel

STACKSIZE equ 0x4000

section .text

	dd 0x1badb002
	dd 0x3
	dd -(0x1badb002+0x3)

_start:
	; Setup the stack.
	xor ebx, ebx
	mov esp, stack+STACKSIZE

	; Check multiboot headers.
	cmp eax, 0x2badb002
	jne _halt

	; Call the kernel.
	call InInitKernel

_halt:
	cli
	.halt:
		hlt
	jmp .halt

section .bss

stack:
	resb STACKSIZE
