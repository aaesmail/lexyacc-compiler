typedef enum { typeCon, typeId, typeOpr } nodeEnum;
typedef enum { PK, INT } varType;

// constant
typedef struct {
  int value;
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
  int value;
  varType type;
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
