typedef enum { typeCon, typeId, typeOpr } nodeEnum;
typedef enum { PK, INT, CHARAC, FLOAT, CONST_INT, CONST_FLOAT, CONST_CHAR, FUNC } varType;

// constant
typedef struct {
  varType type;

  union {
    int intVal;
    char charVal;
    double floatVal;
  };
} conNodeType;

// id
typedef struct {
  char *name;
  varType type;
  int used;
  int init;

  union {
    int intVal;
    char charVal;
    double floatVal;
  };
} idNodeType;

// operator
typedef struct {
  int oper;
  int nops;
  struct nodeTypeTag *op[1];
} oprNodeType;

typedef struct nodeTypeTag {
  nodeEnum type;

  union {
    conNodeType con;
    idNodeType id;
    oprNodeType opr;
  };
} nodeType;

typedef struct {
  varType type;

  union {
    int intVal;
    char charVal;
    double floatVal;
  };
} conSymTable;

typedef struct {
  char *name;
  varType type;
  int used;
  int init;

  union {
    int intVal;
    char charVal;
    double floatVal;
  };
} idSymTable;

typedef struct {
  char *name;
} oprSymTable;

typedef struct {
  nodeEnum type;
  int lineNo;

  union {
    conSymTable con;
    idSymTable id;
    oprSymTable opr;
  };
} symTableEntry;

FILE *fptr;
FILE *symPtr;
FILE *errPtr;
extern int yylineno;
extern char *yytext;
extern int symTableSize;
extern int symTableIndex;
extern symTableEntry *sym;
