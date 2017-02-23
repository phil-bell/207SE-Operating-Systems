[BITS 16]
[ORG 0x7C00] ;Where the code gets mapped
top:
	jmp top ;Loop forever
times 510-($-$$) db 0 ;Pad with 0
dw 0xAA55 ;Bootloader signature (backwards)
;; dw declares a word (2 bytes because we’re 16 bits)