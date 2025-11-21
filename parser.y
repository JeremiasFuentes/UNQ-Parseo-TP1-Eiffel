%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"

    int yylex(void);
    int yyerror(const char *s) {
        fprintf(stderr, "Parser error: %s\n", s);
        return 0;
    }

    Program* root_program = NULL;
%}

/* ------------------------------------------------------------------------- */
/* UNION: tipos de datos usados en tokens y no-terminales                   */
/* ------------------------------------------------------------------------- */

%union {
    char* str;          /* strings e identificadores */
    int   ival;         /* literales enteros */
    double rval;        /* literales reales */
    //bool bval;          /*booleanos */
    void* node;      /* nodos individuales del AST */
    void* nodelist;  /* listas de nodos */
}

/* ------------------------------------------------------------------------- */
/* TOKENS CON VALOR                                                          */
/* ------------------------------------------------------------------------- */
%token <str> TOKEN_IDENTIFIER
%token <ival> TOKEN_INTEGER
%token <rval> TOKEN_REAL
%token <str> TOKEN_STRING

/* ------------------------------------------------------------------------- */
/* TOKENS SIN VALOR                                                          */
/* ------------------------------------------------------------------------- */
%token TOKEN_CLASS TOKEN_INHERIT TOKEN_FEATURE TOKEN_DO TOKEN_END
%token TOKEN_IF TOKEN_THEN TOKEN_ELSE TOKEN_FROM TOKEN_UNTIL TOKEN_LOOP
%token TOKEN_CREATE
%token TOKEN_ASSIGN TOKEN_EQUAL TOKEN_LT TOKEN_GT TOKEN_LE TOKEN_GE
%token TOKEN_LPAREN TOKEN_RPAREN TOKEN_SEMI TOKEN_DOT TOKEN_COLON TOKEN_COMMA
%token TOKEN_PLUS TOKEN_MINUS TOKEN_MUL TOKEN_DIV
%token TOKEN_LOCAL TOKEN_PRINT

/* ------------------------------------------------------------------------- */
/* TIPOS DE NO TERMINALES                                                    */
/* ------------------------------------------------------------------------- */
%type <node> class_decl feature_decl statement expr stmt_block if_stmt loop_stmt
%type <node> local_decl assign_stmt call_stmt print_stmt
%type <nodelist> class_list feature_list stmt_list local_list

/* Prioridades y asociatividad */
%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_MUL TOKEN_DIV
%left TOKEN_EQUAL TOKEN_LT TOKEN_GT TOKEN_LE TOKEN_GE

%%

/* ------------------------------------------------------------------------- */
/* REGLA PRINCIPAL                                                           */
/* ------------------------------------------------------------------------- */

program:
      class_list                   { root_program = make_program($1); }
    ;

class_list:
      class_decl                   { $$ = list_new($1); }
    | class_list class_decl        { $$ = list_append($1, $2); }
    ;

class_decl:
      TOKEN_CLASS TOKEN_IDENTIFIER TOKEN_FEATURE feature_list TOKEN_END
        { $$ = make_class($2, $4); free($2); }
    ;

/* ------------------------------------------------------------------------- */
/* FEATURES / MÉTODOS                                                        */
/* ------------------------------------------------------------------------- */

feature_list:
      feature_decl                 { $$ = list_new($1); }
    | feature_list feature_decl    { $$ = list_append($1, $2); }
    ;

feature_decl:
      TOKEN_IDENTIFIER local_decl TOKEN_DO stmt_list TOKEN_END
        {
            $$ = make_feature($1, $2, $4);
            free($1);
        }
    | TOKEN_IDENTIFIER TOKEN_DO stmt_list TOKEN_END
        {
            $$ = make_feature($1, NULL, $3);
            free($1);
        }
    ;

/* ------------------------------------------------------------------------- */
/* SECCIÓN LOCAL                                                             */
/* ------------------------------------------------------------------------- */

local_decl:
      TOKEN_COLON local_list TOKEN_SEMI    { $$ = make_locals($2); }
    | /* vacio */                          { $$ = NULL; }
    ;

local_list:
      TOKEN_IDENTIFIER                     { $$ = list_new(make_local($1)); free($1); }
    | local_list TOKEN_COMMA TOKEN_IDENTIFIER
                                            { $$ = list_append($1, make_local($3)); free($3); }
    ;

/* ------------------------------------------------------------------------- */
/* STATEMENTS                                                                */
/* ------------------------------------------------------------------------- */

stmt_list:
      statement                             { $$ = list_new($1); }
    | stmt_list statement                    { $$ = list_append($1, $2); }
    ;

statement:
      assign_stmt                            { $$ = $1; }
    | if_stmt                                { $$ = $1; }
    | loop_stmt                              { $$ = $1; }
    | print_stmt                             { $$ = $1; }
    | call_stmt                              { $$ = $1; }
    ;

/* ------------------------------------------------------------------------- */
/* ASIGNACIÓN                                                                */
/* ------------------------------------------------------------------------- */

assign_stmt:
      TOKEN_IDENTIFIER TOKEN_ASSIGN expr
        {
            $$ = make_assign($1, $3);
            free($1);
        }
    ;

/* ------------------------------------------------------------------------- */
/* PRINT                                                                     */
/* ------------------------------------------------------------------------- */

print_stmt:
      TOKEN_IDENTIFIER TOKEN_LPAREN expr TOKEN_RPAREN
        {
            if (strcasecmp($1, "print") != 0) {
                fprintf(stderr, "Error: expected 'print'\n");
            }
            $$ = make_print($3);
            free($1);
        }
    ;

/* ------------------------------------------------------------------------- */
/* LLAMADAS A MÉTODOS                                                        */
/* ------------------------------------------------------------------------- */

call_stmt:
      TOKEN_IDENTIFIER TOKEN_LPAREN TOKEN_RPAREN
        {
            $$ = make_call($1);
            free($1);
        }
    ;

/* ------------------------------------------------------------------------- */
/* IF / ELSE                                                                 */
/* ------------------------------------------------------------------------- */

if_stmt:
      TOKEN_IF expr TOKEN_THEN stmt_list TOKEN_ELSE stmt_list TOKEN_END
        { $$ = make_if($2, $4, $6); }
    | TOKEN_IF expr TOKEN_THEN stmt_list TOKEN_END
        { $$ = make_if($2, $4, NULL); }
    ;

/* ------------------------------------------------------------------------- */
/* FROM-UNTIL-LOOP                                                            */
/* ------------------------------------------------------------------------- */

loop_stmt:
      TOKEN_FROM stmt_list TOKEN_UNTIL expr TOKEN_LOOP stmt_list TOKEN_END
        { $$ = make_loop($2, $4, $6); }
    ;

/* ------------------------------------------------------------------------- */
/* EXPRESIONES                                                               */
/* ------------------------------------------------------------------------- */

expr:
      TOKEN_INTEGER                    { $$ = make_int_literal($1); }
    | TOKEN_REAL                       { $$ = make_real_literal($1); }
    | TOKEN_STRING                     { $$ = make_string_literal($1); free($1); }
    | TOKEN_IDENTIFIER                 { $$ = make_varref($1); free($1); }
    | expr TOKEN_PLUS expr             { $$ = make_binop("+", $1, $3); }
    | expr TOKEN_MINUS expr            { $$ = make_binop("-", $1, $3); }
    | expr TOKEN_MUL expr              { $$ = make_binop("*", $1, $3); }
    | expr TOKEN_DIV expr              { $$ = make_binop("/", $1, $3); }
    | expr TOKEN_EQUAL expr            { $$ = make_binop("=", $1, $3); }
    | expr TOKEN_LT expr               { $$ = make_binop("<", $1, $3); }
    | expr TOKEN_GT expr               { $$ = make_binop(">", $1, $3); }
    | expr TOKEN_LE expr               { $$ = make_binop("<=", $1, $3); }
    | expr TOKEN_GE expr               { $$ = make_binop(">=", $1, $3); }
    | TOKEN_LPAREN expr TOKEN_RPAREN   { $$ = $2; }
    ;

%%

/* ------------------------------------------------------------------------- */
/* MAIN                                                                       */
/* ------------------------------------------------------------------------- */

int main(int argc, char **argv) {
    extern FILE *yyin;

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) { perror(argv[1]); return 1; }
    }

    yyparse();

    /* root_program ahora contiene el AST completo */
    if (root_program)
        interpret_program(root_program);  /* llamada al intérprete */

    return 0;
}
