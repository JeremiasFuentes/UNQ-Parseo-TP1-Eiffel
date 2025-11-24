# TP — Analizador Léxico de Eiffel (Flex + Bison)

Este proyecto implementa **sólo la etapa léxica** del lenguaje Eiffel. Bison se usa como *driver* para coordinar la lectura de tokens; el listado de tokens se imprime desde las acciones de Flex.

## Estructura
```
.
├── Makefile
├── lexer.l          # Reglas de tokens y salida formateada
├── parser.y         # Parser mínimo (consume tokens)
└── tests
    ├── hello.e
    └── tokens.e
```

## Cómo compilar
```bash
flex -l lexer.l
bison -dv parser.y
gcc -o lexer parser.tab.c lex.yy.c
```

### bash
```bash
make
```
### bash
```bash
.\compile.sh
```

## Cómo ejecutar
```bash
./lexer tests/hello.e
./lexer tests/tokens.e
./lexer tests/calculadora.e
```
### windows
```bash
.\out\lexer.exe .\tests\hello.e
```

### Ejecutar interprete
```bash
make run FILE=./examples/01_hello.e
```

### Ejecutar tests
```bash
make tests
```

## Qué cubre el analizador
- Palabras reservadas: `class, inherit, feature, do, end, if, then, else, from, until, loop, create`.
- Identificadores: `[A-Za-z_][A-Za-z0-9_]*`.
- Números:
  - Enteros: `123`
  - Reales: `3.14`, `2E10`, `1.0e-3`
- Cadenas Eiffel con:
  - Comillas internas por duplicación (`""`).
  - Secuencias `%` típicas (`%N`, `%T`, etc.).
- Operadores y símbolos: `:=, =, <, >, <=, >=, (, ), ;, ., +, -, *, /`.
- Comentarios: `--` hasta fin de línea.
- **Insensible a mayúsculas/minúsculas** (Flex `%option caseless`).

## Salida esperada (extracto)
```
TOKEN_CLASS        -> class
TOKEN_IDENTIFIER   -> HELLO_WORLD
...
```
