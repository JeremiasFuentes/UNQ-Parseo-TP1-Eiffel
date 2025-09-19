/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_CLASS = 258,             /* TOKEN_CLASS  */
    TOKEN_INHERIT = 259,           /* TOKEN_INHERIT  */
    TOKEN_FEATURE = 260,           /* TOKEN_FEATURE  */
    TOKEN_DO = 261,                /* TOKEN_DO  */
    TOKEN_END = 262,               /* TOKEN_END  */
    TOKEN_IF = 263,                /* TOKEN_IF  */
    TOKEN_THEN = 264,              /* TOKEN_THEN  */
    TOKEN_ELSE = 265,              /* TOKEN_ELSE  */
    TOKEN_FROM = 266,              /* TOKEN_FROM  */
    TOKEN_UNTIL = 267,             /* TOKEN_UNTIL  */
    TOKEN_LOOP = 268,              /* TOKEN_LOOP  */
    TOKEN_CREATE = 269,            /* TOKEN_CREATE  */
    TOKEN_IDENTIFIER = 270,        /* TOKEN_IDENTIFIER  */
    TOKEN_INTEGER = 271,           /* TOKEN_INTEGER  */
    TOKEN_REAL = 272,              /* TOKEN_REAL  */
    TOKEN_STRING = 273,            /* TOKEN_STRING  */
    TOKEN_ASSIGN = 274,            /* TOKEN_ASSIGN  */
    TOKEN_EQUAL = 275,             /* TOKEN_EQUAL  */
    TOKEN_LT = 276,                /* TOKEN_LT  */
    TOKEN_GT = 277,                /* TOKEN_GT  */
    TOKEN_LE = 278,                /* TOKEN_LE  */
    TOKEN_GE = 279,                /* TOKEN_GE  */
    TOKEN_LPAREN = 280,            /* TOKEN_LPAREN  */
    TOKEN_RPAREN = 281,            /* TOKEN_RPAREN  */
    TOKEN_SEMI = 282,              /* TOKEN_SEMI  */
    TOKEN_DOT = 283,               /* TOKEN_DOT  */
    TOKEN_PLUS = 284,              /* TOKEN_PLUS  */
    TOKEN_MINUS = 285,             /* TOKEN_MINUS  */
    TOKEN_MUL = 286,               /* TOKEN_MUL  */
    TOKEN_DIV = 287                /* TOKEN_DIV  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
