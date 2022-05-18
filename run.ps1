bison -dy parser.y
flex lexer.l
gcc lex.yy.c y.tab.c compiler.c -o compiler.exe
cat example2.program | ./compiler.exe
