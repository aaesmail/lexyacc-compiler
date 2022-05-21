typedef enum { typeCon, typeId, typeOpr } nodeEnum;
typedef enum { PK, INT, CHARAC, FLOAT, CONST_INT, CONST_FLOAT, CONST_CHAR } varType;

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
extern int yylineno;
extern int symTableSize;
extern int symTableIndex;
extern symTableEntry *sym;
