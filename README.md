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

## Cómo ejecutar
```bash
./lexer tests/hello.e
./lexer tests/tokens.e
./lexer tests/calculadora.e
```

### Comandos Makefile
```bash
make # Compilar
make tests # Ejecutar tests de la carpeta 'examples'
make run FILE=./examples/01_hello.e # Ejecutar interprete para el archivo proporcionado
make run FILE=./examples/05_loop_until.e ACTION=lex # Ejecutar parser para archivo e imprimir lexemas reconocidos
make run FILE=./examples/05_loop_until.e ACTION=ast # Ejecutar parser para archivo e imprimir AST generado
make run FILE=./examples/05_loop_until.e ACTION=env # Interpreta el archivo e imprimir las modificaciones del Entorno
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

## Gramatica definida
```
program         → class_def
                | program class_def
class_def       → TOKEN_CLASS TOKEN_IDENTIFIER feature_block TOKEN_END
feature_block   → TOKEN_FEATURE feature_list
feature_list    → feature_or_attr
                | feature_list feature_or_attr
feature_or_attr → TOKEN_IDENTIFIER TOKEN_COLON TOKEN_IDENTIFIER
                | TOKEN_IDENTIFIER TOKEN_COLON TOKEN_IDENTIFIER TOKEN_SEMI
                | feature
feature         → TOKEN_IDENTIFIER opt_locals TOKEN_DO stmt_list TOKEN_END
opt_locals      → ε
                | TOKEN_LOCAL local_decl_list
local_decl_list → local_decl
                | local_decl_list local_decl
local_decl      → id_list TOKEN_COLON TOKEN_IDENTIFIER
                | id_list TOKEN_COLON TOKEN_IDENTIFIER TOKEN_SEMI
id_list         → TOKEN_IDENTIFIER
                | id_list TOKEN_COMMA TOKEN_IDENTIFIER
stmt_list       → ε
                | stmt_item
                | stmt_list stmt_item
stmt_item       → stmt
                | stmt TOKEN_SEMI
stmt            → TOKEN_IDENTIFIER TOKEN_ASSIGN expr
                | if_stmt
                | loop_stmt
                | print_stmt
                | TOKEN_CREATE TOKEN_IDENTIFIER
                | TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER TOKEN_ASSIGN expr
                | TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER
if_stmt         → TOKEN_IF expr TOKEN_THEN stmt_list TOKEN_ELSE stmt_list TOKEN_END
                | TOKEN_IF expr TOKEN_THEN stmt_list TOKEN_END
loop_stmt       → TOKEN_FROM stmt_list TOKEN_UNTIL expr TOKEN_LOOP stmt_list TOKEN_END
print_stmt      → TOKEN_PRINT TOKEN_LPAREN expr TOKEN_RPAREN
expr            → expr TOKEN_PLUS expr
                | expr TOKEN_MINUS expr
                | expr TOKEN_MUL expr
                | expr TOKEN_DIV expr
                | expr TOKEN_EQUAL expr
                | expr TOKEN_LT expr
                | expr TOKEN_GT expr
                | expr TOKEN_LE expr
                | expr TOKEN_GE expr
                | TOKEN_MINUS expr %prec UMINUS
                | TOKEN_LPAREN expr TOKEN_RPAREN
                | TOKEN_INTEGER
                | TOKEN_STRING
                | TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER
```
