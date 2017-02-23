section.data
        star db'*'
        starLen db 10
section.text
        global _start
        _start
        mov cx,1
        call looper
        mov cx,2
        call looper
        mov cx,3
        call looper
        mov cx,4
        call looper
        mov cx,5
        call looper
        mov cx,6
        call looper
        mov cx,7
        call looper
        mov cx,8
        call looper
        mov cx,9
        call looper
        mov cx,10
        call looper
        call quit
looper:
        push cx
        call drawDot
        pop cx
        dec cx
        jnz looper
newLine:
        mov eax,4
        mov ebx,1
        mov ecx,starLen
        mov edx,1
        int 80h
        ret
drawDot:
        mov eax,4
        mov ebx,1
        mov ecx,star
        mov edx,1
        int 80h
        ret
quit:
        mov eax,1
        mov ebx,0
        int 80h
