%{
#include <cstdio>
#include <iostream>
#include "bison_ast.h"

// stuff from flex that bison needs to know about:
extern "C" int yylex();
 
int yyparse();
extern "C" FILE *yyin;
 
void yyerror(const char *s);

T_prog prog_ast;

%}

%token TERMINAL_DECL
%token <strval> TERMINAL NON_TERMINAL CHARACTER TYPE
%token DELIMITER

%start bison_prog

%union value {
  char* strval;
  T_prog bprog;
  T_token_decl_list tdl;
  T_token_decl td;
  T_terminal_list tl;
  T_rule_list rl;
  T_rule r;
  T_reduction red;
  T_reduction_list redl;
}

%nterm <bprog> bison_prog;
%nterm <tdl> token_decl_list;
%nterm <td> token_decl;
%nterm <tl> terminal_list;
%nterm <rl> rule_list;
%nterm <r> rule;
%nterm <red> reduction;
%nterm <redl> reduction_list;

%%

bison_prog
        : token_decl_list DELIMITER rule_list DELIMITER { $$ = T_create_prog($1, $3); prog_ast = $$; }
	;

token_decl_list
        : token_decl                 { $$ = T_create_token_decl_list($1); }
        | token_decl_list token_decl { $$ = T_add_to_token_decl_list($1, $2); }
        ;

token_decl
        : TERMINAL_DECL terminal_list      { $$ = T_create_token_decl($2); }
        | TERMINAL_DECL TYPE terminal_list { $$ = T_create_token_decl($2, $3); }
	;

terminal_list
        : TERMINAL               { $$ = T_create_terminal_list($1); }
	| terminal_list TERMINAL { $$ = T_add_to_terminal_list($1, $2); }
	;

rule_list
        : rule           { $$ = T_create_rule_list($1); }
	| rule_list rule { $$ = T_add_to_rule_list($1, $2); }
	;

rule
        : NON_TERMINAL ':' reduction_list ';' { $$ = T_create_rule($1, $3); }
	;

reduction_list
        : reduction                     { $$ = T_create_reduction_list($1); }
        | reduction_list '|' reduction  { $$ = T_add_to_reduction_list($1, $3); }
        ;

reduction
        : NON_TERMINAL            { $$ = T_create_reduction_terminal($1); }
	| TERMINAL                { $$ = T_create_reduction_non_terminal($1); }
	| CHARACTER               { $$ = T_create_reduction_character($1); }
	| reduction NON_TERMINAL  { $$ = T_add_to_reduction_non_terminal($1, $2); }
	| reduction TERMINAL      { $$ = T_add_to_reduction_terminal($1, $2); }
	| reduction CHARACTER     { $$ = T_add_to_reduction_character($1, $2); }
	;

%%
#include <stdio.h>

void yyerror(const char *s)
{
	fflush(stdout);
	fprintf(stderr, "*** %s\n", s);
}
