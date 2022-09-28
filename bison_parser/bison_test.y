%token TERMINAL_DECL START TERMINAL NON_TERMINAL CHARACTER DELIMITER

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
        : NON_TERMINAL
	| TERMINAL
	| CHARACTER
	| reduction NON_TERMINAL 
	| reduction TERMINAL 
	| reduction CHARACTER 
	;

alternate_reduction_list
        : '|' reduction
	| alternate_reduction_list '|' reduction
	;

%%
