%{
      #include <stdio.h>
      #include <string.h>
      #include <stdlib.h>
      #include <ctype.h>

      void yyerror(const char *s);
      int yylex();
      int yywrap();
      void insertType();
      void add(char c, char* info);
      int search(char *type);
      void extendSymbolTable();

      typedef struct symbolTableStruct {
        char * name;
        char * dataType;
        char * type;
        int lineNo;
      } symbolTableStruct;

      int symbolTableSize = 1;
      symbolTableStruct* symbolTable;

      int count = 0;
      int q;
      char type[10];
      extern int yylineno;
      extern char * yytext;
%}

%token CONST INT FLOAT CHAR
%token NUMBER FLOAT_NUM CHARACTER ID
%token FOR WHILE DO
%token IF ELSE ELIF SWITCH CASE BREAK DEFAULT
%token UNARY
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
          : assignments ';'
          | expression ';'
          | ifStatement
          | switchStatement
          | forLoop
          | whileLoop
          | doWhileLoop
          ;

assignments
          : type ID { add('V', "N/A"); } assignmOpt
          | CONST type ID { add('C', "N/A"); } assignmOpt
          | ID '=' expression
          ;

assignmOpt
          : '=' expression
          |
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
          | NUMBER { add('L', "int"); }
          | FLOAT_NUM { add('L', "float"); }
          | CHARACTER { add('L', "char"); }
          | '(' expression ')'
          ;

type
          : INT { insertType(); }
          | FLOAT { insertType(); }
          | CHAR { insertType(); }
          ;

ifStatement
          : IF { add('K', "N/A"); } '(' expression ')' '{' program '}' elseIfs elseStmt
          ;

elseIfs
          : elseIfs elseIf
          |
          ;

elseIf
          : ELIF { add('K', "N/A"); } '(' expression ')' '{' program '}'
          ;

elseStmt
          : ELSE { add('K', "N/A"); } '{' program '}'
          |
          ;

forLoop
          : FOR { add('K', "N/A"); } '(' assignments ';'
            expression ';' expression ')'
            '{' program '}'
          ;

whileLoop
          : WHILE { add('K', "N/A"); } '(' expression ')'
            '{' program '}'
          ;

doWhileLoop
          : DO { add('K', "N/A"); } '{' program '}'
            WHILE { add('K', "N/A"); } '(' expression ')' ';'
          ;

switchStatement
          : SWITCH { add('K', "N/A"); } '(' ID ')'
            '{' caseStatement '}'
          ;

caseStatement
          : caseStatement caseBody
          |
          ;

caseBody
          : CASE { add('K', "N/A"); } expression ':' program breakOpt
          | DEFAULT { add('K', "N/A"); } ':' program breakOpt
          ;

breakOpt
          : BREAK { add('K', "N/A"); } ';'
          |
          ;

%%

int main() {
  symbolTable = malloc(symbolTableSize * sizeof(symbolTableStruct));

  yyparse();

  printf("\n\n");

  printf("\t\t\t\t\t\t\tSymbol Table \n\n");
  printf("\t\t\t\tCount\tName\t\tData Type\tType\t\tLine Number");
  printf("\n\n\t\t\t____________________________________________________________________________\n\n");
  for (int i = 0; i < count; ++i) {
    printf("\t\t\t\t%d\t%s\t\t%s\t\t%s\t%d\t\n", i + 1, symbolTable[i].name, symbolTable[i].dataType, symbolTable[i].type, symbolTable[i].lineNo);
  }

  printf("\n\n");
}

void yyerror(const char* msg) {
  fprintf(stderr, "%s\n", msg);
}

void insertType() {
  strcpy(type, yytext);
}

void add(char c, char* info) {
  // q = search(yytext);

  if (q) return;

  if (count == symbolTableSize) extendSymbolTable();

  switch(c) {
    case 'H':
      symbolTable[count].name = strdup(yytext);
      symbolTable[count].dataType = strdup(type);
      symbolTable[count].lineNo = yylineno;
      symbolTable[count].type = strdup("Header");
      ++count;
      break;

    case 'K':
      symbolTable[count].name = strdup(yytext);
      symbolTable[count].dataType = strdup("N/A");
      symbolTable[count].lineNo = yylineno;
      symbolTable[count].type = strdup("Keyword\t");
      ++count;
      break;

    case 'V':
      symbolTable[count].name = strdup(yytext);
      symbolTable[count].dataType = strdup(type);
      symbolTable[count].lineNo = yylineno;
      symbolTable[count].type = strdup("Variable");
      ++count;
      break;

    case 'C':
      symbolTable[count].name = strdup(yytext);
      symbolTable[count].dataType = strdup(type);
      symbolTable[count].lineNo = yylineno;
      symbolTable[count].type = strdup("Constant");
      ++count;
      break;

    case 'L':
      symbolTable[count].name = strdup(yytext);
      symbolTable[count].dataType = strdup(info);
      symbolTable[count].lineNo = yylineno;
      symbolTable[count].type = strdup("Literal\t");
      ++count;
      break;

    case 'F':
      symbolTable[count].name = strdup(yytext);
      symbolTable[count].dataType = strdup(type);
      symbolTable[count].lineNo = yylineno;
      symbolTable[count].type = strdup("Function");
      ++count;
      break;

    default:
      break;
  }
}

int search(char *type) {
  int i;

  for (i = count - 1; i >= 0; --i) {
    if (strcmp(symbolTable[i].name, type) == 0) {
      return -1;
      break;
    }
  }

  return 0;
}

void extendSymbolTable() {
  symbolTableSize *= 2;
  symbolTableStruct* tempTable = malloc(symbolTableSize * sizeof(symbolTableStruct));

  for (int i = 0; i < count; ++i) {
    tempTable[i] = symbolTable[i];
  }

  symbolTableStruct* tempTable2 = symbolTable;
  symbolTable = tempTable;
  free(tempTable2);
}
