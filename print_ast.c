#include <stdio.h>
#include <string.h>
#include "ast.h"

static void print_indent(const char *prefix, int is_last) {
    printf("%s", prefix);
    printf(is_last ? "└── " : "├── ");
}

/* Construye el nuevo prefijo para hijos */
static void build_prefix(char *out, const char *prefix, int is_last) {
    strcpy(out, prefix);
    strcat(out, is_last ? "    " : "│   ");
}

static void print_ast_rec(ASTNode *node, const char *prefix, int is_last);

void print_ast(ASTNode *node) {
    print_ast_rec(node, "", 1);
}

/* Imprime un nodo como string */
static const char *node_type_str(ASTNodeType t) {
    switch(t) {
        case AST_PROGRAM: return "PROGRAM";
        case AST_CLASS: return "CLASS";
        case AST_FEATURE: return "FEATURE";
        case AST_STMT_LIST: return "STMT_LIST";
        case AST_ASSIGN: return "ASSIGN";
        case AST_IF: return "IF";
        case AST_LOOP: return "LOOP";
        case AST_PRINT: return "PRINT";
        case AST_BINOP: return "BINOP";
        case AST_VAR: return "VAR";
        case AST_INT_LITERAL: return "INT_LITERAL";
        case AST_STRING_LITERAL: return "STRING_LITERAL";
        case AST_REAL_LITERAL: return "REAL_LITERAL";
        case AST_CREATE: return "CREATE";
        case AST_CALL_PROC: return "CALL_PROC";
        case AST_DECL: return "DECL";
        default: return "UNKNOWN";
    }
}

static const char *binop_str(BinOp op) {
    switch(op) {
        case OP_ADD: return "+";
        case OP_SUB: return "-";
        case OP_MUL: return "*";
        case OP_DIV: return "/";
        case OP_EQ: return "=";
        case OP_LT: return "<";
        case OP_GT: return ">";
        case OP_LE: return "<=";
        case OP_GE: return ">=";
        default: return "?";
    }
}

/* ----------------------------- */
/*  IMPRESIÓN RECURSIVA DEL AST */
/* ----------------------------- */

static void print_ast_rec(ASTNode *node, const char *prefix, int is_last) {
    if (!node) return;

    print_indent(prefix, is_last);
    printf("%s", node_type_str(node->type));

    /* Información adicional según tipo */
    switch(node->type) {
        case AST_CLASS:
            printf(" (%s)", node->u.class_.name);
            break;
        case AST_FEATURE:
            printf(" (%s)", node->u.feature.name);
            break;
        case AST_ASSIGN:
            printf(" (%s = ...)", node->u.assign.name);
            break;
        case AST_VAR:
            printf(" (%s)", node->u.var.name);
            break;
        case AST_INT_LITERAL:
            printf(" (%ld)", node->u.literal.i);
            break;
        case AST_STRING_LITERAL:
            printf(" (\"%s\")", node->u.literal.s);
            break;
        case AST_BINOP:
            printf(" (%s)", binop_str(node->u.binop.op));
            break;
        case AST_CREATE:
            printf(" (create %s)", node->u.create.name);
            break;
        case AST_CALL_PROC:
            printf(" (call %s)", node->u.call_proc.name);
            break;
        case AST_DECL:
            printf(" (: %s)", node->u.decl.type_name);
            break;
        default:
            break;
    }

    printf("\n");

    /* Hijos — determinamos cuántos hay */
    ASTNode *children[4];
    int count = 0;

    switch(node->type) {

        case AST_PROGRAM:
            children[count++] = node->u.program.class_node;
            break;

        case AST_CLASS:
            children[count++] = node->u.class_.feature;
            break;

        case AST_FEATURE:
            children[count++] = node->u.feature.locals;
            children[count++] = node->u.feature.body;
            break;

        case AST_STMT_LIST:
            children[count++] = node->u.stmt_list.first;
            children[count++] = node->u.stmt_list.next;
            break;

        case AST_ASSIGN:
            children[count++] = node->u.assign.expr;
            break;

        case AST_IF:
            children[count++] = node->u.if_stmt.cond;
            children[count++] = node->u.if_stmt.then_branch;
            if (node->u.if_stmt.else_branch)
                children[count++] = node->u.if_stmt.else_branch;
            break;

        case AST_LOOP:
            children[count++] = node->u.loop.init;
            children[count++] = node->u.loop.cond;
            children[count++] = node->u.loop.body;
            break;

        case AST_PRINT:
            children[count++] = node->u.print.expr;
            break;

        case AST_BINOP:
            children[count++] = node->u.binop.left;
            children[count++] = node->u.binop.right;
            break;

        case AST_DECL:
            children[count++] = node->u.decl.names;
            break;

        default:
            break;
    }

    /* Imprimir hijos */
    for (int i = 0; i < count; i++) {
        char new_prefix[256];
        build_prefix(new_prefix, prefix, is_last);
        print_ast_rec(children[i], new_prefix, i == count - 1);
    }
}
