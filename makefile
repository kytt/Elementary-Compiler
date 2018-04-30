all:  asm4

asm4.tab.c asm4.tab.h:	asm4.y
	bison -d asm4.y

lex.yy.c: asm4.l asm4.tab.h
	flex asm4.l

asm4: lex.yy.c asm4.tab.c asm4.tab.h
	gcc -o asm4 asm4.tab.c lex.yy.c -lm

clean:
	rm asm4 asm4.tab.c lex.yy.c asm4.tab.h
