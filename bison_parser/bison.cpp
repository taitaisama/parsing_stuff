#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <bits/stdc++.h>
#include "bison_ast.h"
#include "bison.tab.hpp"

extern "C" int yylex();
int yyparse();
extern "C" FILE *yyin;

extern T_prog prog_ast;

static void usage()
{
  printf("Usage: bison <prog.c>\n");
}

int
main(int argc, char **argv)
{
  if (argc != 2) {
    usage();
    exit(1);
  }
  char const *filename = argv[1];
  yyin = fopen(filename, "r");
  assert(yyin);
  int ret = yyparse();
  printf("retv = %d\n", ret);
  prog_ast->print();
  exit(0);
}
