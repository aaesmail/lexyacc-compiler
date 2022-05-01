flex lexer.l
bison -dy parser.y
gcc lex.yy.c y.tab.c -o compiler.exe
cat example1.c | ./compiler.exe
