[BITS 16]
[ORG 0x7C00]
top:
	mov ah,0x0E ;refer to table... writes a char
	mov bh,0x00 ;Page number 0
	mov bl,0x07 ;Text attributes (plain here)
	mov al,65 ; Character A
	int 0x10 ; Invoke BIOS interrupt 10h
jmp $ ;Change to "jmp top" for much fun!
times 510-($-$$) db 0
dw 0xAA55