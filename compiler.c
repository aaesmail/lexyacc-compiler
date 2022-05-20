#include <stdio.h>
#include "utility.h"
#include "y.tab.h"

static int lbl;

static char switchVar;
static int switchLbl;

int ex(nodeType *p) {
  int lbl1, lbl2;

  if (!p) return 0;

  switch(p->type) {
    case typeCon:
      fprintf(fptr, "\tpush\t%d\n", p->con.value);
      break;

    case typeId:
      fprintf(fptr, "\tpush\t%c\n", p->id.i + 'a');
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
          switchVar = p->opr.op[0]->id.i + 'a';
          switchLbl = lbl++;
          ex(p->opr.op[1]);
          fprintf(fptr, "L%03d:\n", switchLbl);
          break;

        case CASE:
          ex(p->opr.op[0]);
          fprintf(fptr, "\tpush\t%c\n", switchVar);
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
          fprintf(fptr, "\tpop\t%c\n", p->opr.op[0]->id.i + 'a');
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
