#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdbool.h>
#include "ast.h"   /* trae la definición de Value, ValueType y demás */

/* =====================================================
 * Tabla de símbolos basada en scopes anidados
 * ===================================================== */

typedef struct Binding {
    char *name;
    Value val;
    struct Binding *next;
} Binding;

typedef struct Scope {
    struct Scope *parent;
    Binding *bindings;
} Scope;

/* =====================================================
 * Funciones públicas del módulo
 * ===================================================== */

/* Scope */
Scope *scope_create(Scope *parent);
void scope_free(Scope *s);

/* Inserción y consulta */
void scope_set(Scope *s, const char *name, Value v);
bool scope_get(Scope *s, const char *name, Value *out);


#endif /* SYMTAB_H */
