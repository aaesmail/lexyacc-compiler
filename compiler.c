#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "y.tab.h"

static int lbl;

static char *switchVar;
static int switchLbl;

void printConstant(conNodeType con);

int ex(nodeType *p) {
  int lbl1, lbl2;

  if (!p) return 0;

  switch(p->type) {
    case typeCon:
      fprintf(fptr, "\tpush\t");
      printConstant(p->con);
      fprintf(fptr, "\n");
      break;

    case typeId:
      fprintf(fptr, "\tpush\t%s\n", p->id.name);
      break;

    case typeOpr:
      switch(p->opr.oper) {
        case DO:
          fprintf(fptr, "L%03d:\n", lbl1 = lbl++);
          ex(p->opr.op[0]);
          ex(p->opr.op[1]);
          fprintf(fptr, "\tjnz\tL%03d\n", lbl1);
          break;

        case WHILE:
          fprintf(fptr, "L%03d:\n", lbl1 = lbl++);
          ex(p->opr.op[0]);
          fprintf(fptr, "\tjz\tL%03d\n", lbl2 = lbl++);
          ex(p->opr.op[1]);
          fprintf(fptr, "\tjmp\tL%03d\n", lbl1);
          fprintf(fptr, "L%03d:\n", lbl2);
          break;

        case IF:
          ex(p->opr.op[0]);
          if (p->opr.nops > 2) {
            fprintf(fptr, "\tjz\tL%03d\n", lbl1 = lbl++);
            ex(p->opr.op[1]);
            fprintf(fptr, "\tjmp\tL%03d\n", lbl2 = lbl++);
            fprintf(fptr, "L%03d:\n", lbl1);
            ex(p->opr.op[2]);
            fprintf(fptr, "L%03d:\n", lbl2);
          } else {
            fprintf(fptr, "\tjz\tL%03d\n", lbl1 = lbl++);
            ex(p->opr.op[1]);
            fprintf(fptr, "L%03d:\n", lbl1);
          }
          break;

        case SWITCH:
          switchVar = p->opr.op[0]->id.name;
          switchLbl = lbl++;
          ex(p->opr.op[1]);
          fprintf(fptr, "L%03d:\n", switchLbl);
          break;

        case CASE:
          ex(p->opr.op[0]);
          fprintf(fptr, "\tpush\t%s\n", switchVar);
          fprintf(fptr, "\tcmpEQ\n");
          fprintf(fptr, "\tjz\tL%03d\n", lbl1 = lbl++);
          ex(p->opr.op[1]);
          fprintf(fptr, "\tjmp\tL%03d\n", switchLbl);
          fprintf(fptr, "L%03d:\n", lbl1);
          break;

        case DEFAULT:
          ex(p->opr.op[0]);
          fprintf(fptr, "\tjmp\tL%03d\n", switchLbl);
          break;

        case PRINT:
          ex(p->opr.op[0]);
          fprintf(fptr, "\tprint\n");
          break;

        case '=':
          ex(p->opr.op[1]);
          fprintf(fptr, "\tpop\t%s\n", p->opr.op[0]->id.name);
          break;

        case UMINUS:
          ex(p->opr.op[0]);
          fprintf(fptr, "\tneg\n");
          break;

        default:
          ex(p->opr.op[0]);
          ex(p->opr.op[1]);

          switch(p->opr.oper) {
            case '+':
              fprintf(fptr, "\tadd\n");
              break;

            case '-':
              fprintf(fptr, "\tsub\n");
              break;

            case '*':
              fprintf(fptr, "\tmul\n");
              break;

            case '/':
              fprintf(fptr, "\tdiv\n");
              break;

            case '<':
              fprintf(fptr, "\tcmpLT\n");
              break;

            case '>':
              fprintf(fptr, "\tcmpGT\n");
              break;

            case GE:
              fprintf(fptr, "\tcmpGE\n");
              break;

            case LE:
              fprintf(fptr, "\tcmpLE\n");
              break;

            case NE:
              fprintf(fptr, "\tcmpNE\n");
              break;

            case EQ:
              fprintf(fptr, "\tcmpEQ\n");
              break;
          }
      }
  }

  return 0;
}

void printConstant(conNodeType con) {
  switch (con.type) {
    case INT:
      fprintf(fptr, "%d", con.intVal);
      break;

    case CHARAC:
      fprintf(fptr, "%c", con.charVal);
      break;

    case FLOAT:
      fprintf(fptr, "%.6f", con.floatVal);
      break;

    default:
      fprintf(fptr, "ERROR");
      break;
  }
}

void initSymTable() {
  symTableSize = 1;
  symTableIndex = 0;
  sym = malloc(symTableSize * sizeof(symTableEntry));
}

void extendSymTable() {
  symTableSize *= 2;
  sym = realloc(sym, symTableSize * sizeof(symTableEntry));
}

void destroySymTable() {
  free(sym);
}

void addConToSymTable(int intVal, char charVal, double floatVal, varType type, int lineNo) {
  if (symTableSize == symTableIndex) {
    extendSymTable();
  }

  if (type == INT) {
    sym[symTableIndex].con.intVal = intVal;
  } else if (type == CHARAC) {
    sym[symTableIndex].con.charVal = charVal;
  } else if (type == FLOAT) {
    sym[symTableIndex].con.floatVal = floatVal;
  }

  sym[symTableIndex].con.type = type;
  sym[symTableIndex].lineNo = lineNo;
  sym[symTableIndex].type = typeCon;
  symTableIndex++;
}

void addIdToSymTable(char *name, varType type, int lineNo) {
  if (symTableSize == symTableIndex) {
    extendSymTable();
  }

  sym[symTableIndex].id.name = strdup(name);
  sym[symTableIndex].id.type = type;
  sym[symTableIndex].lineNo = lineNo;
  sym[symTableIndex].type = typeId;
  symTableIndex++;
}

void addOprToSymTable(char *name, int lineNo) {
  if (symTableSize == symTableIndex) {
    extendSymTable();
  }

  sym[symTableIndex].opr.name = strdup(name);
  sym[symTableIndex].lineNo = lineNo;
  sym[symTableIndex].type = typeOpr;
  symTableIndex++;
}

int searchForId(char *name) {
  int i;

  for (i = 0; i < symTableIndex; i++) {
    if (sym[i].type == typeId) {
      if (strcmp(name, sym[i].id.name) == 0) {
        return i;
      }
    }
  }

  return -1;
}

void printVarType(varType type) {
  if (type == PK) {
    printf("%s", "PK");
  } else if (type == INT) {
    printf("%s", "int");
  } else if (type == CHARAC) {
    printf("%s", "char");
  } else if (type == FLOAT) {
    printf("%s", "float");
  } else {
    printf("ERROR");
  }
}

void printConstSym(conSymTable con) {
  if (con.type == INT) {
    printf("%d", con.intVal);
  } else if (con.type == CHARAC) {
    printf("%c", con.charVal);
  } else if (con.type == FLOAT) {
    printf("%.6f", con.floatVal);
  } else {
    printf("ERROR");
  }
}

void printSymTable() {
  int i;

  printf("\n\t\t\t\t\t\tSymbol Table\n");
  printf("\t\t\tLineNo\t\tType\t\tName\t\tVarType\t\tValue\n");

  for (i = 0; i < symTableIndex; i++) {
    printf("\t\t\t");

    printf("%d", sym[i].lineNo);

    printf("\t\t");

    if (sym[i].type == typeCon) {
      printf("%s", "const");
    } else if (sym[i].type == typeId) {
      printf("%s", "id");
    } else if (sym[i].type == typeOpr) {
      printf("%s", "opr");
    } else {
      printf("ERROR");
    }

    printf("\t\t");

    if (sym[i].type == typeCon) {
      printf("%s", "NA");
    } else if (sym[i].type == typeId) {
      printf("%s", sym[i].id.name);
    } else if (sym[i].type == typeOpr) {
      printf("%s", sym[i].opr.name);
    } else {
      printf("ERROR");
    }

    printf("\t\t");

    if (sym[i].type == typeCon) {
      printVarType(sym[i].con.type);
    } else if (sym[i].type == typeId) {
      printVarType(sym[i].id.type);
    } else if (sym[i].type == typeOpr) {
      printf("%s", "NA");
    } else {
      printf("ERROR");
    }

    printf("\t\t");

    if (sym[i].type == typeCon) {
      printConstSym(sym[i].con);
    } else if (sym[i].type == typeId) {
      printf("%s", "NA");
    } else if (sym[i].type == typeOpr) {
      printf("%s", "NA");
    } else {
      printf("ERROR");
    }

    printf("\n");
  }

  printf("\n");
}
