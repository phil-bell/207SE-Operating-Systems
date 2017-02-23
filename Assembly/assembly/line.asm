;; assembly code to draw line dots
section .data
	global _start
	char db ' '
	linesize db 12 	; length 12
		
section .text	
_start:

	;; use ax for the counter
	mov rax, [linesize] ; move the value in linesize (12) in 
     ; rax register
	
lineLoop:

	;; draw a dot
	call dot
	;; subtract from the counter ax
	;; and repeat if we haven't hit 0
	dec ax
	cmp ax,0
	jg lineLoop
	;; call the code section linefeed twice	
	call linefeed
	call linefeed
	;; call the code section exit
	call exit
;; Some useful routines that I can call many times
;; or even copy and paste into other code
	
exit:	
	mov eax,1 ;; system call to exit            
	mov ebx,0 ;; error code             
	int 80h;; call interrupt to perform this system call
	ret

linefeed:	
	
	mov [char],  byte 10; move new line character into char
	mov eax,4; move system call 4 into eax register to write 
			; out             
	mov ebx,1; move 1 into ebx register to be standard out 
	mov ecx, char; move char (new line) to ecx register
	mov edx,1; move value 1 to edx register size of newline
	int 80h; call kernel using interrupt to create newline  
	ret
dot:	

	mov [char],  byte '.'; move dot character into char	
	push rax; push rax onto stack so counts down in loop
	mov eax,4; move system call 4 into eax register to write 
			; out             
	mov ebx,1; move 1 into ebx register to be standard out 
	mov ecx, char; move char (.) to ecx register
	mov edx,1; move value 1 to edx register size of newline
	int 80h ; call kernel using interrupt to display              
	pop rax; pop value in stack to rax to count down loop
	ret 