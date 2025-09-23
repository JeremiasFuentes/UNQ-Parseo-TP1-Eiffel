#!/bin/bash
  clear
echo "<inicio de compilacion>"
  mkdir -p ./out
  cd ./out
  flex -l ../lexer.l
  bison -dv ../parser.y
  gcc -o lexer parser.tab.c lex.yy.c
echo "<fin>"
read -p "Press enter to continue"