global _start

section .data
    msg db "Hello World!", 10
    len equ $ - msg

_start:
    ; type of call (sys_write)
    mov eax,4
    ; stdout filedescription
    mov ebx,1
    ; message
    mov ecx,msg
    ; num of bytes
    mov edx,len
    ; the following is an interrupt that invokes sytem call based
    ; on the value in eax,ebx,ecx,edx
    int 0x80

    ; the following code exits the program with exit status 0
    ; type of call (exit)
    mov eax, 1
    ;exit status
    mov ebx, 0
    int 0x80


; points to note

; mov ebx,234
; mov eax,ebx
; mul ebx => eax *=ebx
; div edx => eax /=edx