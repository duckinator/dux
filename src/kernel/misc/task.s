; Set up a stack structure for switching to user mode.
switch_to_user_mode:
	cli
	mov ax, 0x23 ;mov 0x23, ax
	mov ax, ds
	mov ax, es
	mov ax, fs
	mov ax, gs
	
	mov esp, eax
	push dword 0x23 ;pushl 0x23
	push eax ;pushl eax
	pushf
	pop eax
	or eax, 0x200
	push eax
	push dword 0x1B ;pushl 0x1B
	push dword 0x1f
	iret
;1:
