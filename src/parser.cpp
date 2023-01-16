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

/* "%code top" blocks.  */
#line 1 "src/parser.y"

    #include <iostream>
    #include <cstring>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );
    int yyget_lineno(void);
    Type* nowType; // “最近”的类型，用于声明变量

#line 80 "src/parser.cpp"




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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_BOOL = 5,                       /* BOOL  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_WHILE = 8,                      /* WHILE  */
  YYSYMBOL_FOR = 9,                        /* FOR  */
  YYSYMBOL_HEX = 10,                       /* HEX  */
  YYSYMBOL_OCT = 11,                       /* OCT  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_VOID = 13,                      /* VOID  */
  YYSYMBOL_CONST = 14,                     /* CONST  */
  YYSYMBOL_COMMA = 15,                     /* COMMA  */
  YYSYMBOL_LPAREN = 16,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 17,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 18,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 19,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 20,                 /* SEMICOLON  */
  YYSYMBOL_ADD = 21,                       /* ADD  */
  YYSYMBOL_SUB = 22,                       /* SUB  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_AND = 24,                       /* AND  */
  YYSYMBOL_STAR = 25,                      /* STAR  */
  YYSYMBOL_DIV = 26,                       /* DIV  */
  YYSYMBOL_MOD = 27,                       /* MOD  */
  YYSYMBOL_LESS = 28,                      /* LESS  */
  YYSYMBOL_GREATER = 29,                   /* GREATER  */
  YYSYMBOL_EQ = 30,                        /* EQ  */
  YYSYMBOL_NEQ = 31,                       /* NEQ  */
  YYSYMBOL_LEQ = 32,                       /* LEQ  */
  YYSYMBOL_GEQ = 33,                       /* GEQ  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_ASSIGN = 35,                    /* ASSIGN  */
  YYSYMBOL_RETURN = 36,                    /* RETURN  */
  YYSYMBOL_THEN = 37,                      /* THEN  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_Program = 39,                   /* Program  */
  YYSYMBOL_Stmts = 40,                     /* Stmts  */
  YYSYMBOL_Stmt = 41,                      /* Stmt  */
  YYSYMBOL_LVal = 42,                      /* LVal  */
  YYSYMBOL_AssignStmt = 43,                /* AssignStmt  */
  YYSYMBOL_BlockStmt = 44,                 /* BlockStmt  */
  YYSYMBOL_45_1 = 45,                      /* $@1  */
  YYSYMBOL_IfStmt = 46,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 47,                 /* WhileStmt  */
  YYSYMBOL_ReturnStmt = 48,                /* ReturnStmt  */
  YYSYMBOL_ExprStmt = 49,                  /* ExprStmt  */
  YYSYMBOL_Exp = 50,                       /* Exp  */
  YYSYMBOL_Cond = 51,                      /* Cond  */
  YYSYMBOL_PrimaryExp = 52,                /* PrimaryExp  */
  YYSYMBOL_CallExp = 53,                   /* CallExp  */
  YYSYMBOL_CallParam = 54,                 /* CallParam  */
  YYSYMBOL_MulExp = 55,                    /* MulExp  */
  YYSYMBOL_AddExp = 56,                    /* AddExp  */
  YYSYMBOL_RelExp = 57,                    /* RelExp  */
  YYSYMBOL_CmpExp = 58,                    /* CmpExp  */
  YYSYMBOL_LAndExp = 59,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 60,                    /* LOrExp  */
  YYSYMBOL_Type = 61,                      /* Type  */
  YYSYMBOL_DeclStmt = 62,                  /* DeclStmt  */
  YYSYMBOL_VarList = 63,                   /* VarList  */
  YYSYMBOL_ConstList = 64,                 /* ConstList  */
  YYSYMBOL_VarDef = 65,                    /* VarDef  */
  YYSYMBOL_ConstDef = 66,                  /* ConstDef  */
  YYSYMBOL_FuncDef = 67,                   /* FuncDef  */
  YYSYMBOL_68_2 = 68,                      /* $@2  */
  YYSYMBOL_FuncParam = 69                  /* FuncParam  */
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
#define YYFINAL  47
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   155

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

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
       0,    55,    55,    60,    61,    66,    67,    68,    69,    70,
      71,    72,    73,    76,    91,    97,    96,   106,   111,   117,
     120,   125,   131,   135,   141,   147,   151,   155,   158,   162,
     165,   168,   172,   175,   182,   198,   200,   204,   210,   212,
     218,   224,   232,   234,   240,   249,   251,   257,   265,   267,
     273,   279,   285,   293,   295,   303,   305,   312,   316,   319,
     329,   333,   339,   343,   349,   353,   359,   378,   399,   418,
     443,   442,   521,   523,   533
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTEGER",
  "BOOL", "IF", "ELSE", "WHILE", "FOR", "HEX", "OCT", "INT", "VOID",
  "CONST", "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON",
  "ADD", "SUB", "OR", "AND", "STAR", "DIV", "MOD", "LESS", "GREATER", "EQ",
  "NEQ", "LEQ", "GEQ", "NOT", "ASSIGN", "RETURN", "THEN", "$accept",
  "Program", "Stmts", "Stmt", "LVal", "AssignStmt", "BlockStmt", "$@1",
  "IfStmt", "WhileStmt", "ReturnStmt", "ExprStmt", "Exp", "Cond",
  "PrimaryExp", "CallExp", "CallParam", "MulExp", "AddExp", "RelExp",
  "CmpExp", "LAndExp", "LOrExp", "Type", "DeclStmt", "VarList",
  "ConstList", "VarDef", "ConstDef", "FuncDef", "$@2", "FuncParam", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-30)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      97,    22,   -30,   -30,    32,    41,   -30,   -30,    27,   121,
      25,   -30,   121,   121,   121,   118,    12,    97,   -30,   -19,
     -30,   -30,   -30,   -30,   -30,   -30,    49,   -30,   -30,    -1,
      52,    64,   -30,   -30,   121,   121,   121,    68,   -30,    58,
     -30,    97,   -30,   -30,   -30,   -30,    61,   -30,   -30,   121,
     -30,   121,   121,   121,   121,   121,   -13,   -11,   -30,   -30,
      -7,    70,    52,    47,    14,    65,    67,    71,    56,    35,
     -30,   -30,    15,   -30,    73,   -30,   -30,   -30,    -1,    -1,
     121,    78,    94,   -30,   121,   -30,    97,   121,   121,   121,
     121,   121,   121,   121,   121,    97,   121,    68,   -30,   -30,
     -30,   -30,    27,    63,   -30,   -30,    92,    14,    14,    52,
      52,    52,    52,    47,    65,   -30,   -30,   -30,   103,    51,
      97,   -30,    27,    97,   -30,   105,   -30,   -30
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    13,    28,    59,     0,     0,    57,    58,     0,     0,
      15,    18,     0,     0,     0,     0,     0,     2,     3,    27,
       5,     6,     7,    11,     8,    12,     0,    38,    29,    42,
      25,     0,     9,    10,    35,     0,     0,     0,    27,     0,
      17,     0,    32,    31,    33,    23,     0,     1,     4,     0,
      24,     0,     0,     0,     0,     0,    66,     0,    62,    36,
       0,     0,    48,    53,    45,    55,    26,     0,    68,     0,
      64,    30,     0,    22,     0,    39,    40,    41,    43,    44,
       0,     0,     0,    60,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    16,
      14,    67,    72,    66,    63,    37,    19,    46,    47,    49,
      50,    51,    52,    54,    56,    21,    69,    65,     0,     0,
       0,    73,     0,     0,    20,     0,    71,    74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -30,   -30,    85,   -16,     0,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,    -4,    76,     1,   -30,   -30,    28,   -29,    21,
      -3,    33,   -30,    -6,   -30,   -30,   -30,    46,    38,   -30,
     -30,   -30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    16,    17,    18,    38,    20,    21,    41,    22,    23,
      24,    25,    26,    61,    27,    28,    60,    29,    30,    63,
      64,    65,    66,    31,    32,    57,    69,    58,    70,    33,
      81,   119
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      19,    48,    37,   -70,    82,    39,    62,    62,    84,    83,
      85,    46,    47,    42,    43,    44,    49,    19,     1,     2,
       3,     4,    80,     5,    51,    52,    53,     6,     7,     8,
      59,     9,     3,    10,    99,    11,    12,    13,    34,     6,
       7,    19,    89,    90,    40,    74,    91,    92,    35,    14,
      97,    15,    75,    76,    77,    98,    48,    36,    62,    62,
     109,   110,   111,   112,    62,    62,   122,    56,   123,    50,
     106,    68,    19,    54,    55,    71,   101,    87,    88,   115,
     105,    73,    78,    79,   107,   108,    19,    86,    95,    93,
      94,    96,   116,   100,   102,    19,   118,   103,    80,   120,
       1,     2,     3,     4,   124,     5,   121,   126,   127,     6,
       7,     8,    67,     9,   113,    10,   125,    11,    12,    13,
      19,     1,     2,    19,     1,     2,    72,   114,   104,     0,
       0,    14,     0,    15,     9,   117,     0,     9,    45,    12,
      13,     0,    12,    13,     0,     0,     0,     0,     0,     0,
       0,     0,    14,     0,     0,    14
};

static const yytype_int8 yycheck[] =
{
       0,    17,     8,    16,    15,     9,    35,    36,    15,    20,
      17,    15,     0,    12,    13,    14,    35,    17,     3,     4,
       5,     6,    35,     8,    25,    26,    27,    12,    13,    14,
      34,    16,     5,    18,    19,    20,    21,    22,    16,    12,
      13,    41,    28,    29,    19,    49,    32,    33,    16,    34,
      15,    36,    51,    52,    53,    20,    72,    16,    87,    88,
      89,    90,    91,    92,    93,    94,    15,     3,    17,    20,
      86,     3,    72,    21,    22,    17,    80,    30,    31,    95,
      84,    20,    54,    55,    87,    88,    86,    17,    17,    24,
      23,    35,    96,    20,    16,    95,   102,     3,    35,     7,
       3,     4,     5,     6,   120,     8,     3,   123,     3,    12,
      13,    14,    36,    16,    93,    18,   122,    20,    21,    22,
     120,     3,     4,   123,     3,     4,    41,    94,    82,    -1,
      -1,    34,    -1,    36,    16,    97,    -1,    16,    20,    21,
      22,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     8,    12,    13,    14,    16,
      18,    20,    21,    22,    34,    36,    39,    40,    41,    42,
      43,    44,    46,    47,    48,    49,    50,    52,    53,    55,
      56,    61,    62,    67,    16,    16,    16,    61,    42,    50,
      19,    45,    52,    52,    52,    20,    50,     0,    41,    35,
      20,    25,    26,    27,    21,    22,     3,    63,    65,    50,
      54,    51,    56,    57,    58,    59,    60,    51,     3,    64,
      66,    17,    40,    20,    50,    52,    52,    52,    55,    55,
      35,    68,    15,    20,    15,    17,    17,    30,    31,    28,
      29,    32,    33,    24,    23,    17,    35,    15,    20,    19,
      20,    50,    16,     3,    65,    50,    41,    58,    58,    56,
      56,    56,    56,    57,    59,    41,    50,    66,    61,    69,
       7,     3,    15,    17,    41,    61,    41,     3
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    41,    42,    43,    45,    44,    44,    44,    46,
      46,    47,    48,    48,    49,    50,    51,    52,    52,    52,
      52,    52,    52,    52,    53,    54,    54,    54,    55,    55,
      55,    55,    56,    56,    56,    57,    57,    57,    58,    58,
      58,    58,    58,    59,    59,    60,    60,    61,    61,    61,
      62,    62,    63,    63,    64,    64,    65,    65,    66,    66,
      68,    67,    69,    69,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     0,     4,     2,     1,     5,
       7,     5,     3,     2,     2,     1,     1,     1,     1,     1,
       3,     2,     2,     2,     4,     0,     1,     3,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     1,     3,     1,     1,     1,
       3,     4,     1,     3,     1,     3,     1,     3,     1,     3,
       0,     7,     0,     2,     4
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
  case 2: /* Program: Stmts  */
#line 55 "src/parser.y"
            {
        ast.setRoot((yyvsp[0].stmttype));
    }
#line 1232 "src/parser.cpp"
    break;

  case 3: /* Stmts: Stmt  */
#line 60 "src/parser.y"
           {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1238 "src/parser.cpp"
    break;

  case 4: /* Stmts: Stmts Stmt  */
#line 61 "src/parser.y"
                {
        (yyval.stmttype) = new SeqNode((yyvsp[-1].stmttype), (yyvsp[0].stmttype));
    }
#line 1246 "src/parser.cpp"
    break;

  case 5: /* Stmt: AssignStmt  */
#line 66 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1252 "src/parser.cpp"
    break;

  case 6: /* Stmt: BlockStmt  */
#line 67 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1258 "src/parser.cpp"
    break;

  case 7: /* Stmt: IfStmt  */
#line 68 "src/parser.y"
             {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1264 "src/parser.cpp"
    break;

  case 8: /* Stmt: ReturnStmt  */
#line 69 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1270 "src/parser.cpp"
    break;

  case 9: /* Stmt: DeclStmt  */
#line 70 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1276 "src/parser.cpp"
    break;

  case 10: /* Stmt: FuncDef  */
#line 71 "src/parser.y"
              {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1282 "src/parser.cpp"
    break;

  case 11: /* Stmt: WhileStmt  */
#line 72 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1288 "src/parser.cpp"
    break;

  case 12: /* Stmt: ExprStmt  */
#line 73 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1294 "src/parser.cpp"
    break;

  case 13: /* LVal: ID  */
#line 76 "src/parser.y"
         {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[0].strtype));
        if(se == nullptr)
        {
            fprintf(stderr, "\033[31mLine %d: identifier \"%s\" is undefined\033[39m\n", yyget_lineno(), (char*)(yyvsp[0].strtype));
            se = new IdentifierSymbolEntry(
                TypeSystem::errorType, (std::string)"_undefined_"+(yyvsp[0].strtype), identifiers->getLevel());
        }
        (yyval.exprtype) = new Id(se);
        delete [](yyvsp[0].strtype);
    }
#line 1311 "src/parser.cpp"
    break;

  case 14: /* AssignStmt: LVal ASSIGN Exp SEMICOLON  */
#line 91 "src/parser.y"
                              {
        (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[-1].exprtype));
    }
#line 1319 "src/parser.cpp"
    break;

  case 15: /* $@1: %empty  */
#line 97 "src/parser.y"
        {identifiers = new SymbolTable(identifiers);}
#line 1325 "src/parser.cpp"
    break;

  case 16: /* BlockStmt: LBRACE $@1 Stmts RBRACE  */
#line 99 "src/parser.y"
        {
            (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
#line 1336 "src/parser.cpp"
    break;

  case 17: /* BlockStmt: LBRACE RBRACE  */
#line 107 "src/parser.y"
        {
            (yyval.stmttype) = new CompoundStmt(nullptr);
        }
#line 1344 "src/parser.cpp"
    break;

  case 18: /* BlockStmt: SEMICOLON  */
#line 112 "src/parser.y"
        {
            (yyval.stmttype) = new CompoundStmt(nullptr);
        }
#line 1352 "src/parser.cpp"
    break;

  case 19: /* IfStmt: IF LPAREN Cond RPAREN Stmt  */
#line 117 "src/parser.y"
                                            {
        (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1360 "src/parser.cpp"
    break;

  case 20: /* IfStmt: IF LPAREN Cond RPAREN Stmt ELSE Stmt  */
#line 120 "src/parser.y"
                                           {
        (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1368 "src/parser.cpp"
    break;

  case 21: /* WhileStmt: WHILE LPAREN Cond RPAREN Stmt  */
#line 125 "src/parser.y"
                                    {
        (yyval.stmttype) = new WhileStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
    }
#line 1376 "src/parser.cpp"
    break;

  case 22: /* ReturnStmt: RETURN Exp SEMICOLON  */
#line 131 "src/parser.y"
                        {
        (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
    }
#line 1384 "src/parser.cpp"
    break;

  case 23: /* ReturnStmt: RETURN SEMICOLON  */
#line 135 "src/parser.y"
                    {
        (yyval.stmttype) = new ReturnStmt(nullptr);
    }
#line 1392 "src/parser.cpp"
    break;

  case 24: /* ExprStmt: Exp SEMICOLON  */
#line 141 "src/parser.y"
                  {
        (yyval.stmttype) = new ExprStmt((yyvsp[-1].exprtype));
    }
#line 1400 "src/parser.cpp"
    break;

  case 25: /* Exp: AddExp  */
#line 147 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1406 "src/parser.cpp"
    break;

  case 26: /* Cond: LOrExp  */
#line 151 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1412 "src/parser.cpp"
    break;

  case 27: /* PrimaryExp: LVal  */
#line 155 "src/parser.y"
         {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1420 "src/parser.cpp"
    break;

  case 28: /* PrimaryExp: INTEGER  */
#line 158 "src/parser.y"
              {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, (yyvsp[0].itype));
        (yyval.exprtype) = new Constant(se);
    }
#line 1429 "src/parser.cpp"
    break;

  case 29: /* PrimaryExp: CallExp  */
#line 162 "src/parser.y"
              {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1437 "src/parser.cpp"
    break;

  case 30: /* PrimaryExp: LPAREN Exp RPAREN  */
#line 165 "src/parser.y"
                        {
        (yyval.exprtype) = (yyvsp[-1].exprtype);
    }
#line 1445 "src/parser.cpp"
    break;

  case 31: /* PrimaryExp: SUB PrimaryExp  */
#line 168 "src/parser.y"
                     {
        SymbolEntry *se = new TemporarySymbolEntry(nowType, SymbolTable::getLabel());
        (yyval.exprtype) = new UnaryExpr(se, UnaryExpr::SUB, (yyvsp[0].exprtype));
    }
#line 1454 "src/parser.cpp"
    break;

  case 32: /* PrimaryExp: ADD PrimaryExp  */
#line 172 "src/parser.y"
                     {
        (yyval.exprtype) = (yyvsp[0].exprtype);
    }
#line 1462 "src/parser.cpp"
    break;

  case 33: /* PrimaryExp: NOT PrimaryExp  */
#line 175 "src/parser.y"
                     {
        SymbolEntry *se = new TemporarySymbolEntry(nowType, SymbolTable::getLabel());
        (yyval.exprtype) = new UnaryExpr(se, UnaryExpr::NOT, (yyvsp[0].exprtype));
    }
#line 1471 "src/parser.cpp"
    break;

  case 34: /* CallExp: ID LPAREN CallParam RPAREN  */
#line 182 "src/parser.y"
                               {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-3].strtype));

        if(se == nullptr)
        {
            fprintf(stderr, "\033[31mLine %d: function \"%s\" is undefined\033[39m\n", yyget_lineno(), (char*)(yyvsp[-3].strtype));
            se = new IdentifierSymbolEntry(
                TypeSystem::errorType, (std::string)"_undefined_"+(yyvsp[-3].strtype), identifiers->getLevel());
        }
        (yyval.exprtype) = new CallExpr(se, (yyvsp[-1].callparamstype));
        delete [](yyvsp[-3].strtype);
    }
#line 1489 "src/parser.cpp"
    break;

  case 35: /* CallParam: %empty  */
#line 198 "src/parser.y"
           {(yyval.callparamstype) = new CallParams();}
#line 1495 "src/parser.cpp"
    break;

  case 36: /* CallParam: Exp  */
#line 200 "src/parser.y"
        {
        (yyval.callparamstype) = new CallParams();
        (yyval.callparamstype)->append((yyvsp[0].exprtype));
    }
#line 1504 "src/parser.cpp"
    break;

  case 37: /* CallParam: CallParam COMMA Exp  */
#line 204 "src/parser.y"
                          {
        (yyval.callparamstype)->append((yyvsp[0].exprtype));
    }
#line 1512 "src/parser.cpp"
    break;

  case 38: /* MulExp: PrimaryExp  */
#line 210 "src/parser.y"
               {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1518 "src/parser.cpp"
    break;

  case 39: /* MulExp: MulExp STAR PrimaryExp  */
#line 213 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MUL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1527 "src/parser.cpp"
    break;

  case 40: /* MulExp: MulExp DIV PrimaryExp  */
#line 219 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::DIV, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1536 "src/parser.cpp"
    break;

  case 41: /* MulExp: MulExp MOD PrimaryExp  */
#line 225 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1545 "src/parser.cpp"
    break;

  case 42: /* AddExp: MulExp  */
#line 232 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1551 "src/parser.cpp"
    break;

  case 43: /* AddExp: AddExp ADD MulExp  */
#line 235 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1560 "src/parser.cpp"
    break;

  case 44: /* AddExp: AddExp SUB MulExp  */
#line 241 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1569 "src/parser.cpp"
    break;

  case 45: /* RelExp: CmpExp  */
#line 249 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1575 "src/parser.cpp"
    break;

  case 46: /* RelExp: RelExp EQ CmpExp  */
#line 252 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::EQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1584 "src/parser.cpp"
    break;

  case 47: /* RelExp: RelExp NEQ CmpExp  */
#line 258 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::NEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1593 "src/parser.cpp"
    break;

  case 48: /* CmpExp: AddExp  */
#line 265 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1599 "src/parser.cpp"
    break;

  case 49: /* CmpExp: CmpExp LESS AddExp  */
#line 268 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1608 "src/parser.cpp"
    break;

  case 50: /* CmpExp: CmpExp GREATER AddExp  */
#line 274 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATER, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1617 "src/parser.cpp"
    break;

  case 51: /* CmpExp: CmpExp LEQ AddExp  */
#line 280 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1626 "src/parser.cpp"
    break;

  case 52: /* CmpExp: CmpExp GEQ AddExp  */
#line 286 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1635 "src/parser.cpp"
    break;

  case 53: /* LAndExp: RelExp  */
#line 293 "src/parser.y"
           {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1641 "src/parser.cpp"
    break;

  case 54: /* LAndExp: LAndExp AND RelExp  */
#line 296 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1650 "src/parser.cpp"
    break;

  case 55: /* LOrExp: LAndExp  */
#line 303 "src/parser.y"
            {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1656 "src/parser.cpp"
    break;

  case 56: /* LOrExp: LOrExp OR LAndExp  */
#line 306 "src/parser.y"
    {
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
    }
#line 1665 "src/parser.cpp"
    break;

  case 57: /* Type: INT  */
#line 312 "src/parser.y"
          {
        nowType = TypeSystem::intType;
        (yyval.type) = TypeSystem::intType;
    }
#line 1674 "src/parser.cpp"
    break;

  case 58: /* Type: VOID  */
#line 316 "src/parser.y"
           {
        (yyval.type) = TypeSystem::voidType;
    }
#line 1682 "src/parser.cpp"
    break;

  case 59: /* Type: BOOL  */
#line 319 "src/parser.y"
           {
        nowType = TypeSystem::boolType;
        (yyval.type) = TypeSystem::boolType;
    }
#line 1691 "src/parser.cpp"
    break;

  case 60: /* DeclStmt: Type VarList SEMICOLON  */
#line 329 "src/parser.y"
                           {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1699 "src/parser.cpp"
    break;

  case 61: /* DeclStmt: CONST Type ConstList SEMICOLON  */
#line 333 "src/parser.y"
                                   {
        (yyval.stmttype) = (yyvsp[-1].stmttype);
    }
#line 1707 "src/parser.cpp"
    break;

  case 62: /* VarList: VarDef  */
#line 339 "src/parser.y"
           {
        (yyval.stmttype) = (yyvsp[0].stmttype);
    }
#line 1715 "src/parser.cpp"
    break;

  case 63: /* VarList: VarList COMMA VarDef  */
#line 343 "src/parser.y"
                         {
        (yyval.stmttype) = new SeqNode((yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1723 "src/parser.cpp"
    break;

  case 64: /* ConstList: ConstDef  */
#line 349 "src/parser.y"
             {
        (yyval.stmttype) = (yyvsp[0].stmttype);
    }
#line 1731 "src/parser.cpp"
    break;

  case 65: /* ConstList: ConstList COMMA ConstDef  */
#line 353 "src/parser.y"
                             {
        (yyval.stmttype) = new SeqNode((yyvsp[-2].stmttype), (yyvsp[0].stmttype));
    }
#line 1739 "src/parser.cpp"
    break;

  case 66: /* VarDef: ID  */
#line 360 "src/parser.y"
    {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[0].strtype));
        if(identifiers->lookup((yyvsp[0].strtype)) != nullptr)
        {
            fprintf(stderr, "\033[31mLine %d: identifier \"%s\" being redefined\033[39m\n", yyget_lineno(), (char*)(yyvsp[0].strtype));
            se = new IdentifierSymbolEntry(
                TypeSystem::errorType, (std::string)"_redefined_"+(yyvsp[0].strtype), identifiers->getLevel());
        }
        else
        {
            se = new IdentifierSymbolEntry(nowType, (yyvsp[0].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[0].strtype), se);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[0].strtype);
    }
#line 1761 "src/parser.cpp"
    break;

  case 67: /* VarDef: ID ASSIGN Exp  */
#line 379 "src/parser.y"
    {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-2].strtype));
        if(identifiers->lookup((yyvsp[-2].strtype)) != nullptr)
        {
            fprintf(stderr, "\033[31mLine %d: identifier \"%s\" being redefined\033[39m\n", yyget_lineno(), (char*)(yyvsp[-2].strtype));
            se = new IdentifierSymbolEntry(
                TypeSystem::errorType, (std::string)"_redefined_"+(yyvsp[-2].strtype), identifiers->getLevel());
        }
        else
        {
            se = new IdentifierSymbolEntry(nowType, (yyvsp[-2].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-2].strtype), se);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se), (yyvsp[0].exprtype));
        delete [](yyvsp[-2].strtype);
    }
#line 1783 "src/parser.cpp"
    break;

  case 68: /* ConstDef: ID  */
#line 400 "src/parser.y"
    {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[0].strtype));
        if(identifiers->lookup((yyvsp[0].strtype)) != nullptr)
        {
            fprintf(stderr, "\033[31mLine %d: identifier \"%s\" being redefined\033[39m\n", yyget_lineno(), (char*)(yyvsp[0].strtype));
            se = new IdentifierSymbolEntry(
                TypeSystem::errorType, (std::string)"_redefined_"+(yyvsp[0].strtype), identifiers->getLevel());
        }
        else
        {
            se = new IdentifierSymbolEntry(TypeSystem::getConstTypeOf(nowType), (yyvsp[0].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[0].strtype), se);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se));
        delete [](yyvsp[0].strtype);
    }
#line 1805 "src/parser.cpp"
    break;

  case 69: /* ConstDef: ID ASSIGN Exp  */
#line 419 "src/parser.y"
    {
        SymbolEntry *se;
        se = identifiers->lookup((yyvsp[-2].strtype));
        if(identifiers->lookup((yyvsp[-2].strtype)) != nullptr)
        {
            fprintf(stderr, "\033[31mLine %d: identifier \"%s\" being redefined\033[39m\n", yyget_lineno(), (char*)(yyvsp[-2].strtype));
            se = new IdentifierSymbolEntry(
                TypeSystem::errorType, (std::string)"_redefined_"+(yyvsp[-2].strtype), identifiers->getLevel());
        }
        else
        {
            se = new IdentifierSymbolEntry(TypeSystem::getConstTypeOf(nowType), (yyvsp[-2].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-2].strtype), se);
        }
        (yyval.stmttype) = new DeclStmt(new Id(se), (yyvsp[0].exprtype));
        delete [](yyvsp[-2].strtype);
    }
#line 1827 "src/parser.cpp"
    break;

  case 70: /* $@2: %empty  */
#line 443 "src/parser.y"
    {
        
        identifiers = new SymbolTable(identifiers);
    }
#line 1836 "src/parser.cpp"
    break;

  case 71: /* FuncDef: Type ID $@2 LPAREN FuncParam RPAREN Stmt  */
#line 449 "src/parser.y"
    {
        Type *funcType;
        funcType = new FunctionType((yyvsp[-6].type), (yyvsp[-2].funcparamstype)->getTypes()); // FunctionType(Type* returnType, std::vector<Type*> paramsType)
        
        // 是否被重定义、参数是否匹配
        bool isSame = false;
        bool legalRedefine = false;
        SymbolEntry *se = globals->lookup((yyvsp[-5].strtype));
        if(se != nullptr)
        { // 函数重定义
            FunctionType *DefinedType = dynamic_cast<FunctionType *>(se->getType());
            if(DefinedType != nullptr)
            {
                std::vector<Type*> DefinedParamsType = DefinedType->getParamsType();
                std::vector<Type*> NewParamsType = (yyvsp[-2].funcparamstype)->getTypes();
                if(DefinedParamsType.size() == NewParamsType.size())
                {
                    isSame = true;
                    for(int i = 0; i < (int)(DefinedParamsType.size()); i++)
                    {
                        if(DefinedParamsType[i] != NewParamsType[i])
                        {
                            isSame = false;
                            break;
                        }
                    }
                }
            }
        }
        if(isSame)
        { // 完全一致的重定义
            fprintf(stderr, "\033[31mLine %d: function \"%s\" being redefined\033[39m\n", 
                yyget_lineno(), (char*)(yyvsp[-5].strtype));
            se = new IdentifierSymbolEntry(
                TypeSystem::errorType, (std::string)"_redefined_"+(yyvsp[-5].strtype), identifiers->getLevel());
            (yyval.stmttype) = new FunctionDef(se, (yyvsp[-2].funcparamstype), (yyvsp[0].stmttype));
        }
        else if(se != nullptr)
        { // 重定义，但参数不匹配
            // 不能新建entry了，因为会导致函数名被覆盖
            legalRedefine = true;
            (yyval.stmttype) = new FunctionDef(new IdentifierSymbolEntry(funcType, (yyvsp[-5].strtype), identifiers->getLevel()), (yyvsp[-2].funcparamstype), (yyvsp[0].stmttype));
        }
        else
        {
            se = new IdentifierSymbolEntry(funcType, (yyvsp[-5].strtype), identifiers->getLevel());
            globals->install((yyvsp[-5].strtype), se); // 函数定义时，将函数名加入全局符号表
            (yyval.stmttype) = new FunctionDef(se, (yyvsp[-2].funcparamstype), (yyvsp[0].stmttype));
        }
        

        // $$ = new FunctionDef(se, $5, $7);
        SymbolTable *top = identifiers;

        if(legalRedefine)
        { // 合法重定义 TODO
            FunctionDef *current = (FunctionDef *)(((IdentifierSymbolEntry *)se)->reverse_func);
            while(current->next != nullptr)
                current = current->next;
            current->next = (FunctionDef *)(yyval.stmttype);
        }
        else if(!isSame)
        { // 非重定义
            ((IdentifierSymbolEntry *)se)->reverse_func = (FunctionDef *)(yyval.stmttype);
        }
        identifiers = identifiers->getPrev();
        delete top;
        delete [](yyvsp[-5].strtype);
    }
#line 1910 "src/parser.cpp"
    break;

  case 72: /* FuncParam: %empty  */
#line 521 "src/parser.y"
           {(yyval.funcparamstype) = new FuncParams();}
#line 1916 "src/parser.cpp"
    break;

  case 73: /* FuncParam: Type ID  */
#line 523 "src/parser.y"
            {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry((yyvsp[-1].type), (yyvsp[0].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[0].strtype), se);
        DeclStmt* decl = new DeclStmt(new Id(se));
        (yyval.funcparamstype) = new FuncParams();
        (yyval.funcparamstype)->append((yyvsp[-1].type), decl);
        delete [](yyvsp[0].strtype);
    }
#line 1930 "src/parser.cpp"
    break;

  case 74: /* FuncParam: FuncParam COMMA Type ID  */
#line 533 "src/parser.y"
                            {
        SymbolEntry *se;
        se = new IdentifierSymbolEntry((yyvsp[-1].type), (yyvsp[0].strtype), identifiers->getLevel());
        identifiers->install((yyvsp[0].strtype), se);
        DeclStmt* decl = new DeclStmt(new Id(se));
        (yyval.funcparamstype)->append((yyvsp[-1].type), decl);
        delete [](yyvsp[0].strtype);
    }
#line 1943 "src/parser.cpp"
    break;


#line 1947 "src/parser.cpp"

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

#line 542 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<" at line "<<yyget_lineno()<<std::endl;
    return -1;
}
