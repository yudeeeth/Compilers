section .bss
    num resb 5

section .text
global _start

_start:
    call print
    mov eax, 1
    mov ebx, 0
    int 0x80

print:
    push ebp
    mov ebp, esp
    sub esp, 1
    ; actual code
    mov eax, 4
    mov ebx, 1
    ; mov [esp],byte 'H'
    ; mov [esp+1],byte 'i' 
    ; mov [esp+2],byte 'i' 
    ; mov [esp+3],byte 'i' 
    ; mov [esp+4],byte 'i' 
    ; mov [esp+7],byte 10
    mov ecx, num
    mov edx, 4
    int 0x80
    ; end of actual
    mov esp, ebp
    pop ebp
    ret