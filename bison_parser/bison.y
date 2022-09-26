%{
#include <cstdio>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();

string yytext;
 
int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);

void set_var(const char * text);
 
%}

%token TERMINAL_DECL START TERMINAL NON_TERMINAL CHARACTER DELIMITER

%start bison_prog

%%

bison_prog                                               
	: token_decl_list DELIMITER rule_list DELIMITER
	;

token_decl_list
        : token_decl
        | token_decl_list token_decl
        ;

token_decl
        : TERMINAL_DECL terminal_list
	| START NON_TERMINAL
	;

terminal_list
        : TERMINAL
	| terminal_list TERMINAL
	;

rule_list
        : rule
	| rule_list rule
	;

rule
        : NON_TERMINAL ':' reduction ';'
	| NON_TERMINAL ':' reduction alternate_reduction_list ';'
	;

reduction
        : NON_TERMINAL            { std::cout << yytext << std::endl;}
	| TERMINAL                { std::cout << yytext << std::endl;}
	| CHARACTER               { std::cout << yytext << std::endl;}
	| reduction NON_TERMINAL  { std::cout << yytext << std::endl;}
	| reduction TERMINAL      { std::cout << yytext << std::endl;}
	| reduction CHARACTER     { std::cout << yytext << std::endl;}
	;

alternate_reduction_list
        : '|' reduction
	| alternate_reduction_list '|' reduction
	;

%%
#include <stdio.h>

void yyerror(const char *s)
{
	fflush(stdout);
	fprintf(stderr, "*** %s\n", s);
}

void set_var(const char * text){
  std::cout << "lmao" << std::endl;
  yytext = text;
}
