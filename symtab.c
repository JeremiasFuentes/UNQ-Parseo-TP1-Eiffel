#include "symtab.h"
#include "runtime.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *xstrdup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char *p = malloc(len);
    if (!p) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    memcpy(p, s, len);
    return p;
}


static VarEntry *find_in_env(Env *env, const char *name) {
    VarEntry *v = env->vars;
    while (v) {
        if (strcmp(v->name, name) == 0) return v;
        v = v->next;
    }
    return NULL;
}

Env *env_new(Env *parent) {
    Env *env = (Env *)calloc(1, sizeof(Env));
    if (!env) return NULL;
    env->parent = parent;
    env->vars = NULL;
    return env;
}

void env_free(Env *env) {
    (void)env;
}

void env_declare(Env *env, const char *name, const char *type_name) {
    VarEntry *v = malloc(sizeof(VarEntry));
    if (!v) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    v->name = xstrdup(name);        
    v->type_name = type_name ? xstrdup(type_name) : NULL;


    v->value.type = VAL_INT;
    v->value.as.i = 0;

    v->next = env->vars;
    env->vars = v;
}

static VarEntry *lookup_chain(Env *env, const char *name) {
    Env *e = env;
    while (e) {
        VarEntry *v = find_in_env(e, name);
        if (v) return v;
        e = e->parent;
    }
    return NULL;
}

void env_assign(Env *env, const char *name, Value v, int line) {
    VarEntry *cur = env->vars;
    while (cur) {
        if (strcmp(cur->name, name) == 0) {

            // Chequeo de tipos SOLO si tenemos type_name
            if (cur->type_name) {
                if (strcmp(cur->type_name, "INTEGER") == 0) {
                    if (v.type != VAL_INT) {
                        rt_runtime_error(line,
                            "type error: expected INTEGER for variable '%s'", name);
                    }
                } else if (strcmp(cur->type_name, "STRING") == 0) {
                    if (v.type != VAL_STRING) {
                        rt_runtime_error(line,
                            "type error: expected STRING for variable '%s'", name);
                    }
                }
                // Otros tipos (COUNTER, etc.) los dejamos sin chequear
            }

            cur->value = v;
            return;
        }
        cur = cur->next;
    }
    rt_runtime_error(line, "variable '%s' not declared", name);
}

Value env_lookup(Env *env, const char *name, int line) {
    VarEntry *v = lookup_chain(env, name);
    if (!v) {
        rt_runtime_error(line, "variable '%s' not declared", name);
    }
    return v->value;
}
