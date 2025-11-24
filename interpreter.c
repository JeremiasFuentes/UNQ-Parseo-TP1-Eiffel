#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include <string.h>
#include "symtab.h"
#include "runtime.h"

extern int yyparse(void);
extern FILE *yyin;
extern ASTNode *ast_root;

/* Helpers de construcción de valores */

static Value make_int(long i) {
    Value v;
    v.type = VAL_INT;
    v.as.i = i;
    return v;
}

static Value make_bool(int b) {
    Value v;
    v.type = VAL_BOOL;
    v.as.b = b ? 1 : 0;
    return v;
}

static Value make_string(const char *s) {
    Value v;
    v.type = VAL_STRING;
    v.as.s = (char *)s;
    return v;
}

/* Prototipos internos */

static Value eval_expr(ASTNode *expr, Env *env);
static void exec_stmt(ASTNode *stmt, Env *env);
static void exec_stmt_list(ASTNode *list, Env *env);

static void exec_stmt_list(ASTNode *list, Env *env) {
    ASTNode *it = list;
    while (it) {
        exec_stmt(it->u.stmt_list.first, env);
        it = it->u.stmt_list.next;
    }
}

static void exec_if(ASTNode *stmt, Env *env) {
    Value cond = eval_expr(stmt->u.if_stmt.cond, env);
    if (cond.type != VAL_BOOL) {
        rt_runtime_error(stmt->line, "if condition is not boolean");
    }
    if (cond.as.b) {
        exec_stmt_list(stmt->u.if_stmt.then_branch, env);
    } else if (stmt->u.if_stmt.else_branch) {
        exec_stmt_list(stmt->u.if_stmt.else_branch, env);
    }
}

static void exec_loop(ASTNode *stmt, Env *env) {
    /* from init until cond loop body end */
    exec_stmt_list(stmt->u.loop.init, env);
    while (1) {
        Value c = eval_expr(stmt->u.loop.cond, env);
        if (c.type != VAL_BOOL) {
            rt_runtime_error(stmt->line, "loop condition is not boolean");
        }
        if (c.as.b) break;
        exec_stmt_list(stmt->u.loop.body, env);
    }
}

static void exec_stmt(ASTNode *stmt, Env *env) {
    if (!stmt) return;
    switch (stmt->type) {
    case AST_ASSIGN: {
        Value v = eval_expr(stmt->u.assign.expr, env);
        env_assign(env, stmt->u.assign.name, v, stmt->line);
        break;
    }
    case AST_IF:
        exec_if(stmt, env);
        break;
    case AST_LOOP:
        exec_loop(stmt, env);
        break;
    case AST_PRINT: {
        Value v = eval_expr(stmt->u.print.expr, env);
        rt_print(v);
        break;
    }
    case AST_CREATE: {
        const char *obj = stmt->u.create.name;
        const char *field = "value";
        size_t lo = strlen(obj), lf = strlen(field);
        char *fname = (char *)malloc(lo + 1 + lf + 1);
        if (!fname) {
            rt_runtime_error(stmt->line, "out of memory in create");
        }
        memcpy(fname, obj, lo);
        fname[lo] = '_';
        memcpy(fname + lo + 1, field, lf);
        fname[lo + 1 + lf] = '\0';

        /* declaramos c_value; env_declare ya inicializa en 0 y es idempotente */
        env_declare(env, fname, "INTEGER");
        free(fname);
        break;
    }

    /* c.inc → incrementa c_value */
    case AST_CALL_PROC: {
        const char *pname = stmt->u.call_proc.name;
        const char *suffix = "_inc";
        size_t lp = strlen(pname), ls = strlen(suffix);

        if (lp <= ls || strcmp(pname + (lp - ls), suffix) != 0) {
            rt_runtime_error(stmt->line, "unknown procedure '%s'", pname);
        }

        /* objeto: parte antes de "_inc": c */
        size_t lo = lp - ls;
        char *obj = (char *)malloc(lo + 1);
        if (!obj) {
            rt_runtime_error(stmt->line, "out of memory");
        }
        memcpy(obj, pname, lo);
        obj[lo] = '\0';

        /* armamos nombre del atributo: c_value */
        const char *field = "value";
        size_t lf = strlen(field);
        char *fname = (char *)malloc(lo + 1 + lf + 1);
        if (!fname) {
            free(obj);
            rt_runtime_error(stmt->line, "out of memory");
        }
        memcpy(fname, obj, lo);
        fname[lo] = '_';
        memcpy(fname + lo + 1, field, lf);
        fname[lo + 1 + lf] = '\0';

        /* leemos c_value, lo incrementamos y escribimos */
        Value v = env_lookup(env, fname, stmt->line);
        if (v.type != VAL_INT) {
            /* rt_runtime_error probablemente no vuelve, así que no nos preocupamos por free aquí */
            rt_runtime_error(stmt->line, "attribute '%s' is not INTEGER", fname);
        }
        v.as.i += 1;
        env_assign(env, fname, v, stmt->line);

        free(obj);
        free(fname);
        break;
    }
    default:
        rt_runtime_error(stmt->line, "unsupported statement type %d", stmt->type);
    }
}

static Value eval_expr(ASTNode *expr, Env *env) {
    if (!expr) {
        return make_int(0);
    }

    switch (expr->type) {
    case AST_INT_LITERAL:
        return make_int(expr->u.literal.i);
    case AST_STRING_LITERAL:
        return make_string(expr->u.literal.s);
    case AST_VAR:
        return env_lookup(env, expr->u.var.name, expr->line);
    case AST_BINOP: {
        Value l = eval_expr(expr->u.binop.left, env);
        Value r = eval_expr(expr->u.binop.right, env);
        switch (expr->u.binop.op) {
        case OP_ADD:
            /* Suma de enteros */
            if (l.type == VAL_INT && r.type == VAL_INT) {
                return make_int(l.as.i + r.as.i);
            }

            /* Concatenación de strings */
            if (l.type == VAL_STRING && r.type == VAL_STRING) {
                const char *ls = l.as.s ? l.as.s : "";
                const char *rs = r.as.s ? r.as.s : "";

                size_t len1 = strlen(ls);
                size_t len2 = strlen(rs);
                char *buf = (char *)malloc(len1 + len2 + 1);
                if (!buf) {
                    rt_runtime_error(expr->line, "out of memory in string concatenation");
                }

                memcpy(buf, ls, len1);
                memcpy(buf + len1, rs, len2);
                buf[len1 + len2] = '\0';

                return make_string(buf);
            }

            rt_runtime_error(expr->line, "unsupported + operands");
            break;

        case OP_SUB:
            if (l.type == VAL_INT && r.type == VAL_INT) {
                return make_int(l.as.i - r.as.i);
            }
            break;

        case OP_MUL:
            if (l.type == VAL_INT && r.type == VAL_INT) {
                return make_int(l.as.i * r.as.i);
            }
            break;

        case OP_DIV:
            if (l.type == VAL_INT && r.type == VAL_INT) {
                if (r.as.i == 0) {
                    rt_runtime_error(expr->line, "division by zero");
                }
                return make_int(l.as.i / r.as.i);
            }
            break;

        case OP_EQ:
            if (l.type == VAL_INT && r.type == VAL_INT) {
                return make_bool(l.as.i == r.as.i);
            }
            break;

        case OP_LT:
            if (l.type == VAL_INT && r.type == VAL_INT) {
                return make_bool(l.as.i < r.as.i);
            }
            break;

        case OP_GT:
            if (l.type == VAL_INT && r.type == VAL_INT) {
                return make_bool(l.as.i > r.as.i);
            }
            break;

        case OP_LE:
            if (l.type == VAL_INT && r.type == VAL_INT) {
                return make_bool(l.as.i <= r.as.i);
            }
            break;

        case OP_GE:
            if (l.type == VAL_INT && r.type == VAL_INT) {
                return make_bool(l.as.i >= r.as.i);
            }
            break;
        }
        rt_runtime_error(expr->line, "unsupported operands for binary operator");
    }
    default:
        rt_runtime_error(expr->line, "unsupported expression type %d", expr->type);
    }

    /* Solo para calmar al compilador; en teoría nunca se llega acá */
    return make_int(0);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file.e\n", argv[0]);
        return EXIT_FAILURE;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("fopen");
        return EXIT_FAILURE;
    }

    if (yyparse() != 0) {
        fprintf(stderr, "Parse failed.\n");
        fclose(yyin);
        return EXIT_FAILURE;
    }
    fclose(yyin);

    if (!ast_root || ast_root->type != AST_PROGRAM) {
        fprintf(stderr, "No valid program parsed.\n");
        return EXIT_FAILURE;
    }

    ASTNode *class_node = ast_root->u.program.class_node;
    if (!class_node || class_node->type != AST_CLASS) {
        fprintf(stderr, "Expected a MAIN class.\n");
        return EXIT_FAILURE;
    }

    ASTNode *feat = class_node->u.class_.feature;
    if (!feat || feat->type != AST_FEATURE) {
        fprintf(stderr, "Expected a feature make.\n");
        return EXIT_FAILURE;
    }

    Env *global = env_new(NULL);

    /* Declaramos variables locales definidas en la sección local, con tipo */
    ASTNode *locals = feat->u.feature.locals;
    while (locals) {
        ASTNode *decl = locals->u.stmt_list.first;
        if (decl && decl->type == AST_DECL) {
            char *type_name = decl->u.decl.type_name;
            ASTNode *names = decl->u.decl.names;  /* lista de AST_VAR en un AST_STMT_LIST */

            ASTNode *it = names;
            while (it) {
                ASTNode *var = it->u.stmt_list.first;  /* AST_VAR */
                if (var && var->type == AST_VAR) {
                    env_declare(global, var->u.var.name, type_name);
                }
                it = it->u.stmt_list.next;
            }
        }
        locals = locals->u.stmt_list.next;
    }

    /* Ejecutamos el cuerpo de make en el entorno global */
    exec_stmt_list(feat->u.feature.body, global);

    env_free(global);
    ast_free(ast_root);

    return EXIT_SUCCESS;
}
