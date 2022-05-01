%{
      #include <stdio.h>
      #include <string.h>
      #include <stdlib.h>
      #include <ctype.h>

      void yyerror(const char *s);
      int yylex();
      int yywrap();
%}

%token PRINTFF SCANFF CONST INT FLOAT CHAR VOID RETURN FOR IF ELSE INCLUDE TRUE FALSE NUMBER FLOAT_NUM ID UNARY LE GE EQ NE GT LT AND OR ADD SUB DIV MULT STR CHARACTER

%%

program:    
          headers main '(' ')' '{' body return '}'    { printf("wutwutwut"); }
          ;

headers:    
          headers headers
          | INCLUDE
          ;

main:       
          datatype ID
          ;

datatype:   
          INT
          | FLOAT
          | CHAR
          | VOID
          ;

body:
          FOR '(' statement ';' condition ';' statement ')' '{' body '}' 
          | IF '(' condition ')' '{' body '}' else
          | statement ';'
          | body body
          | PRINTFF '(' STR ')' ';'
          | SCANFF '(' STR ',' '&' ID ')' ';'
          ;

else:
          ELSE '{' body '}'
          |
          ;

condition:
            value relationOperator value
            | TRUE
            | FALSE
            ;

statement:
            datatype ID init
            | CONST datatype ID '=' value
            | ID '=' expression
            | ID relationOperator expression
            | ID UNARY
            | UNARY ID
            ;

value:
            NUMBER
            | FLOAT_NUM
            | CHARACTER
            | ID
            ;

relationOperator:
            LT
            | GT
            | LE
            | GE
            | EQ
            | NE
            ;

init:
            '=' value
            |
            ;

expression:
            expression arithmetic expression
            | value
            ;

arithmetic:
            ADD
            | SUB
            | MULT
            | DIV
            ;

return:
            RETURN value ';'
            |
            ;

%%

int main() {
  yyparse();
}

void yyerror(const char* msg) {
  fprintf(stderr, "%s\n", msg);
}
