bits 32

global isr0

extern CoException

%macro ISR_PROTECT_BEGIN 0
	pushad

	push ds
	push es
	push fs
	push gs
	push ss

	mov eax, 0x10
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	mov ss, eax
%endmacro

%macro ISR_PROTECT_END 0
	pop ss
	pop gs
	pop fs
	pop es
	pop ds

	popad
%endmacro

%macro ISR_ABORT 1
global isr%1
isr%1:
	ISR_PROTECT_BEGIN
	call CoException
	ISR_PROTECT_END
	iret
%endmacro

%macro ISR_FAULT 1
global isr%1
isr%1:
	ISR_PROTECT_BEGIN
	call CoException
	ISR_PROTECT_END
	iret
%endmacro

%macro ISR_INTR 1
global isr%1
isr%1:
	ISR_PROTECT_BEGIN
	call CoException
	ISR_PROTECT_END
	iret
%endmacro

%macro ISR_RESV 1
global isr%1
isr%1:
	ISR_PROTECT_BEGIN
	call CoException
	ISR_PROTECT_END
	iret
	iret
%endmacro

%macro ISR_TRAP 1
global isr%1
isr%1:
	ISR_PROTECT_BEGIN
	call CoException
	ISR_PROTECT_END
	iret
	iret
%endmacro

section .text

ISR_FAULT 0
ISR_FAULT 1
ISR_INTR 2
ISR_TRAP 3
ISR_TRAP 4
ISR_FAULT 5
ISR_FAULT 6
ISR_FAULT 7
ISR_ABORT 8
ISR_FAULT 9
ISR_FAULT 10
ISR_FAULT 11
ISR_FAULT 12
ISR_FAULT 13
ISR_FAULT 14
ISR_FAULT 15
ISR_FAULT 16
ISR_FAULT 17
ISR_ABORT 18
ISR_FAULT 19
ISR_RESV 20
ISR_RESV 21
ISR_RESV 22
ISR_RESV 23
ISR_RESV 24
ISR_RESV 25
ISR_RESV 26
ISR_RESV 27
ISR_RESV 28
ISR_RESV 29
ISR_RESV 30
ISR_RESV 31
