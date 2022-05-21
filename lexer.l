%{
    #include <stdlib.h>
    #include <string.h>
    #include "utility.h"
    #include "y.tab.h"

    void yyerror(char *);
%}

%option yylineno

%%

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

[a-zA-Z][0-9a-zA-Z]*            {
                                  yylval.sIndex = strdup(yytext);
                                  return VARIABLE;
                                }

[0-9]+                          {
                                  yylval.iValue = atoi(yytext);
                                  return INTEGER;
                                }

[0-9]+\.[0-9]+                  {
                                  yylval.fValue = atof(yytext);
                                  return FLOAT_NUM;
                                }

['].[']                         {
                                  yylval.cValue = yytext[1];
                                  return CHARACTER;
                                } 

[-()<>=+*/:;{}.]                {
                                  return *yytext;
                                }

[ \t\n]+                        { ; }

.                               { yyerror("Unknown character"); }

%%
int yywrap(void) {
  return 1;
}
