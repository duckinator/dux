global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; 32: IRQ0
irq0:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 32
	jmp irq_common_stub

irq1:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 33
	jmp irq_common_stub

irq2:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 34
	jmp irq_common_stub

irq3:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 35
	jmp irq_common_stub

irq4:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 36
	jmp irq_common_stub

irq5:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 37
	jmp irq_common_stub

irq6:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 38
	jmp irq_common_stub

irq7:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 39
	jmp irq_common_stub

irq8:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 40
	jmp irq_common_stub

irq9:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 41
	jmp irq_common_stub

irq10:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 42
	jmp irq_common_stub

irq11:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 43
	jmp irq_common_stub

irq12:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 44
	jmp irq_common_stub

irq13:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 45
	jmp irq_common_stub

irq14:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 46
	jmp irq_common_stub

; 47: IRQ15
irq15:
	cli
	push byte 0
	push byte 47
	jmp irq_common_stub

extern irq_handler

; This is a stub that we have created for IRQ based ISRs. This calls
; 'irq_handler' in our C code. This is in 'irq_handler.c'
irq_common_stub:
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
	mov eax, irq_handler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret
