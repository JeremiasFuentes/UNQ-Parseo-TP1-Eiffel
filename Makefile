CC ?= gcc

all: lexer

lexer: parser.tab.c lex.yy.c
	$(CC) -o $@ parser.tab.c lex.yy.c -lfl

parser.tab.c parser.tab.h: parser.y
	bison -d -Wall -Wcounterexamples -o parser.tab.c parser.y

lex.yy.c: lexer.l parser.tab.h
	flex -o lex.yy.c lexer.l

clean:
	rm -f lexer parser.tab.c parser.tab.h lex.yy.c
