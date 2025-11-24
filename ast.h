#ifndef AST_H
#define AST_H

#include <stdbool.h>

/* Runtime value type */

typedef enum {
    VAL_INT,
    VAL_BOOL,
    VAL_STRING
} ValueType;

typedef struct Value {
    ValueType type;
    union {
        long i;
        int b;
        char *s;
    } as;
} Value;

/* AST node types */

typedef enum {
    AST_PROGRAM,
    AST_CLASS,
    AST_FEATURE,
    AST_STMT_LIST,
    AST_ASSIGN,
    AST_IF,
    AST_LOOP,
    AST_PRINT,
    AST_BINOP,
    AST_VAR,
    AST_INT_LITERAL,
    AST_STRING_LITERAL,
    AST_REAL_LITERAL,
    AST_CREATE,      // create c
    AST_CALL_PROC,    // c.inc
    AST_DECL
} ASTNodeType;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_EQ,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE
} BinOp;

typedef struct ASTNode ASTNode;

struct ASTNode {
    ASTNodeType type;
    int line;
    union {
        struct {
            ASTNode *class_node;
        } program;

        struct {
            char *name;
            ASTNode *feature;
        } class_;

        struct {
            char *name;
            ASTNode *locals; /* AST_STMT_LIST of AST_VAR */
            ASTNode *body;   /* AST_STMT_LIST of statements */
        } feature;

        struct {
            ASTNode *first; /* the statement/var */
            ASTNode *next;  /* next node in list (or NULL) */
        } stmt_list;

        struct {
            char *name;
            ASTNode *expr;
        } assign;

        struct {
            ASTNode *cond;
            ASTNode *then_branch;
            ASTNode *else_branch; /* may be NULL */
        } if_stmt;

        struct {
            ASTNode *init; /* stmt_list */
            ASTNode *cond; /* expr */
            ASTNode *body; /* stmt_list */
        } loop;

        struct {
            ASTNode *expr;
        } print;

        struct {
            BinOp op;
            ASTNode *left;
            ASTNode *right;
        } binop;

        struct {
            char *name;
        } var;

        struct {
            long i;
            char *s;
        } literal;
        struct { char *name; } create; 
        struct { char *name; } call_proc;
        struct { ASTNode *names; char *type_name; } decl;
    } u;
};

/* Constructors */

ASTNode *ast_program(ASTNode *class_node, int line);
ASTNode *ast_class(char *name, ASTNode *feature, int line);
ASTNode *ast_feature(char *name, ASTNode *locals, ASTNode *body, int line);

ASTNode *ast_stmt_list_single(ASTNode *stmt, int line);
ASTNode *ast_stmt_list_append(ASTNode *list, ASTNode *stmt);
ASTNode *ast_stmt_list_concat(ASTNode *a, ASTNode *b);

ASTNode *ast_assign(char *name, ASTNode *expr, int line);
ASTNode *ast_if(ASTNode *cond, ASTNode *then_branch, ASTNode *else_branch, int line);
ASTNode *ast_loop(ASTNode *init, ASTNode *cond, ASTNode *body, int line);
ASTNode *ast_print(ASTNode *expr, int line);
ASTNode *ast_binop(BinOp op, ASTNode *left, ASTNode *right, int line);
ASTNode *ast_var(char *name, int line);
ASTNode *ast_int_literal(long v, int line);
ASTNode *ast_string_literal(char *s, int line);
ASTNode *ast_create(char *name, int line);
ASTNode *ast_call_proc(char *name, int line);
ASTNode *ast_decl(ASTNode *names, char *type_name, int line);

/* For ahora no liberamos recursivamente: programas chicos -> pérdidas aceptables */
void ast_free(ASTNode *node);

#endif
