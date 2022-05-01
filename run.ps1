bison -dy parser.y
flex lexer.l
gcc lex.yy.c y.tab.c -o compiler.exe
cat example1.c | ./compiler.exe
