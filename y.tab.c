
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <string.h>
    #include "utility.h"

    nodeType *opr(int oper, int nops, ...);
    nodeType *id(char *name, varType type, int intVal, double floatVal, char charVal, int init);
    nodeType *con(int intVal, char charVal, double floatVal, varType type);

    void initSymTable();
    void extendSymTable();
    void destroySymTable();
    void addConToSymTable(int intVal, char charVal, double floatVal, varType type, int lineNo);
    int addIdToSymTable(char *name, varType type, int lineNo, int intVal, double floatVal, char charVal);
    void addOprToSymTable(char *name, int lineNo);
    void printSymTable();
    void checkUnusedVariables();
    int searchForId(char *name);
    void freeNode(nodeType *p);
    int ex(nodeType *p, idNodeType switchVar, int switchLbl);
    int yylex(void);
    void yyerror(char *s);
    int symTableSize;
    int symTableIndex;
    symTableEntry *sym;


/* Line 189 of yacc.c  */
#line 103 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     CHARACTER = 259,
     FLOAT_NUM = 260,
     VARIABLE = 261,
     DO = 262,
     WHILE = 263,
     FOR = 264,
     IF = 265,
     SWITCH = 266,
     CASE = 267,
     DEFAULT = 268,
     BREAK = 269,
     PRINT = 270,
     FUNCTION = 271,
     CONST_INT_TYPE = 272,
     INT_TYPE = 273,
     CONST_FLOAT_TYPE = 274,
     FLOAT_TYPE = 275,
     CONST_CHAR_TYPE = 276,
     CHAR_TYPE = 277,
     IFX = 278,
     ELSE = 279,
     NE = 280,
     EQ = 281,
     LE = 282,
     GE = 283,
     UMINUS = 284
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define CHARACTER 259
#define FLOAT_NUM 260
#define VARIABLE 261
#define DO 262
#define WHILE 263
#define FOR 264
#define IF 265
#define SWITCH 266
#define CASE 267
#define DEFAULT 268
#define BREAK 269
#define PRINT 270
#define FUNCTION 271
#define CONST_INT_TYPE 272
#define INT_TYPE 273
#define CONST_FLOAT_TYPE 274
#define FLOAT_TYPE 275
#define CONST_CHAR_TYPE 276
#define CHAR_TYPE 277
#define IFX 278
#define ELSE 279
#define NE 280
#define EQ 281
#define LE 282
#define GE 283
#define UMINUS 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 30 "parser.y"

  int iValue;
  char cValue;
  double fValue;
  char *sIndex;
  nodeType *nPtr;



/* Line 214 of yacc.c  */
#line 207 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 219 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   287

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,    39,    33,    31,     2,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,    36,
      26,    37,    25,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      27,    28,    29,    30,    35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    11,    14,    15,    20,
      26,    30,    36,    40,    46,    50,    51,    57,    58,    67,
      68,    75,    76,    86,    92,   100,   101,   110,   111,   116,
     120,   122,   125,   127,   130,   131,   132,   141,   142,   143,
     151,   153,   155,   157,   159,   163,   164,   168,   169,   174,
     175,   180,   181,   186,   187,   192,   193,   198,   199,   204,
     205,   210,   211,   216,   217,   222,   223,   228
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    45,    -1,    45,    46,    -1,    -1,    36,
      -1,    61,    36,    -1,    -1,    15,    47,    61,    36,    -1,
      17,     6,    37,     3,    36,    -1,    18,     6,    36,    -1,
      19,     6,    37,     5,    36,    -1,    20,     6,    36,    -1,
      21,     6,    37,     4,    36,    -1,    22,     6,    36,    -1,
      -1,     6,    37,    48,    61,    36,    -1,    -1,     7,    49,
      46,     8,    38,    61,    39,    36,    -1,    -1,     8,    50,
      38,    61,    39,    46,    -1,    -1,     9,    51,    38,    46,
      61,    36,    46,    39,    46,    -1,    10,    38,    61,    39,
      46,    -1,    10,    38,    61,    39,    46,    24,    46,    -1,
      -1,    11,    52,    38,     6,    39,    40,    55,    41,    -1,
      -1,    16,     6,    53,    46,    -1,    40,    54,    41,    -1,
      46,    -1,    54,    46,    -1,    56,    -1,    55,    56,    -1,
      -1,    -1,    12,    57,    61,    42,    46,    14,    58,    36,
      -1,    -1,    -1,    13,    59,    42,    46,    14,    60,    36,
      -1,     3,    -1,     4,    -1,     5,    -1,     6,    -1,     6,
      38,    39,    -1,    -1,    32,    62,    61,    -1,    -1,    61,
      31,    63,    61,    -1,    -1,    61,    32,    64,    61,    -1,
      -1,    61,    33,    65,    61,    -1,    -1,    61,    34,    66,
      61,    -1,    -1,    61,    26,    67,    61,    -1,    -1,    61,
      25,    68,    61,    -1,    -1,    61,    30,    69,    61,    -1,
      -1,    61,    29,    70,    61,    -1,    -1,    61,    27,    71,
      61,    -1,    -1,    61,    28,    72,    61,    -1,    38,    61,
      39,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    56,    56,    60,    61,    65,    66,    67,    67,    68,
      69,    70,    71,    72,    73,    74,    74,    75,    75,    76,
      76,    77,    77,    78,    79,    80,    80,    81,    81,    82,
      86,    87,    91,    92,    96,    96,    96,    97,    97,    97,
     101,   102,   103,   104,   105,   106,   106,   107,   107,   108,
     108,   109,   109,   110,   110,   111,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   116,   117
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "CHARACTER", "FLOAT_NUM",
  "VARIABLE", "DO", "WHILE", "FOR", "IF", "SWITCH", "CASE", "DEFAULT",
  "BREAK", "PRINT", "FUNCTION", "CONST_INT_TYPE", "INT_TYPE",
  "CONST_FLOAT_TYPE", "FLOAT_TYPE", "CONST_CHAR_TYPE", "CHAR_TYPE", "IFX",
  "ELSE", "'>'", "'<'", "NE", "EQ", "LE", "GE", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "';'", "'='", "'('", "')'", "'{'", "'}'", "':'", "$accept",
  "program", "function", "stmt", "$@1", "$@2", "$@3", "$@4", "$@5", "$@6",
  "$@7", "stmt_list", "switch_body", "case_stmt", "$@8", "$@9", "$@10",
  "$@11", "expr", "$@12", "$@13", "$@14", "$@15", "$@16", "$@17", "$@18",
  "$@19", "$@20", "$@21", "$@22", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    62,    60,   280,   281,   282,
     283,    43,    45,    42,    47,   284,    59,    61,    40,    41,
     123,   125,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    47,    46,    46,
      46,    46,    46,    46,    46,    48,    46,    49,    46,    50,
      46,    51,    46,    46,    46,    52,    46,    53,    46,    46,
      54,    54,    55,    55,    57,    58,    56,    59,    60,    56,
      61,    61,    61,    61,    61,    62,    61,    63,    61,    64,
      61,    65,    61,    66,    61,    67,    61,    68,    61,    69,
      61,    70,    61,    71,    61,    72,    61,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     2,     0,     4,     5,
       3,     5,     3,     5,     3,     0,     5,     0,     8,     0,
       6,     0,     9,     5,     7,     0,     8,     0,     4,     3,
       1,     2,     1,     2,     0,     0,     8,     0,     0,     7,
       1,     1,     1,     1,     3,     0,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    40,    41,    42,    43,    17,    19,
      21,     0,    25,     7,     0,     0,     0,     0,     0,     0,
       0,    45,     5,     0,     0,     3,     0,    15,     0,     0,
       0,     0,     0,     0,     0,    27,     0,     0,     0,     0,
       0,     0,     0,    43,     0,    30,     0,    57,    55,    63,
      65,    61,    59,    47,    49,    51,    53,     6,     0,    44,
       0,     0,     0,     0,     0,     0,     0,     0,    10,     0,
      12,     0,    14,    46,    67,    29,    31,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,    28,     0,     0,     0,    58,    56,
      64,    66,    62,    60,    48,    50,    52,    54,    16,     0,
       0,     0,    23,     0,     9,    11,    13,     0,    20,     0,
       0,     0,     0,     0,    24,    34,    37,     0,    32,    18,
       0,     0,     0,    26,    33,    22,     0,     0,     0,     0,
       0,    38,    35,     0,     0,    39,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    25,    34,    58,    29,    30,    31,    33,
      66,    46,   127,   128,   131,   144,   132,   143,    26,    42,
      83,    84,    85,    86,    78,    77,    82,    81,    79,    80
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -28
static const yytype_int16 yypact[] =
{
     -28,     4,   151,   -28,   -28,   -28,   -28,   -20,   -28,   -28,
     -28,   -27,   -28,   -28,    13,    15,    17,    22,    23,    24,
      26,   -28,   -28,     3,   151,   -28,    18,   -28,    -6,   151,
      -4,    -1,     3,     2,     3,   -28,    16,    29,    32,    30,
      33,    45,     3,    44,   167,   -28,   112,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,     3,   -28,
      75,     3,   151,   182,    78,   227,   151,    82,   -28,    84,
     -28,    86,   -28,   -28,   -28,   -28,   -28,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,   239,    53,   197,
       3,   151,    54,   -28,   -28,    56,    58,    61,   -18,   -18,
     -18,   -18,   -18,   -18,    -9,    -9,   -28,   -28,   -28,     3,
     151,   251,    74,    59,   -28,   -28,   -28,   212,   -28,   151,
     151,    14,    64,    62,   -28,   -28,   -28,   -10,   -28,   -28,
     151,     3,    60,   -28,   -28,   -28,    46,   151,   151,    89,
      90,   -28,   -28,    69,    71,   -28,   -28
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -28,   -28,   -28,   -24,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -19,   -28,   -28,   -28,   -28,   -22,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      45,    44,   125,   126,     3,    60,     4,     5,     6,    43,
      63,    32,    65,    53,    54,    55,    56,    27,    28,    35,
      73,    36,    76,    37,    55,    56,   125,   126,    38,    39,
      40,   133,    41,    59,    61,    21,    87,    62,    90,    89,
      64,    23,    94,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    67,    57,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,    68,    70,   112,   111,    69,
      71,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    72,    28,    88,    92,    95,   118,   117,   138,    96,
      97,   109,   114,   113,   115,   123,   124,   116,   120,   121,
     129,   130,   137,   141,   142,   145,   135,   146,   134,   136,
       0,     0,     0,   139,   140,     4,     5,     6,     7,     8,
       9,    10,    11,    12,     0,     0,     0,    13,    14,    15,
      16,    17,    18,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,     0,    22,     0,
      23,     0,    24,    75,     4,     5,     6,     7,     8,     9,
      10,    11,    12,     0,     0,     0,    13,    14,    15,    16,
      17,    18,    19,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,    22,     0,    23,
       0,    24,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,     0,     0,     0,     0,    74,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,     0,     0,     0,
       0,    91,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,     0,     0,     0,     0,   110,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,     0,     0,     0,
       0,   122,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,     0,    93,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,     0,   108,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,     0,   119
};

static const yytype_int16 yycheck[] =
{
      24,    23,    12,    13,     0,    29,     3,     4,     5,     6,
      32,    38,    34,    31,    32,    33,    34,    37,    38,     6,
      42,     6,    46,     6,    33,    34,    12,    13,     6,     6,
       6,    41,     6,    39,    38,    32,    58,    38,    62,    61,
      38,    38,    66,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    37,    36,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    36,    36,    91,    90,    37,
      37,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    36,    38,     8,     6,     3,   110,   109,    42,     5,
       4,    38,    36,    39,    36,   119,   120,    36,    24,    40,
      36,    39,    42,    14,    14,    36,   130,    36,   127,   131,
      -1,    -1,    -1,   137,   138,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    -1,
      38,    -1,    40,    41,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    -1,    38,
      -1,    40,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    -1,    36,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    36,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,    45,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    15,    16,    17,    18,    19,    20,    21,
      22,    32,    36,    38,    40,    46,    61,    37,    38,    49,
      50,    51,    38,    52,    47,     6,     6,     6,     6,     6,
       6,     6,    62,     6,    61,    46,    54,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    36,    48,    39,
      46,    38,    38,    61,    38,    61,    53,    37,    36,    37,
      36,    37,    36,    61,    39,    41,    46,    68,    67,    71,
      72,    70,    69,    63,    64,    65,    66,    61,     8,    61,
      46,    39,     6,    36,    46,     3,     5,     4,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    36,    38,
      39,    61,    46,    39,    36,    36,    36,    61,    46,    36,
      24,    40,    39,    46,    46,    12,    13,    55,    56,    36,
      39,    57,    59,    41,    56,    46,    61,    42,    42,    46,
      46,    14,    14,    60,    58,    36,    36
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:

/* Line 1455 of yacc.c  */
#line 60 "parser.y"
    { ex((yyvsp[(2) - (2)].nPtr), dummyVal, 0); freeNode((yyvsp[(2) - (2)].nPtr)); }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 65 "parser.y"
    { (yyval.nPtr) = opr(';', 2, NULL, NULL); }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 66 "parser.y"
    { (yyval.nPtr) = (yyvsp[(1) - (2)].nPtr); }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 67 "parser.y"
    { addOprToSymTable("print", yylineno); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 67 "parser.y"
    { (yyval.nPtr) = opr(PRINT, 1, (yyvsp[(3) - (4)].nPtr)); }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 68 "parser.y"
    { (yyval.nPtr) = id((yyvsp[(2) - (5)].sIndex), CONST_INT, (yyvsp[(4) - (5)].iValue), 0.5, '0', 1); }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 69 "parser.y"
    { (yyval.nPtr) = id((yyvsp[(2) - (3)].sIndex), INT, 0, 0.5, '0', 0); }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 70 "parser.y"
    { (yyval.nPtr) = id((yyvsp[(2) - (5)].sIndex), CONST_FLOAT, 0, (yyvsp[(4) - (5)].fValue), '0', 1); }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 71 "parser.y"
    { (yyval.nPtr) = id((yyvsp[(2) - (3)].sIndex), FLOAT, 0, 0.5, '0', 0); }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 72 "parser.y"
    { (yyval.nPtr) = id((yyvsp[(2) - (5)].sIndex), CONST_CHAR, 0, 0.5, (yyvsp[(4) - (5)].cValue), 1); }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 73 "parser.y"
    { (yyval.nPtr) = id((yyvsp[(2) - (3)].sIndex), CHARAC, 0, 0.5, '0', 0); }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 74 "parser.y"
    { addOprToSymTable("assign", yylineno); }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 74 "parser.y"
    { (yyval.nPtr) = opr('=', 2, id((yyvsp[(1) - (5)].sIndex), PK, 0, 0.5, '0', 1), (yyvsp[(4) - (5)].nPtr)); }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 75 "parser.y"
    { addOprToSymTable("do while", yylineno); }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 75 "parser.y"
    { (yyval.nPtr) = opr(DO, 2, (yyvsp[(3) - (8)].nPtr), (yyvsp[(6) - (8)].nPtr)); }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 76 "parser.y"
    { addOprToSymTable("while", yylineno); }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 76 "parser.y"
    { (yyval.nPtr) = opr(WHILE, 2, (yyvsp[(4) - (6)].nPtr), (yyvsp[(6) - (6)].nPtr)); }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 77 "parser.y"
    { addOprToSymTable("for", yylineno); }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 77 "parser.y"
    { (yyval.nPtr) = opr(FOR, 4, (yyvsp[(4) - (9)].nPtr), (yyvsp[(5) - (9)].nPtr), (yyvsp[(7) - (9)].nPtr), (yyvsp[(9) - (9)].nPtr)); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 78 "parser.y"
    { (yyval.nPtr) = opr(IF, 2, (yyvsp[(3) - (5)].nPtr), (yyvsp[(5) - (5)].nPtr)); addOprToSymTable("if", yylineno); }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 79 "parser.y"
    { (yyval.nPtr) = opr(IF, 3, (yyvsp[(3) - (7)].nPtr), (yyvsp[(5) - (7)].nPtr), (yyvsp[(7) - (7)].nPtr)); addOprToSymTable("if else", yylineno); }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 80 "parser.y"
    { addOprToSymTable("switch", yylineno); }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 80 "parser.y"
    { (yyval.nPtr) = opr(SWITCH, 2, id((yyvsp[(4) - (8)].sIndex), PK, 0, 0.5, '0', 0), (yyvsp[(7) - (8)].nPtr)); }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 81 "parser.y"
    { addIdToSymTable(yytext, FUNC, yylineno, 0, 0.5, '0'); }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 81 "parser.y"
    { (yyval.nPtr) = opr(FUNCTION, 2, id((yyvsp[(2) - (4)].sIndex), FUNC, 0, 0.5, '0', 1), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 82 "parser.y"
    { (yyval.nPtr) = (yyvsp[(2) - (3)].nPtr); }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 86 "parser.y"
    { (yyval.nPtr) = (yyvsp[(1) - (1)].nPtr); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 87 "parser.y"
    { (yyval.nPtr) = opr(';', 2, (yyvsp[(1) - (2)].nPtr), (yyvsp[(2) - (2)].nPtr)); }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 91 "parser.y"
    { (yyval.nPtr) = (yyvsp[(1) - (1)].nPtr); }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 92 "parser.y"
    { (yyval.nPtr) = opr(';', 2, (yyvsp[(1) - (2)].nPtr), (yyvsp[(2) - (2)].nPtr)); }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    { addOprToSymTable("case", yylineno); }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    { addOprToSymTable("break", yylineno); }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 96 "parser.y"
    { (yyval.nPtr) = opr(CASE, 2, (yyvsp[(3) - (8)].nPtr), (yyvsp[(5) - (8)].nPtr)); }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    { addOprToSymTable("default", yylineno); }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    { addOprToSymTable("break", yylineno); }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    { (yyval.nPtr) = opr(DEFAULT, 1, (yyvsp[(4) - (7)].nPtr)); }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 101 "parser.y"
    { (yyval.nPtr) = con((yyvsp[(1) - (1)].iValue), '0', 0.5, INT); }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 102 "parser.y"
    { (yyval.nPtr) = con(0, (yyvsp[(1) - (1)].cValue), 0.5, CHARAC); }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 103 "parser.y"
    { (yyval.nPtr) = con(0, '0', (yyvsp[(1) - (1)].fValue), FLOAT); }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 104 "parser.y"
    { (yyval.nPtr) = id((yyvsp[(1) - (1)].sIndex), PK, 0, 0.5, '0', 0); }
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 105 "parser.y"
    { (yyval.nPtr) = opr('f', 1, id((yyvsp[(1) - (3)].sIndex), PK, 0, 0.5, '0', 0)); }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    { addOprToSymTable("negative", yylineno); }
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 106 "parser.y"
    { (yyval.nPtr) = opr(UMINUS, 1, (yyvsp[(3) - (3)].nPtr)); }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 107 "parser.y"
    { addOprToSymTable("add", yylineno); }
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 107 "parser.y"
    { (yyval.nPtr) = opr('+', 2, (yyvsp[(1) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 108 "parser.y"
    { addOprToSymTable("sub", yylineno); }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 108 "parser.y"
    { (yyval.nPtr) = opr('-', 2, (yyvsp[(1) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 109 "parser.y"
    { addOprToSymTable("mul", yylineno); }
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 109 "parser.y"
    { (yyval.nPtr) = opr('*', 2, (yyvsp[(1) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    { addOprToSymTable("div", yylineno); }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    { (yyval.nPtr) = opr('/', 2, (yyvsp[(1) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 111 "parser.y"
    { addOprToSymTable("<", yylineno); }
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 111 "parser.y"
    { (yyval.nPtr) = opr('<', 2, (yyvsp[(1) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 112 "parser.y"
    { addOprToSymTable(">", yylineno); }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 112 "parser.y"
    { (yyval.nPtr) = opr('>', 2, (yyvsp[(1) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    { addOprToSymTable(">=", yylineno); }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 113 "parser.y"
    { (yyval.nPtr) = opr(GE, 2, (yyvsp[(1) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 114 "parser.y"
    { addOprToSymTable("<=", yylineno); }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 114 "parser.y"
    { (yyval.nPtr) = opr(LE, 2, (yyvsp[(1) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    { addOprToSymTable("!=", yylineno); }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    { (yyval.nPtr) = opr(NE, 2, (yyvsp[(1) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    { addOprToSymTable("==", yylineno); }
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    { (yyval.nPtr) = opr(EQ, 2, (yyvsp[(1) - (4)].nPtr), (yyvsp[(4) - (4)].nPtr)); }
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 117 "parser.y"
    { (yyval.nPtr) = (yyvsp[(2) - (3)].nPtr); }
    break;



/* Line 1455 of yacc.c  */
#line 2008 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 120 "parser.y"


#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p)

nodeType *con(int intVal, char charVal, double floatVal, varType type) {
  nodeType *p;
  size_t nodeSize;

  nodeSize = SIZEOF_NODETYPE + sizeof(conNodeType);

  if ((p = malloc(nodeSize)) == NULL)
    yyerror("Out of memory!");

  p->type = typeCon;
  p->con.type = type;

  if (type == INT) {
    p->con.intVal = intVal;
  } else if (type == CHARAC) {
    p->con.charVal = charVal;
  } else if (type == FLOAT) {
    p->con.floatVal = floatVal;
  }

  addConToSymTable(intVal, charVal, floatVal, type, yylineno);

  return p;
}

nodeType *id(char *name, varType type, int intVal, double floatVal, char charVal, int init) {
  nodeType *p;
  size_t nodeSize;
  int locInSym;

  nodeSize = SIZEOF_NODETYPE + sizeof(idNodeType);

  if ((p = malloc(nodeSize)) == NULL)
    yyerror("Out of memory!");

  p->type = typeId;
  p->id.name = strdup(name);
  p->id.type = type;

  if (type == CONST_INT) {
    p->id.intVal = intVal;
  } else if (type == CONST_FLOAT) {
    p->id.floatVal = floatVal;
  } else if (type == CONST_CHAR) {
    p->id.charVal = charVal;
  }

  locInSym = searchForId(name);

  if (type == PK && init != 1) {
    p->id.used = 1;
  } else {
    p->id.used = 0;
    p->id.init = 0;
  }

  if (locInSym != -1 && type == PK && init != 1) {
    sym[locInSym].id.used = 1;
  }

  if (type == PK && locInSym == -1) {
    fprintf(errPtr, ",\n  { \"line\": %d, \"description\": \"Variable %s not defined before\" }", yylineno, name);
  }

  if (type != PK && locInSym != -1 && type != FUNC) {
    fprintf(errPtr, ",\n  { \"line\": %d, \"description\": \"Variable %s already declared before on line %d\" }", yylineno, sym[locInSym].id.name, sym[locInSym].lineNo);
  }

  if (locInSym != -1 && type == PK) {
    if (sym[locInSym].id.init == 0 && init != 1) {
      fprintf(errPtr, ",\n  { \"line\": %d, \"description\": \"Variable %s declared on line %d used before being initialized\" }", yylineno, sym[locInSym].id.name, sym[locInSym].lineNo);
    }
  }

  if (locInSym == -1 && type != PK) {
    locInSym = addIdToSymTable(name, type, yylineno, intVal, floatVal, charVal);
  }

  if (init == 1) {
    sym[locInSym].id.init = 1;
  }

  p->id.type = sym[locInSym].id.type;
  p->id.init = sym[locInSym].id.init;

  if (p->id.type == CONST_INT) {
    p->id.intVal = sym[locInSym].id.intVal;
  } else if (p->id.type == CONST_FLOAT) {
    p->id.floatVal = sym[locInSym].id.floatVal;
  } else if (p->id.type == CONST_CHAR) {
    p->id.charVal = sym[locInSym].id.charVal;
  }

  return p;
}

nodeType *opr(int oper, int nops, ...) {
  va_list ap;
  nodeType *p;
  size_t nodeSize;
  int i;

  nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) + ((nops - 1) * sizeof(nodeType*));

  if ((p = malloc(nodeSize)) == NULL)
    yyerror("Out of memory!");

  p->type = typeOpr;
  p->opr.oper = oper;
  p->opr.nops = nops;

  va_start(ap, nops);
  for (i = 0; i < nops; i++)
    p->opr.op[i] = va_arg(ap, nodeType*);
  va_end(ap);

  return p;
}

void freeNode(nodeType *p) {
  int i;

  if (!p) return;

  if (p->type == typeOpr) {
    for (i = 0; i < p->opr.nops; i++)
      freeNode(p->opr.op[i]);
  }

  free(p);
}

void yyerror(char *s) {
  if (strcmp(s, "syntax error") == 0) {
    fprintf(errPtr, ",\n  { \"line\": %d, \"description\": \"Unexpected input or missing semicolon around line %d\" }", yylineno, yylineno);
  } else {
    fprintf(errPtr, ",\n  { \"line\": %d, \"description\": \"%s\" }", yylineno, s);
  }
}

int main(void) {
  fptr = fopen("./program.out", "w");
  errPtr = fopen("./error.json", "w");
  symPtr = fopen("./symbolTable.json", "w");

  if (fptr == NULL || symPtr == NULL || errPtr == NULL) {
    printf("Couldn't open file!");
    exit(1);
  }

  fprintf(errPtr, "[\n  { \"line\": 0, \"description\": \"whatever\" }");

  initSymTable();

  yyparse();

  checkUnusedVariables();

  printSymTable();
  destroySymTable();

  fprintf(errPtr, "\n]\n");

  fclose(symPtr);
  fclose(errPtr);
  fclose(fptr);

  return 0;
}

