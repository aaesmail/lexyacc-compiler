#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "y.tab.h"

static int lbl;

void printConstant(conNodeType con);
void writeId(idNodeType id);
void handleAssignmentToConstantError(idNodeType id);
void handleTypesError(struct nodeTypeTag * left, struct nodeTypeTag * right);
void handleNegativeError(struct nodeTypeTag * node);
void handleNotFunctionCallError(idNodeType node);

int ex(nodeType *p, idNodeType switchVar, int switchLbl) {
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
        fprintf(fptr, "\tmov\t");
        writeId(p->id);
        fprintf(fptr, ",\tR0\n");
        fprintf(fptr, "\tpush\tR0\n");
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
          ex(p->opr.op[0], switchVar, switchLbl);
          ex(p->opr.op[1], switchVar, switchLbl);
          fprintf(fptr, "\tjnz\tL%03d\n", lbl1);
          break;

        case WHILE:
          fprintf(fptr, "L%03d:\n", lbl1 = lbl++);
          ex(p->opr.op[0], switchVar, switchLbl);
          fprintf(fptr, "\tjz\tL%03d\n", lbl2 = lbl++);
          ex(p->opr.op[1], switchVar, switchLbl);
          fprintf(fptr, "\tjmp\tL%03d\n", lbl1);
          fprintf(fptr, "L%03d:\n", lbl2);
          break;

        case IF:
          ex(p->opr.op[0], switchVar, switchLbl);
          if (p->opr.nops > 2) {
            fprintf(fptr, "\tjz\tL%03d\n", lbl1 = lbl++);
            ex(p->opr.op[1], switchVar, switchLbl);
            fprintf(fptr, "\tjmp\tL%03d\n", lbl2 = lbl++);
            fprintf(fptr, "L%03d:\n", lbl1);
            ex(p->opr.op[2], switchVar, switchLbl);
            fprintf(fptr, "L%03d:\n", lbl2);
          } else {
            fprintf(fptr, "\tjz\tL%03d\n", lbl1 = lbl++);
            ex(p->opr.op[1], switchVar, switchLbl);
            fprintf(fptr, "L%03d:\n", lbl1);
          }
          break;

        case SWITCH:
          switchVar = p->opr.op[0]->id;
          switchLbl = lbl++;
          ex(p->opr.op[1], switchVar, switchLbl);
          fprintf(fptr, "L%03d:\n", switchLbl);
          break;

        case CASE:
          ex(p->opr.op[0], switchVar, switchLbl);
          fprintf(fptr, "\tmov\t");
          writeId(switchVar);
          fprintf(fptr, ",\tR0\n");
          fprintf(fptr, "\tpop\tR1\n");
          fprintf(fptr, "\tcmpEQ\tR1,\tR0\n");
          fprintf(fptr, "\tjz\tL%03d\n", lbl1 = lbl++);
          ex(p->opr.op[1], switchVar, switchLbl);
          fprintf(fptr, "\tjmp\tL%03d\n", switchLbl);
          fprintf(fptr, "L%03d:\n", lbl1);
          break;

        case DEFAULT:
          ex(p->opr.op[0], switchVar, switchLbl);
          fprintf(fptr, "\tjmp\tL%03d\n", switchLbl);
          break;

        case PRINT:
          ex(p->opr.op[0], switchVar, switchLbl);
          fprintf(fptr, "\tpop\tR0\n");
          fprintf(fptr, "\tprint\tR0\n");
          break;

        case '=':
          ex(p->opr.op[1], switchVar, switchLbl);
          handleAssignmentToConstantError(p->opr.op[0]->id);
          handleTypesError(p->opr.op[0], p->opr.op[1]);
          fprintf(fptr, "\tpop\tR0\n");
          fprintf(fptr, "\tmov\tR0,\t%s\n", p->opr.op[0]->id.name);
          break;

        case UMINUS:
          handleNegativeError(p->opr.op[0]);
          ex(p->opr.op[0], switchVar, switchLbl);
          fprintf(fptr, "\tpop\tR0\n");
          fprintf(fptr, "\tneg\tR0,\tR1\n");
          fprintf(fptr, "\tpush\tR1\n");
          break;

        case FUNCTION:
          fprintf(fptr, "subroutine\t%s:\n", p->opr.op[0]->id.name);
          ex(p->opr.op[1], switchVar, switchLbl);
          fprintf(fptr, "end\tsubroutine\n");
          break;

        case 'f':
          handleNotFunctionCallError(p->opr.op[0]->id);
          fprintf(fptr, "\tcall\t%s\n", p->opr.op[0]->id.name);
          break;

        default:
          handleTypesError(p->opr.op[0], p->opr.op[1]);
          ex(p->opr.op[0], switchVar, switchLbl);
          ex(p->opr.op[1], switchVar, switchLbl);

          switch(p->opr.oper) {
            case '+':
              fprintf(fptr, "\tpop\tR0\n");
              fprintf(fptr, "\tpop\tR1\n");
              fprintf(fptr, "\tadd\tR0,\tR1,\tR2\n");
              fprintf(fptr, "\tpush\tR2\n");
              break;

            case '-':
              fprintf(fptr, "\tpop\tR0\n");
              fprintf(fptr, "\tpop\tR1\n");
              fprintf(fptr, "\tsub\tR1,\tR0,\tR2\n");
              fprintf(fptr, "\tpush\tR2\n");
              break;

            case '*':
              fprintf(fptr, "\tpop\tR0\n");
              fprintf(fptr, "\tpop\tR1\n");
              fprintf(fptr, "\tmul\tR0,\tR1,\tR2\n");
              fprintf(fptr, "\tpush\tR2\n");
              break;

            case '/':
              fprintf(fptr, "\tpop\tR0\n");
              fprintf(fptr, "\tpop\tR1\n");
              fprintf(fptr, "\tdiv\tR1,\tR0,\tR2\n");
              fprintf(fptr, "\tpush\tR2\n");
              break;

            case '<':
              fprintf(fptr, "\tpop\tR0\n");
              fprintf(fptr, "\tpop\tR1\n");
              fprintf(fptr, "\tcmpLT\tR1,\tR0\n");
              break;

            case '>':
              fprintf(fptr, "\tpop\tR0\n");
              fprintf(fptr, "\tpop\tR1\n");
              fprintf(fptr, "\tcmpGT\tR1,\tR0\n");
              break;

            case GE:
              fprintf(fptr, "\tpop\tR0\n");
              fprintf(fptr, "\tpop\tR1\n");
              fprintf(fptr, "\tcmpGE\tR1,\tR0\n");
              break;

            case LE:
              fprintf(fptr, "\tpop\tR0\n");
              fprintf(fptr, "\tpop\tR1\n");
              fprintf(fptr, "\tcmpLE\tR1,\tR0\n");
              break;

            case NE:
              fprintf(fptr, "\tpop\tR0\n");
              fprintf(fptr, "\tpop\tR1\n");
              fprintf(fptr, "\tcmpNE\tR1,\tR0\n");
              break;

            case EQ:
              fprintf(fptr, "\tpop\tR0\n");
              fprintf(fptr, "\tpop\tR1\n");
              fprintf(fptr, "\tcmpEQ\tR1,\tR0\n");
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
    fprintf(symPtr, "%s", "PK");
  } else if (type == INT) {
    fprintf(symPtr, "%s", "int");
  } else if (type == CHARAC) {
    fprintf(symPtr, "%s", "char");
  } else if (type == FLOAT) {
    fprintf(symPtr, "%s", "float");
  } else if (type == CONST_INT) {
    fprintf(symPtr, "%s", "const_int");
  } else if (type == CONST_FLOAT) {
    fprintf(symPtr, "%s", "const_float");
  } else if (type == CONST_CHAR) {
    fprintf(symPtr, "%s", "const_char");
  } else if (type == FUNC) {
    fprintf(symPtr, "%s", "function");
  } else {
    fprintf(symPtr, "ERROR");
  }
}

void printConstSym(conSymTable con) {
  if (con.type == INT) {
    fprintf(symPtr, "%d", con.intVal);
  } else if (con.type == CHARAC) {
    fprintf(symPtr, "%c", con.charVal);
  } else if (con.type == FLOAT) {
    fprintf(symPtr, "%.6f", con.floatVal);
  } else {
    fprintf(symPtr, "ERROR");
  }
}

void printConstIdSym(idSymTable id) {
  if (id.type == CONST_INT) {
    fprintf(symPtr, "%d", id.intVal);
  } else if (id.type == CONST_CHAR) {
    fprintf(symPtr, "%c", id.charVal);
  } else if (id.type == CONST_FLOAT) {
    fprintf(symPtr, "%.6f", id.floatVal);
  } else {
    fprintf(symPtr, "NA");
  }
}

void printSymTable() {
  int i;

  fprintf(symPtr, "[\n  { \"line\": 0, \"type\": \"whatever\", \"name\": \"whatever\", \"varType\": \"whatever\", \"value\": \"whatever\" }");

  for (i = 0; i < symTableIndex; i++) {
    fprintf(symPtr, ",\n  { \"line\": %d, \"type\": \"", sym[i].lineNo);

    if (sym[i].type == typeCon) {
      fprintf(symPtr, "%s", "const");
    } else if (sym[i].type == typeId) {
      fprintf(symPtr, "%s", "id");
    } else if (sym[i].type == typeOpr) {
      fprintf(symPtr, "%s", "opr");
    } else {
      fprintf(symPtr, "ERROR");
    }

    fprintf(symPtr, "\", \"name\": \"");

    if (sym[i].type == typeCon) {
      fprintf(symPtr, "%s", "NA");
    } else if (sym[i].type == typeId) {
      fprintf(symPtr, "%s", sym[i].id.name);
    } else if (sym[i].type == typeOpr) {
      fprintf(symPtr, "%s", sym[i].opr.name);
    } else {
      fprintf(symPtr, "ERROR");
    }

    fprintf(symPtr, "\", \"varType\": \"");

    if (sym[i].type == typeCon) {
      printVarType(sym[i].con.type);
    } else if (sym[i].type == typeId) {
      printVarType(sym[i].id.type);
    } else if (sym[i].type == typeOpr) {
      fprintf(symPtr, "%s", "NA");
    } else {
      fprintf(symPtr, "ERROR");
    }

    fprintf(symPtr, "\", \"value\": \"");

    if (sym[i].type == typeCon) {
      printConstSym(sym[i].con);
    } else if (sym[i].type == typeId) {
      printConstIdSym(sym[i].id);
    } else if (sym[i].type == typeOpr) {
      fprintf(symPtr, "%s", "NA");
    } else {
      fprintf(symPtr, "ERROR");
    }

    fprintf(symPtr, "\" }");
  }

  fprintf(symPtr, "\n]\n");
}

void checkUnusedVariables() {
  int i;

  for (i = 0; i < symTableIndex; i++) {
    if (sym[i].type == typeId) {
      if (sym[i].id.used == 0) {
        fprintf(errPtr, ",\n  { \"line\": %d, \"description\": \"Unused variable %s\" }", sym[i].lineNo, sym[i].id.name);
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
          fprintf(errPtr, ",\n  { \"line\": %d, \"description\": \"Assignment to constant variable %s declared on line %d\" }", yylineno, sym[i].id.name, sym[i].lineNo);
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
    fprintf(errPtr, ",\n  { \"line\": %d, \"description\": \"Type mismatch between ", yylineno);

    if (leftType == INT) {
      fprintf(errPtr, "int");
    } else if (leftType == CHARAC) {
      fprintf(errPtr, "char");
    } else if (leftType == FLOAT) {
      fprintf(errPtr, "float");
    } else {
      printf("[handleTypesError] UNKNOWN LEFT TYPE ERROR\n");
    }

    fprintf(errPtr, " and ");

    if (rightType == INT) {
      fprintf(errPtr, "int");
    } else if (rightType == CHARAC) {
      fprintf(errPtr, "char");
    } else if (rightType == FLOAT) {
      fprintf(errPtr, "float");
    } else {
      printf("[handleTypesError] UNKNOWN RIGHT TYPE ERROR\n");
    }

    fprintf(errPtr, "\" }");
  }
}

void handleNegativeError(struct nodeTypeTag * node) {
  if (node->type == typeOpr) {
    return;
  }

  varType type = getType(node);

  if (type == CHARAC) {
    fprintf(errPtr, ",\n  { \"line\": %d, \"description\": \"Cannot apply unary minus to char type\" }", yylineno);
  }
}

void handleNotFunctionCallError(idNodeType node) {
  if (node.type != FUNC) {
    fprintf(errPtr, ",\n  { \"line\": %d, \"description\": \"%s is not a function\" }", yylineno, node.name);
  }
}
