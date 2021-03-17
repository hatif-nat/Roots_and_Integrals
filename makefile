all: main
main.o: main.c
	gcc -o main.o -c main.c -m32
ff.o: ff.asm
	nasm -o ff.o ff.asm -f elf32
main: main.o ff.o
	gcc -o main main.o ff.o -m32
clean:
	rm -rf *.o main
