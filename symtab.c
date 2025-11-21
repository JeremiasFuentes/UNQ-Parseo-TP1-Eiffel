#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "value.h"
#include "symtab.h"
#include "ast.h"

/* =====================================================
 * Creación y liberación de scopes
 * ===================================================== */

Scope *scope_create(Scope *parent) {
    Scope *s = malloc(sizeof(Scope));
    s->parent = parent;
    s->bindings = NULL;
    return s;
}

void scope_free(Scope *s) {
    Binding *b = s->bindings;
    while (b) {
        Binding *next = b->next;

        if (b->val.type == TYPE_STRING && b->val.s)
            free(b->val.s);

        free(b->name);
        free(b);
        b = next;
    }
    free(s);
}

/* =====================================================
 * Inserción y consulta
 * ===================================================== */

void scope_set(Scope *s, const char *name, Value v) {
    Binding *b = s->bindings;

    /* buscar si ya existe */
    while (b) {
        if (strcmp(b->name, name) == 0) {
            /* reemplazar valor anterior */
            if (b->val.type == TYPE_STRING && b->val.s)
                free(b->val.s);

            b->val = v;
            return;
        }
        b = b->next;
    }

    /* crear nuevo binding */
    Binding *nb = malloc(sizeof(Binding));
    nb->name = strdup(name);
    nb->val = v;
    nb->next = s->bindings;
    s->bindings = nb;
}

bool scope_get(Scope *s, const char *name, Value *out) {
    for (Scope *cur = s; cur != NULL; cur = cur->parent) {
        Binding *b = cur->bindings;
        while (b) {
            if (strcmp(b->name, name) == 0) {
                *out = b->val;
                return true;
            }
            b = b->next;
        }
    }
    return false;
}

/* =====================================================
 * Constructores de valores
 * ===================================================== */

Value make_int_value(int i) {
    Value v;
    v.type = TYPE_INT;
    v.i = i;
    v.r = (double)i;
    v.s = NULL;
    // v.b = NULL;
    return v;
}

Value make_real_value(double r) {
    Value v;
    v.type = TYPE_REAL;
    v.r = r;
    v.i = (long)r;
    v.s = NULL;
    // v.b = NULL;
    return v;
}

Value make_string_value(const char *s) {
    Value v;
    v.type = TYPE_STRING;
    v.s = strdup(s);
    v.i = 0;
    v.r = 0.0;
    // v.b = NULL;
    return v;
}

// Value make_bool_value(bool x) {
//     Value v;
//     v.type = TYPE_BOOL;
//     v.i = 0;
//     v.r = 0.0;
//     v.s = NULL;
//     v.b = NULL;
//     return v;
// }

Value make_void_value() {
    Value v;
    v.type = TYPE_VOID;
    v.i = 0;
    v.r = 0.0;
    v.s = NULL;
    // v.b = NULL;
    return v;
}
