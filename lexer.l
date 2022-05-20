%{
    #include <stdlib.h>
    #include "utility.h"
    #include "y.tab.h"

    void yyerror(char *);
%}

%option yylineno

%%

[a-z]                           {
                                  yylval.sIndex = *yytext - 'a';
                                  return VARIABLE;
                                }

[0-9]+                          {
                                  yylval.iValue = atoi(yytext);
                                  return INTEGER;
                                }

[-()<>=+*/:;{}.]                 {
                                  return *yytext;
                                }

">="                            { return GE; }
"<="                            { return LE; }
"=="                            { return EQ; }
"!="                            { return NE; }
"do"                            { return DO; }
"while"                         { return WHILE; }
"if"                            { return IF; }
"else"                          { return ELSE; }
"switch"                        { return SWITCH; }
"case"                          { return CASE; }
"default"                       { return DEFAULT; }
"break"                         { return BREAK; }
"print"                         { return PRINT; }

[ \t\n]+                        { ; }

.                               { yyerror("Unknown character"); }

%%
int yywrap(void) {
  return 1;
}
