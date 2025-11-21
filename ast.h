#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "value.h"

/* ---------------------------
   Tipos de nodos usados por ast.c
   ---------------------------*/

/* Tipos de expresiones */
typedef enum { EXPR_INT, EXPR_REAL, EXPR_STRING, EXPR_VAR, EXPR_BINOP } ExprKind;

/* Expresión */
typedef struct Expr {
    ExprKind kind;
    long i;
    double r;
    char *s;       /* para cadenas, nombre de variable o símbolo del binop */
    struct Expr *left;
    struct Expr *right;
} Expr;

/* Declaración local (lista enlazada simple) */
typedef struct LocalDecl {
    char *name;
    struct LocalDecl *next;
} LocalDecl;

typedef struct Locals {
    LocalDecl *first;
} Locals;

/* Sentencias */
typedef enum { STMT_ASSIGN, STMT_PRINT, STMT_IF, STMT_FROM_UNTIL, STMT_CALL } StmtKind;

typedef struct Stmt {
    StmtKind kind;
    /* para asignación y llamada */
    char *assign_name;   /* nombre variable (assign) o nombre de llamada (call) */
    Expr *assign_expr;   /* expresión asignada (assign) */

    /* para print */
    Expr *print_expr;

    /* para if */
    Expr *cond;
    struct Stmts *then_branch;
    struct Stmts *else_branch;

    /* para from ... until ... loop ... end */
    struct Stmts *from_init;
    Expr *until_cond;
    struct Stmts *loop_body;

    /* enlace a siguiente sentencia en lista */
    struct Stmt *next;
} Stmt;

typedef struct Stmts {
    Stmt *first;
} Stmts;

/* Features (rutinas) */
typedef struct Feature {
    char *name;
    Locals *locals;
    Stmts *body;
    struct Feature *next;
} Feature;

typedef struct Features {
    Feature *first;
} Features;

/* Clase y Programa */
typedef struct ClassNode {
    char *name;
    Features *features;
} ClassNode;

typedef struct Program {
    ClassNode *klass;
} Program;

/* ---------------------------
   Prototipos (constructores / utilidades)
   ---------------------------*/

/* Programa / Clase */
Program *make_program(ClassNode *c);
ClassNode *make_class(char *name, Features *f);

/* Features */
Feature *make_feature(char *name, Locals *locals, Stmts *body);
Features *single_feature(Feature *f);
Features *append_feature(Features *list, Feature *f);

/* Locals */
LocalDecl *make_local(char *name);
LocalDecl *append_local(LocalDecl *list, char *name);
Locals *single_locals(LocalDecl *d);

/* Statements */
Stmts *append_stmt(Stmts *list, Stmt *s);
Stmt *make_assign(char *name, Expr *e);
Stmt *make_print(Expr *e);
Stmt *make_if(Expr *cond, Stmts *t, Stmts *e);
Stmt *make_from_until(Stmts *init, Expr *untilc, Stmts *body);
Stmt *make_call(char *name);

/* Expressions */
Expr *make_int_literal(long v);
Expr *make_real_literal(double v);
Expr *make_string_literal(char *s);
Expr *make_varref(char *name);
Expr *make_binop(const char *op, Expr *l, Expr *r);

/* Interpreter entry + free */
void interpret_program(Program *p);
void free_program(Program *p);

#endif /* AST_H */
