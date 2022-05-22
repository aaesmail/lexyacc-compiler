#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "y.tab.h"

static int lbl;

static idNodeType switchVar;
static int switchLbl;

void printConstant(conNodeType con);
void writeId(idNodeType id);
void handleAssignmentToConstantError(idNodeType id);
void handleTypesError(struct nodeTypeTag * left, struct nodeTypeTag * right);
void handleNegativeError(struct nodeTypeTag * node);
void handleNotFunctionCallError(idNodeType node);

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
      if (p->id.used == 1) {
        fprintf(fptr, "\tpush\t");
        writeId(p->id);
        fprintf(fptr, "\n");
      } else {
        if (p->id.type == INT) {
          fprintf(fptr, "\tvar\t%s\t4\n", p->id.name);
        } else if (p->id.type == CHARAC) {
          fprintf(fptr, "\tvar\t%s\t1\n", p->id.name);
        } else if (p->id.type == FLOAT) {
          fprintf(fptr, "\tvar\t%s\t8\n", p->id.name);
        }
      }
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
          switchVar = p->opr.op[0]->id;
          switchLbl = lbl++;
          ex(p->opr.op[1]);
          fprintf(fptr, "L%03d:\n", switchLbl);
          break;

        case CASE:
          ex(p->opr.op[0]);
          fprintf(fptr, "\tpush\t");
          writeId(switchVar);
          fprintf(fptr, "\n");
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
          handleAssignmentToConstantError(p->opr.op[0]->id);
          handleTypesError(p->opr.op[0], p->opr.op[1]);
          fprintf(fptr, "\tpop\t%s\n", p->opr.op[0]->id.name);
          break;

        case UMINUS:
          handleNegativeError(p->opr.op[0]);
          ex(p->opr.op[0]);
          fprintf(fptr, "\tneg\n");
          break;

        case FUNCTION:
          fprintf(fptr, "function\t%s:\n", p->opr.op[0]->id.name);
          ex(p->opr.op[1]);
          fprintf(fptr, "\treturn\n");
          fprintf(fptr, "end\tfunction\n");
          break;

        case 'f':
          handleNotFunctionCallError(p->opr.op[0]->id);
          fprintf(fptr, "\tcall\t%s\n", p->opr.op[0]->id.name);
          break;

        default:
          handleTypesError(p->opr.op[0], p->opr.op[1]);
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
      fprintf(fptr, "%d", con.charVal);
      break;

    case FLOAT:
      fprintf(fptr, "%.6f", con.floatVal);
      break;

    default:
      fprintf(fptr, "ERROR");
      break;
  }
}

void writeId(idNodeType id) {
  switch(id.type) {
    case CONST_INT:
      fprintf(fptr, "%d", id.intVal);
      break;

    case CONST_FLOAT:
      fprintf(fptr, "%.6f", id.floatVal);
      break;

    case CONST_CHAR:
      fprintf(fptr, "%d", id.charVal);
      break;

    default:
      fprintf(fptr, "%s", id.name);
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

int addIdToSymTable(char *name, varType type, int lineNo, int intVal, double floatVal, char charVal) {
  if (symTableSize == symTableIndex) {
    extendSymTable();
  }

  sym[symTableIndex].id.name = strdup(name);
  sym[symTableIndex].id.type = type;
  sym[symTableIndex].id.used = 0;
  sym[symTableIndex].id.init = 0;
  sym[symTableIndex].lineNo = lineNo;
  sym[symTableIndex].type = typeId;

  if (type == CONST_INT) {
    sym[symTableIndex].id.intVal = intVal;
  } else if (type == CONST_FLOAT) {
    sym[symTableIndex].id.floatVal = floatVal;
  } else if (type == CONST_CHAR) {
    sym[symTableIndex].id.charVal = charVal;
  }

  return symTableIndex++;
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
    printf("%s", "PK\t");
  } else if (type == INT) {
    printf("%s", "int\t");
  } else if (type == CHARAC) {
    printf("%s", "char\t");
  } else if (type == FLOAT) {
    printf("%s", "float\t");
  } else if (type == CONST_INT) {
    printf("%s", "const_int");
  } else if (type == CONST_FLOAT) {
    printf("%s", "const_float");
  } else if (type == CONST_CHAR) {
    printf("%s", "const_char");
  } else if (type == FUNC) {
    printf("%s", "function");
  } else {
    printf("ERROR\t");
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

void printConstIdSym(idSymTable id) {
  if (id.type == CONST_INT) {
    printf("%d", id.intVal);
  } else if (id.type == CONST_CHAR) {
    printf("%c", id.charVal);
  } else if (id.type == CONST_FLOAT) {
    printf("%.6f", id.floatVal);
  } else {
    printf("NA");
  }
}

void printSymTable() {
  int i;

  printf("\n\t\t\t\t\t\t\tSymbol Table\n\n");
  printf("\t\t\tLineNo\t\tType\t\tName\t\tVarType\t\tValue\n\n");

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
      printf("%s", "NA\t");
    } else {
      printf("ERROR\t");
    }

    printf("\t");

    if (sym[i].type == typeCon) {
      printConstSym(sym[i].con);
    } else if (sym[i].type == typeId) {
      printConstIdSym(sym[i].id);
    } else if (sym[i].type == typeOpr) {
      printf("%s", "NA");
    } else {
      printf("ERROR");
    }

    printf("\n");
  }

  printf("\n");
}

void checkUnusedVariables() {
  int i;

  for (i = 0; i < symTableIndex; i++) {
    if (sym[i].type == typeId) {
      if (sym[i].id.used == 0) {
        printf("\nWarning: Unused variable %s declared on line %d\n", sym[i].id.name, sym[i].lineNo);
      }
    }
  }
}

void handleAssignmentToConstantError(idNodeType id) {
  int i;

  for (i = 0; i < symTableIndex; i++) {
    if (sym[i].type == typeId) {
      if (strcmp(id.name, sym[i].id.name) == 0) {
        if (sym[i].id.type == CONST_INT || sym[i].id.type == CONST_FLOAT || sym[i].id.type == CONST_CHAR) {
          printf("\nError on line %d: Assignment to constant variable %s declared on line %d\n", yylineno, sym[i].id.name, sym[i].lineNo);
        }
      }
    }
  }
}

varType getType(struct nodeTypeTag * node) {
  varType type;
  if (node->type == typeId) {
    type = node->id.type;
  } else if (node->type == typeCon) {
    type = node->con.type;
  } else {
    printf("[getType] ERROR type unknown\n");
  }

  if (type == CONST_CHAR) {
    type = CHARAC;
  } else if (type == CONST_FLOAT) {
    type = FLOAT;
  } else if (type == CONST_INT) {
    type = INT;
  } else if (type == PK) {
    printf("[getType] ERROR got variable of type PK\n");
  }

  return type;
}

void handleTypesError(struct nodeTypeTag * left, struct nodeTypeTag * right) {
  if (left->type == typeOpr || right->type == typeOpr) {
    return;
  }

  varType leftType = getType(left);
  varType rightType = getType(right);

  if (leftType != rightType) {
    printf("\nError on line %d: Type mismatch between ", yylineno);

    if (leftType == INT) {
      printf("int");
    } else if (leftType == CHARAC) {
      printf("char");
    } else if (leftType == FLOAT) {
      printf("float");
    } else {
      printf("[handleTypesError] UNKNOWN LEFT TYPE ERROR\n");
    }

    printf(" and ");

    if (rightType == INT) {
      printf("int");
    } else if (rightType == CHARAC) {
      printf("char");
    } else if (rightType == FLOAT) {
      printf("float");
    } else {
      printf("[handleTypesError] UNKNOWN RIGHT TYPE ERROR\n");
    }

    printf("\n");
  }
}

void handleNegativeError(struct nodeTypeTag * node) {
  if (node->type == typeOpr) {
    return;
  }

  varType type = getType(node);

  if (type == CHARAC) {
    printf("\nError on line %d: Cannot apply unary minus to char type\n", yylineno);
  }
}

void handleNotFunctionCallError(idNodeType node) {
  if (node.type != FUNC) {
    printf("\nError on line %d: %s is not a function\n", yylineno, node.name);
  }
}
