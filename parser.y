%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <string.h>
    #include "utility.h"

    nodeType *opr(char *name, int oper, int nops, ...);
    nodeType *id(char *name, varType type, int intVal, double floatVal, char charVal);
    nodeType *con(int intVal, char charVal, double floatVal, varType type);

    void initSymTable();
    void extendSymTable();
    void destroySymTable();
    void addConToSymTable(int intVal, char charVal, double floatVal, varType type, int lineNo);
    void addIdToSymTable(char *name, varType type, int lineNo, int intVal, double floatVal, char charVal);
    void addOprToSymTable(char *name, int lineNo);
    void printSymTable();
    int searchForId(char *name);
    void freeNode(nodeType *p);
    int ex(nodeType *p);
    int yylex(void);
    void yyerror(char *s);
    int symTableSize;
    int symTableIndex;
    symTableEntry *sym;
%}

%union {
  int iValue;
  char cValue;
  double fValue;
  char *sIndex;
  nodeType *nPtr;
};

%token <iValue> INTEGER
%token <cValue> CHARACTER
%token <fValue> FLOAT_NUM
%token <sIndex> VARIABLE
%token DO WHILE IF SWITCH CASE DEFAULT BREAK PRINT CONST_INT_TYPE INT_TYPE CONST_FLOAT_TYPE FLOAT_TYPE CONST_CHAR_TYPE CHAR_TYPE
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list switch_body case_stmt

%%

program:
              function
            ;

function:
              function stmt                   { ex($2); freeNode($2); }
            | /* NULL */
            ;

stmt:
              ';'                             { $$ = opr("NA", ';', 2, NULL, NULL); }
            | expr ';'                        { $$ = $1; }
            | PRINT expr ';'                  { $$ = opr("print", PRINT, 1, $2); }
            | CONST_INT_TYPE VARIABLE '=' INTEGER ';'     { $$ = id($2, CONST_INT, $4, 0.5, '0'); }
            | INT_TYPE VARIABLE ';'           { $$ = id($2, INT, 0, 0.5, '0'); }
            | CONST_FLOAT_TYPE VARIABLE '=' FLOAT_NUM ';'   { $$ = id($2, CONST_FLOAT, 0, $4, '0'); }
            | FLOAT_TYPE VARIABLE ';'         { $$ = id($2, FLOAT, 0, 0.5, '0'); }
            | CONST_CHAR_TYPE VARIABLE '=' CHARACTER ';'    { $$ = id($2, CONST_CHAR, 0, 0.5, $4); }
            | CHAR_TYPE VARIABLE ';'          { $$ = id($2, CHARAC, 0, 0.5, '0'); }
            | VARIABLE '=' expr ';'           { $$ = opr("assign", '=', 2, id($1, PK, 0, 0.5, '0'), $3); }
            | DO stmt WHILE '(' expr ')' ';'  { $$ = opr("do", DO, 2, $2, $5); }
            | WHILE '(' expr ')' stmt         { $$ = opr("while", WHILE, 2, $3, $5); }
            | IF '(' expr ')' stmt %prec IFX  { $$ = opr("if", IF, 2, $3, $5); }
            | IF '(' expr ')' stmt ELSE stmt  { $$ = opr("if else", IF, 3, $3, $5, $7); }
            | SWITCH '(' VARIABLE ')' '{' switch_body '}' { $$ = opr("switch", SWITCH, 2, id($3, PK, 0, 0.5, '0'), $6); }
            | '{' stmt_list '}'               { $$ = $2; }
            ;

stmt_list:
              stmt                            { $$ = $1; }
            | stmt_list stmt                  { $$ = opr("NA", ';', 2, $1, $2); }
            ;

switch_body:
              case_stmt                       { $$ = $1; }
            | switch_body case_stmt           { $$ = opr("NA", ';', 2, $1, $2); }
            ;

case_stmt:
              CASE expr ':' stmt BREAK ';'    { $$ = opr("case", CASE, 2, $2, $4); }
            | DEFAULT ':' stmt BREAK ';'      { $$ = opr("default", DEFAULT, 1, $3); }
            ;

expr:
              INTEGER                         { $$ = con($1, '0', 0.5, INT); }
            | CHARACTER                       { $$ = con(0, $1, 0.5, CHARAC); }
            | FLOAT_NUM                       { $$ = con(0, '0', $1, FLOAT); }
            | VARIABLE                        { $$ = id($1, PK, 0, 0.5, '0'); }
            | '-' expr %prec UMINUS           { $$ = opr("negative", UMINUS, 1, $2); }
            | expr '+' expr                   { $$ = opr("add", '+', 2, $1, $3); }
            | expr '-' expr                   { $$ = opr("sub", '-', 2, $1, $3); }
            | expr '*' expr                   { $$ = opr("mul", '*', 2, $1, $3); }
            | expr '/' expr                   { $$ = opr("div", '/', 2, $1, $3); }
            | expr '<' expr                   { $$ = opr("<", '<', 2, $1, $3); }
            | expr '>' expr                   { $$ = opr(">", '>', 2, $1, $3); }
            | expr GE expr                    { $$ = opr(">=", GE, 2, $1, $3); }
            | expr LE expr                    { $$ = opr("<=", LE, 2, $1, $3); }
            | expr NE expr                    { $$ = opr("!=", NE, 2, $1, $3); }
            | expr EQ expr                    { $$ = opr("==", EQ, 2, $1, $3); }
            | '(' expr ')'                    { $$ = $2; }
            ;

%%

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

nodeType *id(char *name, varType type, int intVal, double floatVal, char charVal) {
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

  if (type == PK) {
    p->id.used = 1;
  } else {
    p->id.used = 0;
  }

  if (locInSym != -1 && type == PK) {
    sym[locInSym].id.used = 1;
  }

  if (type == PK && locInSym == -1) {
    // handle variable used not defined error
  }

  if (type != PK && locInSym != -1) {
    // handle multiple declaration of same var
  }

  if (locInSym == -1 && type != PK) {
    addIdToSymTable(name, type, yylineno, intVal, floatVal, charVal);
  }

  if (locInSym != -1) {
    p->id.type = sym[locInSym].id.type;

    if (p->id.type == CONST_INT) {
      p->id.intVal = sym[locInSym].id.intVal;
    } else if (p->id.type == CONST_FLOAT) {
      p->id.floatVal = sym[locInSym].id.floatVal;
    } else if (p->id.type == CONST_CHAR) {
      p->id.charVal = sym[locInSym].id.charVal;
    }
  }

  return p;
}

nodeType *opr(char *name, int oper, int nops, ...) {
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

  if (strcmp(name, "NA") != 0) { 
    addOprToSymTable(name, yylineno);
  }

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
  fprintf(stdout, "%s\n", s);
}

int main(void) {
  fptr = fopen("./program.out", "w");

  if (fptr == NULL) {
    printf("Couldn't open file!");
    exit(1);
  }

  initSymTable();

  yyparse();

  fclose(fptr);

  printSymTable();
  destroySymTable();

  return 0;
}
