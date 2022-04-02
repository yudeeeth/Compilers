; jump, labels and interrupts
global _start:

_start:
    mov ecx, 99
    mov ebx, 32
    mov eax, 1
    cmp ecx, 100
    jg skip
    mov ebx, 13
skip:
    int 0x80