%{
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
%token DO WHILE IF SWITCH CASE DEFAULT BREAK PRINT FUNCTION CONST_INT_TYPE INT_TYPE CONST_FLOAT_TYPE FLOAT_TYPE CONST_CHAR_TYPE CHAR_TYPE
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
              ';'                             { $$ = opr(';', 2, NULL, NULL); }
            | expr ';'                        { $$ = $1; }
            | PRINT { addOprToSymTable("print", yylineno); } expr ';'                  { $$ = opr(PRINT, 1, $3); }
            | CONST_INT_TYPE VARIABLE '=' INTEGER ';'     { $$ = id($2, CONST_INT, $4, 0.5, '0', 1); }
            | INT_TYPE VARIABLE ';'           { $$ = id($2, INT, 0, 0.5, '0', 0); }
            | CONST_FLOAT_TYPE VARIABLE '=' FLOAT_NUM ';'   { $$ = id($2, CONST_FLOAT, 0, $4, '0', 1); }
            | FLOAT_TYPE VARIABLE ';'         { $$ = id($2, FLOAT, 0, 0.5, '0', 0); }
            | CONST_CHAR_TYPE VARIABLE '=' CHARACTER ';'    { $$ = id($2, CONST_CHAR, 0, 0.5, $4, 1); }
            | CHAR_TYPE VARIABLE ';'          { $$ = id($2, CHARAC, 0, 0.5, '0', 0); }
            | VARIABLE '=' { addOprToSymTable("assign", yylineno); } expr ';'           { $$ = opr('=', 2, id($1, PK, 0, 0.5, '0', 1), $4); }
            | DO { addOprToSymTable("do while", yylineno); } stmt WHILE '(' expr ')' ';'  { $$ = opr(DO, 2, $3, $6); }
            | WHILE { addOprToSymTable("while", yylineno); } '(' expr ')' stmt         { $$ = opr(WHILE, 2, $4, $6); }
            | IF '(' expr ')' stmt %prec IFX  { $$ = opr(IF, 2, $3, $5); addOprToSymTable("if", yylineno); }
            | IF '(' expr ')' stmt ELSE stmt  { $$ = opr(IF, 3, $3, $5, $7); addOprToSymTable("if else", yylineno); }
            | SWITCH { addOprToSymTable("switch", yylineno); } '(' VARIABLE ')' '{' switch_body '}' { $$ = opr(SWITCH, 2, id($4, PK, 0, 0.5, '0', 0), $7); }
            | FUNCTION VARIABLE { addIdToSymTable(yytext, FUNC, yylineno, 0, 0.5, '0'); } stmt { $$ = opr(FUNCTION, 2, id($2, FUNC, 0, 0.5, '0', 1), $4); }
            | '{' stmt_list '}'               { $$ = $2; }
            ;

stmt_list:
              stmt                            { $$ = $1; }
            | stmt_list stmt                  { $$ = opr(';', 2, $1, $2); }
            ;

switch_body:
              case_stmt                       { $$ = $1; }
            | switch_body case_stmt           { $$ = opr(';', 2, $1, $2); }
            ;

case_stmt:
              CASE { addOprToSymTable("case", yylineno); } expr ':' stmt BREAK { addOprToSymTable("break", yylineno); } ';'    { $$ = opr(CASE, 2, $3, $5); }
            | DEFAULT { addOprToSymTable("default", yylineno); } ':' stmt BREAK { addOprToSymTable("break", yylineno); } ';'      { $$ = opr(DEFAULT, 1, $4); }
            ;

expr:
              INTEGER                         { $$ = con($1, '0', 0.5, INT); }
            | CHARACTER                       { $$ = con(0, $1, 0.5, CHARAC); }
            | FLOAT_NUM                       { $$ = con(0, '0', $1, FLOAT); }
            | VARIABLE                        { $$ = id($1, PK, 0, 0.5, '0', 0); }
            | VARIABLE '(' ')'                { $$ = opr('f', 1, id($1, PK, 0, 0.5, '0', 0)); }
            | '-' { addOprToSymTable("negative", yylineno); } expr %prec UMINUS           { $$ = opr(UMINUS, 1, $3); }
            | expr '+' { addOprToSymTable("add", yylineno); } expr                   { $$ = opr('+', 2, $1, $4); }
            | expr '-' { addOprToSymTable("sub", yylineno); } expr                   { $$ = opr('-', 2, $1, $4); }
            | expr '*' { addOprToSymTable("mul", yylineno); } expr                   { $$ = opr('*', 2, $1, $4); }
            | expr '/' { addOprToSymTable("div", yylineno); } expr                   { $$ = opr('/', 2, $1, $4); }
            | expr '<' { addOprToSymTable("<", yylineno); } expr                   { $$ = opr('<', 2, $1, $4); }
            | expr '>' { addOprToSymTable(">", yylineno); } expr                   { $$ = opr('>', 2, $1, $4); }
            | expr GE { addOprToSymTable(">=", yylineno); } expr                    { $$ = opr(GE, 2, $1, $4); }
            | expr LE { addOprToSymTable("<=", yylineno); } expr                    { $$ = opr(LE, 2, $1, $4); }
            | expr NE { addOprToSymTable("!=", yylineno); } expr                    { $$ = opr(NE, 2, $1, $4); }
            | expr EQ { addOprToSymTable("==", yylineno); } expr                    { $$ = opr(EQ, 2, $1, $4); }
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

  if (type == PK) {
    p->id.used = 1;
  } else {
    p->id.used = 0;
    p->id.init = 0;
  }

  if (locInSym != -1 && type == PK) {
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
