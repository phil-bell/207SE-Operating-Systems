;;; Assembly program to print 2 dots, go on to next line and 
;;; print another 2 line then quit
section .data ; area declare constants
	dot db '.'; constant holding a dot
	cr db 10	; 10 is the code for new line 
			;and it is stored in cr

section .text; section where code is written
	call drawDot; call code section drawDot
	call drawDot; call code section drawDot
	call newLine; call code section newline
	call drawDot; call code section drawDot
	call drawDot; call code section drawDot
	call newLine; call code section newline
	call quit; call code section quit

;;; functions from above
newLine:

	mov eax,4 	; Put 4 in eax register into which is system 
                ;call for write (sys_write)	
	mov ebx,1 	; Put 1 in ebx register which is the standard 
			; output to the screen 
	mov ecx, cr	; Put the newline value into ecx register
	mov edx, 1	; Put the length of the newline value into edx 
			; register
	int 80h 	; Call the kernel with interrupt to check the 
			; registers and perform the action of moving to 
			; the next line like endl in c++
	ret	; return to previous position in code


drawDot:

	mov eax,4 	; Put 4 in eax register which is system call for 
			; write (sys_write)	
	mov ebx,1 	; Put 1 in ebx register which is the standard 
			; output to the screen 
	mov ecx, dot	; Put the '.' character in register ecx
	mov edx, 1	; Put the length in bytes of the '.' character 
			; in  ecx register
	int 80h 	; Call the kernel with interrupt to check the 
			; registers and print a dot to the screen
	ret	; return to previous position in code
	
	
quit:
	mov eax,1 	; Put 1 in the eax register which is the system 
			; call for exit (sys_exit)
	mov ebx,0 	; Put 0 into the ebx register which is the exit 
			; return code of 0 (no error)
	int 80h; ; Call the kernel with interrupt to check the 
		    ; registers and quit the program with no ;
			; segmentation error
