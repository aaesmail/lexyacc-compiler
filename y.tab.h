
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
     PRINTFF = 258,
     SCANFF = 259,
     CONST = 260,
     INT = 261,
     FLOAT = 262,
     CHAR = 263,
     VOID = 264,
     RETURN = 265,
     FOR = 266,
     IF = 267,
     ELSE = 268,
     INCLUDE = 269,
     TRUE = 270,
     FALSE = 271,
     NUMBER = 272,
     FLOAT_NUM = 273,
     ID = 274,
     UNARY = 275,
     LE = 276,
     GE = 277,
     EQ = 278,
     NE = 279,
     GT = 280,
     LT = 281,
     AND = 282,
     OR = 283,
     ADD = 284,
     SUB = 285,
     DIV = 286,
     MULT = 287,
     STR = 288,
     CHARACTER = 289
   };
#endif
/* Tokens.  */
#define PRINTFF 258
#define SCANFF 259
#define CONST 260
#define INT 261
#define FLOAT 262
#define CHAR 263
#define VOID 264
#define RETURN 265
#define FOR 266
#define IF 267
#define ELSE 268
#define INCLUDE 269
#define TRUE 270
#define FALSE 271
#define NUMBER 272
#define FLOAT_NUM 273
#define ID 274
#define UNARY 275
#define LE 276
#define GE 277
#define EQ 278
#define NE 279
#define GT 280
#define LT 281
#define AND 282
#define OR 283
#define ADD 284
#define SUB 285
#define DIV 286
#define MULT 287
#define STR 288
#define CHARACTER 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


