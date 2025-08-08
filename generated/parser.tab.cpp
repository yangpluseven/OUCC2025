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
#line 4 "/home/yang/playground/src/sysy/parser.y"

    #include <cstring>
    #include <memory>
    #include <stdarg.h>

    #include "ast.h"
    #include "define.h"

    using namespace std;
    unique_ptr<CompUnit> root;

    extern int yylineno;
    extern int yylex();
    extern void yyerror(const char *s);
    extern void initFileName(char *name);
    char filename[100];

#line 89 "/home/yang/playground/generated/parser.tab.cpp"

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
  YYSYMBOL_Decl = 43,                      /* Decl  */
  YYSYMBOL_BType = 44,                     /* BType  */
  YYSYMBOL_VoidType = 45,                  /* VoidType  */
  YYSYMBOL_DefList = 46,                   /* DefList  */
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
  YYSYMBOL_IterationStmt = 59,             /* IterationStmt  */
  YYSYMBOL_ReturnStmt = 60,                /* ReturnStmt  */
  YYSYMBOL_Exp = 61,                       /* Exp  */
  YYSYMBOL_Cond = 62,                      /* Cond  */
  YYSYMBOL_LVal = 63,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 64,                /* PrimaryExp  */
  YYSYMBOL_Number = 65,                    /* Number  */
  YYSYMBOL_UnaryExp = 66,                  /* UnaryExp  */
  YYSYMBOL_Call = 67,                      /* Call  */
  YYSYMBOL_UnaryOp = 68,                   /* UnaryOp  */
  YYSYMBOL_FuncCParamList = 69,            /* FuncCParamList  */
  YYSYMBOL_MulExp = 70,                    /* MulExp  */
  YYSYMBOL_AddExp = 71,                    /* AddExp  */
  YYSYMBOL_RelExp = 72,                    /* RelExp  */
  YYSYMBOL_EqExp = 73,                     /* EqExp  */
  YYSYMBOL_LAndExp = 74,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 75                     /* LOrExp  */
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
#define YYLAST   225

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

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
       0,   124,   124,   130,   134,   138,   142,   149,   155,   164,
     167,   173,   179,   183,   190,   196,   201,   206,   213,   217,
     224,   228,   231,   238,   242,   249,   256,   262,   269,   278,
     282,   289,   295,   301,   311,   314,   321,   325,   332,   336,
     342,   346,   352,   357,   361,   365,   370,   375,   380,   388,
     393,   402,   410,   414,   420,   426,   432,   436,   444,   448,
     452,   459,   464,   472,   476,   480,   488,   492,   500,   503,
     506,   512,   516,   523,   527,   533,   539,   548,   552,   558,
     567,   571,   577,   583,   589,   598,   602,   608,   617,   621,
     629,   633
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
  "$accept", "Program", "CompUnit", "Decl", "BType", "VoidType", "DefList",
  "Def", "Arrays", "InitVal", "InitValList", "FuncDef", "FuncFParamList",
  "FuncFParam", "Block", "BlockItemList", "BlockItem", "Stmt", "IfStmt",
  "IterationStmt", "ReturnStmt", "Exp", "Cond", "LVal", "PrimaryExp",
  "Number", "UnaryExp", "Call", "UnaryOp", "FuncCParamList", "MulExp",
  "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-132)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     118,  -132,  -132,  -132,    59,    23,   118,  -132,    31,    34,
    -132,    45,  -132,  -132,  -132,    51,    88,  -132,     7,   -11,
     106,    -1,   192,   156,    -5,    45,  -132,    12,  -132,    30,
      57,    10,  -132,  -132,  -132,    77,   192,  -132,  -132,  -132,
      54,  -132,  -132,  -132,  -132,  -132,   192,    24,   130,   144,
    -132,  -132,   192,   156,  -132,    30,    26,    93,  -132,    52,
      30,    59,   176,    63,    67,  -132,  -132,   192,   192,   192,
     192,   192,  -132,  -132,   137,    70,  -132,  -132,    30,   188,
      80,    85,    82,    89,  -132,  -132,  -132,    45,  -132,   124,
    -132,  -132,  -132,  -132,  -132,    92,   107,    99,  -132,  -132,
    -132,  -132,    66,  -132,  -132,  -132,  -132,    24,    24,  -132,
     156,  -132,  -132,  -132,   113,   192,   192,  -132,  -132,  -132,
    -132,  -132,   192,   128,  -132,   192,  -132,  -132,   132,   130,
     194,   157,   121,   131,   152,   158,    63,  -132,    48,   192,
     192,   192,   192,   192,   192,   192,   192,    48,  -132,   167,
     130,   130,   130,   130,   194,   194,   157,   121,  -132,    48,
    -132
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,    11,     0,     0,     2,     5,     0,     0,
       6,     0,     1,     3,     4,    17,     0,    12,     0,    17,
       0,     0,     0,     0,    16,     0,     8,     0,     7,     0,
       0,     0,    29,    61,    62,    56,     0,    70,    69,    68,
       0,    59,    63,    60,    73,    64,     0,    77,    54,     0,
      15,    20,     0,     0,    13,     0,     0,     0,    26,    31,
       0,     0,     0,    57,     0,    18,    65,     0,     0,     0,
       0,     0,    21,    24,     0,     0,    14,    28,     0,     0,
       0,     0,     0,     0,    34,    40,    38,     0,    45,     0,
      36,    39,    47,    48,    46,     0,    59,     0,    25,    30,
      66,    71,     0,    58,    74,    75,    76,    79,    78,    22,
       0,    19,    27,    53,     0,     0,     0,    44,    43,    35,
      37,    42,     0,    32,    67,     0,    23,    52,     0,    80,
      85,    88,    90,    55,     0,     0,    33,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    49,
      81,    82,    83,    84,    86,    87,    89,    91,    51,     0,
      50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,  -132,    15,     4,  -132,   179,   169,   -32,   -44,
    -132,   198,   178,   146,   -23,  -132,   122,  -131,  -132,  -132,
    -132,   -22,    96,   -55,  -132,  -132,    17,  -132,  -132,  -132,
     102,   -98,    40,    68,    69,  -132
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,    86,    30,     9,    16,    17,    24,    50,
      74,    10,    31,    32,    88,    89,    90,    91,    92,    93,
      94,    95,   128,    41,    42,    43,    44,    45,    46,   102,
      47,    48,   130,   131,   132,   133
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,    51,    96,    63,     8,    73,    58,   149,    11,    76,
       8,     1,     2,    22,    64,     7,   158,   129,   129,    52,
      23,    13,    29,    12,     1,     2,    53,    51,   160,    27,
      75,    51,    77,    60,    96,    55,    15,    98,    61,    18,
     101,   150,   151,   152,   153,   129,   129,   129,   129,    78,
      19,    33,    34,    35,    61,   112,    57,   114,    67,    68,
      69,    87,    59,    66,    79,    80,   126,    81,    82,    83,
      36,     1,     2,    21,    57,    22,    97,    85,    37,    65,
      38,    39,    23,    96,   104,   105,   106,    52,    51,   124,
     103,   136,    96,    87,   125,   111,    33,    34,    35,    62,
     135,    22,   115,   137,    96,     1,     2,   116,     4,    79,
      80,   117,    81,    82,    83,    36,    25,    26,   118,    57,
      84,   121,    85,    37,   123,    38,    39,    33,    34,    35,
       1,     2,     3,     4,    25,    28,     1,     2,   122,     4,
      79,    80,   127,    81,    82,    83,    36,    33,    34,    35,
      57,   119,    22,    85,    37,   138,    38,    39,   145,    33,
      34,    35,    70,    71,   109,   110,    36,   143,   144,   146,
      49,    72,   107,   108,    37,   147,    38,    39,    36,    33,
      34,    35,    49,   154,   155,   159,    37,   148,    38,    39,
      20,    33,    34,    35,    54,    33,    34,    35,    36,   100,
     139,   140,   141,   142,    14,    56,    37,    99,    38,    39,
      36,   120,   134,   156,    36,   157,     0,   113,    37,     0,
      38,    39,    37,     0,    38,    39
};

static const yytype_int16 yycheck[] =
{
      22,    23,    57,    35,     0,    49,    29,   138,     4,    53,
       6,    12,    13,    24,    36,     0,   147,   115,   116,    24,
      31,     6,    23,     0,    12,    13,    31,    49,   159,    22,
      52,    53,    55,    23,    89,    23,     5,    60,    28,     5,
      62,   139,   140,   141,   142,   143,   144,   145,   146,    23,
       5,     3,     4,     5,    28,    78,    26,    79,    34,    35,
      36,    57,     5,    46,    16,    17,   110,    19,    20,    21,
      22,    12,    13,    22,    26,    24,    24,    29,    30,    25,
      32,    33,    31,   138,    67,    68,    69,    24,   110,    23,
      23,   123,   147,    89,    28,    25,     3,     4,     5,    22,
     122,    24,    22,   125,   159,    12,    13,    22,    15,    16,
      17,    29,    19,    20,    21,    22,    28,    29,    29,    26,
      27,    29,    29,    30,    25,    32,    33,     3,     4,     5,
      12,    13,    14,    15,    28,    29,    12,    13,    31,    15,
      16,    17,    29,    19,    20,    21,    22,     3,     4,     5,
      26,    27,    24,    29,    30,    23,    32,    33,    37,     3,
       4,     5,    32,    33,    27,    28,    22,    10,    11,    38,
      26,    27,    70,    71,    30,    23,    32,    33,    22,     3,
       4,     5,    26,   143,   144,    18,    30,    29,    32,    33,
      11,     3,     4,     5,    25,     3,     4,     5,    22,    23,
       6,     7,     8,     9,     6,    27,    30,    61,    32,    33,
      22,    89,   116,   145,    22,   146,    -1,    29,    30,    -1,
      32,    33,    30,    -1,    32,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    12,    13,    14,    15,    41,    42,    43,    44,    45,
      51,    44,     0,    43,    51,     5,    46,    47,     5,     5,
      46,    22,    24,    31,    48,    28,    29,    22,    29,    23,
      44,    52,    53,     3,     4,     5,    22,    30,    32,    33,
      61,    63,    64,    65,    66,    67,    68,    70,    71,    26,
      49,    61,    24,    31,    47,    23,    52,    26,    54,     5,
      23,    28,    22,    48,    61,    25,    66,    34,    35,    36,
      32,    33,    27,    49,    50,    61,    49,    54,    23,    16,
      17,    19,    20,    21,    27,    29,    43,    44,    54,    55,
      56,    57,    58,    59,    60,    61,    63,    24,    54,    53,
      23,    61,    69,    23,    66,    66,    66,    70,    70,    27,
      28,    25,    54,    29,    61,    22,    22,    29,    29,    27,
      56,    29,    31,    25,    23,    28,    49,    29,    62,    71,
      72,    73,    74,    75,    62,    61,    48,    61,    23,     6,
       7,     8,     9,    10,    11,    37,    38,    23,    29,    57,
      71,    71,    71,    71,    72,    72,    73,    74,    57,    18,
      57
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    42,    43,    43,    44,
      44,    45,    46,    46,    47,    47,    47,    47,    48,    48,
      49,    49,    49,    50,    50,    51,    51,    51,    51,    52,
      52,    53,    53,    53,    54,    54,    55,    55,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    58,
      58,    59,    60,    60,    61,    62,    63,    63,    64,    64,
      64,    65,    65,    66,    66,    66,    67,    67,    68,    68,
      68,    69,    69,    70,    70,    70,    70,    71,    71,    71,
      72,    72,    72,    72,    72,    73,    73,    73,    74,    74,
      75,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     1,     1,     4,     3,     1,
       1,     1,     1,     3,     4,     3,     2,     1,     3,     4,
       1,     2,     3,     3,     1,     6,     5,     6,     5,     1,
       3,     2,     4,     5,     2,     3,     1,     2,     1,     1,
       1,     4,     2,     2,     2,     1,     1,     1,     1,     5,
       7,     5,     3,     2,     1,     1,     1,     2,     3,     1,
       1,     1,     1,     1,     1,     2,     3,     4,     1,     1,
       1,     1,     3,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3
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
#line 124 "/home/yang/playground/src/sysy/parser.y"
             {
        root = unique_ptr<CompUnit>((yyvsp[0].compUnit));
    }
#line 1664 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 3: /* CompUnit: CompUnit Decl  */
#line 130 "/home/yang/playground/src/sysy/parser.y"
                  {
        (yyval.compUnit) = (yyvsp[-1].compUnit);
        (yyval.compUnit)->declList.push_back(unique_ptr<Decl>((yyvsp[0].decl)));
    }
#line 1673 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 4: /* CompUnit: CompUnit FuncDef  */
#line 134 "/home/yang/playground/src/sysy/parser.y"
                     {
        (yyval.compUnit) = (yyvsp[-1].compUnit);
        (yyval.compUnit)->funcDefList.push_back(unique_ptr<FuncDef>((yyvsp[0].funcDef)));
    }
#line 1682 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 5: /* CompUnit: Decl  */
#line 138 "/home/yang/playground/src/sysy/parser.y"
         {
        (yyval.compUnit) = new CompUnit();
        (yyval.compUnit)->declList.push_back(unique_ptr<Decl>((yyvsp[0].decl)));
    }
#line 1691 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 6: /* CompUnit: FuncDef  */
#line 142 "/home/yang/playground/src/sysy/parser.y"
            {
        (yyval.compUnit) = new CompUnit(); 
        (yyval.compUnit)->funcDefList.push_back(unique_ptr<FuncDef>((yyvsp[0].funcDef)));
    }
#line 1700 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 7: /* Decl: CONST BType DefList SEMICOLON  */
#line 149 "/home/yang/playground/src/sysy/parser.y"
                                  {
        (yyval.decl) = new Decl();
        (yyval.decl)->isConst = true;
        (yyval.decl)->bType = (yyvsp[-2].ty);
        (yyval.decl)->defList.swap((yyvsp[-1].defList)->list);
    }
#line 1711 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 8: /* Decl: BType DefList SEMICOLON  */
#line 155 "/home/yang/playground/src/sysy/parser.y"
                            {
        (yyval.decl) = new Decl();
        (yyval.decl)->isConst = false;
        (yyval.decl)->bType = (yyvsp[-2].ty);
        (yyval.decl)->defList.swap((yyvsp[-1].defList)->list);
    }
#line 1722 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 9: /* BType: INTTYPE  */
#line 164 "/home/yang/playground/src/sysy/parser.y"
            {
        (yyval.ty) = BType::INT;
    }
#line 1730 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 10: /* BType: FLOATTYPE  */
#line 167 "/home/yang/playground/src/sysy/parser.y"
              {
        (yyval.ty) = BType::FLOAT;
    }
#line 1738 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 11: /* VoidType: VOID  */
#line 173 "/home/yang/playground/src/sysy/parser.y"
         {
        (yyval.ty) = BType::VOID;
    }
#line 1746 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 12: /* DefList: Def  */
#line 179 "/home/yang/playground/src/sysy/parser.y"
        {
        (yyval.defList) = new DefList();
        (yyval.defList)->list.push_back(unique_ptr<Def>((yyvsp[0].def)));
    }
#line 1755 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 13: /* DefList: DefList COMMA Def  */
#line 183 "/home/yang/playground/src/sysy/parser.y"
                      {
        (yyval.defList) = (yyvsp[-2].defList);
        (yyval.defList)->list.push_back(unique_ptr<Def>((yyvsp[0].def)));
    }
#line 1764 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 14: /* Def: ID Arrays ASSIGN InitVal  */
#line 190 "/home/yang/playground/src/sysy/parser.y"
                             {
        (yyval.def) = new Def();
        (yyval.def)->id = unique_ptr<string>((yyvsp[-3].token));
        (yyval.def)->arrays.swap((yyvsp[-2].arrays)->list);
        (yyval.def)->initVal = unique_ptr<InitVal>((yyvsp[0].initVal));
    }
#line 1775 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 15: /* Def: ID ASSIGN InitVal  */
#line 196 "/home/yang/playground/src/sysy/parser.y"
                      {
        (yyval.def) = new Def();
        (yyval.def)->id = unique_ptr<string>((yyvsp[-2].token));
        (yyval.def)->initVal = unique_ptr<InitVal>((yyvsp[0].initVal));
    }
#line 1785 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 16: /* Def: ID Arrays  */
#line 201 "/home/yang/playground/src/sysy/parser.y"
              {
        (yyval.def) = new Def();
        (yyval.def)->id = unique_ptr<string>((yyvsp[-1].token));
        (yyval.def)->arrays.swap((yyvsp[0].arrays)->list);
    }
#line 1795 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 17: /* Def: ID  */
#line 206 "/home/yang/playground/src/sysy/parser.y"
       {
        (yyval.def) = new Def();
        (yyval.def)->id = unique_ptr<string>((yyvsp[0].token));
    }
#line 1804 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 18: /* Arrays: LB Exp RB  */
#line 213 "/home/yang/playground/src/sysy/parser.y"
              {
        (yyval.arrays) = new ArrayList();
        (yyval.arrays)->list.push_back(unique_ptr<AddExp>((yyvsp[-1].addExp)));
    }
#line 1813 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 19: /* Arrays: Arrays LB Exp RB  */
#line 217 "/home/yang/playground/src/sysy/parser.y"
                     {
        (yyval.arrays) = (yyvsp[-3].arrays);
        (yyval.arrays)->list.push_back(unique_ptr<AddExp>((yyvsp[-1].addExp)));
    }
#line 1822 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 20: /* InitVal: Exp  */
#line 224 "/home/yang/playground/src/sysy/parser.y"
        {
        (yyval.initVal) = new InitVal();
        (yyval.initVal)->exp = unique_ptr<AddExp>((yyvsp[0].addExp));
    }
#line 1831 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 21: /* InitVal: LC RC  */
#line 228 "/home/yang/playground/src/sysy/parser.y"
          {
        (yyval.initVal) = new InitVal();
    }
#line 1839 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 22: /* InitVal: LC InitValList RC  */
#line 231 "/home/yang/playground/src/sysy/parser.y"
                      {
        (yyval.initVal) = new InitVal();
        (yyval.initVal)->initValList.swap((yyvsp[-1].initValList)->list);
    }
#line 1848 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 23: /* InitValList: InitValList COMMA InitVal  */
#line 238 "/home/yang/playground/src/sysy/parser.y"
                              {
        (yyval.initValList) = (yyvsp[-2].initValList);
        (yyval.initValList)->list.push_back(unique_ptr<InitVal>((yyvsp[0].initVal)));
    }
#line 1857 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 24: /* InitValList: InitVal  */
#line 242 "/home/yang/playground/src/sysy/parser.y"
            {
        (yyval.initValList) = new InitValList();
        (yyval.initValList)->list.push_back(unique_ptr<InitVal>((yyvsp[0].initVal)));
    }
#line 1866 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 25: /* FuncDef: BType ID LP FuncFParamList RP Block  */
#line 249 "/home/yang/playground/src/sysy/parser.y"
                                        {
        (yyval.funcDef) = new FuncDef();
        (yyval.funcDef)->returnType = (yyvsp[-5].ty);
        (yyval.funcDef)->id = unique_ptr<string>((yyvsp[-4].token));
        (yyval.funcDef)->funcFParamList.swap((yyvsp[-2].funcFParamList)->list);
        (yyval.funcDef)->block = unique_ptr<Block>((yyvsp[0].block));
    }
#line 1878 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 26: /* FuncDef: BType ID LP RP Block  */
#line 256 "/home/yang/playground/src/sysy/parser.y"
                         {
        (yyval.funcDef) = new FuncDef();
        (yyval.funcDef)->returnType = (yyvsp[-4].ty);
        (yyval.funcDef)->id = unique_ptr<string>((yyvsp[-3].token));
        (yyval.funcDef)->block = unique_ptr<Block>((yyvsp[0].block));
    }
#line 1889 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 27: /* FuncDef: VoidType ID LP FuncFParamList RP Block  */
#line 262 "/home/yang/playground/src/sysy/parser.y"
                                           {
        (yyval.funcDef) = new FuncDef();
        (yyval.funcDef)->returnType = (yyvsp[-5].ty);
        (yyval.funcDef)->id = unique_ptr<string>((yyvsp[-4].token));
        (yyval.funcDef)->funcFParamList.swap((yyvsp[-2].funcFParamList)->list);
        (yyval.funcDef)->block = unique_ptr<Block>((yyvsp[0].block));
    }
#line 1901 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 28: /* FuncDef: VoidType ID LP RP Block  */
#line 269 "/home/yang/playground/src/sysy/parser.y"
                            {
        (yyval.funcDef) = new FuncDef();
        (yyval.funcDef)->returnType = (yyvsp[-4].ty);
        (yyval.funcDef)->id = unique_ptr<string>((yyvsp[-3].token));
        (yyval.funcDef)->block = unique_ptr<Block>((yyvsp[0].block));
    }
#line 1912 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 29: /* FuncFParamList: FuncFParam  */
#line 278 "/home/yang/playground/src/sysy/parser.y"
               {
        (yyval.funcFParamList) = new FuncFParamList();
        (yyval.funcFParamList)->list.push_back(unique_ptr<FuncFParam>((yyvsp[0].funcFParam)));
    }
#line 1921 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 30: /* FuncFParamList: FuncFParamList COMMA FuncFParam  */
#line 282 "/home/yang/playground/src/sysy/parser.y"
                                    {
        (yyval.funcFParamList) = (yyvsp[-2].funcFParamList);
        (yyval.funcFParamList)->list.push_back(unique_ptr<FuncFParam>((yyvsp[0].funcFParam)));
    }
#line 1930 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 31: /* FuncFParam: BType ID  */
#line 289 "/home/yang/playground/src/sysy/parser.y"
             {
        (yyval.funcFParam) = new FuncFParam();
        (yyval.funcFParam)->bType = (yyvsp[-1].ty);
        (yyval.funcFParam)->id = unique_ptr<string>((yyvsp[0].token));
        (yyval.funcFParam)->isArray = false;
    }
#line 1941 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 32: /* FuncFParam: BType ID LB RB  */
#line 295 "/home/yang/playground/src/sysy/parser.y"
                   {
        (yyval.funcFParam) = new FuncFParam();
        (yyval.funcFParam)->bType = (yyvsp[-3].ty);
        (yyval.funcFParam)->id = unique_ptr<string>((yyvsp[-2].token));
        (yyval.funcFParam)->isArray = true;
    }
#line 1952 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 33: /* FuncFParam: BType ID LB RB Arrays  */
#line 301 "/home/yang/playground/src/sysy/parser.y"
                          {
        (yyval.funcFParam) = new FuncFParam();
        (yyval.funcFParam)->bType = (yyvsp[-4].ty);
        (yyval.funcFParam)->id = unique_ptr<string>((yyvsp[-3].token));
        (yyval.funcFParam)->isArray = true;
        (yyval.funcFParam)->arrays.swap((yyvsp[0].arrays)->list);
    }
#line 1964 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 34: /* Block: LC RC  */
#line 311 "/home/yang/playground/src/sysy/parser.y"
          {
        (yyval.block) = new Block();
    }
#line 1972 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 35: /* Block: LC BlockItemList RC  */
#line 314 "/home/yang/playground/src/sysy/parser.y"
                        {
        (yyval.block) = new Block();
        (yyval.block)->blockItemList.swap((yyvsp[-1].blockItemList)->list);
    }
#line 1981 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 36: /* BlockItemList: BlockItem  */
#line 321 "/home/yang/playground/src/sysy/parser.y"
              {
        (yyval.blockItemList) = new BlockItemList();
        (yyval.blockItemList)->list.push_back(unique_ptr<BlockItem>((yyvsp[0].blockItem)));
    }
#line 1990 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 37: /* BlockItemList: BlockItemList BlockItem  */
#line 325 "/home/yang/playground/src/sysy/parser.y"
                            {
        (yyval.blockItemList) = (yyvsp[-1].blockItemList);
        (yyval.blockItemList)->list.push_back(unique_ptr<BlockItem>((yyvsp[0].blockItem)));
    }
#line 1999 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 38: /* BlockItem: Decl  */
#line 332 "/home/yang/playground/src/sysy/parser.y"
         {
        (yyval.blockItem) = new BlockItem();
        (yyval.blockItem)->decl = unique_ptr<Decl>((yyvsp[0].decl));
    }
#line 2008 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 39: /* BlockItem: Stmt  */
#line 336 "/home/yang/playground/src/sysy/parser.y"
         {
        (yyval.blockItem) = new BlockItem();
        (yyval.blockItem)->stmt = unique_ptr<Stmt>((yyvsp[0].stmt));
    }
#line 2017 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 40: /* Stmt: SEMICOLON  */
#line 342 "/home/yang/playground/src/sysy/parser.y"
              {
        (yyval.stmt) = new Stmt();
        (yyval.stmt)->sType = StmtType::SEMI;
    }
#line 2026 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 41: /* Stmt: LVal ASSIGN Exp SEMICOLON  */
#line 346 "/home/yang/playground/src/sysy/parser.y"
                              {
        (yyval.stmt) = new Stmt();
        (yyval.stmt)->sType = StmtType::ASGN;
        (yyval.stmt)->lVal = unique_ptr<LVal>((yyvsp[-3].lVal));
        (yyval.stmt)->exp = unique_ptr<AddExp>((yyvsp[-1].addExp));
    }
#line 2037 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 42: /* Stmt: Exp SEMICOLON  */
#line 352 "/home/yang/playground/src/sysy/parser.y"
                  {
        (yyval.stmt) = new Stmt();
        (yyval.stmt)->sType = StmtType::EXP;
        (yyval.stmt)->exp = unique_ptr<AddExp>((yyvsp[-1].addExp));
    }
#line 2047 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 43: /* Stmt: CONTINUE SEMICOLON  */
#line 357 "/home/yang/playground/src/sysy/parser.y"
                       {
        (yyval.stmt) = new Stmt();
        (yyval.stmt)->sType = StmtType::CONTINUE;
    }
#line 2056 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 44: /* Stmt: BREAK SEMICOLON  */
#line 361 "/home/yang/playground/src/sysy/parser.y"
                    {
        (yyval.stmt) = new Stmt();
        (yyval.stmt)->sType = StmtType::BREAK;
    }
#line 2065 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 45: /* Stmt: Block  */
#line 365 "/home/yang/playground/src/sysy/parser.y"
          {
        (yyval.stmt) = new Stmt();
        (yyval.stmt)->sType = StmtType::BLK;
        (yyval.stmt)->block = unique_ptr<Block>((yyvsp[0].block));
    }
#line 2075 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 46: /* Stmt: ReturnStmt  */
#line 370 "/home/yang/playground/src/sysy/parser.y"
               {
        (yyval.stmt) = new Stmt();
        (yyval.stmt)->sType = StmtType::RET;
        (yyval.stmt)->returnStmt = unique_ptr<ReturnStmt>((yyvsp[0].returnStmt));
    }
#line 2085 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 47: /* Stmt: IfStmt  */
#line 375 "/home/yang/playground/src/sysy/parser.y"
           {
        (yyval.stmt) = new Stmt();
        (yyval.stmt)->sType = StmtType::IF;
        (yyval.stmt)->ifStmt = unique_ptr<IfStmt>((yyvsp[0].ifStmt));
    }
#line 2095 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 48: /* Stmt: IterationStmt  */
#line 380 "/home/yang/playground/src/sysy/parser.y"
                  {
        (yyval.stmt) = new Stmt();
        (yyval.stmt)->sType = StmtType::WHILE;
        (yyval.stmt)->whileStmtAST = unique_ptr<WhileStmt>((yyvsp[0].whileStmtAST));
    }
#line 2105 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 49: /* IfStmt: IF LP Cond RP Stmt  */
#line 388 "/home/yang/playground/src/sysy/parser.y"
                                             {
        (yyval.ifStmt) = new IfStmt();
        (yyval.ifStmt)->cond = unique_ptr<LOrExp>((yyvsp[-2].lOrExp));
        (yyval.ifStmt)->ifStmt = unique_ptr<Stmt>((yyvsp[0].stmt));
    }
#line 2115 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 50: /* IfStmt: IF LP Cond RP Stmt ELSE Stmt  */
#line 393 "/home/yang/playground/src/sysy/parser.y"
                                 {
        (yyval.ifStmt) = new IfStmt();
        (yyval.ifStmt)->cond = unique_ptr<LOrExp>((yyvsp[-4].lOrExp));
        (yyval.ifStmt)->ifStmt = unique_ptr<Stmt>((yyvsp[-2].stmt));
        (yyval.ifStmt)->elseStmt = unique_ptr<Stmt>((yyvsp[0].stmt));
    }
#line 2126 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 51: /* IterationStmt: WHILE LP Cond RP Stmt  */
#line 402 "/home/yang/playground/src/sysy/parser.y"
                          {
        (yyval.whileStmtAST) = new WhileStmt();
        (yyval.whileStmtAST)->cond = unique_ptr<LOrExp>((yyvsp[-2].lOrExp));
        (yyval.whileStmtAST)->stmt = unique_ptr<Stmt>((yyvsp[0].stmt));
    }
#line 2136 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 52: /* ReturnStmt: RETURN Exp SEMICOLON  */
#line 410 "/home/yang/playground/src/sysy/parser.y"
                         {
        (yyval.returnStmt) = new ReturnStmt();
        (yyval.returnStmt)->exp = unique_ptr<AddExp>((yyvsp[-1].addExp));
    }
#line 2145 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 53: /* ReturnStmt: RETURN SEMICOLON  */
#line 414 "/home/yang/playground/src/sysy/parser.y"
                     {
        (yyval.returnStmt) = new ReturnStmt();
    }
#line 2153 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 54: /* Exp: AddExp  */
#line 420 "/home/yang/playground/src/sysy/parser.y"
           {
        (yyval.addExp) = (yyvsp[0].addExp);
    }
#line 2161 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 55: /* Cond: LOrExp  */
#line 426 "/home/yang/playground/src/sysy/parser.y"
           {
        (yyval.lOrExp) = (yyvsp[0].lOrExp);
    }
#line 2169 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 56: /* LVal: ID  */
#line 432 "/home/yang/playground/src/sysy/parser.y"
       {
        (yyval.lVal) = new LVal();
        (yyval.lVal)->id = unique_ptr<string>((yyvsp[0].token));
    }
#line 2178 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 57: /* LVal: ID Arrays  */
#line 436 "/home/yang/playground/src/sysy/parser.y"
              {
        (yyval.lVal) = new LVal();
        (yyval.lVal)->id = unique_ptr<string>((yyvsp[-1].token));
        (yyval.lVal)->arrays.swap((yyvsp[0].arrays)->list);
    }
#line 2188 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 58: /* PrimaryExp: LP Exp RP  */
#line 444 "/home/yang/playground/src/sysy/parser.y"
              {
        (yyval.primaryExp) = new PrimaryExp();
        (yyval.primaryExp)->exp = unique_ptr<AddExp>((yyvsp[-1].addExp));
    }
#line 2197 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 59: /* PrimaryExp: LVal  */
#line 448 "/home/yang/playground/src/sysy/parser.y"
         {
        (yyval.primaryExp) = new PrimaryExp();
        (yyval.primaryExp)->lval = unique_ptr<LVal>((yyvsp[0].lVal));
    }
#line 2206 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 60: /* PrimaryExp: Number  */
#line 452 "/home/yang/playground/src/sysy/parser.y"
           {
        (yyval.primaryExp) = new PrimaryExp();
        (yyval.primaryExp)->number = unique_ptr<NumberNode>((yyvsp[0].number));
    }
#line 2215 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 61: /* Number: INT  */
#line 459 "/home/yang/playground/src/sysy/parser.y"
        {
        (yyval.number) = new NumberNode();
        (yyval.number)->isInt = true;
        (yyval.number)->intval = (yyvsp[0].int_val);
    }
#line 2225 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 62: /* Number: FLOAT  */
#line 464 "/home/yang/playground/src/sysy/parser.y"
          {
        (yyval.number) = new NumberNode();
        (yyval.number)->isInt = false;
        (yyval.number)->floatval = (yyvsp[0].float_val);
    }
#line 2235 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 63: /* UnaryExp: PrimaryExp  */
#line 472 "/home/yang/playground/src/sysy/parser.y"
               {
        (yyval.unaryExp) = new UnaryExp();
        (yyval.unaryExp)->primaryExp = unique_ptr<PrimaryExp>((yyvsp[0].primaryExp));
    }
#line 2244 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 64: /* UnaryExp: Call  */
#line 476 "/home/yang/playground/src/sysy/parser.y"
         {
        (yyval.unaryExp) = new UnaryExp();
        (yyval.unaryExp)->call = unique_ptr<Call>((yyvsp[0].call));
    }
#line 2253 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 65: /* UnaryExp: UnaryOp UnaryExp  */
#line 480 "/home/yang/playground/src/sysy/parser.y"
                     {
        (yyval.unaryExp) = new UnaryExp();
        (yyval.unaryExp)->op = (yyvsp[-1].op);
        (yyval.unaryExp)->unaryExp = unique_ptr<UnaryExp>((yyvsp[0].unaryExp));
    }
#line 2263 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 66: /* Call: ID LP RP  */
#line 488 "/home/yang/playground/src/sysy/parser.y"
             {
        (yyval.call) = new Call();
        (yyval.call)->id = unique_ptr<string>((yyvsp[-2].token));
    }
#line 2272 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 67: /* Call: ID LP FuncCParamList RP  */
#line 492 "/home/yang/playground/src/sysy/parser.y"
                            {
        (yyval.call) = new Call();
        (yyval.call)->id = unique_ptr<string>((yyvsp[-3].token));
        (yyval.call)->funcCParamList.swap((yyvsp[-1].funcCParamList)->list);
    }
#line 2282 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 68: /* UnaryOp: ADD  */
#line 500 "/home/yang/playground/src/sysy/parser.y"
        {
        (yyval.op) = UnaryOp::ADD;
    }
#line 2290 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 69: /* UnaryOp: MINUS  */
#line 503 "/home/yang/playground/src/sysy/parser.y"
          {
        (yyval.op) = UnaryOp::MINUS;
    }
#line 2298 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 70: /* UnaryOp: NOT  */
#line 506 "/home/yang/playground/src/sysy/parser.y"
        {
        (yyval.op) = UnaryOp::NOT;
    }
#line 2306 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 71: /* FuncCParamList: Exp  */
#line 512 "/home/yang/playground/src/sysy/parser.y"
        {
        (yyval.funcCParamList) = new FuncCParamList();
        (yyval.funcCParamList)->list.push_back(unique_ptr<AddExp>((yyvsp[0].addExp)));
    }
#line 2315 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 72: /* FuncCParamList: FuncCParamList COMMA Exp  */
#line 516 "/home/yang/playground/src/sysy/parser.y"
                             {
        (yyval.funcCParamList) = (FuncCParamList*) (yyvsp[-2].funcCParamList);
        (yyval.funcCParamList)->list.push_back(unique_ptr<AddExp>((yyvsp[0].addExp)));
    }
#line 2324 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 73: /* MulExp: UnaryExp  */
#line 523 "/home/yang/playground/src/sysy/parser.y"
             {
        (yyval.mulExp) = new MulExp();
        (yyval.mulExp)->unaryExp = unique_ptr<UnaryExp>((yyvsp[0].unaryExp));
    }
#line 2333 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 74: /* MulExp: MulExp MUL UnaryExp  */
#line 527 "/home/yang/playground/src/sysy/parser.y"
                        {
        (yyval.mulExp) = new MulExp();
        (yyval.mulExp)->mulExp = unique_ptr<MulExp>((yyvsp[-2].mulExp));
        (yyval.mulExp)->op = MulOp::MUL;
        (yyval.mulExp)->unaryExp = unique_ptr<UnaryExp>((yyvsp[0].unaryExp));
    }
#line 2344 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 75: /* MulExp: MulExp DIV UnaryExp  */
#line 533 "/home/yang/playground/src/sysy/parser.y"
                        {
        (yyval.mulExp) = new MulExp();
        (yyval.mulExp)->mulExp = unique_ptr<MulExp>((yyvsp[-2].mulExp));
        (yyval.mulExp)->op = MulOp::DIV;
        (yyval.mulExp)->unaryExp = unique_ptr<UnaryExp>((yyvsp[0].unaryExp));
    }
#line 2355 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 76: /* MulExp: MulExp MOD UnaryExp  */
#line 539 "/home/yang/playground/src/sysy/parser.y"
                        {
        (yyval.mulExp) = new MulExp();
        (yyval.mulExp)->mulExp = unique_ptr<MulExp>((yyvsp[-2].mulExp));
        (yyval.mulExp)->op = MulOp::MOD;
        (yyval.mulExp)->unaryExp = unique_ptr<UnaryExp>((yyvsp[0].unaryExp));
    }
#line 2366 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 77: /* AddExp: MulExp  */
#line 548 "/home/yang/playground/src/sysy/parser.y"
           {
        (yyval.addExp) = new AddExp();
        (yyval.addExp)->mulExp = unique_ptr<MulExp>((yyvsp[0].mulExp));
    }
#line 2375 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 78: /* AddExp: AddExp ADD MulExp  */
#line 552 "/home/yang/playground/src/sysy/parser.y"
                      {
        (yyval.addExp) = new AddExp();
        (yyval.addExp)->addExp = unique_ptr<AddExp>((yyvsp[-2].addExp));
        (yyval.addExp)->op = AddOp::ADD;
        (yyval.addExp)->mulExp = unique_ptr<MulExp>((yyvsp[0].mulExp));
    }
#line 2386 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 79: /* AddExp: AddExp MINUS MulExp  */
#line 558 "/home/yang/playground/src/sysy/parser.y"
                        {
        (yyval.addExp) = new AddExp();
        (yyval.addExp)->addExp = unique_ptr<AddExp>((yyvsp[-2].addExp));
        (yyval.addExp)->op = AddOp::MINUS;
        (yyval.addExp)->mulExp = unique_ptr<MulExp>((yyvsp[0].mulExp));
    }
#line 2397 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 80: /* RelExp: AddExp  */
#line 567 "/home/yang/playground/src/sysy/parser.y"
           {
        (yyval.relExp) = new RelExp();
        (yyval.relExp)->addExp = unique_ptr<AddExp>((yyvsp[0].addExp));
    }
#line 2406 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 81: /* RelExp: RelExp GTE AddExp  */
#line 571 "/home/yang/playground/src/sysy/parser.y"
                      {
        (yyval.relExp) = new RelExp();
        (yyval.relExp)->relExp = unique_ptr<RelExp>((yyvsp[-2].relExp));
        (yyval.relExp)->op = RelOp::GTE;
        (yyval.relExp)->addExp = unique_ptr<AddExp>((yyvsp[0].addExp));
    }
#line 2417 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 82: /* RelExp: RelExp LTE AddExp  */
#line 577 "/home/yang/playground/src/sysy/parser.y"
                      {
        (yyval.relExp) = new RelExp();
        (yyval.relExp)->relExp = unique_ptr<RelExp>((yyvsp[-2].relExp));
        (yyval.relExp)->op = RelOp::LTE;
        (yyval.relExp)->addExp = unique_ptr<AddExp>((yyvsp[0].addExp));
    }
#line 2428 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 83: /* RelExp: RelExp GT AddExp  */
#line 583 "/home/yang/playground/src/sysy/parser.y"
                     {
        (yyval.relExp) = new RelExp();
        (yyval.relExp)->relExp = unique_ptr<RelExp>((yyvsp[-2].relExp));
        (yyval.relExp)->op = RelOp::GT;
        (yyval.relExp)->addExp = unique_ptr<AddExp>((yyvsp[0].addExp));
    }
#line 2439 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 84: /* RelExp: RelExp LT AddExp  */
#line 589 "/home/yang/playground/src/sysy/parser.y"
                     {
        (yyval.relExp) = new RelExp();
        (yyval.relExp)->relExp = unique_ptr<RelExp>((yyvsp[-2].relExp));
        (yyval.relExp)->op = RelOp::LT;
        (yyval.relExp)->addExp = unique_ptr<AddExp>((yyvsp[0].addExp));
    }
#line 2450 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 85: /* EqExp: RelExp  */
#line 598 "/home/yang/playground/src/sysy/parser.y"
           {
        (yyval.eqExp) = new EqExp();
        (yyval.eqExp)->relExp = unique_ptr<RelExp>((yyvsp[0].relExp));
    }
#line 2459 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 86: /* EqExp: EqExp EQ RelExp  */
#line 602 "/home/yang/playground/src/sysy/parser.y"
                    {
        (yyval.eqExp) = new EqExp();
        (yyval.eqExp)->eqExp = unique_ptr<EqExp>((yyvsp[-2].eqExp));
        (yyval.eqExp)->op = EqOp::EQ;
        (yyval.eqExp)->relExp = unique_ptr<RelExp>((yyvsp[0].relExp));
    }
#line 2470 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 87: /* EqExp: EqExp NEQ RelExp  */
#line 608 "/home/yang/playground/src/sysy/parser.y"
                     {
        (yyval.eqExp) = new EqExp();
        (yyval.eqExp)->eqExp = unique_ptr<EqExp>((yyvsp[-2].eqExp));
        (yyval.eqExp)->op = EqOp::NEQ;
        (yyval.eqExp)->relExp = unique_ptr<RelExp>((yyvsp[0].relExp));
    }
#line 2481 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 88: /* LAndExp: EqExp  */
#line 617 "/home/yang/playground/src/sysy/parser.y"
          {
        (yyval.lAndExp) = new LAndExp();
        (yyval.lAndExp)->eqExp = unique_ptr<EqExp>((yyvsp[0].eqExp));
    }
#line 2490 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 89: /* LAndExp: LAndExp AND EqExp  */
#line 621 "/home/yang/playground/src/sysy/parser.y"
                      {
        (yyval.lAndExp) = new LAndExp();
        (yyval.lAndExp)->lAndExp = unique_ptr<LAndExp>((yyvsp[-2].lAndExp));
        (yyval.lAndExp)->eqExp = unique_ptr<EqExp>((yyvsp[0].eqExp));
    }
#line 2500 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 90: /* LOrExp: LAndExp  */
#line 629 "/home/yang/playground/src/sysy/parser.y"
            {
        (yyval.lOrExp) = new LOrExp();
        (yyval.lOrExp)->lAndExp = unique_ptr<LAndExp>((yyvsp[0].lAndExp));
    }
#line 2509 "/home/yang/playground/generated/parser.tab.cpp"
    break;

  case 91: /* LOrExp: LOrExp OR LAndExp  */
#line 633 "/home/yang/playground/src/sysy/parser.y"
                      {
        (yyval.lOrExp) = new LOrExp();
        (yyval.lOrExp)->lOrExp = unique_ptr<LOrExp>((yyvsp[-2].lOrExp));
        (yyval.lOrExp)->lAndExp = unique_ptr<LAndExp>((yyvsp[0].lAndExp));
    }
#line 2519 "/home/yang/playground/generated/parser.tab.cpp"
    break;


#line 2523 "/home/yang/playground/generated/parser.tab.cpp"

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

#line 638 "/home/yang/playground/src/sysy/parser.y"


void initFileName(char *name) {
    strcpy(filename, name);
}

void yyerror(const char* fmt) {
    printf("%s:%d ", filename, yylloc.first_line);
    printf("%s\n", fmt);
}
