test:
	nasm -f elf32 basic.asm -o basic.o
	ld -m elf_i386 basic.o -o basic
	./basic
dev:
	nasm -f elf32 ${f}.asm -o basic.o
	ld -m elf_i386 basic.o -o basic
	./basic