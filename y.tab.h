
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 30 "parser.y"

  int iValue;
  char cValue;
  double fValue;
  char *sIndex;
  nodeType *nPtr;



/* Line 1676 of yacc.c  */
#line 120 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


