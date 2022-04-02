
# Registers
## general
eax, ebx,
ecx, edx,
esi, edi,

## reserved
ebp - bottom of current stack frame
esp - top element of current stack frame
eip - instruction pointer

# stack
 - each function adds a stackframe

# Intel
2 parts
op and arguments

 -> mov arg1,arg2     => copies value in arg2 to arg1
 -> mov arg1,[arg2]   => arg2 is a pointer
 -> add arg1,arg2     => arg1 = arg1 + arg2
 -> sub arg1,arg2     => arg1 = arg1 - arg2
 -> push arg and pop arg => pushes and pops stuff off the stack
 -> lea reg, addr     => reg = [addr]
 -> cmp arg1,arg2     => arg1 == arg2 and sets flag in processor, which can be checked later
 -> jmp addr          => jumps to addr if flag is set
    -> je, jne, jg, jl
 -> call func         => push eip to top of stack, jumps to func
 -> leave             => pops eip and esp from stack
 -> ret               => pops eip from stack, and jmps to ret addr

# Idea

[x86 guide](https://www.cs.virginia.edu/~evans/cs216/guides/x86.html)
[x86 reference](https://www.felixcloutier.com/x86/)

1. Add all global variables to stack and remember where they are using symbol table.
2. for each expression, fetch the variables from stack location(using symbol table), compute and store values back into the required location.
3. If and While conditionals are easy to make, since it has predetermined operators in asm.
4. Print and In shall be written and treated as pre made subroutines/functions and shall be used as show
5. Call and function subroutine shall be used
6. Arrays will use heap and not stack
7. strings shall just be used from data section for simplicity