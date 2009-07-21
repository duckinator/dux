global HalIrq0
global HalIrq1
global HalIrq2
global HalIrq3
global HalIrq4
global HalIrq5
global HalIrq6
global HalIrq7
global HalIrq8
global HalIrq9
global HalIrq10
global HalIrq11
global HalIrq12
global HalIrq13
global HalIrq14
global HalIrq15

; 32: irq 0
HalIrq0:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 32
	jmp HalIrqCommonStub

HalIrq1:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 33
	jmp HalIrqCommonStub

HalIrq2:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 34
	jmp HalIrqCommonStub

HalIrq3:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 35
	jmp HalIrqCommonStub

HalIrq4:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 36
	jmp HalIrqCommonStub

HalIrq5:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 37
	jmp HalIrqCommonStub

HalIrq6:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 38
	jmp HalIrqCommonStub

HalIrq7:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 39
	jmp HalIrqCommonStub

HalIrq8:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 40
	jmp HalIrqCommonStub

HalIrq9:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 41
	jmp HalIrqCommonStub

HalIrq10:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 42
	jmp HalIrqCommonStub

HalIrq11:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 43
	jmp HalIrqCommonStub

HalIrq12:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 44
	jmp HalIrqCommonStub

HalIrq13:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 45
	jmp HalIrqCommonStub

HalIrq14:
	cli
	push byte 0		; Note that these don't push an error code on the stack:
				; We need to push a dummy error code
	push byte 46
	jmp HalIrqCommonStub

; 47: irq 15
HalIrq15:
	cli
	push byte 0
	push byte 47
	jmp HalIrqCommonStub

extern HalIrqHandler

; This is a stub that we have created for IRQ based ISRs. This calls
; 'HalIrqHandler' in our C code. This is in 'HalIrqHandler.c'
HalIrqCommonStub:
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
	mov eax, HalIrqHandler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret
