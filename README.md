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
> En sistemas macOS puede que necesites `-ll` en lugar de `-lfl`. Edita el `Makefile` si fuera necesario.

## Cómo compilar
```bash
make
```

## Cómo ejecutar
```bash
./lexer tests/hello.e
./lexer tests/tokens.e
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

## Sugerencias para el Informe
1. **Diseño del analizador**: explicar decisión de usar `%option caseless`, seguimiento de línea con `yylineno`, e impresión desde acciones léxicas.
2. **Expresiones regulares**: justificar `ID`, `INTEGER`, `REAL` y `STRING` (doble comilla `""` y `%N`).
3. **Compilación/Ejecución**: incluir capturas de `make` y ejecución sobre `tests/*.e`.
4. **Reseña Eiffel**: incluir breve historia y referencias (agregar bibliografía).
