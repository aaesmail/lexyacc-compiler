%{
    #include "y.tab.h"
    int lineNumber = 0;
%}

%option yylineno

letter [a-zA-Z]
number [0-9]
unaryOp "++"|"--"

%%

"const"                         { return CONST; }
"int"                           { return INT; }
"float"                         { return FLOAT; }
"char"                          { return CHAR; }
"for"                           { return FOR; }
"while"                         { return WHILE; }
"do"                            { return DO; }
"if"                            { return IF; }
"else"                          { return ELSE; }
"switch"                        { return SWITCH; }
"case"                          { return CASE; }
"break"                         { return BREAK; }
"default"                       { return DEFAULT; }
[-]?{number}+                   { return NUMBER; }
[-]?{number}+\.{number}{1,6}    { return FLOAT_NUM; }
{letter}({letter}|{number})*    { return ID; }
{unaryOp}                       { return UNARY; }
"="                             { return ASSIGNMENT; }
":"                             { return COLON; }
";"                             { return SEMI; }
"("                             { return OPENING_BRACKET; }
")"                             { return CLOSING_BRACKET; }
"{"                             { return OPENING_BRACES; }
"}"                             { return CLOSING_BRACES; }
"<="                            { return LE; }
">="                            { return GE; }
"=="                            { return EQ; }
"!="                            { return NE; }
">"                             { return GT; }
"<"                             { return LT; }
"&&"                            { return AND; }
"||"                            { return OR; }
"!"                             { return NOT; }
"+"                             { return ADD; }
"-"                             { return SUB; }
"*"                             { return MULT; }
"/"                             { return DIV; }
\/\/.*                          { ; }
\/\*(.*\n)*.*\*\/               { ; }
[ \t]*                          { ; }
[\n]                            { lineNumber++; }
.                               { return *yytext; }
['].[']                         { return CHARACTER; }

%%

int yywrap() {
  return 1;
}
