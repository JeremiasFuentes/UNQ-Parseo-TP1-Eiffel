%{
  #include <stdio.h>
  int yylex(void);
  int yyerror(const char *s) { return 0; }
%}

%token TOKEN_CLASS TOKEN_INHERIT TOKEN_FEATURE TOKEN_DO TOKEN_END
%token TOKEN_IF TOKEN_THEN TOKEN_ELSE TOKEN_FROM TOKEN_UNTIL TOKEN_LOOP
%token TOKEN_CREATE
%token TOKEN_IDENTIFIER TOKEN_INTEGER TOKEN_REAL TOKEN_STRING
%token TOKEN_ASSIGN TOKEN_EQUAL TOKEN_LT TOKEN_GT TOKEN_LE TOKEN_GE
%token TOKEN_LPAREN TOKEN_RPAREN TOKEN_SEMI TOKEN_DOT TOKEN_COLON TOKEN_COMMA
%token TOKEN_PLUS TOKEN_MINUS TOKEN_MUL TOKEN_DIV

%%

input
  : /* empty */
  | input token
  ;

token
  : TOKEN_CLASS
  | TOKEN_INHERIT
  | TOKEN_FEATURE
  | TOKEN_DO
  | TOKEN_END
  | TOKEN_IF
  | TOKEN_THEN
  | TOKEN_ELSE
  | TOKEN_FROM
  | TOKEN_UNTIL
  | TOKEN_LOOP
  | TOKEN_CREATE
  | TOKEN_IDENTIFIER
  | TOKEN_INTEGER
  | TOKEN_REAL
  | TOKEN_STRING
  | TOKEN_ASSIGN
  | TOKEN_EQUAL
  | TOKEN_LT
  | TOKEN_GT
  | TOKEN_LE
  | TOKEN_GE
  | TOKEN_LPAREN
  | TOKEN_RPAREN
  | TOKEN_SEMI
  | TOKEN_DOT
  | TOKEN_PLUS
  | TOKEN_MINUS
  | TOKEN_MUL
  | TOKEN_DIV
  | TOKEN_COLON
  | TOKEN_COMMA
  ;

%%

int main(int argc, char **argv) {
  extern FILE *yyin;
  if (argc > 1) {
    yyin = fopen(argv[1], "r");
    if (!yyin) { perror(argv[1]); return 1; }
  }
  return yyparse();
}
