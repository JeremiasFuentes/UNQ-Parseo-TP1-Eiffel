%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

int yylex(void);
void yyerror(const char *s);
extern int yylineno;

ASTNode *ast_root = NULL;

/* arma nombres tipo "c_value" o "c_inc" */
static char *make_field_name(const char *obj, const char *field) {
    size_t lo = strlen(obj), lf = strlen(field);
    char *s = (char *)malloc(lo + 1 + lf + 1);
    if (!s) {
        fprintf(stderr, "Out of memory in make_field_name\n");
        exit(1);
    }
    memcpy(s, obj, lo);
    s[lo] = '_';
    memcpy(s + lo + 1, field, lf);
    s[lo + 1 + lf] = '\0';
    return s;
}
%}

%union {
    long ival;
    double rval;
    char *sval;
    ASTNode *node;
}

/* Tokens que viene del lexer */
%token TOKEN_CLASS TOKEN_INHERIT TOKEN_FEATURE TOKEN_DO TOKEN_END
%token TOKEN_IF TOKEN_THEN TOKEN_ELSE
%token TOKEN_FROM TOKEN_UNTIL TOKEN_LOOP
%token TOKEN_CREATE TOKEN_LOCAL TOKEN_PRINT

%token TOKEN_ASSIGN
%token TOKEN_LE TOKEN_GE TOKEN_EQUAL TOKEN_LT TOKEN_GT
%token TOKEN_LPAREN TOKEN_RPAREN TOKEN_SEMI TOKEN_DOT
%token TOKEN_PLUS TOKEN_MINUS TOKEN_MUL TOKEN_DIV
%token TOKEN_COLON TOKEN_COMMA

%token <sval> TOKEN_IDENTIFIER
%token <ival> TOKEN_INTEGER
%token TOKEN_REAL
%token <sval> TOKEN_STRING

%type <node> program class_def feature_block feature_list feature_or_attr feature
%type <node> opt_locals local_decl_list local_decl id_list
%type <node> stmt_list stmt_item stmt
%type <node> loop_stmt if_stmt print_stmt
%type <node> expr

%left TOKEN_EQUAL TOKEN_LT TOKEN_GT TOKEN_LE TOKEN_GE
%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_MUL TOKEN_DIV
%right UMINUS

%%

/* Un programa puede tener una o más clases; nos quedamos con la última (MAIN) */
program
    : class_def
      {
          ast_root = ast_program($1, yylineno);
          $$ = $1;
      }
    | program class_def
      {
          ast_root = ast_program($2, yylineno);
          $$ = $2;
      }
    ;

class_def
    : TOKEN_CLASS TOKEN_IDENTIFIER feature_block TOKEN_END
      { $$ = ast_class($2, $3, yylineno); }
    ;

/* Bloque de features:
   acepta atributos y routines, pero solo nos interesa la PRIMER routine. */
feature_block
    : TOKEN_FEATURE feature_list
      { $$ = $2; }
    ;

/* feature_list devuelve la PRIMER routine que encuentre (o NULL si no hay) */
feature_list
    : feature_or_attr
      { $$ = $1; }
    | feature_list feature_or_attr
      { $$ = $1 ? $1 : $2; }
    ;

/* Un miembro puede ser:
 *  - un atributo: value: INTEGER [;]
 *  - una routine: make ... end, inc ... end
 */
feature_or_attr
    /* atributo: value: INTEGER */
    : TOKEN_IDENTIFIER TOKEN_COLON TOKEN_IDENTIFIER
      { $$ = NULL; }
    /* atributo con ; opcional */
    | TOKEN_IDENTIFIER TOKEN_COLON TOKEN_IDENTIFIER TOKEN_SEMI
      { $$ = NULL; }

    /* routine con locals: make / inc / etc. */
    | feature
      { $$ = $1; }
    ;

/* Una routine: make, inc, etc.
   Reutilizamos opt_locals y stmt_list. */
feature
    : TOKEN_IDENTIFIER opt_locals TOKEN_DO stmt_list TOKEN_END
      { $$ = ast_feature($1, $2, $4, yylineno); }
    ;

opt_locals
    : /* empty */
      { $$ = NULL; }
    | TOKEN_LOCAL local_decl_list
      { $$ = $2; }
    ;

local_decl_list
    : local_decl
      { $$ = ast_stmt_list_single($1, yylineno); }
    | local_decl_list local_decl
      { $$ = ast_stmt_list_append($1, $2); }
    ;

/* Declaraciones locales: x, y: INTEGER [;] */
local_decl
    : id_list TOKEN_COLON TOKEN_IDENTIFIER
      { $$ = ast_decl($1, $3, yylineno); }
    | id_list TOKEN_COLON TOKEN_IDENTIFIER TOKEN_SEMI
      { $$ = ast_decl($1, $3, yylineno); }
    ;

/* Lista de identificadores: x, y, z */
id_list
    : TOKEN_IDENTIFIER
      { $$ = ast_stmt_list_single(ast_var($1, yylineno), yylineno); }
    | id_list TOKEN_COMMA TOKEN_IDENTIFIER
      { $$ = ast_stmt_list_append($1, ast_var($3, yylineno)); }
    ;

/* Lista de sentencias, admitiendo ; opcionales */
stmt_list
    : /* empty */
      { $$ = NULL; }
    | stmt_item
      { $$ = ast_stmt_list_single($1, yylineno); }
    | stmt_list stmt_item
      { $$ = ast_stmt_list_append($1, $2); }
    ;

/* Una sentencia con o sin ; final */
stmt_item
    : stmt
      { $$ = $1; }
    | stmt TOKEN_SEMI
      { $$ = $1; }
    ;

stmt
    : TOKEN_IDENTIFIER TOKEN_ASSIGN expr
      { $$ = ast_assign($1, $3, yylineno); }
    | if_stmt
      { $$ = $1; }
    | loop_stmt
      { $$ = $1; }
    | print_stmt
      { $$ = $1; }

    /* create c */
    | TOKEN_CREATE TOKEN_IDENTIFIER
      { $$ = ast_create($2, yylineno); }

    /* c.value := expr → asignación al atributo "c_value" */
    | TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER TOKEN_ASSIGN expr
      {
          char *fname = make_field_name($1, $3);        /* "c_value" */
          $$ = ast_assign(fname, $5, yylineno);         /* ast_assign("c_value", expr) */
          free(fname);
      }

    /* c.inc → call_proc con nombre "c_inc" */
    | TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER
      {
          char *mname = make_field_name($1, $3);        /* "c_inc" */
          $$ = ast_call_proc(mname, yylineno);
          free(mname);
      }
    ;

if_stmt
    : TOKEN_IF expr TOKEN_THEN stmt_list TOKEN_ELSE stmt_list TOKEN_END
      { $$ = ast_if($2, $4, $6, yylineno); }
    | TOKEN_IF expr TOKEN_THEN stmt_list TOKEN_END
      { $$ = ast_if($2, $4, NULL, yylineno); }
    ;

loop_stmt
    : TOKEN_FROM stmt_list TOKEN_UNTIL expr TOKEN_LOOP stmt_list TOKEN_END
      { $$ = ast_loop($2, $4, $6, yylineno); }
    ;

print_stmt
    : TOKEN_PRINT TOKEN_LPAREN expr TOKEN_RPAREN
      { $$ = ast_print($3, yylineno); }
    ;

/* Expresiones: enteros, strings, comparaciones, + con enteros y strings, etc. */
expr
    : expr TOKEN_PLUS expr
      { $$ = ast_binop(OP_ADD, $1, $3, yylineno); }
    | expr TOKEN_MINUS expr
      { $$ = ast_binop(OP_SUB, $1, $3, yylineno); }
    | expr TOKEN_MUL expr
      { $$ = ast_binop(OP_MUL, $1, $3, yylineno); }
    | expr TOKEN_DIV expr
      { $$ = ast_binop(OP_DIV, $1, $3, yylineno); }
    | expr TOKEN_EQUAL expr
      { $$ = ast_binop(OP_EQ, $1, $3, yylineno); }
    | expr TOKEN_LT expr
      { $$ = ast_binop(OP_LT, $1, $3, yylineno); }
    | expr TOKEN_GT expr
      { $$ = ast_binop(OP_GT, $1, $3, yylineno); }
    | expr TOKEN_LE expr
      { $$ = ast_binop(OP_LE, $1, $3, yylineno); }
    | expr TOKEN_GE expr
      { $$ = ast_binop(OP_GE, $1, $3, yylineno); }
    | TOKEN_MINUS expr %prec UMINUS
      { $$ = ast_binop(OP_SUB, ast_int_literal(0, yylineno), $2, yylineno); }
    | TOKEN_LPAREN expr TOKEN_RPAREN
      { $$ = $2; }
    | TOKEN_INTEGER
      { $$ = ast_int_literal($1, yylineno); }
    | TOKEN_STRING
      { $$ = ast_string_literal($1, yylineno); }

    /* c.value → variable "c_value" */
    | TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER
      {
          char *fname = make_field_name($1, $3);
          $$ = ast_var(fname, yylineno);
          free(fname);
      }

    | TOKEN_IDENTIFIER
      { $$ = ast_var($1, yylineno); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, s);
}
