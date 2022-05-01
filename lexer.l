%{
    #include "y.tab.h"
    int lineNumber = 0;
%}

%option yylineno

letter [a-zA-Z]
number [0-9]
unaryOp "++"|"--"

%%

"printf"                        { return PRINTFF; }
"scanf"                         { return SCANFF; }
"const"                         { return CONST; }
"int"                           { return INT; }
"float"                         { return FLOAT; }
"char"                          { return CHAR; }
"void"                          { return VOID; }
"return"                        { return RETURN; }
"for"                           { return FOR; }
"while"                         { return WHILE; }
"do"                            { return DO; }
"if"                            { return IF; }
"else"                          { return ELSE; }
"switch"                        { return SWITCH; }
"case"                          { return CASE; }
"break"                         { return BREAK; }
"default"                       { return DEFAULT; }
^"#include"[ ]*<.+\.h>          { return INCLUDE; }
"true"                          { return TRUE; }
"false"                         { return FALSE; }
[-]?{number}+                   { return NUMBER; }
[-]?{number}+\.{number}{1,6}    { return FLOAT_NUM; }
{letter}({letter}|{number})*    { return ID; }
{unaryOp}                       { return UNARY; }
"<="                            { return LE; }
">="                            { return GE; }
"=="                            { return EQ; }
"!="                            { return NE; }
">"                             { return GT; }
"<"                             { return LT; }
"&&"                            { return AND; }
"||"                            { return OR; }
"+"                             { return ADD; }
"-"                             { return SUB; }
"*"                             { return MULT; }
"/"                             { return DIV; }
\/\/.*                          { ; }
\/\*(.*\n)*.*\*\/               { ; }
[ \t]*                          { ; }
[\n]                            { lineNumber++; }
.                               { return *yytext; }
["].*["]                        { return STR; }
['].[']                         { return CHARACTER; }

%%

int yywrap() {
  return 1;
}
