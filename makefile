all:	asm4.exe

asm4.tab.c asm4.tab.h:	asm4.y
	bison -d asm4.y

lex.yy.c: asm4.l asm4.tab.h
	flex asm4.l

asm4: lex.yy.c asm4.tab.c asm4.tab.h
	gcc -o asm4 asm4.tab.c lex.yy.c -lm

asm4.asm: asm4 asm4.txt
	./asm4 asm4.txt
	
asm4.o:	asm4.asm
	nasm -f elf asm4.asm
	
asm4.exe: asm4.o
	ld -melf_i386 -o asm4.exe asm4.o
	
clean:
	rm asm4 asm4.tab.c lex.yy.c asm4.tab.h asm4.o asm4.exe
