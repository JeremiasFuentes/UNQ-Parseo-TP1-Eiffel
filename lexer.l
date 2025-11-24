%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"    
#include "parser.tab.h"

extern int yylineno;
%}

%option noyywrap
%option nounput noinput
%option yylineno
%option caseless

%%

"class"        { return TOKEN_CLASS; }
"inherit"      { return TOKEN_INHERIT; }
"feature"      { return TOKEN_FEATURE; }
"do"           { return TOKEN_DO; }
"end"          { return TOKEN_END; }
"if"           { return TOKEN_IF; }
"then"         { return TOKEN_THEN; }
"else"         { return TOKEN_ELSE; }
"from"         { return TOKEN_FROM; }
"until"        { return TOKEN_UNTIL; }
"loop"         { return TOKEN_LOOP; }
"create"       { return TOKEN_CREATE; }
"local"        { return TOKEN_LOCAL; }
"print"        { return TOKEN_PRINT; }

":="           { return TOKEN_ASSIGN; }
"<="           { return TOKEN_LE; }
">="           { return TOKEN_GE; }
"="            { return TOKEN_EQUAL; }
"<"            { return TOKEN_LT; }
">"            { return TOKEN_GT; }
"("            { return TOKEN_LPAREN; }
")"            { return TOKEN_RPAREN; }
";"            { return TOKEN_SEMI; }
"."            { return TOKEN_DOT; }
"+"            { return TOKEN_PLUS; }
"-"            { return TOKEN_MINUS; }
"*"            { return TOKEN_MUL; }
"/"            { return TOKEN_DIV; }
":"            { return TOKEN_COLON; }
","            { return TOKEN_COMMA; }

[0-9]+"."[0-9]*([eE][+-]?[0-9]+)? {
    yylval.rval = strtod(yytext, NULL);
    return TOKEN_REAL;
}

[0-9]+ {
    yylval.ival = strtol(yytext, NULL, 10);
    return TOKEN_INTEGER;
}

[A-Za-z_][A-Za-z_0-9]* {
    size_t len = yyleng;
    char *buf = (char*)malloc(len + 1);
    if (!buf) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    memcpy(buf, yytext, len);
    buf[len] = '\0';
    yylval.sval = buf;
    return TOKEN_IDENTIFIER;
}

\"[^"\n]*\" {
    size_t len = yyleng;
    char *buf = (char*)malloc(len - 1);
    memcpy(buf, yytext + 1, len - 2);
    buf[len - 2] = '\0';
    yylval.sval = buf;
    return TOKEN_STRING;
}

"--".* {
    /* skip comment */
}

[ \t\r\n]+ {
    /* skip whitespace */
}

. {
    fprintf(stderr,
            "Lexical error at line %d: unexpected character '%s'\n",
            yylineno, yytext);
}

%%
