/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

#line 99 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOKEN_CLASS = 3,                /* TOKEN_CLASS  */
  YYSYMBOL_TOKEN_INHERIT = 4,              /* TOKEN_INHERIT  */
  YYSYMBOL_TOKEN_FEATURE = 5,              /* TOKEN_FEATURE  */
  YYSYMBOL_TOKEN_DO = 6,                   /* TOKEN_DO  */
  YYSYMBOL_TOKEN_END = 7,                  /* TOKEN_END  */
  YYSYMBOL_TOKEN_IF = 8,                   /* TOKEN_IF  */
  YYSYMBOL_TOKEN_THEN = 9,                 /* TOKEN_THEN  */
  YYSYMBOL_TOKEN_ELSE = 10,                /* TOKEN_ELSE  */
  YYSYMBOL_TOKEN_FROM = 11,                /* TOKEN_FROM  */
  YYSYMBOL_TOKEN_UNTIL = 12,               /* TOKEN_UNTIL  */
  YYSYMBOL_TOKEN_LOOP = 13,                /* TOKEN_LOOP  */
  YYSYMBOL_TOKEN_CREATE = 14,              /* TOKEN_CREATE  */
  YYSYMBOL_TOKEN_LOCAL = 15,               /* TOKEN_LOCAL  */
  YYSYMBOL_TOKEN_PRINT = 16,               /* TOKEN_PRINT  */
  YYSYMBOL_TOKEN_ASSIGN = 17,              /* TOKEN_ASSIGN  */
  YYSYMBOL_TOKEN_LE = 18,                  /* TOKEN_LE  */
  YYSYMBOL_TOKEN_GE = 19,                  /* TOKEN_GE  */
  YYSYMBOL_TOKEN_EQUAL = 20,               /* TOKEN_EQUAL  */
  YYSYMBOL_TOKEN_LT = 21,                  /* TOKEN_LT  */
  YYSYMBOL_TOKEN_GT = 22,                  /* TOKEN_GT  */
  YYSYMBOL_TOKEN_LPAREN = 23,              /* TOKEN_LPAREN  */
  YYSYMBOL_TOKEN_RPAREN = 24,              /* TOKEN_RPAREN  */
  YYSYMBOL_TOKEN_SEMI = 25,                /* TOKEN_SEMI  */
  YYSYMBOL_TOKEN_DOT = 26,                 /* TOKEN_DOT  */
  YYSYMBOL_TOKEN_PLUS = 27,                /* TOKEN_PLUS  */
  YYSYMBOL_TOKEN_MINUS = 28,               /* TOKEN_MINUS  */
  YYSYMBOL_TOKEN_MUL = 29,                 /* TOKEN_MUL  */
  YYSYMBOL_TOKEN_DIV = 30,                 /* TOKEN_DIV  */
  YYSYMBOL_TOKEN_COLON = 31,               /* TOKEN_COLON  */
  YYSYMBOL_TOKEN_COMMA = 32,               /* TOKEN_COMMA  */
  YYSYMBOL_TOKEN_IDENTIFIER = 33,          /* TOKEN_IDENTIFIER  */
  YYSYMBOL_TOKEN_INTEGER = 34,             /* TOKEN_INTEGER  */
  YYSYMBOL_TOKEN_REAL = 35,                /* TOKEN_REAL  */
  YYSYMBOL_TOKEN_STRING = 36,              /* TOKEN_STRING  */
  YYSYMBOL_UMINUS = 37,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_class_def = 40,                 /* class_def  */
  YYSYMBOL_feature_block = 41,             /* feature_block  */
  YYSYMBOL_feature_list = 42,              /* feature_list  */
  YYSYMBOL_feature_or_attr = 43,           /* feature_or_attr  */
  YYSYMBOL_feature = 44,                   /* feature  */
  YYSYMBOL_opt_locals = 45,                /* opt_locals  */
  YYSYMBOL_local_decl_list = 46,           /* local_decl_list  */
  YYSYMBOL_local_decl = 47,                /* local_decl  */
  YYSYMBOL_id_list = 48,                   /* id_list  */
  YYSYMBOL_stmt_list = 49,                 /* stmt_list  */
  YYSYMBOL_stmt_item = 50,                 /* stmt_item  */
  YYSYMBOL_stmt = 51,                      /* stmt  */
  YYSYMBOL_if_stmt = 52,                   /* if_stmt  */
  YYSYMBOL_loop_stmt = 53,                 /* loop_stmt  */
  YYSYMBOL_print_stmt = 54,                /* print_stmt  */
  YYSYMBOL_expr = 55                       /* expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   160

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  96

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    68,    68,    73,    81,    88,    94,    96,   106,   109,
     113,   120,   126,   127,   132,   134,   140,   142,   148,   150,
     157,   158,   160,   166,   168,   173,   175,   177,   179,   183,
     187,   195,   204,   206,   211,   216,   222,   224,   226,   228,
     230,   232,   234,   236,   238,   240,   242,   244,   246,   250,
     257
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOKEN_CLASS",
  "TOKEN_INHERIT", "TOKEN_FEATURE", "TOKEN_DO", "TOKEN_END", "TOKEN_IF",
  "TOKEN_THEN", "TOKEN_ELSE", "TOKEN_FROM", "TOKEN_UNTIL", "TOKEN_LOOP",
  "TOKEN_CREATE", "TOKEN_LOCAL", "TOKEN_PRINT", "TOKEN_ASSIGN", "TOKEN_LE",
  "TOKEN_GE", "TOKEN_EQUAL", "TOKEN_LT", "TOKEN_GT", "TOKEN_LPAREN",
  "TOKEN_RPAREN", "TOKEN_SEMI", "TOKEN_DOT", "TOKEN_PLUS", "TOKEN_MINUS",
  "TOKEN_MUL", "TOKEN_DIV", "TOKEN_COLON", "TOKEN_COMMA",
  "TOKEN_IDENTIFIER", "TOKEN_INTEGER", "TOKEN_REAL", "TOKEN_STRING",
  "UMINUS", "$accept", "program", "class_def", "feature_block",
  "feature_list", "feature_or_attr", "feature", "opt_locals",
  "local_decl_list", "local_decl", "id_list", "stmt_list", "stmt_item",
  "stmt", "if_stmt", "loop_stmt", "print_stmt", "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-41)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      34,     6,    12,   -41,    36,   -41,   -41,    11,    41,    21,
      11,   -41,   -41,   -41,    22,    26,    61,   -41,   -41,    22,
     -41,   -26,    39,    62,   -41,    38,    44,   -41,    56,    62,
      52,    63,   -13,     0,   -41,    68,   -41,   -41,   -41,    69,
     -41,    56,    56,    75,   -41,   -41,    78,    42,   -41,    56,
      56,    55,   -41,   -41,   -41,   -41,   104,   -41,    70,    62,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
     117,   130,    85,   -41,   -41,    24,    53,    53,    53,    53,
      53,   -11,   -11,   -41,   -41,    91,   -41,    56,   -41,    62,
      62,   130,    35,    58,   -41,   -41
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     3,     0,     0,    12,
       5,     6,    10,     4,     0,     0,     0,     7,    18,    13,
      14,     0,     8,    20,    15,     0,     0,     9,     0,    20,
       0,     0,     0,     0,    21,    23,    26,    27,    28,    16,
      19,     0,     0,    50,    47,    48,     0,     0,    29,     0,
       0,     0,    11,    22,    24,    17,     0,    45,     0,    20,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    25,    31,    46,    49,     0,    43,    44,    40,    41,
      42,    36,    37,    38,    39,     0,    35,     0,    33,    20,
      20,    30,     0,     0,    32,    34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,   112,   -41,   -41,   105,   -41,   -41,   -41,    97,
     -41,   -29,   -30,   -41,   -41,   -41,   -41,   -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     8,    10,    11,    12,    16,    19,    20,
      21,    33,    34,    35,    36,    37,    38,    46
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      47,    56,    57,    53,    50,    25,    26,    52,    28,    70,
      71,    29,     5,    51,    30,     1,    31,    53,    67,    68,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      75,    88,    28,    32,    89,    29,    14,     1,    30,     4,
      31,     7,    94,    28,     9,    53,    29,    91,    13,    30,
      28,    31,    15,    29,    69,    18,    30,    32,    31,    22,
      92,    93,    53,    53,    27,    95,    28,    23,    32,    29,
      28,    39,    30,    29,    31,    32,    30,    40,    31,    41,
      65,    66,    67,    68,    42,    48,    49,    59,    72,    43,
      44,    32,    45,    54,    55,    32,    60,    61,    62,    63,
      64,    58,    87,    74,    90,    65,    66,    67,    68,    60,
      61,    62,    63,    64,     6,    17,    24,     0,    65,    66,
      67,    68,    60,    61,    62,    63,    64,     0,    73,     0,
       0,    65,    66,    67,    68,    60,    61,    62,    63,    64,
       0,    86,     0,     0,    65,    66,    67,    68,    60,    61,
      62,    63,    64,     0,     0,     0,     0,    65,    66,    67,
      68
};

static const yytype_int8 yycheck[] =
{
      29,    41,    42,    33,    17,    31,    32,     7,     8,    49,
      50,    11,     0,    26,    14,     3,    16,    47,    29,    30,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      59,     7,     8,    33,    10,    11,    15,     3,    14,    33,
      16,     5,     7,     8,    33,    75,    11,    87,     7,    14,
       8,    16,    31,    11,    12,    33,    14,    33,    16,    33,
      89,    90,    92,    93,    25,     7,     8,     6,    33,    11,
       8,    33,    14,    11,    16,    33,    14,    33,    16,    23,
      27,    28,    29,    30,    28,    33,    23,     9,    33,    33,
      34,    33,    36,    25,    25,    33,    18,    19,    20,    21,
      22,    26,    17,    33,    13,    27,    28,    29,    30,    18,
      19,    20,    21,    22,     2,    10,    19,    -1,    27,    28,
      29,    30,    18,    19,    20,    21,    22,    -1,    24,    -1,
      -1,    27,    28,    29,    30,    18,    19,    20,    21,    22,
      -1,    24,    -1,    -1,    27,    28,    29,    30,    18,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    27,    28,    29,
      30
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    39,    40,    33,     0,    40,     5,    41,    33,
      42,    43,    44,     7,    15,    31,    45,    43,    33,    46,
      47,    48,    33,     6,    47,    31,    32,    25,     8,    11,
      14,    16,    33,    49,    50,    51,    52,    53,    54,    33,
      33,    23,    28,    33,    34,    36,    55,    49,    33,    23,
      17,    26,     7,    50,    25,    25,    55,    55,    26,     9,
      18,    19,    20,    21,    22,    27,    28,    29,    30,    12,
      55,    55,    33,    24,    33,    49,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    24,    17,     7,    10,
      13,    55,    49,    49,     7,     7
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    39,    40,    41,    42,    42,    43,    43,
      43,    44,    45,    45,    46,    46,    47,    47,    48,    48,
      49,    49,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    52,    52,    53,    54,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     4,     2,     1,     2,     3,     4,
       1,     5,     0,     2,     1,     2,     3,     4,     1,     3,
       0,     1,     2,     1,     2,     3,     1,     1,     1,     2,
       5,     3,     7,     5,     7,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     1,     1,     3,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: class_def  */
#line 69 "parser.y"
      {
          ast_root = ast_program((yyvsp[0].node), yylineno);
          (yyval.node) = (yyvsp[0].node);
      }
#line 1220 "parser.tab.c"
    break;

  case 3: /* program: program class_def  */
#line 74 "parser.y"
      {
          ast_root = ast_program((yyvsp[0].node), yylineno);
          (yyval.node) = (yyvsp[0].node);
      }
#line 1229 "parser.tab.c"
    break;

  case 4: /* class_def: TOKEN_CLASS TOKEN_IDENTIFIER feature_block TOKEN_END  */
#line 82 "parser.y"
      { (yyval.node) = ast_class((yyvsp[-2].sval), (yyvsp[-1].node), yylineno); }
#line 1235 "parser.tab.c"
    break;

  case 5: /* feature_block: TOKEN_FEATURE feature_list  */
#line 89 "parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1241 "parser.tab.c"
    break;

  case 6: /* feature_list: feature_or_attr  */
#line 95 "parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1247 "parser.tab.c"
    break;

  case 7: /* feature_list: feature_list feature_or_attr  */
#line 97 "parser.y"
      { (yyval.node) = (yyvsp[-1].node) ? (yyvsp[-1].node) : (yyvsp[0].node); }
#line 1253 "parser.tab.c"
    break;

  case 8: /* feature_or_attr: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_IDENTIFIER  */
#line 107 "parser.y"
      { (yyval.node) = NULL; }
#line 1259 "parser.tab.c"
    break;

  case 9: /* feature_or_attr: TOKEN_IDENTIFIER TOKEN_COLON TOKEN_IDENTIFIER TOKEN_SEMI  */
#line 110 "parser.y"
      { (yyval.node) = NULL; }
#line 1265 "parser.tab.c"
    break;

  case 10: /* feature_or_attr: feature  */
#line 114 "parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1271 "parser.tab.c"
    break;

  case 11: /* feature: TOKEN_IDENTIFIER opt_locals TOKEN_DO stmt_list TOKEN_END  */
#line 121 "parser.y"
      { (yyval.node) = ast_feature((yyvsp[-4].sval), (yyvsp[-3].node), (yyvsp[-1].node), yylineno); }
#line 1277 "parser.tab.c"
    break;

  case 12: /* opt_locals: %empty  */
#line 126 "parser.y"
      { (yyval.node) = NULL; }
#line 1283 "parser.tab.c"
    break;

  case 13: /* opt_locals: TOKEN_LOCAL local_decl_list  */
#line 128 "parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1289 "parser.tab.c"
    break;

  case 14: /* local_decl_list: local_decl  */
#line 133 "parser.y"
      { (yyval.node) = ast_stmt_list_single((yyvsp[0].node), yylineno); }
#line 1295 "parser.tab.c"
    break;

  case 15: /* local_decl_list: local_decl_list local_decl  */
#line 135 "parser.y"
      { (yyval.node) = ast_stmt_list_append((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1301 "parser.tab.c"
    break;

  case 16: /* local_decl: id_list TOKEN_COLON TOKEN_IDENTIFIER  */
#line 141 "parser.y"
      { (yyval.node) = ast_decl((yyvsp[-2].node), (yyvsp[0].sval), yylineno); }
#line 1307 "parser.tab.c"
    break;

  case 17: /* local_decl: id_list TOKEN_COLON TOKEN_IDENTIFIER TOKEN_SEMI  */
#line 143 "parser.y"
      { (yyval.node) = ast_decl((yyvsp[-3].node), (yyvsp[-1].sval), yylineno); }
#line 1313 "parser.tab.c"
    break;

  case 18: /* id_list: TOKEN_IDENTIFIER  */
#line 149 "parser.y"
      { (yyval.node) = ast_stmt_list_single(ast_var((yyvsp[0].sval), yylineno), yylineno); }
#line 1319 "parser.tab.c"
    break;

  case 19: /* id_list: id_list TOKEN_COMMA TOKEN_IDENTIFIER  */
#line 151 "parser.y"
      { (yyval.node) = ast_stmt_list_append((yyvsp[-2].node), ast_var((yyvsp[0].sval), yylineno)); }
#line 1325 "parser.tab.c"
    break;

  case 20: /* stmt_list: %empty  */
#line 157 "parser.y"
      { (yyval.node) = NULL; }
#line 1331 "parser.tab.c"
    break;

  case 21: /* stmt_list: stmt_item  */
#line 159 "parser.y"
      { (yyval.node) = ast_stmt_list_single((yyvsp[0].node), yylineno); }
#line 1337 "parser.tab.c"
    break;

  case 22: /* stmt_list: stmt_list stmt_item  */
#line 161 "parser.y"
      { (yyval.node) = ast_stmt_list_append((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1343 "parser.tab.c"
    break;

  case 23: /* stmt_item: stmt  */
#line 167 "parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1349 "parser.tab.c"
    break;

  case 24: /* stmt_item: stmt TOKEN_SEMI  */
#line 169 "parser.y"
      { (yyval.node) = (yyvsp[-1].node); }
#line 1355 "parser.tab.c"
    break;

  case 25: /* stmt: TOKEN_IDENTIFIER TOKEN_ASSIGN expr  */
#line 174 "parser.y"
      { (yyval.node) = ast_assign((yyvsp[-2].sval), (yyvsp[0].node), yylineno); }
#line 1361 "parser.tab.c"
    break;

  case 26: /* stmt: if_stmt  */
#line 176 "parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1367 "parser.tab.c"
    break;

  case 27: /* stmt: loop_stmt  */
#line 178 "parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1373 "parser.tab.c"
    break;

  case 28: /* stmt: print_stmt  */
#line 180 "parser.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1379 "parser.tab.c"
    break;

  case 29: /* stmt: TOKEN_CREATE TOKEN_IDENTIFIER  */
#line 184 "parser.y"
      { (yyval.node) = ast_create((yyvsp[0].sval), yylineno); }
#line 1385 "parser.tab.c"
    break;

  case 30: /* stmt: TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER TOKEN_ASSIGN expr  */
#line 188 "parser.y"
      {
          char *fname = make_field_name((yyvsp[-4].sval), (yyvsp[-2].sval));        /* "c_value" */
          (yyval.node) = ast_assign(fname, (yyvsp[0].node), yylineno);         /* ast_assign("c_value", expr) */
          free(fname);
      }
#line 1395 "parser.tab.c"
    break;

  case 31: /* stmt: TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER  */
#line 196 "parser.y"
      {
          char *mname = make_field_name((yyvsp[-2].sval), (yyvsp[0].sval));        /* "c_inc" */
          (yyval.node) = ast_call_proc(mname, yylineno);
          free(mname);
      }
#line 1405 "parser.tab.c"
    break;

  case 32: /* if_stmt: TOKEN_IF expr TOKEN_THEN stmt_list TOKEN_ELSE stmt_list TOKEN_END  */
#line 205 "parser.y"
      { (yyval.node) = ast_if((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), yylineno); }
#line 1411 "parser.tab.c"
    break;

  case 33: /* if_stmt: TOKEN_IF expr TOKEN_THEN stmt_list TOKEN_END  */
#line 207 "parser.y"
      { (yyval.node) = ast_if((yyvsp[-3].node), (yyvsp[-1].node), NULL, yylineno); }
#line 1417 "parser.tab.c"
    break;

  case 34: /* loop_stmt: TOKEN_FROM stmt_list TOKEN_UNTIL expr TOKEN_LOOP stmt_list TOKEN_END  */
#line 212 "parser.y"
      { (yyval.node) = ast_loop((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node), yylineno); }
#line 1423 "parser.tab.c"
    break;

  case 35: /* print_stmt: TOKEN_PRINT TOKEN_LPAREN expr TOKEN_RPAREN  */
#line 217 "parser.y"
      { (yyval.node) = ast_print((yyvsp[-1].node), yylineno); }
#line 1429 "parser.tab.c"
    break;

  case 36: /* expr: expr TOKEN_PLUS expr  */
#line 223 "parser.y"
      { (yyval.node) = ast_binop(OP_ADD, (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1435 "parser.tab.c"
    break;

  case 37: /* expr: expr TOKEN_MINUS expr  */
#line 225 "parser.y"
      { (yyval.node) = ast_binop(OP_SUB, (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1441 "parser.tab.c"
    break;

  case 38: /* expr: expr TOKEN_MUL expr  */
#line 227 "parser.y"
      { (yyval.node) = ast_binop(OP_MUL, (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1447 "parser.tab.c"
    break;

  case 39: /* expr: expr TOKEN_DIV expr  */
#line 229 "parser.y"
      { (yyval.node) = ast_binop(OP_DIV, (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1453 "parser.tab.c"
    break;

  case 40: /* expr: expr TOKEN_EQUAL expr  */
#line 231 "parser.y"
      { (yyval.node) = ast_binop(OP_EQ, (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1459 "parser.tab.c"
    break;

  case 41: /* expr: expr TOKEN_LT expr  */
#line 233 "parser.y"
      { (yyval.node) = ast_binop(OP_LT, (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1465 "parser.tab.c"
    break;

  case 42: /* expr: expr TOKEN_GT expr  */
#line 235 "parser.y"
      { (yyval.node) = ast_binop(OP_GT, (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1471 "parser.tab.c"
    break;

  case 43: /* expr: expr TOKEN_LE expr  */
#line 237 "parser.y"
      { (yyval.node) = ast_binop(OP_LE, (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1477 "parser.tab.c"
    break;

  case 44: /* expr: expr TOKEN_GE expr  */
#line 239 "parser.y"
      { (yyval.node) = ast_binop(OP_GE, (yyvsp[-2].node), (yyvsp[0].node), yylineno); }
#line 1483 "parser.tab.c"
    break;

  case 45: /* expr: TOKEN_MINUS expr  */
#line 241 "parser.y"
      { (yyval.node) = ast_binop(OP_SUB, ast_int_literal(0, yylineno), (yyvsp[0].node), yylineno); }
#line 1489 "parser.tab.c"
    break;

  case 46: /* expr: TOKEN_LPAREN expr TOKEN_RPAREN  */
#line 243 "parser.y"
      { (yyval.node) = (yyvsp[-1].node); }
#line 1495 "parser.tab.c"
    break;

  case 47: /* expr: TOKEN_INTEGER  */
#line 245 "parser.y"
      { (yyval.node) = ast_int_literal((yyvsp[0].ival), yylineno); }
#line 1501 "parser.tab.c"
    break;

  case 48: /* expr: TOKEN_STRING  */
#line 247 "parser.y"
      { (yyval.node) = ast_string_literal((yyvsp[0].sval), yylineno); }
#line 1507 "parser.tab.c"
    break;

  case 49: /* expr: TOKEN_IDENTIFIER TOKEN_DOT TOKEN_IDENTIFIER  */
#line 251 "parser.y"
      {
          char *fname = make_field_name((yyvsp[-2].sval), (yyvsp[0].sval));
          (yyval.node) = ast_var(fname, yylineno);
          free(fname);
      }
#line 1517 "parser.tab.c"
    break;

  case 50: /* expr: TOKEN_IDENTIFIER  */
#line 258 "parser.y"
      { (yyval.node) = ast_var((yyvsp[0].sval), yylineno); }
#line 1523 "parser.tab.c"
    break;


#line 1527 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 261 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, s);
}
