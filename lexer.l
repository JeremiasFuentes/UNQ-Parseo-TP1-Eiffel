%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"    
#include "parser.tab.h"
#include "debug.h"

extern int yylineno;
%}

%option noyywrap
%option nounput noinput
%option yylineno
%option caseless

WS             [ \t\r\n\f]+
DIGIT          [0-9]
ID_START       [A-Za-z_]
ID_CONT        [A-Za-z0-9_]
STRING_CONTENT ([^\"\n]|\\\")*

%%

"class"        { print_token("TOKEN_CLASS", yytext); return TOKEN_CLASS; }
"inherit"      { print_token("TOKEN_INHERIT", yytext); return TOKEN_INHERIT; }
"feature"      { print_token("TOKEN_FEATURE", yytext); return TOKEN_FEATURE; }
"do"           { print_token("TOKEN_DO", yytext); return TOKEN_DO; }
"end"          { print_token("TOKEN_END", yytext); return TOKEN_END; }
"if"           { print_token("TOKEN_IF", yytext); return TOKEN_IF; }
"then"         { print_token("TOKEN_THEN", yytext); return TOKEN_THEN; }
"else"         { print_token("TOKEN_ELSE", yytext); return TOKEN_ELSE; }
"from"         { print_token("TOKEN_FROM", yytext); return TOKEN_FROM; }
"until"        { print_token("TOKEN_UNTIL", yytext); return TOKEN_UNTIL; }
"loop"         { print_token("TOKEN_LOOP", yytext); return TOKEN_LOOP; }
"create"       { print_token("TOKEN_CREATE", yytext); return TOKEN_CREATE; }
"local"        { print_token("TOKEN_LOCAL", yytext); return TOKEN_LOCAL; }
"print"        { print_token("TOKEN_PRINT", yytext); return TOKEN_PRINT; }

":="           { print_token("TOKEN_ASSIGN", yytext); return TOKEN_ASSIGN; }
"<="           { print_token("TOKEN_LE", yytext); return TOKEN_LE; }
">="           { print_token("TOKEN_GE", yytext); return TOKEN_GE; }
"="            { print_token("TOKEN_EQUAL", yytext); return TOKEN_EQUAL; }
"<"            { print_token("TOKEN_LT", yytext); return TOKEN_LT; }
">"            { print_token("TOKEN_GT", yytext); return TOKEN_GT; }
"("            { print_token("TOKEN_LPAREN", yytext); return TOKEN_LPAREN; }
")"            { print_token("TOKEN_RPAREN", yytext); return TOKEN_RPAREN; }
";"            { print_token("TOKEN_SEMI", yytext); return TOKEN_SEMI; }
"."            { print_token("TOKEN_DOT", yytext); return TOKEN_DOT; }
"+"            { print_token("TOKEN_PLUS", yytext); return TOKEN_PLUS; }
"-"            { print_token("TOKEN_MINUS", yytext); return TOKEN_MINUS; }
"*"            { print_token("TOKEN_MUL", yytext); return TOKEN_MUL; }
"/"            { print_token("TOKEN_DIV", yytext); return TOKEN_DIV; }
":"            { print_token("TOKEN_COLON", yytext); return TOKEN_COLON; }
","            { print_token("TOKEN_COMMA", yytext); return TOKEN_COMMA; }

{DIGIT}+"."{DIGIT}*([eE][+-]?{DIGIT}+)? {
    yylval.rval = strtod(yytext, NULL);
    print_token("TOKEN_REAL", yytext);
    return TOKEN_REAL;
}

{DIGIT}+([eE][+-]?{DIGIT}+) {
    yylval.rval = strtod(yytext, NULL);
    print_token("TOKEN_REAL", yytext);
    return TOKEN_REAL;
}

{DIGIT}+ {
    yylval.ival = strtol(yytext, NULL, 10);
    print_token("TOKEN_INTEGER", yytext);
    return TOKEN_INTEGER;
}

{ID_START}{ID_CONT}* {
    size_t len = yyleng;
    char *buf = (char*)malloc(len + 1);
    if (!buf) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    memcpy(buf, yytext, len);
    buf[len] = '\0';
    yylval.sval = buf;
    print_token("TOKEN_IDENTIFIER", yytext);
    return TOKEN_IDENTIFIER;
}

\"{STRING_CONTENT}\" {
    size_t len = yyleng;
    char *buf = (char*)malloc(len - 1);
    memcpy(buf, yytext + 1, len - 2);
    buf[len - 2] = '\0';
    yylval.sval = buf;
    print_token("TOKEN_STRING", yytext);
    return TOKEN_STRING;
}

"--".* {
    /* skip comment */
}

{WS}+ {
    /* skip whitespace */
}

. {
    fprintf(stderr,
            "Lexical error at line %d: unexpected character '%s'\n",
            yylineno, yytext);
}

%%
