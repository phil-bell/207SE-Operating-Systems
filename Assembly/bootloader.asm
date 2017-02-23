[BITS 16]               ;;sets set it to a 16 bit bootloader
[ORG 0x7C00]            ;;sets where the code gets mapped
top:                    ;;this is the main fucntion that makes everything happen
        mov ax,0x0000   ;; refers to the table and writes a char
        mov dx,ax       ;; page nuymber 0
        mov si, name    ;;puts the contents of the name variable si register
        call writeString;;call the writeString fucntion to output what is in the si register which is my name in this instance
        mov si, email   ;;puts the email in the si register
        call writeString;;calls the writeString function to output the email
        mov si,studentNo;;sets the si to my student number
        call writeString;;call the writeString function to output the studentNo
        mov si,star1    ;;next 10 lines output the a triagle of asterisk
        call writeString
        mov si,star2
        call writeString
        mov si,star3
        call writeString
        mov si,star4
        call writeString
        mov si,star5
        call writeString
        jmp $           ;;jumps to $

writeString:            ;;this fucntion output what is in the si register
        mov ah,0x0E     ;;moves 0x0E to the ah register
        mov bh,0x00     ;;moves 0x00 to the bh register
        mov bl,0x07     ;;moves 0x07 to the bl register

nextchar:               ;;moves to the next char
        lodsb           ;;pumps the string through
        cmp al,0        ;;ends the string
        jz done         ;;jumps to done if zero
        int 0x10        ;;interupts the bios
        jmp nextchar    ;;jumps to nextChar
done:
        ret
        name db 'Philip Bell' ,13,10,0 ;;assigns my name to the variable name
        email db 'bellp7@uni.coventry.ac.uk',13,10,0 ;;assigns my email to the variable email
        studentNo db '5690404',13,10,0 ;;assigns my student number to the variable studentNo
        star1 db '*',13,10,0 ;;next 5 lines assign the astrisk to each line of the triangle of astrisks
        star2 db '**',13,10,0
        star3 db '***',13,10,0
        star4 db '****',13,10,0
        star5 db '*****',13,10,0
        times 510-($-$$) db 0 ;;starts the instruction and the program
        dw 0xAA55       ;;this is the bootloader signiture
