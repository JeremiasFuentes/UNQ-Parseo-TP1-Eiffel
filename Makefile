CC=gcc
FLEX=flex
BISON=bison
NTESTS = 11

CFLAGS=-Wall -Wextra -std=c11 -g

OBJS=parser.tab.o lex.yy.o ast.o symtab.o runtime.o interpreter.o

all: interpreter

build: interpreter

interpreter: $(OBJS)
	$(CC) $(CFLAGS) -o interpreter $(OBJS)

parser.tab.c parser.tab.h: parser.y
	$(BISON) -dv parser.y -o parser.tab.c

lex.yy.c: lexer.l parser.tab.h
	$(FLEX) lexer.l

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

symtab.o: symtab.c symtab.h ast.h runtime.h
	$(CC) $(CFLAGS) -c symtab.c

runtime.o: runtime.c runtime.h ast.h
	$(CC) $(CFLAGS) -c runtime.c

interpreter.o: interpreter.c ast.h symtab.h runtime.h
	$(CC) $(CFLAGS) -c interpreter.c

run: interpreter
	./interpreter $(FILE)

clean:
	rm -f interpreter interpreter.exe parser.tab.c parser.tab.h parser.output lex.yy.c *.o

.PHONY: tests

tests: interpreter
	@echo "== Ejecutando tests =="
	@fails=0; ln=1; \
	for i in $$(seq -w 1 $(NTESTS)); do \
		testfile=$$(echo examples/$${i}_*.e); \
		if [ ! -f "$$testfile" ]; then \
			echo "Test $$i: archivo $$testfile no encontrado"; \
			fails=$$((fails+1)); \
			ln=$$((ln+1)); \
			continue; \
		fi; \
		name=$$(basename "$$testfile"); \
		# Normalizamos salida igual que en regen \
		got=$$(./interpreter "$$testfile" 2>&1 | tr -d '\r' | awk 'NR==1{printf "%s", $$0; next}{printf "\\n%s", $$0} END{print ""}'); \
		exp=$$(sed -n "$${ln}p" salidas_esperadas.txt | tr -d '\r'); \
		printf "Test %s (%s): " "$$i" "$$name"; \
		if [ "$$got" = "$$exp" ]; then \
			echo "OK ✅"; \
		else \
			echo "FAIL ❌"; \
			echo "  Esperado: '$$exp'"; \
			echo "  Obtenido: '$$got'"; \
			fails=$$((fails+1)); \
		fi; \
		ln=$$((ln+1)); \
	done; \
	if [ $$fails -eq 0 ]; then \
		echo "== Todos los tests pasaron ✅ =="; \
	else \
		echo "== $$fails tests fallaron ❌ =="; \
		exit 1; \
	fi




.PHONY: regen

regen: interpreter
	@echo "== Generando salidas_esperadas.txt =="
	@rm -f salidas_esperadas.txt
	@for i in $$(seq -w 1 $(NTESTS)); do \
		testfile=$$(echo examples/$${i}_*.e); \
		if [ ! -f "$$testfile" ]; then \
			echo "!! Test $$i NO encontrado, guardando línea vacía"; \
			echo "" >> salidas_esperadas.txt; \
			continue; \
		fi; \
		# Ejecutamos el intérprete, borramos \r y unimos líneas con \\n usando awk \
		got=$$(./interpreter "$$testfile" 2>&1 | tr -d '\r' | awk 'NR==1{printf "%s", $$0; next}{printf "\\n%s", $$0} END{print ""}'); \
		echo "$$got" >> salidas_esperadas.txt; \
		echo "Generado salida $$i: $$got"; \
	done
	@echo "== salidas_esperadas.txt generado ✅ =="

