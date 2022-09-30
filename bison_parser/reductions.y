%union value {
	char* strval;
	int* intval;
	float* floatval;
	T_abstract_declarator val_abstract_declarator;
	T_alignment_specifier val_alignment_specifier;
	T_argument_expression_list val_argument_expression_list;
	T_assignment_expression val_assignment_expression;
	T_assignment_operator val_assignment_operator;
	T_atomic_type_specifier val_atomic_type_specifier;
	T_binary_expression val_binary_expression;
	T_block_item val_block_item;
	T_block_item_list val_block_item_list;
	T_compound_statement val_compound_statement;
	T_conditional_expression val_conditional_expression;
	T_constant val_constant;
	T_constant_expression val_constant_expression;
	T_declaration val_declaration;
	T_declaration_list val_declaration_list;
	T_declaration_specifiers val_declaration_specifiers;
	T_declarator val_declarator;
	T_designation val_designation;
	T_designator val_designator;
	T_designator_list val_designator_list;
	T_direct_abstract_declarator val_direct_abstract_declarator;
	T_direct_declarator val_direct_declarator;
	T_enum_specifier val_enum_specifier;
	T_enumeration_constant val_enumeration_constant;
	T_enumerator val_enumerator;
	T_enumerator_list val_enumerator_list;
	T_expression val_expression;
	T_expression_statement val_expression_statement;
	T_external_declaration val_external_declaration;
	T_function_definition val_function_definition;
	T_function_specifier val_function_specifier;
	T_generic_assoc_list val_generic_assoc_list;
	T_generic_association val_generic_association;
	T_generic_selection val_generic_selection;
	T_identifier_list val_identifier_list;
	T_init_declarator val_init_declarator;
	T_init_declarator_list val_init_declarator_list;
	T_initializer val_initializer;
	T_initializer_list val_initializer_list;
	T_iteration_statement val_iteration_statement;
	T_jump_statement val_jump_statement;
	T_labeled_statement val_labeled_statement;
	T_parameter_declaration val_parameter_declaration;
	T_parameter_list val_parameter_list;
	T_parameter_type_list val_parameter_type_list;
	T_pointer val_pointer;
	T_primary_expression val_primary_expression;
	T_selection_statement val_selection_statement;
	T_specifier_qualifier_list val_specifier_qualifier_list;
	T_statement val_statement;
	T_static_assert_declaration val_static_assert_declaration;
	T_storage_class_specifier val_storage_class_specifier;
	T_string val_string;
	T_struct_declaration val_struct_declaration;
	T_struct_declaration_list val_struct_declaration_list;
	T_struct_declarator val_struct_declarator;
	T_struct_declarator_list val_struct_declarator_list;
	T_struct_or_union val_struct_or_union;
	T_struct_or_union_specifier val_struct_or_union_specifier;
	T_translation_unit val_translation_unit;
	T_type_name val_type_name;
	T_type_qualifier val_type_qualifier;
	T_type_qualifier_list val_type_qualifier_list;
	T_type_specifier val_type_specifier;
	T_unary_expression val_unary_expression;
	T_unary_operator val_unary_operator;
};
%nterm <val_abstract_declarator> abstract_declarator;
%nterm <val_binary_expression> additive_expression;
%nterm <val_alignment_specifier> alignment_specifier;
%nterm <val_binary_expression> and_expression;
%nterm <val_argument_expression_list> argument_expression_list;
%nterm <val_assignment_expression> assignment_expression;
%nterm <val_assignment_operator> assignment_operator;
%nterm <val_atomic_type_specifier> atomic_type_specifier;
%nterm <val_block_item> block_item;
%nterm <val_block_item_list> block_item_list;
%nterm <val_unary_expression> cast_expression;
%nterm <val_compound_statement> compound_statement;
%nterm <val_conditional_expression> conditional_expression;
%nterm <val_constant> constant;
%nterm <val_constant_expression> constant_expression;
%nterm <val_declaration> declaration;
%nterm <val_declaration_list> declaration_list;
%nterm <val_declaration_specifiers> declaration_specifiers;
%nterm <val_declarator> declarator;
%nterm <val_designation> designation;
%nterm <val_designator> designator;
%nterm <val_designator_list> designator_list;
%nterm <val_direct_abstract_declarator> direct_abstract_declarator;
%nterm <val_direct_declarator> direct_declarator;
%nterm <val_enum_specifier> enum_specifier;
%nterm <val_enumeration_constant> enumeration_constant;
%nterm <val_enumerator> enumerator;
%nterm <val_enumerator_list> enumerator_list;
%nterm <val_binary_expression> equality_expression;
%nterm <val_binary_expression> exclusive_or_expression;
%nterm <val_expression> expression;
%nterm <val_expression_statement> expression_statement;
%nterm <val_external_declaration> external_declaration;
%nterm <val_function_definition> function_definition;
%nterm <val_function_specifier> function_specifier;
%nterm <val_generic_assoc_list> generic_assoc_list;
%nterm <val_generic_association> generic_association;
%nterm <val_generic_selection> generic_selection;
%nterm <val_identifier_list> identifier_list;
%nterm <val_binary_expression> inclusive_or_expression;
%nterm <val_init_declarator> init_declarator;
%nterm <val_init_declarator_list> init_declarator_list;
%nterm <val_initializer> initializer;
%nterm <val_initializer_list> initializer_list;
%nterm <val_iteration_statement> iteration_statement;
%nterm <val_jump_statement> jump_statement;
%nterm <val_labeled_statement> labeled_statement;
%nterm <val_binary_expression> logical_and_expression;
%nterm <val_binary_expression> logical_or_expression;
%nterm <val_binary_expression> multiplicative_expression;
%nterm <val_parameter_declaration> parameter_declaration;
%nterm <val_parameter_list> parameter_list;
%nterm <val_parameter_type_list> parameter_type_list;
%nterm <val_pointer> pointer;
%nterm <val_unary_expression> postfix_expression;
%nterm <val_primary_expression> primary_expression;
%nterm <val_binary_expression> relational_expression;
%nterm <val_selection_statement> selection_statement;
%nterm <val_binary_expression> shift_expression;
%nterm <val_specifier_qualifier_list> specifier_qualifier_list;
%nterm <val_statement> statement;
%nterm <val_static_assert_declaration> static_assert_declaration;
%nterm <val_storage_class_specifier> storage_class_specifier;
%nterm <val_string> string;
%nterm <val_struct_declaration> struct_declaration;
%nterm <val_struct_declaration_list> struct_declaration_list;
%nterm <val_struct_declarator> struct_declarator;
%nterm <val_struct_declarator_list> struct_declarator_list;
%nterm <val_struct_or_union> struct_or_union;
%nterm <val_struct_or_union_specifier> struct_or_union_specifier;
%nterm <val_translation_unit> translation_unit;
%nterm <val_type_name> type_name;
%nterm <val_type_qualifier> type_qualifier;
%nterm <val_type_qualifier_list> type_qualifier_list;
%nterm <val_type_specifier> type_specifier;
%nterm <val_unary_expression> unary_expression;
%nterm <val_unary_operator> unary_operator;

primary_expression
        : IDENTIFIER                                                                             { $$ = new S_primary_expression($1); }
        | constant                                                                               { $$ = new S_primary_expression($1); }
        | string                                                                                 { $$ = new S_primary_expression($1); }
        | '(' expression ')'                                                                     { $$ = new S_primary_expression($2); }
        | generic_selection                                                                      { $$ = new S_primary_expression($1); }
        ;
constant
        : I_CONSTANT                                                                             { $$ = new S_constant($1); }
        | F_CONSTANT                                                                             { $$ = new S_constant($1); }
        | ENUMERATION_CONSTANT                                                                   { $$ = new S_constant(); }
        ;
enumeration_constant
        : IDENTIFIER                                                                             { $$ = new S_enumeration_constant($1); }
        ;
string
        : STRING_LITERAL                                                                         { $$ = new S_string($1, 0); }
        | FUNC_NAME                                                                              { $$ = new S_string($1, 1); }
        ;
generic_selection
        : GENERIC '(' assignment_expression ',' generic_assoc_list ')'                           { $$ = new S_generic_selection($3, $5); }
        ;
generic_assoc_list
        : generic_association                                                                    { $$ = new S_generic_assoc_list($1, NULL); }
        | generic_assoc_list ',' generic_association                                             { $$ = new S_generic_assoc_list($3, $1); }
        ;
generic_association
        : type_name ':' assignment_expression                                                    { $$ = new S_generic_association($1, $3, 0); }
        | DEFAULT ':' assignment_expression                                                      { $$ = new S_generic_association(NULL, $3, 1); }
        ;
postfix_expression
        : primary_expression                                                                     { $$ = new S_unary_expression($1); }
        | postfix_expression '[' expression ']'                                                  { $$ = new S_unary_expression($1, $3); }
        | postfix_expression '(' ')'                                                             
        | postfix_expression '(' argument_expression_list ')'                                    { $$ = new S_unary_expression($1, $3); }
        | postfix_expression '.' IDENTIFIER                                                      { $$ = new S_unary_expression($1, $3, 5); }
        | postfix_expression PTR_OP IDENTIFIER                                                   { $$ = new S_unary_expression($1, $3, 6); }
        | postfix_expression INC_OP                                                              { $$ = new S_unary_expression($1, 7); }
        | postfix_expression DEC_OP                                                              { $$ = new S_unary_expression($1, 8); }
        | '(' type_name ')' '{' initializer_list '}'                                             { $$ = new S_unary_expression($2, $5); }
        | '(' type_name ')' '{' initializer_list ',' '}'                                         
        ;

argument_expression_list
        : assignment_expression                                                                  { $$ = new S_argument_expression_list($1, NULL); }
        | argument_expression_list ',' assignment_expression                                     { $$ = new S_argument_expression_list($3, $1); }
        ;
unary_expression
        : postfix_expression                                                                     { }
        | INC_OP unary_expression                                                                { $$ = new S_unary_expression($2, 11); }
        | DEC_OP unary_expression                                                                { $$ = new S_unary_expression($2, 12); }
        | unary_operator cast_expression                                                         { $$ = new S_unary_expression($1, $2); }
        | SIZEOF unary_expression                                                                { $$ = new S_unary_expression($2, 14); }
        | SIZEOF '(' type_name ')'                                                               { $$ = new S_unary_expression($3, 15); }
        | ALIGNOF '(' type_name ')'                                                              { $$ = new S_unary_expression($3, 16); }
        ;

unary_operator
        : '&'                                                                                    { $$ = new S_unary_operator(0); }
        | '*'                                                                                    { $$ = new S_unary_operator(1); }
        | '+'                                                                                    { $$ = new S_unary_operator(2); }
        | '-'                                                                                    { $$ = new S_unary_operator(3); }
        | '~'                                                                                    { $$ = new S_unary_operator(4); }
        | '!'                                                                                    { $$ = new S_unary_operator(5); }
        ;
cast_expression
        : unary_expression                                                                       { }
        | '(' type_name ')' cast_expression                                                      { $$ = new S_unary_expression($2, $4); }
        ;

multiplicative_expression
        : cast_expression                                                                        { $$ = new S_binary_expression($1); }
        | multiplicative_expression '*' cast_expression                                          { $$ = new S_binary_expression($1, $3, 10); }
        | multiplicative_expression '/' cast_expression                                          { $$ = new S_binary_expression($1, $3, 11); }
        | multiplicative_expression '%' cast_expression                                          { $$ = new S_binary_expression($1, $3, 12); }
        ;

additive_expression
        : multiplicative_expression                                                              { }
        | additive_expression '+' multiplicative_expression                                      { $$ = new S_binary_expression($1, $3, 0); }
        | additive_expression '-' multiplicative_expression                                      { $$ = new S_binary_expression($1, $3, 1); }
        ;

shift_expression
        : additive_expression                                                                    { }
        | shift_expression LEFT_OP additive_expression                                           { $$ = new S_binary_expression($1, $3, 17); }
        | shift_expression RIGHT_OP additive_expression                                          { $$ = new S_binary_expression($1, $3, 18); }
        ;

relational_expression
        : shift_expression                                                                       { }
        | relational_expression '<' shift_expression                                             { $$ = new S_binary_expression($1, $3, 13); }
        | relational_expression '>' shift_expression                                             { $$ = new S_binary_expression($1, $3, 14); }
        | relational_expression LE_OP shift_expression                                           { $$ = new S_binary_expression($1, $3, 15); }
        | relational_expression GE_OP shift_expression                                           { $$ = new S_binary_expression($1, $3, 16); }
        ;

equality_expression
        : relational_expression                                                                  { }
        | equality_expression EQ_OP relational_expression                                        { $$ = new S_binary_expression($1, $3, 3); }
        | equality_expression NE_OP relational_expression                                        { $$ = new S_binary_expression($1, $3, 4); }
        ;

and_expression
        : equality_expression                                                                    { }
        | and_expression '&' equality_expression                                                 { $$ = new S_binary_expression($1, $3, 2); }
        ;

exclusive_or_expression
        : and_expression                                                                         { }
        | exclusive_or_expression '^' and_expression                                             { $$ = new S_binary_expression($1, $3, 5); }
        ;

inclusive_or_expression
        : exclusive_or_expression                                                                { }
        | inclusive_or_expression '|' exclusive_or_expression                                    { $$ = new S_binary_expression($1, $3, 6); }
        ;

logical_and_expression
        : inclusive_or_expression                                                                { }
        | logical_and_expression AND_OP inclusive_or_expression                                  { $$ = new S_binary_expression($1, $3, 7); }
        ;

logical_or_expression
        : logical_and_expression                                                                 { }
        | logical_or_expression OR_OP logical_and_expression                                     { $$ = new S_binary_expression($1, $3, 8); }
        ;

conditional_expression
        : binary_expression                                                                      { $$ = new S_conditional_expression($1); }
        | binary_expression '?' expression ':' conditional_expression                            { $$ = new S_conditional_expression($1, $3, $5); }
        ;
assignment_expression
        : conditional_expression                                                                 { $$ = new S_assignment_expression($1); }
        | unary_expression assignment_operator assignment_expression                             { $$ = new S_assignment_expression($1, $2, $3); }
        ;
assignment_operator
        : '='                                                                                    { $$ = new S_assignment_operator(0); }
        | MUL_ASSIGN                                                                             { $$ = new S_assignment_operator(1); }
        | DIV_ASSIGN                                                                             { $$ = new S_assignment_operator(2); }
        | MOD_ASSIGN                                                                             { $$ = new S_assignment_operator(3); }
        | ADD_ASSIGN                                                                             { $$ = new S_assignment_operator(4); }
        | SUB_ASSIGN                                                                             { $$ = new S_assignment_operator(5); }
        | LEFT_ASSIGN                                                                            { $$ = new S_assignment_operator(6); }
        | RIGHT_ASSIGN                                                                           { $$ = new S_assignment_operator(7); }
        | AND_ASSIGN                                                                             { $$ = new S_assignment_operator(8); }
        | XOR_ASSIGN                                                                             { $$ = new S_assignment_operator(9); }
        | OR_ASSIGN                                                                              { $$ = new S_assignment_operator(10); }
        ;
expression
        : assignment_expression                                                                  { $$ = new S_expression($1, NULL); }
        | expression ',' assignment_expression                                                   { $$ = new S_expression($3, $1); }
        ;
constant_expression
        : conditional_expression                                                                 { $$ = new S_constant_expression($1); }
        ;
declaration
        : declaration_specifiers ';'                                                             { throw "not implemented declaration"; }
        | declaration_specifiers init_declarator_list ';'                                        { $$ = new S_declaration($1, $2); }
        | static_assert_declaration                                                              { $$ = new S_declaration($1); }
        ;
declaration_specifiers
        : storage_class_specifier declaration_specifiers                                         { $$ = new S_declaration_specifiers($1, $2); }
        | storage_class_specifier                                                                { throw "not implemented declaration_specifiers"; }
        | type_specifier declaration_specifiers                                                  { $$ = new S_declaration_specifiers($1, $2); }
        | type_specifier                                                                         { throw "not implemented declaration_specifiers"; }
        | type_qualifier declaration_specifiers                                                  { $$ = new S_declaration_specifiers($1, $2); }
        | type_qualifier                                                                         { throw "not implemented declaration_specifiers"; }
        | function_specifier declaration_specifiers                                              { $$ = new S_declaration_specifiers($1, $2); }
        | function_specifier                                                                     { throw "not implemented declaration_specifiers"; }
        | alignment_specifier declaration_specifiers                                             { $$ = new S_declaration_specifiers($1, $2); }
        | alignment_specifier                                                                    { throw "not implemented declaration_specifiers"; }
        ;
init_declarator_list
        : init_declarator                                                                        { $$ = new S_init_declarator_list($1, NULL); }
        | init_declarator_list ',' init_declarator                                               { $$ = new S_init_declarator_list($3, $1); }
        ;
init_declarator
        : declarator '=' initializer                                                             { $$ = new S_init_declarator($1, $3, 0); }
        | declarator                                                                             { $$ = new S_init_declarator($1, NULL, 1); }
        ;
storage_class_specifier
        : TYPEDEF                                                                                { $$ = new S_storage_class_specifier(0); }
        | EXTERN                                                                                 { $$ = new S_storage_class_specifier(1); }
        | STATIC                                                                                 { $$ = new S_storage_class_specifier(2); }
        | THREAD_LOCAL                                                                           { $$ = new S_storage_class_specifier(3); }
        | AUTO                                                                                   { $$ = new S_storage_class_specifier(4); }
        | REGISTER                                                                               { $$ = new S_storage_class_specifier(5); }
        ;
type_specifier
        : VOID                                                                                   { $$ = new S_type_specifier(0); }
        | CHAR                                                                                   { $$ = new S_type_specifier(1); }
        | SHORT                                                                                  { $$ = new S_type_specifier(2); }
        | INT                                                                                    { $$ = new S_type_specifier(3); }
        | LONG                                                                                   { $$ = new S_type_specifier(4); }
        | FLOAT                                                                                  { $$ = new S_type_specifier(5); }
        | DOUBLE                                                                                 { $$ = new S_type_specifier(6); }
        | SIGNED                                                                                 { $$ = new S_type_specifier(7); }
        | UNSIGNED                                                                               { $$ = new S_type_specifier(8); }
        | BOOL                                                                                   { $$ = new S_type_specifier(9); }
        | COMPLEX                                                                                { $$ = new S_type_specifier(10); }
        | IMAGINARY                                                                              { $$ = new S_type_specifier(11); }
        | atomic_type_specifier                                                                  { $$ = new S_type_specifier($1); }
        | struct_or_union_specifier                                                              { $$ = new S_type_specifier($1); }
        | enum_specifier                                                                         { $$ = new S_type_specifier($1); }
        | TYPEDEF_NAME                                                                           { $$ = new S_type_specifier(15); }
        ;
struct_or_union_specifier
        : struct_or_union '{' struct_declaration_list '}'                                        { $$ = new S_struct_or_union_specifier($1, $3, NULL, 0); }
        | struct_or_union IDENTIFIER '{' struct_declaration_list '}'                             { $$ = new S_struct_or_union_specifier($1, $4, $2, 1); }
        | struct_or_union IDENTIFIER                                                             { $$ = new S_struct_or_union_specifier($1, NULL, $2, 2); }
        ;
struct_or_union
        : STRUCT                                                                                 { $$ = new S_struct_or_union(0); }
        | UNION                                                                                  { $$ = new S_struct_or_union(1); }
        ;
struct_declaration_list
        : struct_declaration                                                                     { $$ = new S_struct_declaration_list($1, NULL); }
        | struct_declaration_list struct_declaration                                             { $$ = new S_struct_declaration_list($2, $1); }
        ;
struct_declaration
        : specifier_qualifier_list ';'                                                           { $$ = new S_struct_declaration($1); }
        | specifier_qualifier_list struct_declarator_list ';'                                    { $$ = new S_struct_declaration($1, $2); }
        | static_assert_declaration                                                              { $$ = new S_struct_declaration($1); }
        ;
specifier_qualifier_list
        : type_specifier specifier_qualifier_list                                                { $$ = new S_specifier_qualifier_list($1, $2); }
        | type_specifier                                                                         { $$ = new S_specifier_qualifier_list($1); }
        | type_qualifier specifier_qualifier_list                                                { $$ = new S_specifier_qualifier_list($1, $2); }
        | type_qualifier                                                                         { $$ = new S_specifier_qualifier_list($1); }
        ;
struct_declarator_list
        : struct_declarator                                                                      { $$ = new S_struct_declarator_list($1, NULL); }
        | struct_declarator_list ',' struct_declarator                                           { $$ = new S_struct_declarator_list($3, $1); }
        ;
struct_declarator
        : ':' constant_expression                                                                { $$ = new S_struct_declarator($2, NULL, 0); }
        | declarator ':' constant_expression                                                     { $$ = new S_struct_declarator($3, $1, 1); }
        | declarator                                                                             { $$ = new S_struct_declarator(NULL, $1, 2); }
        ;
enum_specifier
        : ENUM '{' enumerator_list '}'                                                           { $$ = new S_enum_specifier($3, NULL, 0); }
        | ENUM '{' enumerator_list ',' '}'                                                       { throw "not implemented enum_specifier"; }
        | ENUM IDENTIFIER '{' enumerator_list '}'                                                { $$ = new S_enum_specifier($4, $2, 2); }
        | ENUM IDENTIFIER '{' enumerator_list ',' '}'                                            { throw "not implemented enum_specifier"; }
        | ENUM IDENTIFIER                                                                        { $$ = new S_enum_specifier(NULL, $2, 4); }
        ;
enumerator_list
        : enumerator                                                                             { $$ = new S_enumerator_list($1, NULL); }
        | enumerator_list ',' enumerator                                                         { $$ = new S_enumerator_list($3, $1); }
        ;
enumerator
        : enumeration_constant '=' constant_expression                                           { $$ = new S_enumerator($1, $3); }
        | enumeration_constant                                                                   { $$ = new S_enumerator($1, NULL); }
        ;
atomic_type_specifier
        : ATOMIC '(' type_name ')'                                                               { $$ = new S_atomic_type_specifier($3); }
        ;
type_qualifier
        : CONST                                                                                  { $$ = new S_type_qualifier(0); }
        | RESTRICT                                                                               { $$ = new S_type_qualifier(1); }
        | VOLATILE                                                                               { $$ = new S_type_qualifier(2); }
        | ATOMIC                                                                                 { $$ = new S_type_qualifier(3); }
        ;
function_specifier
        : INLINE                                                                                 { $$ = new S_function_specifier(0); }
        | NORETURN                                                                               { $$ = new S_function_specifier(1); }
        ;
alignment_specifier
        : ALIGNAS '(' type_name ')'                                                              { $$ = new S_alignment_specifier($3); }
        | ALIGNAS '(' constant_expression ')'                                                    { $$ = new S_alignment_specifier($3); }
        ;
declarator
        : pointer direct_declarator                                                              { $$ = new S_declarator($1, $2, 0); }
        | direct_declarator                                                                      { $$ = new S_declarator(NULL, $1, 1); }
        ;
direct_declarator
        : IDENTIFIER                                                                             { $$ = new S_direct_declarator($1); }
        | '(' declarator ')'                                                                     { $$ = new S_direct_declarator($2); }
        | direct_declarator '[' ']'                                                              { $$ = new S_direct_declarator($1, 2); }
        | direct_declarator '[' '*' ']'                                                          { $$ = new S_direct_declarator($1, 3); }
        | direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'             { $$ = new S_direct_declarator($1, $4, $5, 4); }
        | direct_declarator '[' STATIC assignment_expression ']'                                 { $$ = new S_direct_declarator($1, $4, 5); }
        | direct_declarator '[' type_qualifier_list '*' ']'                                      { $$ = new S_direct_declarator($1, $3, 6); }
        | direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'             { $$ = new S_direct_declarator($1, $3, $5, 7); }
        | direct_declarator '[' type_qualifier_list assignment_expression ']'                    { $$ = new S_direct_declarator($1, $3, $4, 8); }
        | direct_declarator '[' type_qualifier_list ']'                                          { $$ = new S_direct_declarator($1, $3, 9); }
        | direct_declarator '[' assignment_expression ']'                                        { $$ = new S_direct_declarator($1, $3, 10); }
        | direct_declarator '(' parameter_type_list ')'                                          { $$ = new S_direct_declarator($1, $3); }
        | direct_declarator '(' ')'                                                              { $$ = new S_direct_declarator($1, 12); }
        | direct_declarator '(' identifier_list ')'                                              { $$ = new S_direct_declarator($1, $3); }
        ;
pointer
        : '*' type_qualifier_list pointer                                                        { $$ = new S_pointer($2, $3); }
        | '*' type_qualifier_list                                                                { $$ = new S_pointer($2, NULL); }
        | '*' pointer                                                                            { $$ = new S_pointer(NULL, $2); }
        | '*'                                                                                    { $$ = new S_pointer(NULL, NULL); }
        ;
type_qualifier_list
        : type_qualifier                                                                         { $$ = new S_type_qualifier_list($1, NULL); }
        | type_qualifier_list type_qualifier                                                     { $$ = new S_type_qualifier_list($2, $1); }
        ;
parameter_type_list
        : parameter_list ',' ELLIPSIS                                                            { $$ = new S_parameter_type_list($1, 0); }
        | parameter_list                                                                         { $$ = new S_parameter_type_list($1, 1); }
        ;
parameter_list
        : parameter_declaration                                                                  { $$ = new S_parameter_list($1, NULL); }
        | parameter_list ',' parameter_declaration                                               { $$ = new S_parameter_list($3, $1); }
        ;
parameter_declaration
        : declaration_specifiers declarator                                                      { $$ = new S_parameter_declaration($1, $2); }
        | declaration_specifiers abstract_declarator                                             { $$ = new S_parameter_declaration($1, $2); }
        | declaration_specifiers                                                                 { $$ = new S_parameter_declaration($1); }
        ;
identifier_list
        : IDENTIFIER                                                                             { $$ = new S_identifier_list($1, NULL); }
        | identifier_list ',' IDENTIFIER                                                         { $$ = new S_identifier_list($3, $1); }
        ;
type_name
        : specifier_qualifier_list abstract_declarator                                           { $$ = new S_type_name($1, $2); }
        | specifier_qualifier_list                                                               { $$ = new S_type_name($1, NULL); }
        ;
abstract_declarator
        : pointer direct_abstract_declarator                                                     { $$ = new S_abstract_declarator($1, $2); }
        | pointer                                                                                { $$ = new S_abstract_declarator($1, NULL); }
        | direct_abstract_declarator                                                             { $$ = new S_abstract_declarator(NULL, $1); }
        ;
direct_abstract_declarator
        : '(' abstract_declarator ')'                                                            { $$ = new S_direct_abstract_declarator($2); }
        | '[' ']'                                                                                { $$ = new S_direct_abstract_declarator(1); }
        | '[' '*' ']'                                                                            { $$ = new S_direct_abstract_declarator(2); }
        | '[' STATIC type_qualifier_list assignment_expression ']'                               { $$ = new S_direct_abstract_declarator($3, $4, 3); }
        | '[' STATIC assignment_expression ']'                                                   { $$ = new S_direct_abstract_declarator($3, 4); }
        | '[' type_qualifier_list STATIC assignment_expression ']'                               { $$ = new S_direct_abstract_declarator($2, $4, 5); }
        | '[' type_qualifier_list assignment_expression ']'                                      { $$ = new S_direct_abstract_declarator($2, $3, 6); }
        | '[' type_qualifier_list ']'                                                            { $$ = new S_direct_abstract_declarator($2); }
        | '[' assignment_expression ']'                                                          { $$ = new S_direct_abstract_declarator($2, 8); }
        | direct_abstract_declarator '[' ']'                                                     { $$ = new S_direct_abstract_declarator($1, 9); }
        | direct_abstract_declarator '[' '*' ']'                                                 { $$ = new S_direct_abstract_declarator($1, 10); }
        | direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'    { $$ = new S_direct_abstract_declarator($1, $4, $5, 11); }
        | direct_abstract_declarator '[' STATIC assignment_expression ']'                        { $$ = new S_direct_abstract_declarator($1, $4, 12); }
        | direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'           { $$ = new S_direct_abstract_declarator($1, $3, $4, 13); }
        | direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'    { $$ = new S_direct_abstract_declarator($1, $3, $5, 14); }
        | direct_abstract_declarator '[' type_qualifier_list ']'                                 { $$ = new S_direct_abstract_declarator($1, $3); }
        | direct_abstract_declarator '[' assignment_expression ']'                               { $$ = new S_direct_abstract_declarator($1, $3, 16); }
        | '(' ')'                                                                                { $$ = new S_direct_abstract_declarator(17); }
        | '(' parameter_type_list ')'                                                            { $$ = new S_direct_abstract_declarator($2); }
        | direct_abstract_declarator '(' ')'                                                     { $$ = new S_direct_abstract_declarator($1, 19); }
        | direct_abstract_declarator '(' parameter_type_list ')'                                 { $$ = new S_direct_abstract_declarator($1, $3); }
        ;
initializer
        : '{' initializer_list '}'                                                               { $$ = new S_initializer($2); }
        | '{' initializer_list ',' '}'                                                           { throw "not implemented initializer"; }
        | assignment_expression                                                                  { $$ = new S_initializer($1); }
        ;
initializer_list
        : designation initializer                                                                { $$ = new S_initializer_list($1, $2, NULL); }
        | initializer                                                                            { $$ = new S_initializer_list(NULL, $1, NULL); }
        | initializer_list ',' designation initializer                                           { $$ = new S_initializer_list($3, $4, $1); }
        | initializer_list ',' initializer                                                       { $$ = new S_initializer_list(NULL, $3, $1); }
        ;
designation
        : designator_list '='                                                                    { $$ = new S_designation($1); }
        ;
designator_list
        : designator                                                                             { $$ = new S_designator_list($1, NULL); }
        | designator_list designator                                                             { $$ = new S_designator_list($2, $1); }
        ;
designator
        : '[' constant_expression ']'                                                            { $$ = new S_designator($2); }
        | '.' IDENTIFIER                                                                         { $$ = new S_designator($2); }
        ;
static_assert_declaration
        : STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'                       { $$ = new S_static_assert_declaration($3, $5); }
        ;
statement
        : labeled_statement                                                                      { $$ = new S_statement($1); }
        | compound_statement                                                                     { $$ = new S_statement($1); }
        | expression_statement                                                                   { $$ = new S_statement($1); }
        | selection_statement                                                                    { $$ = new S_statement($1); }
        | iteration_statement                                                                    { $$ = new S_statement($1); }
        | jump_statement                                                                         { $$ = new S_statement($1); }
        ;
labeled_statement
        : IDENTIFIER ':' statement                                                               { $$ = new S_labeled_statement($1, $3); }
        | CASE constant_expression ':' statement                                                 { $$ = new S_labeled_statement($2, $4); }
        | DEFAULT ':' statement                                                                  { $$ = new S_labeled_statement($3); }
        ;
compound_statement
        : '{' '}'                                                                                { $$ = new S_compound_statement(NULL); }
        | '{' block_item_list '}'                                                                { $$ = new S_compound_statement($2); }
        ;
block_item_list
        : block_item                                                                             { $$ = new S_block_item_list($1, NULL); }
        | block_item_list block_item                                                             { $$ = new S_block_item_list($2, $1); }
        ;
block_item
        : declaration                                                                            { $$ = new S_block_item($1); }
        | statement                                                                              { $$ = new S_block_item($1); }
        ;
expression_statement
        : ';'                                                                                    { $$ = new S_expression_statement(NULL); }
        | expression ';'                                                                         { $$ = new S_expression_statement($1); }
        ;
selection_statement
        : IF '(' expression ')' statement ELSE statement                                         { $$ = new S_selection_statement($3, $5, $7); }
        | IF '(' expression ')' statement                                                        { $$ = new S_selection_statement($3, $5, 1); }
        | SWITCH '(' expression ')' statement                                                    { $$ = new S_selection_statement($3, $5, 2); }
        ;
iteration_statement
        : WHILE '(' expression ')' statement                                                     { $$ = new S_iteration_statement($3, $5); }
        | DO statement WHILE '(' expression ')' ';'                                              { $$ = new S_iteration_statement($2, $5); }
        | FOR '(' expression_statement expression_statement ')' statement                        { $$ = new S_iteration_statement($3, $4, $6); }
        | FOR '(' expression_statement expression_statement expression ')' statement             { $$ = new S_iteration_statement($3, $4, $5, $7); }
        | FOR '(' declaration expression_statement ')' statement                                 { $$ = new S_iteration_statement($3, $4, $6); }
        | FOR '(' declaration expression_statement expression ')' statement                      { $$ = new S_iteration_statement($3, $4, $5, $7); }
        ;
jump_statement
        : GOTO IDENTIFIER ';'                                                                    { $$ = new S_jump_statement($2); }
        | CONTINUE ';'                                                                           { $$ = new S_jump_statement(1); }
        | BREAK ';'                                                                              { $$ = new S_jump_statement(2); }
        | RETURN ';'                                                                             { $$ = new S_jump_statement(3); }
        | RETURN expression ';'                                                                  { $$ = new S_jump_statement($2); }
        ;
translation_unit
        : external_declaration                                                                   { $$ = new S_translation_unit($1, NULL); }
        | translation_unit external_declaration                                                  { $$ = new S_translation_unit($2, $1); }
        ;
external_declaration
        : function_definition                                                                    { $$ = new S_external_declaration($1); }
        | declaration                                                                            { $$ = new S_external_declaration($1); }
        ;
function_definition
        : declaration_specifiers declarator declaration_list compound_statement                  { $$ = new S_function_definition($1, $2, $3, $4); }
        | declaration_specifiers declarator compound_statement                                   { $$ = new S_function_definition($1, $2, NULL, $3); }
        ;
declaration_list
        : declaration                                                                            { $$ = new S_declaration_list($1, NULL); }
        | declaration_list declaration                                                           { $$ = new S_declaration_list($2, $1); }
        ;

