CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -g -Wall

all: build

build: parser.c lexer.c ast.o symtab.o interpreter.o runtime.o
	$(CC) $(CFLAGS) -o interpreter parser.c lexer.c ast.o symtab.o interpreter.o runtime.o -lfl

parser.c: parser.y
	$(BISON) -d -o parser.c parser.y

lexer.c: lexer.l parser.c
	$(FLEX) -o lexer.c lexer.l

ast.o: ast.c ast.h symtab.h
	$(CC) $(CFLAGS) -c ast.c

symtab.o: symtab.c symtab.h ast.h
	$(CC) $(CFLAGS) -c symtab.c

interpreter.o: interpreter.c ast.h symtab.h
	$(CC) $(CFLAGS) -c interpreter.c

runtime.o: runtime.c ast.h
	$(CC) $(CFLAGS) -c runtime.c

run: interpreter
	@if [ -z "$(FILE)" ]; then echo "Usar: make run FILE=salidas/hello.e"; exit 1; fi
	./interpreter $(FILE)

tests: all
	@echo "Ejecutando tests..."
	@for f in salidas/*.e; do echo "---- $$f ----"; ./interpreter $$f; done

clean: 
	rm -f lexer lexer.exe parser.output parser.c parser.h parser.tab.c parser.tab.h lexer.c interpreter *.o
