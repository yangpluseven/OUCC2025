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

    #include <cstring>
    #include <memory>
    #include <stdarg.h>

    #include "ast.h"
    #include "define.h"

    using namespace std;
    unique_ptr<CompUnitNode> root;

    extern int yylineno;
    extern int yylex();
    extern void yyerror(const char *s);
    extern void initFileName(char *name);
    char filename[100];


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

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_GTE = 6,                        /* GTE  */
  YYSYMBOL_LTE = 7,                        /* LTE  */
  YYSYMBOL_GT = 8,                         /* GT  */
  YYSYMBOL_LT = 9,                         /* LT  */
  YYSYMBOL_EQ = 10,                        /* EQ  */
  YYSYMBOL_NEQ = 11,                       /* NEQ  */
  YYSYMBOL_INTTYPE = 12,                   /* INTTYPE  */
  YYSYMBOL_FLOATTYPE = 13,                 /* FLOATTYPE  */
  YYSYMBOL_VOID = 14,                      /* VOID  */
  YYSYMBOL_CONST = 15,                     /* CONST  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_ELSE = 18,                      /* ELSE  */
  YYSYMBOL_WHILE = 19,                     /* WHILE  */
  YYSYMBOL_BREAK = 20,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 21,                  /* CONTINUE  */
  YYSYMBOL_LP = 22,                        /* LP  */
  YYSYMBOL_RP = 23,                        /* RP  */
  YYSYMBOL_LB = 24,                        /* LB  */
  YYSYMBOL_RB = 25,                        /* RB  */
  YYSYMBOL_LC = 26,                        /* LC  */
  YYSYMBOL_RC = 27,                        /* RC  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 29,                 /* SEMICOLON  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_ASSIGN = 31,                    /* ASSIGN  */
  YYSYMBOL_MINUS = 32,                     /* MINUS  */
  YYSYMBOL_ADD = 33,                       /* ADD  */
  YYSYMBOL_MUL = 34,                       /* MUL  */
  YYSYMBOL_DIV = 35,                       /* DIV  */
  YYSYMBOL_MOD = 36,                       /* MOD  */
  YYSYMBOL_AND = 37,                       /* AND  */
  YYSYMBOL_OR = 38,                        /* OR  */
  YYSYMBOL_LOWER_THEN_ELSE = 39,           /* LOWER_THEN_ELSE  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Program = 41,                   /* Program  */
  YYSYMBOL_CompUnit = 42,                  /* CompUnit  */
  YYSYMBOL_DefList = 43,                   /* DefList  */
  YYSYMBOL_Decl = 44,                      /* Decl  */
  YYSYMBOL_BType = 45,                     /* BType  */
  YYSYMBOL_VoidType = 46,                  /* VoidType  */
  YYSYMBOL_Def = 47,                       /* Def  */
  YYSYMBOL_Arrays = 48,                    /* Arrays  */
  YYSYMBOL_InitVal = 49,                   /* InitVal  */
  YYSYMBOL_InitValList = 50,               /* InitValList  */
  YYSYMBOL_FuncDef = 51,                   /* FuncDef  */
  YYSYMBOL_FuncFParamList = 52,            /* FuncFParamList  */
  YYSYMBOL_FuncFParam = 53,                /* FuncFParam  */
  YYSYMBOL_Block = 54,                     /* Block  */
  YYSYMBOL_BlockItemList = 55,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 56,                 /* BlockItem  */
  YYSYMBOL_Stmt = 57,                      /* Stmt  */
  YYSYMBOL_IfStmt = 58,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 59,                 /* WhileStmt  */
  YYSYMBOL_ReturnStmt = 60,                /* ReturnStmt  */
  YYSYMBOL_Cond = 61,                      /* Cond  */
  YYSYMBOL_LVal = 62,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 63,                /* PrimaryExp  */
  YYSYMBOL_Number = 64,                    /* Number  */
  YYSYMBOL_UnaryExp = 65,                  /* UnaryExp  */
  YYSYMBOL_Call = 66,                      /* Call  */
  YYSYMBOL_UnaryOp = 67,                   /* UnaryOp  */
  YYSYMBOL_FuncCParamList = 68,            /* FuncCParamList  */
  YYSYMBOL_MulExp = 69,                    /* MulExp  */
  YYSYMBOL_AddExp = 70,                    /* AddExp  */
  YYSYMBOL_RelExp = 71,                    /* RelExp  */
  YYSYMBOL_EqExp = 72,                     /* EqExp  */
  YYSYMBOL_LAndExp = 73,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 74                     /* LOrExp  */
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
typedef yytype_uint8 yy_state_t;

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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   234

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   123,   123,   129,   133,   137,   141,   148,   152,   159,
     165,   174,   177,   183,   189,   195,   200,   205,   212,   216,
     223,   227,   230,   237,   241,   248,   255,   261,   268,   277,
     281,   288,   294,   300,   310,   313,   320,   324,   331,   335,
     341,   345,   351,   356,   360,   364,   369,   374,   379,   387,
     392,   401,   409,   413,   419,   425,   429,   437,   441,   445,
     452,   457,   465,   469,   473,   481,   485,   493,   496,   499,
     505,   509,   516,   520,   526,   532,   541,   545,   551,   560,
     564,   570,   576,   582,   591,   595,   601,   610,   614,   622,
     626
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "GTE", "LTE", "GT", "LT", "EQ", "NEQ", "INTTYPE", "FLOATTYPE", "VOID",
  "CONST", "RETURN", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "LP",
  "RP", "LB", "RB", "LC", "RC", "COMMA", "SEMICOLON", "NOT", "ASSIGN",
  "MINUS", "ADD", "MUL", "DIV", "MOD", "AND", "OR", "LOWER_THEN_ELSE",
  "$accept", "Program", "CompUnit", "DefList", "Decl", "BType", "VoidType",
  "Def", "Arrays", "InitVal", "InitValList", "FuncDef", "FuncFParamList",
  "FuncFParam", "Block", "BlockItemList", "BlockItem", "Stmt", "IfStmt",
  "WhileStmt", "ReturnStmt", "Cond", "LVal", "PrimaryExp", "Number",
  "UnaryExp", "Call", "UnaryOp", "FuncCParamList", "MulExp", "AddExp",
  "RelExp", "EqExp", "LAndExp", "LOrExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-114)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     195,  -114,  -114,  -114,    15,     5,   195,  -114,    20,    65,
    -114,    71,  -114,  -114,  -114,    57,    66,  -114,    37,    -8,
      83,    -3,   201,    45,     7,    71,  -114,     9,  -114,    94,
     102,    46,  -114,  -114,  -114,    -9,   201,  -114,  -114,  -114,
    -114,  -114,  -114,  -114,  -114,   201,   107,    64,    14,  -114,
      53,   201,    45,  -114,    94,    78,   118,  -114,    85,    94,
      15,    50,   108,    29,  -114,   201,   201,   201,  -114,   201,
     201,  -114,  -114,    99,    67,  -114,  -114,    94,   189,    82,
     124,   120,   131,  -114,  -114,  -114,    71,  -114,   149,  -114,
    -114,  -114,  -114,  -114,   132,    81,   142,  -114,  -114,  -114,
      80,    53,  -114,  -114,  -114,  -114,   107,   107,  -114,    45,
    -114,  -114,  -114,    96,   201,   201,  -114,  -114,  -114,  -114,
     201,  -114,   153,  -114,   201,  -114,  -114,   157,    53,   206,
     146,   150,   162,   180,   126,   108,    53,   169,   201,   201,
     201,   201,   201,   201,   201,   201,   169,  -114,   198,    53,
      53,    53,    53,   206,   206,   146,   150,  -114,   169,  -114
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    12,    13,     0,     0,     2,     5,     0,     0,
       6,     0,     1,     3,     4,    17,     0,     7,     0,    17,
       0,     0,     0,     0,    16,     0,    10,     0,     9,     0,
       0,     0,    29,    60,    61,    55,     0,    69,    68,    67,
      58,    62,    59,    72,    63,     0,    76,     0,     0,    15,
      20,     0,     0,     8,     0,     0,     0,    26,    31,     0,
       0,     0,    56,     0,    64,     0,     0,     0,    18,     0,
       0,    21,    24,     0,     0,    14,    28,     0,     0,     0,
       0,     0,     0,    34,    40,    38,     0,    45,     0,    36,
      39,    47,    48,    46,    58,     0,     0,    25,    30,    65,
       0,    70,    57,    73,    74,    75,    78,    77,    22,     0,
      19,    27,    53,     0,     0,     0,    44,    43,    35,    37,
       0,    42,    32,    66,     0,    23,    52,     0,    79,    84,
      87,    89,    54,     0,     0,    33,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    41,    49,    80,
      81,    82,    83,    85,    86,    88,    90,    51,     0,    50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,  -114,   209,    51,     2,  -114,   192,   -31,   -41,
    -114,   218,   199,   165,   -17,  -114,   139,  -113,  -114,  -114,
    -114,   113,   -53,  -114,  -114,    -2,  -114,  -114,  -114,   114,
     -22,    54,    86,    84,  -114
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,    16,    85,    30,     9,    17,    24,    49,
      73,    10,    31,    32,    87,    88,    89,    90,    91,    92,
      93,   127,    40,    41,    42,    43,    44,    45,   100,    46,
     128,   129,   130,   131,   132
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      47,    50,     8,    94,    62,    12,    11,    72,     8,     1,
       2,    75,    57,    61,    63,    22,    22,    33,    34,    35,
      29,     1,     2,    23,   148,    15,    50,     1,     2,    74,
      50,    51,    54,   157,    95,    94,    36,    76,    52,   101,
      48,    71,    97,    64,    37,   159,    38,    39,    33,    34,
      35,     7,   102,    33,    34,    35,   113,    13,    86,    27,
     111,    69,    70,   103,   104,   105,    95,    36,   125,    59,
      18,    48,    36,    99,    60,    37,    19,    38,    39,    21,
      37,    22,    38,    39,    94,    69,    70,    50,    23,    68,
      86,   135,   110,    94,    25,    26,    69,    70,   134,    69,
      70,    77,   136,   123,   114,    94,    60,    58,   124,    96,
     121,    25,    28,    69,    70,    95,   149,   150,   151,   152,
      56,    33,    34,    35,    95,   126,   108,   109,    69,    70,
       1,     2,    51,     4,    78,    79,    95,    80,    81,    82,
      36,    65,    66,    67,    56,    83,   115,    84,    37,   116,
      38,    39,    33,    34,    35,   147,   142,   143,    69,    70,
     117,     1,     2,   120,     4,    78,    79,   122,    80,    81,
      82,    36,    33,    34,    35,    56,   118,    22,    84,    37,
     137,    38,    39,   106,   107,    78,    79,   144,    80,    81,
      82,    36,    33,    34,    35,    56,   153,   154,    84,    37,
     145,    38,    39,   146,    33,    34,    35,     1,     2,     3,
       4,    36,   138,   139,   140,   141,   158,    53,   112,    37,
      20,    38,    39,    36,    14,    98,    55,   119,   133,   156,
     155,    37,     0,    38,    39
};

static const yytype_int16 yycheck[] =
{
      22,    23,     0,    56,    35,     0,     4,    48,     6,    12,
      13,    52,    29,    22,    36,    24,    24,     3,     4,     5,
      23,    12,    13,    31,   137,     5,    48,    12,    13,    51,
      52,    24,    23,   146,    56,    88,    22,    54,    31,    61,
      26,    27,    59,    45,    30,   158,    32,    33,     3,     4,
       5,     0,    23,     3,     4,     5,    78,     6,    56,    22,
      77,    32,    33,    65,    66,    67,    88,    22,   109,    23,
       5,    26,    22,    23,    28,    30,     5,    32,    33,    22,
      30,    24,    32,    33,   137,    32,    33,   109,    31,    25,
      88,   122,    25,   146,    28,    29,    32,    33,   120,    32,
      33,    23,   124,    23,    22,   158,    28,     5,    28,    24,
      29,    28,    29,    32,    33,   137,   138,   139,   140,   141,
      26,     3,     4,     5,   146,    29,    27,    28,    32,    33,
      12,    13,    24,    15,    16,    17,   158,    19,    20,    21,
      22,    34,    35,    36,    26,    27,    22,    29,    30,    29,
      32,    33,     3,     4,     5,    29,    10,    11,    32,    33,
      29,    12,    13,    31,    15,    16,    17,    25,    19,    20,
      21,    22,     3,     4,     5,    26,    27,    24,    29,    30,
      23,    32,    33,    69,    70,    16,    17,    37,    19,    20,
      21,    22,     3,     4,     5,    26,   142,   143,    29,    30,
      38,    32,    33,    23,     3,     4,     5,    12,    13,    14,
      15,    22,     6,     7,     8,     9,    18,    25,    29,    30,
      11,    32,    33,    22,     6,    60,    27,    88,   115,   145,
     144,    30,    -1,    32,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    13,    14,    15,    41,    42,    44,    45,    46,
      51,    45,     0,    44,    51,     5,    43,    47,     5,     5,
      43,    22,    24,    31,    48,    28,    29,    22,    29,    23,
      45,    52,    53,     3,     4,     5,    22,    30,    32,    33,
      62,    63,    64,    65,    66,    67,    69,    70,    26,    49,
      70,    24,    31,    47,    23,    52,    26,    54,     5,    23,
      28,    22,    48,    70,    65,    34,    35,    36,    25,    32,
      33,    27,    49,    50,    70,    49,    54,    23,    16,    17,
      19,    20,    21,    27,    29,    44,    45,    54,    55,    56,
      57,    58,    59,    60,    62,    70,    24,    54,    53,    23,
      68,    70,    23,    65,    65,    65,    69,    69,    27,    28,
      25,    54,    29,    70,    22,    22,    29,    29,    27,    56,
      31,    29,    25,    23,    28,    49,    29,    61,    70,    71,
      72,    73,    74,    61,    70,    48,    70,    23,     6,     7,
       8,     9,    10,    11,    37,    38,    23,    29,    57,    70,
      70,    70,    70,    71,    71,    72,    73,    57,    18,    57
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    42,    43,    43,    44,
      44,    45,    45,    46,    47,    47,    47,    47,    48,    48,
      49,    49,    49,    50,    50,    51,    51,    51,    51,    52,
      52,    53,    53,    53,    54,    54,    55,    55,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    59,    60,    60,    61,    62,    62,    63,    63,    63,
      64,    64,    65,    65,    65,    66,    66,    67,    67,    67,
      68,    68,    69,    69,    69,    69,    70,    70,    70,    71,
      71,    71,    71,    71,    72,    72,    72,    73,    73,    74,
      74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     1,     3,     4,
       3,     1,     1,     1,     4,     3,     2,     1,     3,     4,
       1,     2,     3,     3,     1,     6,     5,     6,     5,     1,
       3,     2,     4,     5,     2,     3,     1,     2,     1,     1,
       1,     4,     2,     2,     2,     1,     1,     1,     1,     5,
       7,     5,     3,     2,     1,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     2,     3,     4,     1,     1,     1,
       1,     3,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       3
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: CompUnit  */
             {
        root = unique_ptr<CompUnitNode>((yyvsp[0].compUnit));
    }
    break;

  case 3: /* CompUnit: CompUnit Decl  */
                  {
        (yyval.compUnit) = (yyvsp[-1].compUnit);
        (yyval.compUnit)->declList.push_back(unique_ptr<DeclNode>((yyvsp[0].decl)));
    }
    break;

  case 4: /* CompUnit: CompUnit FuncDef  */
                     {
        (yyval.compUnit) = (yyvsp[-1].compUnit);
        (yyval.compUnit)->funcDefList.push_back(unique_ptr<FuncDefNode>((yyvsp[0].funcDef)));
    }
    break;

  case 5: /* CompUnit: Decl  */
         {
        (yyval.compUnit) = new CompUnitNode();
        (yyval.compUnit)->declList.push_back(unique_ptr<DeclNode>((yyvsp[0].decl)));
    }
    break;

  case 6: /* CompUnit: FuncDef  */
            {
        (yyval.compUnit) = new CompUnitNode(); 
        (yyval.compUnit)->funcDefList.push_back(unique_ptr<FuncDefNode>((yyvsp[0].funcDef)));
    }
    break;

  case 7: /* DefList: Def  */
        {
        (yyval.defList) = new DefList();
        (yyval.defList)->list.push_back(unique_ptr<DefNode>((yyvsp[0].def)));
    }
    break;

  case 8: /* DefList: DefList COMMA Def  */
                      {
        (yyval.defList) = (yyvsp[-2].defList);
        (yyval.defList)->list.push_back(unique_ptr<DefNode>((yyvsp[0].def)));
    }
    break;

  case 9: /* Decl: CONST BType DefList SEMICOLON  */
                                  {
        (yyval.decl) = new DeclNode();
        (yyval.decl)->bType = (yyvsp[-2].ty);
        (yyval.decl)->isConst = true;
        (yyval.decl)->defList.swap((yyvsp[-1].defList)->list);
    }
    break;

  case 10: /* Decl: BType DefList SEMICOLON  */
                            {
        (yyval.decl) = new DeclNode();
        (yyval.decl)->bType = (yyvsp[-2].ty);
        (yyval.decl)->isConst = false;
        (yyval.decl)->defList.swap((yyvsp[-1].defList)->list);
    }
    break;

  case 11: /* BType: INTTYPE  */
            {
        (yyval.ty) = BType::INT;
    }
    break;

  case 12: /* BType: FLOATTYPE  */
              {
        (yyval.ty) = BType::FLOAT;
    }
    break;

  case 13: /* VoidType: VOID  */
         {
        (yyval.ty) = BType::VOID;
    }
    break;

  case 14: /* Def: ID Arrays ASSIGN InitVal  */
                             {
        (yyval.def) = new DefNode();
        (yyval.def)->id = unique_ptr<string>((yyvsp[-3].token));
        (yyval.def)->arrays.swap((yyvsp[-2].arrays)->list);
        (yyval.def)->initVal = unique_ptr<InitValNode>((yyvsp[0].initVal));
    }
    break;

  case 15: /* Def: ID ASSIGN InitVal  */
                      {
        (yyval.def) = new DefNode();
        (yyval.def)->id = unique_ptr<string>((yyvsp[-2].token));
        (yyval.def)->initVal = unique_ptr<InitValNode>((yyvsp[0].initVal));
    }
    break;

  case 16: /* Def: ID Arrays  */
              {
        (yyval.def) = new DefNode();
        (yyval.def)->id = unique_ptr<string>((yyvsp[-1].token));
        (yyval.def)->arrays.swap((yyvsp[0].arrays)->list);
    }
    break;

  case 17: /* Def: ID  */
       {
        (yyval.def) = new DefNode();
        (yyval.def)->id = unique_ptr<string>((yyvsp[0].token));
    }
    break;

  case 18: /* Arrays: LB AddExp RB  */
                 {
        (yyval.arrays) = new ArrayList();
        (yyval.arrays)->list.push_back(unique_ptr<AddExpNode>((yyvsp[-1].addExp)));
    }
    break;

  case 19: /* Arrays: Arrays LB AddExp RB  */
                        {
        (yyval.arrays) = (yyvsp[-3].arrays);
        (yyval.arrays)->list.push_back(unique_ptr<AddExpNode>((yyvsp[-1].addExp)));
    }
    break;

  case 20: /* InitVal: AddExp  */
           {
        (yyval.initVal) = new InitValNode();
        (yyval.initVal)->exp = unique_ptr<AddExpNode>((yyvsp[0].addExp));
    }
    break;

  case 21: /* InitVal: LC RC  */
          {
        (yyval.initVal) = new InitValNode();
    }
    break;

  case 22: /* InitVal: LC InitValList RC  */
                      {
        (yyval.initVal) = new InitValNode();
        (yyval.initVal)->initValList.swap((yyvsp[-1].initValList)->list);
    }
    break;

  case 23: /* InitValList: InitValList COMMA InitVal  */
                              {
        (yyval.initValList) = (yyvsp[-2].initValList);
        (yyval.initValList)->list.push_back(unique_ptr<InitValNode>((yyvsp[0].initVal)));
    }
    break;

  case 24: /* InitValList: InitVal  */
            {
        (yyval.initValList) = new InitValList();
        (yyval.initValList)->list.push_back(unique_ptr<InitValNode>((yyvsp[0].initVal)));
    }
    break;

  case 25: /* FuncDef: BType ID LP FuncFParamList RP Block  */
                                        {
        (yyval.funcDef) = new FuncDefNode();
        (yyval.funcDef)->returnType = (yyvsp[-5].ty);
        (yyval.funcDef)->id = unique_ptr<string>((yyvsp[-4].token));
        (yyval.funcDef)->funcFParamList.swap((yyvsp[-2].funcFParamList)->list);
        (yyval.funcDef)->block = unique_ptr<BlockNode>((yyvsp[0].block));
    }
    break;

  case 26: /* FuncDef: BType ID LP RP Block  */
                         {
        (yyval.funcDef) = new FuncDefNode();
        (yyval.funcDef)->returnType = (yyvsp[-4].ty);
        (yyval.funcDef)->id = unique_ptr<string>((yyvsp[-3].token));
        (yyval.funcDef)->block = unique_ptr<BlockNode>((yyvsp[0].block));
    }
    break;

  case 27: /* FuncDef: VoidType ID LP FuncFParamList RP Block  */
                                           {
        (yyval.funcDef) = new FuncDefNode();
        (yyval.funcDef)->returnType = (yyvsp[-5].ty);
        (yyval.funcDef)->id = unique_ptr<string>((yyvsp[-4].token));
        (yyval.funcDef)->funcFParamList.swap((yyvsp[-2].funcFParamList)->list);
        (yyval.funcDef)->block = unique_ptr<BlockNode>((yyvsp[0].block));
    }
    break;

  case 28: /* FuncDef: VoidType ID LP RP Block  */
                            {
        (yyval.funcDef) = new FuncDefNode();
        (yyval.funcDef)->returnType = (yyvsp[-4].ty);
        (yyval.funcDef)->id = unique_ptr<string>((yyvsp[-3].token));
        (yyval.funcDef)->block = unique_ptr<BlockNode>((yyvsp[0].block));
    }
    break;

  case 29: /* FuncFParamList: FuncFParam  */
               {
        (yyval.funcFParamList) = new FuncFParamList();
        (yyval.funcFParamList)->list.push_back(unique_ptr<FuncFParamNode>((yyvsp[0].funcFParam)));
    }
    break;

  case 30: /* FuncFParamList: FuncFParamList COMMA FuncFParam  */
                                    {
        (yyval.funcFParamList) = (yyvsp[-2].funcFParamList);
        (yyval.funcFParamList)->list.push_back(unique_ptr<FuncFParamNode>((yyvsp[0].funcFParam)));
    }
    break;

  case 31: /* FuncFParam: BType ID  */
             {
        (yyval.funcFParam) = new FuncFParamNode();
        (yyval.funcFParam)->bType = (yyvsp[-1].ty);
        (yyval.funcFParam)->id = unique_ptr<string>((yyvsp[0].token));
        (yyval.funcFParam)->isArray = false;
    }
    break;

  case 32: /* FuncFParam: BType ID LB RB  */
                   {
        (yyval.funcFParam) = new FuncFParamNode();
        (yyval.funcFParam)->bType = (yyvsp[-3].ty);
        (yyval.funcFParam)->id = unique_ptr<string>((yyvsp[-2].token));
        (yyval.funcFParam)->isArray = true;
    }
    break;

  case 33: /* FuncFParam: BType ID LB RB Arrays  */
                          {
        (yyval.funcFParam) = new FuncFParamNode();
        (yyval.funcFParam)->bType = (yyvsp[-4].ty);
        (yyval.funcFParam)->id = unique_ptr<string>((yyvsp[-3].token));
        (yyval.funcFParam)->isArray = true;
        (yyval.funcFParam)->arrays.swap((yyvsp[0].arrays)->list);
    }
    break;

  case 34: /* Block: LC RC  */
          {
        (yyval.block) = new BlockNode();
    }
    break;

  case 35: /* Block: LC BlockItemList RC  */
                        {
        (yyval.block) = new BlockNode();
        (yyval.block)->blockItemList.swap((yyvsp[-1].blockItemList)->list);
    }
    break;

  case 36: /* BlockItemList: BlockItem  */
              {
        (yyval.blockItemList) = new BlockItemList();
        (yyval.blockItemList)->list.push_back(unique_ptr<BlockItemNode>((yyvsp[0].blockItem)));
    }
    break;

  case 37: /* BlockItemList: BlockItemList BlockItem  */
                            {
        (yyval.blockItemList) = (yyvsp[-1].blockItemList);
        (yyval.blockItemList)->list.push_back(unique_ptr<BlockItemNode>((yyvsp[0].blockItem)));
    }
    break;

  case 38: /* BlockItem: Decl  */
         {
        (yyval.blockItem) = new BlockItemNode();
        (yyval.blockItem)->decl = unique_ptr<DeclNode>((yyvsp[0].decl));
    }
    break;

  case 39: /* BlockItem: Stmt  */
         {
        (yyval.blockItem) = new BlockItemNode();
        (yyval.blockItem)->stmt = unique_ptr<StmtNode>((yyvsp[0].stmt));
    }
    break;

  case 40: /* Stmt: SEMICOLON  */
              {
        (yyval.stmt) = new StmtNode();
        (yyval.stmt)->sType = StmtType::SEMI;
    }
    break;

  case 41: /* Stmt: LVal ASSIGN AddExp SEMICOLON  */
                                 {
        (yyval.stmt) = new StmtNode();
        (yyval.stmt)->sType = StmtType::ASGN;
        (yyval.stmt)->lVal = unique_ptr<LValNode>((yyvsp[-3].lVal));
        (yyval.stmt)->exp = unique_ptr<AddExpNode>((yyvsp[-1].addExp));
    }
    break;

  case 42: /* Stmt: AddExp SEMICOLON  */
                     {
        (yyval.stmt) = new StmtNode();
        (yyval.stmt)->sType = StmtType::EXP;
        (yyval.stmt)->exp = unique_ptr<AddExpNode>((yyvsp[-1].addExp));
    }
    break;

  case 43: /* Stmt: CONTINUE SEMICOLON  */
                       {
        (yyval.stmt) = new StmtNode();
        (yyval.stmt)->sType = StmtType::CONTINUE;
    }
    break;

  case 44: /* Stmt: BREAK SEMICOLON  */
                    {
        (yyval.stmt) = new StmtNode();
        (yyval.stmt)->sType = StmtType::BREAK;
    }
    break;

  case 45: /* Stmt: Block  */
          {
        (yyval.stmt) = new StmtNode();
        (yyval.stmt)->sType = StmtType::BLK;
        (yyval.stmt)->block = unique_ptr<BlockNode>((yyvsp[0].block));
    }
    break;

  case 46: /* Stmt: ReturnStmt  */
               {
        (yyval.stmt) = new StmtNode();
        (yyval.stmt)->sType = StmtType::RET;
        (yyval.stmt)->returnStmt = unique_ptr<ReturnStmtNode>((yyvsp[0].returnStmt));
    }
    break;

  case 47: /* Stmt: IfStmt  */
           {
        (yyval.stmt) = new StmtNode();
        (yyval.stmt)->sType = StmtType::IF;
        (yyval.stmt)->ifStmt = unique_ptr<IfStmtNode>((yyvsp[0].ifStmt));
    }
    break;

  case 48: /* Stmt: WhileStmt  */
              {
        (yyval.stmt) = new StmtNode();
        (yyval.stmt)->sType = StmtType::WHILE;
        (yyval.stmt)->whileStmtAST = unique_ptr<WhileStmtNode>((yyvsp[0].whileStmt));
    }
    break;

  case 49: /* IfStmt: IF LP Cond RP Stmt  */
                                             {
        (yyval.ifStmt) = new IfStmtNode();
        (yyval.ifStmt)->cond = unique_ptr<LOrExpNode>((yyvsp[-2].lOrExp));
        (yyval.ifStmt)->ifStmt = unique_ptr<StmtNode>((yyvsp[0].stmt));
    }
    break;

  case 50: /* IfStmt: IF LP Cond RP Stmt ELSE Stmt  */
                                 {
        (yyval.ifStmt) = new IfStmtNode();
        (yyval.ifStmt)->cond = unique_ptr<LOrExpNode>((yyvsp[-4].lOrExp));
        (yyval.ifStmt)->ifStmt = unique_ptr<StmtNode>((yyvsp[-2].stmt));
        (yyval.ifStmt)->elseStmt = unique_ptr<StmtNode>((yyvsp[0].stmt));
    }
    break;

  case 51: /* WhileStmt: WHILE LP Cond RP Stmt  */
                          {
        (yyval.whileStmt) = new WhileStmtNode();
        (yyval.whileStmt)->cond = unique_ptr<LOrExpNode>((yyvsp[-2].lOrExp));
        (yyval.whileStmt)->stmt = unique_ptr<StmtNode>((yyvsp[0].stmt));
    }
    break;

  case 52: /* ReturnStmt: RETURN AddExp SEMICOLON  */
                            {
        (yyval.returnStmt) = new ReturnStmtNode();
        (yyval.returnStmt)->exp = unique_ptr<AddExpNode>((yyvsp[-1].addExp));
    }
    break;

  case 53: /* ReturnStmt: RETURN SEMICOLON  */
                     {
        (yyval.returnStmt) = new ReturnStmtNode();
    }
    break;

  case 54: /* Cond: LOrExp  */
           {
        (yyval.lOrExp) = (yyvsp[0].lOrExp);
    }
    break;

  case 55: /* LVal: ID  */
       {
        (yyval.lVal) = new LValNode();
        (yyval.lVal)->id = unique_ptr<string>((yyvsp[0].token));
    }
    break;

  case 56: /* LVal: ID Arrays  */
              {
        (yyval.lVal) = new LValNode();
        (yyval.lVal)->id = unique_ptr<string>((yyvsp[-1].token));
        (yyval.lVal)->arrays.swap((yyvsp[0].arrays)->list);
    }
    break;

  case 57: /* PrimaryExp: LP AddExp RP  */
                 {
        (yyval.primaryExp) = new PrimaryExpNode();
        (yyval.primaryExp)->exp = unique_ptr<AddExpNode>((yyvsp[-1].addExp));
    }
    break;

  case 58: /* PrimaryExp: LVal  */
         {
        (yyval.primaryExp) = new PrimaryExpNode();
        (yyval.primaryExp)->lval = unique_ptr<LValNode>((yyvsp[0].lVal));
    }
    break;

  case 59: /* PrimaryExp: Number  */
           {
        (yyval.primaryExp) = new PrimaryExpNode();
        (yyval.primaryExp)->number = unique_ptr<NumberNode>((yyvsp[0].number));
    }
    break;

  case 60: /* Number: INT  */
        {
        (yyval.number) = new NumberNode();
        (yyval.number)->isInt = true;
        (yyval.number)->intval = (yyvsp[0].int_val);
    }
    break;

  case 61: /* Number: FLOAT  */
          {
        (yyval.number) = new NumberNode();
        (yyval.number)->isInt = false;
        (yyval.number)->floatval = (yyvsp[0].float_val);
    }
    break;

  case 62: /* UnaryExp: PrimaryExp  */
               {
        (yyval.unaryExp) = new UnaryExpNode();
        (yyval.unaryExp)->primaryExp = unique_ptr<PrimaryExpNode>((yyvsp[0].primaryExp));
    }
    break;

  case 63: /* UnaryExp: Call  */
         {
        (yyval.unaryExp) = new UnaryExpNode();
        (yyval.unaryExp)->call = unique_ptr<CallNode>((yyvsp[0].call));
    }
    break;

  case 64: /* UnaryExp: UnaryOp UnaryExp  */
                     {
        (yyval.unaryExp) = new UnaryExpNode();
        (yyval.unaryExp)->op = (yyvsp[-1].op);
        (yyval.unaryExp)->unaryExp = unique_ptr<UnaryExpNode>((yyvsp[0].unaryExp));
    }
    break;

  case 65: /* Call: ID LP RP  */
             {
        (yyval.call) = new CallNode();
        (yyval.call)->id = unique_ptr<string>((yyvsp[-2].token));
    }
    break;

  case 66: /* Call: ID LP FuncCParamList RP  */
                            {
        (yyval.call) = new CallNode();
        (yyval.call)->id = unique_ptr<string>((yyvsp[-3].token));
        (yyval.call)->funcCParamList.swap((yyvsp[-1].funcCParamList)->list);
    }
    break;

  case 67: /* UnaryOp: ADD  */
        {
        (yyval.op) = UnaryOp::ADD;
    }
    break;

  case 68: /* UnaryOp: MINUS  */
          {
        (yyval.op) = UnaryOp::MINUS;
    }
    break;

  case 69: /* UnaryOp: NOT  */
        {
        (yyval.op) = UnaryOp::NOT;
    }
    break;

  case 70: /* FuncCParamList: AddExp  */
           {
        (yyval.funcCParamList) = new FuncCParamList();
        (yyval.funcCParamList)->list.push_back(unique_ptr<AddExpNode>((yyvsp[0].addExp)));
    }
    break;

  case 71: /* FuncCParamList: FuncCParamList COMMA AddExp  */
                                {
        (yyval.funcCParamList) = (FuncCParamList*) (yyvsp[-2].funcCParamList);
        (yyval.funcCParamList)->list.push_back(unique_ptr<AddExpNode>((yyvsp[0].addExp)));
    }
    break;

  case 72: /* MulExp: UnaryExp  */
             {
        (yyval.mulExp) = new MulExpNode();
        (yyval.mulExp)->unaryExp = unique_ptr<UnaryExpNode>((yyvsp[0].unaryExp));
    }
    break;

  case 73: /* MulExp: MulExp MUL UnaryExp  */
                        {
        (yyval.mulExp) = new MulExpNode();
        (yyval.mulExp)->mulExp = unique_ptr<MulExpNode>((yyvsp[-2].mulExp));
        (yyval.mulExp)->op = MulOp::MUL;
        (yyval.mulExp)->unaryExp = unique_ptr<UnaryExpNode>((yyvsp[0].unaryExp));
    }
    break;

  case 74: /* MulExp: MulExp DIV UnaryExp  */
                        {
        (yyval.mulExp) = new MulExpNode();
        (yyval.mulExp)->mulExp = unique_ptr<MulExpNode>((yyvsp[-2].mulExp));
        (yyval.mulExp)->op = MulOp::DIV;
        (yyval.mulExp)->unaryExp = unique_ptr<UnaryExpNode>((yyvsp[0].unaryExp));
    }
    break;

  case 75: /* MulExp: MulExp MOD UnaryExp  */
                        {
        (yyval.mulExp) = new MulExpNode();
        (yyval.mulExp)->mulExp = unique_ptr<MulExpNode>((yyvsp[-2].mulExp));
        (yyval.mulExp)->op = MulOp::MOD;
        (yyval.mulExp)->unaryExp = unique_ptr<UnaryExpNode>((yyvsp[0].unaryExp));
    }
    break;

  case 76: /* AddExp: MulExp  */
           {
        (yyval.addExp) = new AddExpNode();
        (yyval.addExp)->mulExp = unique_ptr<MulExpNode>((yyvsp[0].mulExp));
    }
    break;

  case 77: /* AddExp: AddExp ADD MulExp  */
                      {
        (yyval.addExp) = new AddExpNode();
        (yyval.addExp)->addExp = unique_ptr<AddExpNode>((yyvsp[-2].addExp));
        (yyval.addExp)->op = AddOp::ADD;
        (yyval.addExp)->mulExp = unique_ptr<MulExpNode>((yyvsp[0].mulExp));
    }
    break;

  case 78: /* AddExp: AddExp MINUS MulExp  */
                        {
        (yyval.addExp) = new AddExpNode();
        (yyval.addExp)->addExp = unique_ptr<AddExpNode>((yyvsp[-2].addExp));
        (yyval.addExp)->op = AddOp::MINUS;
        (yyval.addExp)->mulExp = unique_ptr<MulExpNode>((yyvsp[0].mulExp));
    }
    break;

  case 79: /* RelExp: AddExp  */
           {
        (yyval.relExp) = new RelExpNode();
        (yyval.relExp)->addExp = unique_ptr<AddExpNode>((yyvsp[0].addExp));
    }
    break;

  case 80: /* RelExp: RelExp GTE AddExp  */
                      {
        (yyval.relExp) = new RelExpNode();
        (yyval.relExp)->relExp = unique_ptr<RelExpNode>((yyvsp[-2].relExp));
        (yyval.relExp)->op = RelOp::GTE;
        (yyval.relExp)->addExp = unique_ptr<AddExpNode>((yyvsp[0].addExp));
    }
    break;

  case 81: /* RelExp: RelExp LTE AddExp  */
                      {
        (yyval.relExp) = new RelExpNode();
        (yyval.relExp)->relExp = unique_ptr<RelExpNode>((yyvsp[-2].relExp));
        (yyval.relExp)->op = RelOp::LTE;
        (yyval.relExp)->addExp = unique_ptr<AddExpNode>((yyvsp[0].addExp));
    }
    break;

  case 82: /* RelExp: RelExp GT AddExp  */
                     {
        (yyval.relExp) = new RelExpNode();
        (yyval.relExp)->relExp = unique_ptr<RelExpNode>((yyvsp[-2].relExp));
        (yyval.relExp)->op = RelOp::GT;
        (yyval.relExp)->addExp = unique_ptr<AddExpNode>((yyvsp[0].addExp));
    }
    break;

  case 83: /* RelExp: RelExp LT AddExp  */
                     {
        (yyval.relExp) = new RelExpNode();
        (yyval.relExp)->relExp = unique_ptr<RelExpNode>((yyvsp[-2].relExp));
        (yyval.relExp)->op = RelOp::LT;
        (yyval.relExp)->addExp = unique_ptr<AddExpNode>((yyvsp[0].addExp));
    }
    break;

  case 84: /* EqExp: RelExp  */
           {
        (yyval.eqExp) = new EqExpNode();
        (yyval.eqExp)->relExp = unique_ptr<RelExpNode>((yyvsp[0].relExp));
    }
    break;

  case 85: /* EqExp: EqExp EQ RelExp  */
                    {
        (yyval.eqExp) = new EqExpNode();
        (yyval.eqExp)->eqExp = unique_ptr<EqExpNode>((yyvsp[-2].eqExp));
        (yyval.eqExp)->op = EqOp::EQ;
        (yyval.eqExp)->relExp = unique_ptr<RelExpNode>((yyvsp[0].relExp));
    }
    break;

  case 86: /* EqExp: EqExp NEQ RelExp  */
                     {
        (yyval.eqExp) = new EqExpNode();
        (yyval.eqExp)->eqExp = unique_ptr<EqExpNode>((yyvsp[-2].eqExp));
        (yyval.eqExp)->op = EqOp::NEQ;
        (yyval.eqExp)->relExp = unique_ptr<RelExpNode>((yyvsp[0].relExp));
    }
    break;

  case 87: /* LAndExp: EqExp  */
          {
        (yyval.lAndExp) = new LAndExpNode();
        (yyval.lAndExp)->eqExp = unique_ptr<EqExpNode>((yyvsp[0].eqExp));
    }
    break;

  case 88: /* LAndExp: LAndExp AND EqExp  */
                      {
        (yyval.lAndExp) = new LAndExpNode();
        (yyval.lAndExp)->lAndExp = unique_ptr<LAndExpNode>((yyvsp[-2].lAndExp));
        (yyval.lAndExp)->eqExp = unique_ptr<EqExpNode>((yyvsp[0].eqExp));
    }
    break;

  case 89: /* LOrExp: LAndExp  */
            {
        (yyval.lOrExp) = new LOrExpNode();
        (yyval.lOrExp)->lAndExp = unique_ptr<LAndExpNode>((yyvsp[0].lAndExp));
    }
    break;

  case 90: /* LOrExp: LOrExp OR LAndExp  */
                      {
        (yyval.lOrExp) = new LOrExpNode();
        (yyval.lOrExp)->lOrExp = unique_ptr<LOrExpNode>((yyvsp[-2].lOrExp));
        (yyval.lOrExp)->lAndExp = unique_ptr<LAndExpNode>((yyvsp[0].lAndExp));
    }
    break;



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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}



void initFileName(char *name) {
    strcpy(filename, name);
}

void yyerror(const char* fmt) {
    printf("%s:%d ", filename, yylloc.first_line);
    printf("%s\n", fmt);
}
