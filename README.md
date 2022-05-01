# lexyacc-compiler
A C like language compiler made using lex &amp; yacc

Run:
- Have a lex and yacc parsers and a C compiler installed
- yacc –d parser.y
- lex lexer.l
- gcc lex.yy.c y.tab.c -o compiler.exe
- feed a C program to the compiler.exe through stdin


If you have a windows machine:
- Install flex and bison and add them to environment variables
- Install gcc compiler and add it to environment variables
- Run the powershell script [run.ps1]
- It builds and feeds an example1.c to the compiler
