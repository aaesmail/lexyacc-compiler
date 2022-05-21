typedef enum { typeCon, typeId, typeOpr } nodeEnum;
typedef enum { PK, INT, CHARAC } varType;

// constant
typedef struct {
  varType type;

  union {
    int intVal;
    char charVal;
  };
} conNodeType;

// id
typedef struct {
  char *name;
  varType type;
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
  };
} conSymTable;

typedef struct {
  char *name;
  varType type;
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
