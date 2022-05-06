%{
      #include <stdio.h>
      #include <string.h>
      #include <stdlib.h>
      #include <ctype.h>

      void yyerror(const char *s);
      int yylex();
      int yywrap();
%}

%token CONST INT FLOAT CHAR
%token NUMBER FLOAT_NUM CHARACTER ID
%token FOR WHILE DO
%token IF ELSE SWITCH CASE BREAK DEFAULT
%token UNARY ASSIGNMENT COLON SEMI
%token OPENING_BRACKET CLOSING_BRACKET OPENING_BRACES CLOSING_BRACES
%token LE GE EQ NE GT LT AND OR NOT
%token ADD SUB MULT DIV

%left ADD SUB
%left MULT DIV

%start program

%%

program
          : statement
          | program statement
          ;

statement
          : assignments SEMI
          | expression SEMI
          | ifStatement
          | switchStatement
          | forLoop
          | whileLoop
          | doWhileLoop
          ;

assignments
          : type ID
          | type ID ASSIGNMENT expression
          | CONST type ID ASSIGNMENT expression
          | ID ASSIGNMENT expression
          ;

expression
          : expression ADD term
          | expression SUB term
          | expression LE term
          | expression GE term
          | expression EQ term
          | expression NE term
          | expression GT term
          | expression LT term
          | expression AND term
          | expression OR term
          | term
          ;

term
          : term MULT factor
          | term DIV factor
          | factor
          | NOT factor
          ;

factor
          : ID
          | UNARY ID
          | ID UNARY
          | NUMBER
          | FLOAT_NUM
          | CHARACTER
          | OPENING_BRACKET expression CLOSING_BRACKET
          ;

type
          : INT
          | FLOAT
          | CHAR
          ;

ifStatement
          : IF OPENING_BRACKET expression CLOSING_BRACKET
            OPENING_BRACES program CLOSING_BRACES
          | IF OPENING_BRACKET expression CLOSING_BRACKET
            OPENING_BRACES program CLOSING_BRACES
            ELSE OPENING_BRACES program CLOSING_BRACES
          | IF OPENING_BRACKET expression CLOSING_BRACKET
            OPENING_BRACES program CLOSING_BRACES
            elseIf
            ELSE OPENING_BRACES program CLOSING_BRACES
          | IF OPENING_BRACKET expression CLOSING_BRACKET
            OPENING_BRACES program CLOSING_BRACES
            elseIf
          ;

elseIf
          : ELSE IF OPENING_BRACKET expression CLOSING_BRACKET
            OPENING_BRACES program CLOSING_BRACES
          | elseIf ELSE IF OPENING_BRACKET expression CLOSING_BRACKET
            OPENING_BRACES program CLOSING_BRACES
          ;

forLoop
          : FOR OPENING_BRACKET assignments SEMI
            expression SEMI expression CLOSING_BRACKET
            OPENING_BRACES program CLOSING_BRACES
          ;

whileLoop
          : WHILE OPENING_BRACKET expression CLOSING_BRACKET
            OPENING_BRACES program CLOSING_BRACES
          ;

doWhileLoop
          : DO OPENING_BRACES program CLOSING_BRACES
            WHILE OPENING_BRACKET expression CLOSING_BRACKET SEMI
          ;

switchStatement
          : SWITCH OPENING_BRACKET ID CLOSING_BRACKET
            OPENING_BRACES caseStatement CLOSING_BRACES
          ;

caseStatement
          : caseBody
          | caseStatement caseBody
          ;

caseBody
          : CASE expression COLON program BREAK SEMI
          | CASE expression COLON program
          | DEFAULT COLON program BREAK SEMI
          | DEFAULT COLON program
          ;

%%

int main() {
  yyparse();
}

void yyerror(const char* msg) {
  fprintf(stderr, "%s\n", msg);
}
