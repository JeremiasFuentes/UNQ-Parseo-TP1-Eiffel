#include "ast.h"
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

static ASTNode *new_node(ASTNodeType type, int line) {
    ASTNode *n = (ASTNode *)calloc(1, sizeof(ASTNode));
    if (!n) return NULL;
    n->type = type;
    n->line = line;
    return n;
}

ASTNode *ast_program(ASTNode *class_node, int line) {
    ASTNode *n = new_node(AST_PROGRAM, line);
    n->u.program.class_node = class_node;
    return n;
}

ASTNode *ast_class(char *name, ASTNode *feature, int line) {
    ASTNode *n = new_node(AST_CLASS, line);
    n->u.class_.name = xstrdup(name);
    n->u.class_.feature = feature;
    return n;
}

ASTNode *ast_feature(char *name, ASTNode *locals, ASTNode *body, int line) {
    ASTNode *n = new_node(AST_FEATURE, line);
    n->u.feature.name = xstrdup(name);
    n->u.feature.locals = locals;
    n->u.feature.body = body;
    return n;
}

ASTNode *ast_stmt_list_single(ASTNode *stmt, int line) {
    if (!stmt) return NULL;
    ASTNode *n = new_node(AST_STMT_LIST, line);
    n->u.stmt_list.first = stmt;
    n->u.stmt_list.next = NULL;
    return n;
}

ASTNode *ast_stmt_list_append(ASTNode *list, ASTNode *stmt) {
    if (!stmt) return list;
    if (!list) return ast_stmt_list_single(stmt, stmt->line);
    ASTNode *it = list;
    while (it->u.stmt_list.next) {
        it = it->u.stmt_list.next;
    }
    it->u.stmt_list.next = ast_stmt_list_single(stmt, stmt->line);
    return list;
}

ASTNode *ast_stmt_list_concat(ASTNode *a, ASTNode *b) {
    if (!a) return b;
    if (!b) return a;
    ASTNode *it = a;
    while (it->u.stmt_list.next) {
        it = it->u.stmt_list.next;
    }
    it->u.stmt_list.next = b;
    return a;
}

ASTNode *ast_assign(char *name, ASTNode *expr, int line) {
    ASTNode *n = new_node(AST_ASSIGN, line);
    n->u.assign.name = xstrdup(name);
    n->u.assign.expr = expr;
    return n;
}

ASTNode *ast_if(ASTNode *cond, ASTNode *then_branch, ASTNode *else_branch, int line) {
    ASTNode *n = new_node(AST_IF, line);
    n->u.if_stmt.cond = cond;
    n->u.if_stmt.then_branch = then_branch;
    n->u.if_stmt.else_branch = else_branch;
    return n;
}

ASTNode *ast_loop(ASTNode *init, ASTNode *cond, ASTNode *body, int line) {
    ASTNode *n = new_node(AST_LOOP, line);
    n->u.loop.init = init;
    n->u.loop.cond = cond;
    n->u.loop.body = body;
    return n;
}

ASTNode *ast_print(ASTNode *expr, int line) {
    ASTNode *n = new_node(AST_PRINT, line);
    n->u.print.expr = expr;
    return n;
}

ASTNode *ast_binop(BinOp op, ASTNode *left, ASTNode *right, int line) {
    ASTNode *n = new_node(AST_BINOP, line);
    n->u.binop.op = op;
    n->u.binop.left = left;
    n->u.binop.right = right;
    return n;
}

ASTNode *ast_var(char *name, int line) {
    ASTNode *n = new_node(AST_VAR, line);
    n->u.var.name = xstrdup(name);
    return n;
}

ASTNode *ast_int_literal(long v, int line) {
    ASTNode *n = new_node(AST_INT_LITERAL, line);
    n->u.literal.i = v;
    n->u.literal.s = NULL;
    return n;
}

ASTNode *ast_string_literal(char *s, int line) {
    ASTNode *n = new_node(AST_STRING_LITERAL, line);
    n->u.literal.s = xstrdup(s);
    n->u.literal.i = 0;
    return n;
}

ASTNode *ast_create(char *name, int line) {
    ASTNode *n = new_node(AST_CREATE, line);
    n->u.create.name = xstrdup(name);
    return n;
}

ASTNode *ast_call_proc(char *name, int line) {
    ASTNode *n = new_node(AST_CALL_PROC, line);
    n->u.call_proc.name = xstrdup(name);
    return n;
}

ASTNode *ast_decl(ASTNode *names, char *type_name, int line) {
    ASTNode *n = new_node(AST_DECL, line);
    n->u.decl.names = names;
    n->u.decl.type_name = type_name ? xstrdup(type_name) : NULL;
    return n;
}

void ast_free(ASTNode *node) {
    if (!node) return;

    switch (node->type) {

    case AST_PROGRAM:
        ast_free(node->u.program.class_node);
        break;

    case AST_CLASS:
        free(node->u.class_.name);
        ast_free(node->u.class_.feature);
        break;

    case AST_FEATURE:
        free(node->u.feature.name);
        ast_free(node->u.feature.locals);
        ast_free(node->u.feature.body);
        break;

    case AST_STMT_LIST: {
        ASTNode *it = node;
        while (it) {
            ASTNode *next = it->u.stmt_list.next;
            ast_free(it->u.stmt_list.first);
            if (it != node) {
                free(it);
            }
            it = next;
        }
        break;
    }

    case AST_ASSIGN:
        free(node->u.assign.name);
        ast_free(node->u.assign.expr);
        break;

    case AST_IF:
        ast_free(node->u.if_stmt.cond);
        ast_free(node->u.if_stmt.then_branch);
        ast_free(node->u.if_stmt.else_branch);
        break;

    case AST_LOOP:
        ast_free(node->u.loop.init);
        ast_free(node->u.loop.cond);
        ast_free(node->u.loop.body);
        break;

    case AST_PRINT:
        ast_free(node->u.print.expr);
        break;

    case AST_BINOP:
        ast_free(node->u.binop.left);
        ast_free(node->u.binop.right);
        break;

    case AST_VAR:
        free(node->u.var.name);
        break;

    case AST_INT_LITERAL:
    case AST_REAL_LITERAL:
        /* nada extra que liberar */
        break;

    case AST_STRING_LITERAL:
        free(node->u.literal.s);
        break;

    case AST_CREATE:
        free(node->u.create.name);
        break;

    case AST_CALL_PROC:
        free(node->u.call_proc.name);
        break;

    case AST_DECL:
        ast_free(node->u.decl.names);
        free(node->u.decl.type_name);
        break;
    }



    free(node);
}

