%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include "utility.h"

    nodeType *opr(int oper, int nops, ...);
    nodeType *id(int i, varType type);
    nodeType *con(int value);

    void freeNode(nodeType *p);
    int ex(nodeType *p);
    int yylex(void);
    void yyerror(char *s);
    int sym[26];
%}

%union {
  int iValue;
  char sIndex;
  nodeType *nPtr;
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token DO WHILE IF SWITCH CASE DEFAULT BREAK PRINT
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list switch_body case_stmt

%%

program:
              function                          { exit(0); }
            ;

function:
              function stmt                   { ex($2); freeNode($2); }
            | /* NULL */
            ;

stmt:
              ';'                             { $$ = opr(';', 2, NULL, NULL); }
            | expr ';'                        { $$ = $1; }
            | PRINT expr ';'                  { $$ = opr(PRINT, 1, $2); }
            | VARIABLE '=' expr ';'           { $$ = opr('=', 2, id($1, INT), $3); }
            | DO stmt WHILE '(' expr ')' ';'  { $$ = opr(DO, 2, $2, $5); }
            | WHILE '(' expr ')' stmt         { $$ = opr(WHILE, 2, $3, $5); }
            | IF '(' expr ')' stmt %prec IFX  { $$ = opr(IF, 2, $3, $5); }
            | IF '(' expr ')' stmt ELSE stmt  { $$ = opr(IF, 3, $3, $5, $7); }
            | SWITCH '(' VARIABLE ')' '{' switch_body '}' { $$ = opr(SWITCH, 2, id($3, PK), $6); }
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
              CASE expr ':' stmt BREAK ';'    { $$ = opr(CASE, 2, $2, $4); }
            | DEFAULT ':' stmt BREAK ';'      { $$ = opr(DEFAULT, 1, $3); }
            ;

expr:
              INTEGER                         { $$ = con($1); }
            | VARIABLE                        { $$ = id($1, PK); }
            | '-' expr %prec UMINUS           { $$ = opr(UMINUS, 1, $2); }
            | expr '+' expr                   { $$ = opr('+', 2, $1, $3); }
            | expr '-' expr                   { $$ = opr('-', 2, $1, $3); }
            | expr '*' expr                   { $$ = opr('*', 2, $1, $3); }
            | expr '/' expr                   { $$ = opr('/', 2, $1, $3); }
            | expr '<' expr                   { $$ = opr('<', 2, $1, $3); }
            | expr '>' expr                   { $$ = opr('>', 2, $1, $3); }
            | expr GE expr                    { $$ = opr(GE, 2, $1, $3); }
            | expr LE expr                    { $$ = opr(LE, 2, $1, $3); }
            | expr NE expr                    { $$ = opr(NE, 2, $1, $3); }
            | expr EQ expr                    { $$ = opr(EQ, 2, $1, $3); }
            | '(' expr ')'                    { $$ = $2; }
            ;

%%

#define SIZEOF_NODETYPE ((char *)&p->con - (char *)p)

nodeType *con(int value) {
  nodeType *p;
  size_t nodeSize;

  nodeSize = SIZEOF_NODETYPE + sizeof(conNodeType);

  if ((p = malloc(nodeSize)) == NULL)
    yyerror("Out of memory!");

  p->type = typeCon;
  p->con.value = value;

  return p;
}

nodeType *id(int i, varType type) {
  nodeType *p;
  size_t nodeSize;

  nodeSize = SIZEOF_NODETYPE + sizeof(idNodeType);

  if ((p = malloc(nodeSize)) == NULL)
    yyerror("Out of memory!");

  p->type = typeId;
  p->id.i = i;

  if (type != PK) {
    p->id.type = type;
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
  fprintf(stdout, "%s\n", s);
}

int main(void) {
  fptr = fopen("./program.out", "w");

  if (fptr == NULL) {
    printf("Couldn't open file!");
    exit(1);
  }

  yyparse();

  fclose(fptr);

  return 0;
}
