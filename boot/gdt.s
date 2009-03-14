[GLOBAL gdt_flush]    ; Allows the C code to call gdt_flush().

gdt_flush:
   mov eax, [esp+4]  ; Get the pointer to the GDT, passed as a parameter.
   lgdt [eax]        ; Load the new GDT pointer

   mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
   mov ds, ax        ; Load all data segment selectors
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
   ret

[GLOBAL tss_flush]	; Allows our C code to call tss_flush().
tss_flush:
	mov ax, 0x2B	; Load the index of our TSS structure - The index is
			; 0x28, as it is the 5th selector and each is 8 bytes
			; long, but we set the bottom two bits (making 0x2B)
			; so that it has an RPL of 3, not zero.
	ltr ax		; Load 0x2B into the task state register.
	ret

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
	dw 0xFFFF    ;
	dw 0         ; first 16 bits of base address
	db 0         ; next 8 bits of base address
	db 10010010b ; data segment, writable, extends downwards
	db 11001111b ; big
	db 0         ; final 8 bits of base address
gdt_end:
gdt_desc:
	dw gdt_end - gdt - 1
	dd gdt