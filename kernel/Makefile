CFLAGS  := -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I.

all:	kernel.bin

kernel.bin:     header.o  main.o 
	ld -m elf_i386 -T link.ld -o kernel.bin header.o main.o 
	@echo Done!

header.o: header.S 
	nasm -f elf32 header.S 

main.o: main.c 
	gcc -m32 -c main.c -o main.o

clean: 
	rm -f *.o *.bin
