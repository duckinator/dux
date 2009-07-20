[bits 32]
 
[global HalIsr0]
[global HalIsr1]
[global HalIsr2]
[global HalIsr3]
[global HalIsr4]
[global HalIsr5]
[global HalIsr6]
[global HalIsr7]
[global HalIsr8]
[global HalIsr9]
[global HalIsr10]
[global HalIsr11]
[global HalIsr12]
[global HalIsr13]
[global HalIsr14]
[global HalIsr15]
[global HalIsr16]
[global HalIsr17]
[global HalIsr18]
[global HalIsr19]
[global HalIsr20]
[global HalIsr21]
[global HalIsr22]
[global HalIsr23]
[global HalIsr24]
[global HalIsr25]
[global HalIsr26]
[global HalIsr27]
[global HalIsr28]
[global HalIsr29]
[global HalIsr30]
[global HalIsr31]

[extern HalFaultHandler]
 

[section .text]
 
HalIsr0:
	cli
	push byte 0
	push byte 0
	jmp HalIsrCommon

HalIsr1:
	cli
	push byte 0
	push byte 1
	jmp HalIsrCommon

HalIsr2:
	cli
	push byte 0
	push byte 2
	jmp HalIsrCommon

HalIsr3:
	cli
	push byte 0
	push byte 3
	jmp HalIsrCommon

HalIsr4:
	cli
	push byte 0
	push byte 4
	jmp HalIsrCommon


HalIsr5:
	cli
	push byte 0
	push byte 5
	jmp HalIsrCommon

HalIsr6:
	cli
	push byte 0
	push byte 6
	jmp HalIsrCommon

HalIsr7:
	cli
	push byte 0
	push byte 7
	jmp HalIsrCommon

HalIsr8:
	cli
	push byte 8
	jmp HalIsrCommon

HalIsr9:
	cli
	push byte 0
	push byte 9
	jmp HalIsrCommon

HalIsr10:
	cli
	push byte 10
	jmp HalIsrCommon

HalIsr11:
	cli
	push byte 11
	jmp HalIsrCommon

HalIsr12:
	cli
	push byte 12
	jmp HalIsrCommon

HalIsr13:
	cli
	push byte 13
	jmp HalIsrCommon

HalIsr14:
	cli
	push byte 14
	jmp HalIsrCommon

HalIsr15:
	cli
	push byte 0
	push byte 15
	jmp HalIsrCommon

HalIsr16:
	cli
	push byte 0
	push byte 16
	jmp HalIsrCommon

HalIsr17:
	cli
	push byte 0
	push byte 17
	jmp HalIsrCommon

HalIsr18:
	cli
	push byte 0
	push byte 18
	jmp HalIsrCommon

HalIsr19:
	cli
	push byte 0
	push byte 19
	jmp HalIsrCommon

HalIsr20:
	cli
	push byte 0
	push byte 20
	jmp HalIsrCommon

HalIsr21:
	cli
	push byte 0
	push byte 21
	jmp HalIsrCommon

HalIsr22:
	cli
	push byte 0
	push byte 22
	jmp HalIsrCommon

HalIsr23:
	cli
	push byte 0
	push byte 23
	jmp HalIsrCommon

HalIsr24:
	cli
	push byte 0
	push byte 24
	jmp HalIsrCommon

HalIsr25:
	cli
	push byte 0
	push byte 25
	jmp HalIsrCommon

HalIsr26:
	cli
	push byte 0
	push byte 26
	jmp HalIsrCommon

HalIsr27:
	cli
	push byte 0
	push byte 27
	jmp HalIsrCommon

HalIsr28:
	cli
	push byte 0
	push byte 28
	jmp HalIsrCommon

HalIsr29:
	cli
	push byte 0
	push byte 29
	jmp HalIsrCommon

HalIsr30:
	cli
	push byte 0
	push byte 30
	jmp HalIsrCommon

HalIsr31:
	cli
	push byte 0
	push byte 31
	jmp HalIsrCommon

HalIsrCommon:
	; Push everything to the stack, then call a global fault handler.
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10 
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, HalFaultHandler
	call eax ; Special! Preserves eip!
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret
