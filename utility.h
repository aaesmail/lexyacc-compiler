typedef enum { typeCon, typeId, typeOpr } nodeEnum;

// constant
typedef struct {
  int value;
} conNodeType;

// id
typedef struct {
  int i;
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

extern int sym[26];
FILE *fptr;
