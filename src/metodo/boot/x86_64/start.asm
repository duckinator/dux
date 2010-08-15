; Large masses of this borrowed from http://github.com/xomboverlord/xomb-bare-bones/blob/master/kernel/arch/x86_64/boot/boot.s
; Thanks all the people of xomb ;D

global _start		; making entry point visible to linker
global _stacktop
extern InitKernel	; Defined in init/init.c

; setting up the Multiboot header - see GRUB docs for details
MODULEALIGN      1<<0                     ; align loaded modules on page boundaries
MEMINFO          1<<1                     ; provide memory map
FLAGS            MODULEALIGN | MEMINFO    ; this is the Multiboot 'flag' field
MAGIC            0x1BADB002               ; 'magic number' lets bootloader find the header
CHECKSUM         -(MAGIC + FLAGS)          ; checksum required
KERNEL_VMA_BASE  0xFFFF800000000000       ; Kernel in virtual memory
KERNEL_LMA_BASE  0x100000                 ; Kernel in physical memory

CS_KERNEL        0x10
CS_KERNEL32      0x08

section .text
bits 32

; reserve initial kernel stack space
STACKSIZE equ 0x4000			; that's 16k.

extern stop
_start:
	; Save values for multiboot
	mov esi, ebx
	mov edi, eax

	jmp _start32

	align 4
	MultiBootHeader:
		dd MAGIC
		dd FLAGS
		dd CHECKSUM
		dd MultiBootHeader
		dd _start
		dd (_edata-KERNEL_VMA_BASE)
		dd (_end-KERNEL_VMA_BASE)
		dd _start

_start32:
	cli

	; enable 64-bit page translation table entries
	; by setting CR4.PAE = 1.
	;
	; Paging is not enabled until long mode.
	mov eax, cr4
	bts eax, 5
	mov cr4, eax

	; Create long mode page table and init CR3 to
	; point to the base of the PML4 page table
	mov eax, pml4_base
	mov cr3, eax

	; Enable Long mode and SYSCALL / SYSRET instructions
	mov ecx, 0xC0000080
	rdmsr
	bts eax, 8
	bts eax, 0
	wrmsr

	; Load the 32 bit GDT
	lgdt [gdt2]

	; Load the 32 bit IDT
	; lidt [pIDT32]

	; establish a stack for 32 bit code
	mov esp, (stack-KERNEL_VMA_BASE) + STACK_SIZE

	; enable paging to activate long mode
	mov eax, cr0
	bts eax, 31
	mov cr0, eax

	jmp CS_KERNEL:(_start64-KERNEL_VMA_BASE)

;	jmp gdt_code:_start64			;Load CS with 64 bit segment and flush the instruction cache
bits 64
_jump64:
	jmp (_start64-KERNEL_VMA_BASE)

_start64:
	mov esp, _stacktop	; set up the stack
	mov rsi, esi		   ; argument to kmain
	mov rdi, edi		   ; provided by multiboot compliant bootloaders
;	mov rsi, ebx		   ; argument to kmain
;	mov rdi, eax		   ; provided by multiboot compliant bootloaders
;	push ebx		; argument to kmain
;	push eax		; provided by multiboot compliant bootloaders
	call  InitKernel	; call kernel proper
	cli               ; stop interrupts
	hlt               ; halt machine should kernel return


bits 32

; 32bit GDT
align 4096

gdt32:

gdt32_null:
	dq 0

gdt32_code:
	dw 0xFFFF ; first 16 bits of segment limiter
	dw 0 ; first 16 bits of base address
	db 0 ; next 8 bits of base address
	db 10011010b ; code segment, readable, nonconforming
	db 11001111b ; ganular, last 4 bits of segment limiter
	db 0 ; final 8 bits of base address

gdt32_data:
	dw 0xFFFF
	dw 0 ; first 16 bits of base address
	db 0 ; next 8 bits of base address
	db 10010010b ; data segment, writable, extends downwards
	db 11001111b ; big
	db 0 ; final 8 bits of base address

gdt32_end:

gdt32_desc:
	dw gdt32_end - gdt32 - 1
	dd gdt32

; Temporary page tables

; These assume linking to 0xFFFF800000000000
align 4096
pml4_base:
	dq (pml3_base + 0x7)
	times 255 dq 0
	dq (pml3_base + 0x7)
	times 255 dq 0

align 4096
pml3_base:
	dq (pml2_base + 0x7)
	times 511 dq 0

align 4096
pml2_base:
	%assign i 0
	%rep 25
	dq (pml1_base + i + 0x7)
	%assign i i+4096
	%endrep

	times (512-25) dq 0

align 4096
; 15 tables are described here
; this maps 40 MB from address 0x0
; to an identity mapping
pml1_base:
	%assign i 0
	%rep 512*25
	dq (i << 12) | 0x087
	%assign i i+1
	%endrep

section .bss
align 32
	resb STACKSIZE			; reserve 16k stack on a quadword boundary
_stacktop:
