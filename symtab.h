#ifndef SYMTAB_H
#define SYMTAB_H

#include "ast.h"

typedef struct VarEntry {
    char *name;
    char *type_name;    // NUEVO: tipo declarado, ej. "INTEGER", "STRING", "COUNTER"
    Value value;
    struct VarEntry *next;
} VarEntry;

typedef struct Env {
    struct Env *parent;
    VarEntry *vars;
} Env;

Env *env_new(Env *parent);
void env_free(Env *env);

void env_declare(Env *env, const char *name, const char *type_name);
void env_assign(Env *env, const char *name, Value value, int line);
Value env_lookup(Env *env, const char *name, int line);

#endif
