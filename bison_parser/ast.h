#include <bits/stdc++.h>
using namespace std;

typedef char* T_intval;
typedef char* T_strval;
typedef char* T_floatval;
void print_tab(int tab);
struct S_abstract_declarator;
struct S_alignment_specifier;
struct S_argument_expression_list;
struct S_assignment_expression;
struct S_assignment_operator;
struct S_atomic_type_specifier;
struct S_binary_expression;
struct S_block_item;
struct S_block_item_list;
struct S_compound_statement;
struct S_conditional_expression;
struct S_constant;
struct S_constant_expression;
struct S_declaration;
struct S_declaration_list;
struct S_declaration_specifiers;
struct S_declarator;
struct S_designation;
struct S_designator;
struct S_designator_list;
struct S_direct_abstract_declarator;
struct S_direct_declarator;
struct S_enum_specifier;
struct S_enumeration_constant;
struct S_enumerator;
struct S_enumerator_list;
struct S_expression;
struct S_expression_statement;
struct S_external_declaration;
struct S_function_definition;
struct S_function_specifier;
struct S_generic_assoc_list;
struct S_generic_association;
struct S_generic_selection;
struct S_identifier_list;
struct S_init_declarator;
struct S_init_declarator_list;
struct S_initializer;
struct S_initializer_list;
struct S_iteration_statement;
struct S_jump_statement;
struct S_labeled_statement;
struct S_parameter_declaration;
struct S_parameter_list;
struct S_parameter_type_list;
struct S_pointer;
struct S_primary_expression;
struct S_selection_statement;
struct S_specifier_qualifier_list;
struct S_statement;
struct S_static_assert_declaration;
struct S_storage_class_specifier;
struct S_string;
struct S_struct_declaration;
struct S_struct_declaration_list;
struct S_struct_declarator;
struct S_struct_declarator_list;
struct S_struct_or_union;
struct S_struct_or_union_specifier;
struct S_translation_unit;
struct S_type_name;
struct S_type_qualifier;
struct S_type_qualifier_list;
struct S_type_specifier;
struct S_unary_expression;
struct S_unary_operator;
typedef struct S_abstract_declarator* T_abstract_declarator;
typedef struct S_alignment_specifier* T_alignment_specifier;
typedef struct S_argument_expression_list* T_argument_expression_list;
typedef struct S_assignment_expression* T_assignment_expression;
typedef struct S_assignment_operator* T_assignment_operator;
typedef struct S_atomic_type_specifier* T_atomic_type_specifier;
typedef struct S_binary_expression* T_binary_expression;
typedef struct S_block_item* T_block_item;
typedef struct S_block_item_list* T_block_item_list;
typedef struct S_compound_statement* T_compound_statement;
typedef struct S_conditional_expression* T_conditional_expression;
typedef struct S_constant* T_constant;
typedef struct S_constant_expression* T_constant_expression;
typedef struct S_declaration* T_declaration;
typedef struct S_declaration_list* T_declaration_list;
typedef struct S_declaration_specifiers* T_declaration_specifiers;
typedef struct S_declarator* T_declarator;
typedef struct S_designation* T_designation;
typedef struct S_designator* T_designator;
typedef struct S_designator_list* T_designator_list;
typedef struct S_direct_abstract_declarator* T_direct_abstract_declarator;
typedef struct S_direct_declarator* T_direct_declarator;
typedef struct S_enum_specifier* T_enum_specifier;
typedef struct S_enumeration_constant* T_enumeration_constant;
typedef struct S_enumerator* T_enumerator;
typedef struct S_enumerator_list* T_enumerator_list;
typedef struct S_expression* T_expression;
typedef struct S_expression_statement* T_expression_statement;
typedef struct S_external_declaration* T_external_declaration;
typedef struct S_function_definition* T_function_definition;
typedef struct S_function_specifier* T_function_specifier;
typedef struct S_generic_assoc_list* T_generic_assoc_list;
typedef struct S_generic_association* T_generic_association;
typedef struct S_generic_selection* T_generic_selection;
typedef struct S_identifier_list* T_identifier_list;
typedef struct S_init_declarator* T_init_declarator;
typedef struct S_init_declarator_list* T_init_declarator_list;
typedef struct S_initializer* T_initializer;
typedef struct S_initializer_list* T_initializer_list;
typedef struct S_iteration_statement* T_iteration_statement;
typedef struct S_jump_statement* T_jump_statement;
typedef struct S_labeled_statement* T_labeled_statement;
typedef struct S_parameter_declaration* T_parameter_declaration;
typedef struct S_parameter_list* T_parameter_list;
typedef struct S_parameter_type_list* T_parameter_type_list;
typedef struct S_pointer* T_pointer;
typedef struct S_primary_expression* T_primary_expression;
typedef struct S_selection_statement* T_selection_statement;
typedef struct S_specifier_qualifier_list* T_specifier_qualifier_list;
typedef struct S_statement* T_statement;
typedef struct S_static_assert_declaration* T_static_assert_declaration;
typedef struct S_storage_class_specifier* T_storage_class_specifier;
typedef struct S_string* T_string;
typedef struct S_struct_declaration* T_struct_declaration;
typedef struct S_struct_declaration_list* T_struct_declaration_list;
typedef struct S_struct_declarator* T_struct_declarator;
typedef struct S_struct_declarator_list* T_struct_declarator_list;
typedef struct S_struct_or_union* T_struct_or_union;
typedef struct S_struct_or_union_specifier* T_struct_or_union_specifier;
typedef struct S_translation_unit* T_translation_unit;
typedef struct S_type_name* T_type_name;
typedef struct S_type_qualifier* T_type_qualifier;
typedef struct S_type_qualifier_list* T_type_qualifier_list;
typedef struct S_type_specifier* T_type_specifier;
typedef struct S_unary_expression* T_unary_expression;
typedef struct S_unary_operator* T_unary_operator;
struct S_abstract_declarator {
	T_pointer v0;
	T_direct_abstract_declarator v1;
	S_abstract_declarator(T_pointer a0, T_direct_abstract_declarator a1);
	void print(int tab);
};
struct S_alignment_specifier {
	enum {TYPE_NAME = 0, CONST_EXPR = 1, } kind;
	union {
		struct { T_type_name v0; } type_name;
		struct { T_constant_expression v0; } const_expr;
	};
	S_alignment_specifier(T_constant_expression a0);
	S_alignment_specifier(T_type_name a0);
	void print(int tab);
};
struct S_argument_expression_list {
	T_assignment_expression v0;
	T_argument_expression_list v1;
	S_argument_expression_list(T_assignment_expression a0, T_argument_expression_list a1);
	void print(int tab);
};
struct S_assignment_expression {
	enum {NONE = 0, ASSIGNMENT = 1, } kind;
	union {
		struct { T_conditional_expression v0; } none;
		struct { T_unary_expression v0; T_assignment_operator v1; T_assignment_expression v2; } assignment;
	};
	S_assignment_expression(T_conditional_expression a0);
	S_assignment_expression(T_unary_expression a0, T_assignment_operator a1, T_assignment_expression a2);
	void print(int tab);
};
struct S_assignment_operator {
	enum {ASS = 0, MUL_ASS = 1, DIV_ASS = 2, MOD_ASS = 3, ADD_ASS = 4, SUB_ASS = 5, LEFT_ASS = 6, RIGHT_ASS = 7, AND_ASS = 8, XOR_ASS = 9, OR_ASS = 10, } kind;
	S_assignment_operator(int enum_kind);
	void print(int tab);
};
struct S_atomic_type_specifier {
	T_type_name v0;
	S_atomic_type_specifier (T_type_name a0);
	void print(int tab);
};
struct S_binary_expression {
	enum {ADD = 0, SUB = 1, BIT_AND = 2, EQU = 3, NEQ = 4, BIT_XOR = 5, BIT_OR = 6, LOGIC_AND = 7, LOGIC_OR = 8, NONE = 9, MULT = 10, DIV = 11, MOD = 12, LTH = 13, GTH = 14, LTE = 15, GTE = 16, LEFT_SHIFT = 17, RIGHT_SHIFT = 18, } kind;
	union {
		struct { T_binary_expression v0; T_binary_expression v1; } add;
		struct { T_binary_expression v0; T_binary_expression v1; } sub;
		struct { T_binary_expression v0; T_binary_expression v1; } bit_and;
		struct { T_binary_expression v0; T_binary_expression v1; } equ;
		struct { T_binary_expression v0; T_binary_expression v1; } neq;
		struct { T_binary_expression v0; T_binary_expression v1; } bit_xor;
		struct { T_binary_expression v0; T_binary_expression v1; } bit_or;
		struct { T_binary_expression v0; T_binary_expression v1; } logic_and;
		struct { T_binary_expression v0; T_binary_expression v1; } logic_or;
		struct { T_unary_expression v0; } none;
		struct { T_binary_expression v0; T_unary_expression v1; } mult;
		struct { T_binary_expression v0; T_unary_expression v1; } div;
		struct { T_binary_expression v0; T_unary_expression v1; } mod;
		struct { T_binary_expression v0; T_binary_expression v1; } lth;
		struct { T_binary_expression v0; T_binary_expression v1; } gth;
		struct { T_binary_expression v0; T_binary_expression v1; } lte;
		struct { T_binary_expression v0; T_binary_expression v1; } gte;
		struct { T_binary_expression v0; T_binary_expression v1; } left_shift;
		struct { T_binary_expression v0; T_binary_expression v1; } right_shift;
	};
	S_binary_expression(T_binary_expression a0, T_binary_expression a1, int enum_kind);
	S_binary_expression(T_binary_expression a0, T_unary_expression a1, int enum_kind);
	S_binary_expression(T_unary_expression a0);
	void print(int tab);
};
struct S_block_item {
	enum {DECLARATION = 0, STATEMENT = 1, } kind;
	union {
		struct { T_declaration v0; } declaration;
		struct { T_statement v0; } statement;
	};
	S_block_item(T_declaration a0);
	S_block_item(T_statement a0);
	void print(int tab);
};
struct S_block_item_list {
	T_block_item v0;
	T_block_item_list v1;
	S_block_item_list(T_block_item a0, T_block_item_list a1);
	void print(int tab);
};
struct S_compound_statement {
	T_block_item_list v0;
	S_compound_statement(T_block_item_list a0);
	void print(int tab);
};
struct S_conditional_expression {
	enum {BINARY = 0, TERRINARY = 1, } kind;
	union {
		struct { T_binary_expression v0; } binary;
		struct { T_binary_expression v0; T_expression v1; T_conditional_expression v2; } terrinary;
	};
	S_conditional_expression(T_binary_expression a0);
	S_conditional_expression(T_binary_expression a0, T_expression a1, T_conditional_expression a2);
	void print(int tab);
};
struct S_constant {
	enum {INTEGER = 0, FLOAT_ = 1, ENUM_CONST = 2, } kind;
	union {
		struct { T_intval v0; } integer;
		struct { T_floatval v0; } float_;
	};
	S_constant();
	S_constant(T_floatval a0);
	S_constant(T_intval a0);
	void print(int tab);
};
struct S_constant_expression {
	T_conditional_expression v0;
	S_constant_expression (T_conditional_expression a0);
	void print(int tab);
};
struct S_declaration {
	enum {NORMAL = 0, STATIC_ASSERT = 1, } kind;
	union {
		struct { T_declaration_specifiers v0; T_init_declarator_list v1; } normal;
		struct { T_static_assert_declaration v0; } static_assert;
	};
	S_declaration(T_declaration_specifiers a0, T_init_declarator_list a1);
	S_declaration(T_static_assert_declaration a0);
	void print(int tab);
};
struct S_declaration_list {
	T_declaration v0;
	T_declaration_list v1;
	S_declaration_list(T_declaration a0, T_declaration_list a1);
	void print(int tab);
};
struct S_declaration_specifiers {
	enum {STORAGE = 0, TYPE_SPEC = 1, TYPE_QUAL = 2, FUNCTION_SPEC = 3, ALIGHTMENT_SPEC = 4, } kind;
	union {
		struct { T_storage_class_specifier v0; T_declaration_specifiers v1; } storage;
		struct { T_type_specifier v0; T_declaration_specifiers v1; } type_spec;
		struct { T_type_qualifier v0; T_declaration_specifiers v1; } type_qual;
		struct { T_function_specifier v0; T_declaration_specifiers v1; } function_spec;
		struct { T_alignment_specifier v0; T_declaration_specifiers v1; } alightment_spec;
	};
	S_declaration_specifiers(T_alignment_specifier a0, T_declaration_specifiers a1);
	S_declaration_specifiers(T_function_specifier a0, T_declaration_specifiers a1);
	S_declaration_specifiers(T_storage_class_specifier a0, T_declaration_specifiers a1);
	S_declaration_specifiers(T_type_qualifier a0, T_declaration_specifiers a1);
	S_declaration_specifiers(T_type_specifier a0, T_declaration_specifiers a1);
	void print(int tab);
};
struct S_declarator {
	enum {POINTER = 0, NO_POINTER = 1, } kind;
	T_pointer v0;
	T_direct_declarator v1;
	S_declarator(T_pointer a0, T_direct_declarator a1, int enum_kind);
	void print(int tab);
};
struct S_designation {
	T_designator_list v0;
	S_designation (T_designator_list a0);
	void print(int tab);
};
struct S_designator {
	enum {INDEX = 0, DOT = 1, } kind;
	union {
		struct { T_constant_expression v0; } index;
		struct { T_strval v0; } dot;
	};
	S_designator(T_constant_expression a0);
	S_designator(T_strval a0);
	void print(int tab);
};
struct S_designator_list {
	T_designator v0;
	T_designator_list v1;
	S_designator_list(T_designator a0, T_designator_list a1);
	void print(int tab);
};
struct S_direct_abstract_declarator {
	enum {DECL1 = 0, DECL2 = 1, DECL3 = 2, DECL4 = 3, DECL5 = 4, DECL6 = 5, DECL7 = 6, DECL8 = 7, DECL9 = 8, DECL10 = 9, DECL11 = 10, DECL12 = 11, DECL13 = 12, DECL14 = 13, DECL15 = 14, DECL16 = 15, DECL17 = 16, DECL18 = 17, DECL19 = 18, DECL20 = 19, DECL21 = 20, } kind;
	union {
		struct { T_abstract_declarator v0; } decl1;
		struct { T_type_qualifier_list v0; T_assignment_expression v1; } decl4;
		struct { T_assignment_expression v0; } decl5;
		struct { T_type_qualifier_list v0; T_assignment_expression v1; } decl6;
		struct { T_type_qualifier_list v0; T_assignment_expression v1; } decl7;
		struct { T_type_qualifier_list v0; } decl8;
		struct { T_assignment_expression v0; } decl9;
		struct { T_direct_abstract_declarator v0; } decl10;
		struct { T_direct_abstract_declarator v0; } decl11;
		struct { T_direct_abstract_declarator v0; T_type_qualifier_list v1; T_assignment_expression v2; } decl12;
		struct { T_direct_abstract_declarator v0; T_assignment_expression v1; } decl13;
		struct { T_direct_abstract_declarator v0; T_type_qualifier_list v1; T_assignment_expression v2; } decl14;
		struct { T_direct_abstract_declarator v0; T_type_qualifier_list v1; T_assignment_expression v2; } decl15;
		struct { T_direct_abstract_declarator v0; T_type_qualifier_list v1; } decl16;
		struct { T_direct_abstract_declarator v0; T_assignment_expression v1; } decl17;
		struct { T_parameter_type_list v0; } decl19;
		struct { T_direct_abstract_declarator v0; } decl20;
		struct { T_direct_abstract_declarator v0; T_parameter_type_list v1; } decl21;
	};
	S_direct_abstract_declarator(int enum_kind);
	S_direct_abstract_declarator(T_abstract_declarator a0);
	S_direct_abstract_declarator(T_assignment_expression a0, int enum_kind);
	S_direct_abstract_declarator(T_direct_abstract_declarator a0, int enum_kind);
	S_direct_abstract_declarator(T_direct_abstract_declarator a0, T_assignment_expression a1, int enum_kind);
	S_direct_abstract_declarator(T_direct_abstract_declarator a0, T_parameter_type_list a1);
	S_direct_abstract_declarator(T_direct_abstract_declarator a0, T_type_qualifier_list a1);
	S_direct_abstract_declarator(T_direct_abstract_declarator a0, T_type_qualifier_list a1, T_assignment_expression a2, int enum_kind);
	S_direct_abstract_declarator(T_parameter_type_list a0);
	S_direct_abstract_declarator(T_type_qualifier_list a0);
	S_direct_abstract_declarator(T_type_qualifier_list a0, T_assignment_expression a1, int enum_kind);
	void print(int tab);
};
struct S_direct_declarator {
	enum {IDENTIFIER = 0, DECL1 = 1, DECL2 = 2, DECL3 = 3, DECL4 = 4, DECL5 = 5, DECL6 = 6, DECL7 = 7, DECL8 = 8, DECL9 = 9, DECL10 = 10, DECL11 = 11, DECL12 = 12, DECL12 = 13, } kind;
	union {
		struct { T_strval v0; } identifier;
		struct { T_declarator v0; } decl1;
		struct { T_direct_declarator v0; } decl2;
		struct { T_direct_declarator v0; } decl3;
		struct { T_direct_declarator v0; T_type_qualifier_list v1; T_assignment_expression v2; } decl4;
		struct { T_direct_declarator v0; T_assignment_expression v1; } decl5;
		struct { T_direct_declarator v0; T_type_qualifier_list v1; } decl6;
		struct { T_direct_declarator v0; T_type_qualifier_list v1; T_assignment_expression v2; } decl7;
		struct { T_direct_declarator v0; T_type_qualifier_list v1; T_assignment_expression v2; } decl8;
		struct { T_direct_declarator v0; T_type_qualifier_list v1; } decl9;
		struct { T_direct_declarator v0; T_assignment_expression v1; } decl10;
		struct { T_direct_declarator v0; T_parameter_type_list v1; } decl11;
		struct { T_direct_declarator v0; } decl12;
		struct { T_direct_declarator v0; T_identifier_list v1; } decl12;
	};
	S_direct_declarator(T_declarator a0);
	S_direct_declarator(T_direct_declarator a0, int enum_kind);
	S_direct_declarator(T_direct_declarator a0, T_assignment_expression a1, int enum_kind);
	S_direct_declarator(T_direct_declarator a0, T_identifier_list a1);
	S_direct_declarator(T_direct_declarator a0, T_parameter_type_list a1);
	S_direct_declarator(T_direct_declarator a0, T_type_qualifier_list a1, int enum_kind);
	S_direct_declarator(T_direct_declarator a0, T_type_qualifier_list a1, T_assignment_expression a2, int enum_kind);
	S_direct_declarator(T_strval a0);
	void print(int tab);
};
struct S_enum_specifier {
	enum {NO_IDEN = 0, WITH_IDEN = 1, DECL = 2, } kind;
	T_enumerator_list v0;
	T_strval v1;
	S_enum_specifier(T_enumerator_list a0, T_strval a1, int enum_kind);
	void print(int tab);
};
struct S_enumeration_constant {
	T_strval v0;
	S_enumeration_constant (T_strval a0);
	void print(int tab);
};
struct S_enumerator {
	T_enumeration_constant v0;
	T_constant_expression v1;
	S_enumerator(T_enumeration_constant a0, T_constant_expression a1);
	void print(int tab);
};
struct S_enumerator_list {
	T_enumerator v0;
	T_enumerator_list v1;
	S_enumerator_list(T_enumerator a0, T_enumerator_list a1);
	void print(int tab);
};
struct S_expression {
	T_assignment_expression v0;
	T_expression v1;
	S_expression(T_assignment_expression a0, T_expression a1);
	void print(int tab);
};
struct S_expression_statement {
	T_expression v0;
	S_expression_statement(T_expression a0);
	void print(int tab);
};
struct S_external_declaration {
	enum {FUNCTION_DEFINITION = 0, DECLARATION = 1, } kind;
	union {
		struct { T_function_definition v0; } function_definition;
		struct { T_declaration v0; } declaration;
	};
	S_external_declaration(T_declaration a0);
	S_external_declaration(T_function_definition a0);
	void print(int tab);
};
struct S_function_definition {
	T_declaration_specifiers v0;
	T_declarator v1;
	T_declaration_list v2;
	T_compound_statement v3;
	S_function_definition(T_declaration_specifiers a0, T_declarator a1, T_declaration_list a2, T_compound_statement a3);
	void print(int tab);
};
struct S_function_specifier {
	enum {INLINE = 0, NORETURN = 1, } kind;
	S_function_specifier(int enum_kind);
	void print(int tab);
};
struct S_generic_assoc_list {
	T_generic_association v0;
	T_generic_assoc_list v1;
	S_generic_assoc_list(T_generic_association a0, T_generic_assoc_list a1);
	void print(int tab);
};
struct S_generic_association {
	enum {TYPE_NAME = 0, DEFAULT = 1, } kind;
	T_type_name v0;
	T_assignment_expression v1;
	S_generic_association(T_type_name a0, T_assignment_expression a1, int enum_kind);
	void print(int tab);
};
struct S_generic_selection {
	T_assignment_expression v0;
	T_generic_assoc_list v1;
	S_generic_selection (T_assignment_expression a0, T_generic_assoc_list a1);
	void print(int tab);
};
struct S_identifier_list {
	T_strval v0;
	T_identifier_list v1;
	S_identifier_list(T_strval a0, T_identifier_list a1);
	void print(int tab);
};
struct S_init_declarator {
	enum {INITIALISED = 0, UNINITIALISED = 1, } kind;
	T_declarator v0;
	T_initializer v1;
	S_init_declarator(T_declarator a0, T_initializer a1, int enum_kind);
	void print(int tab);
};
struct S_init_declarator_list {
	T_init_declarator v0;
	T_init_declarator_list v1;
	S_init_declarator_list(T_init_declarator a0, T_init_declarator_list a1);
	void print(int tab);
};
struct S_initializer {
	enum {INIT_LIST = 0, ASS_EXPR = 1, } kind;
	union {
		struct { T_initializer_list v0; } init_list;
		struct { T_assignment_expression v0; } ass_expr;
	};
	S_initializer(T_assignment_expression a0);
	S_initializer(T_initializer_list a0);
	void print(int tab);
};
struct S_initializer_list {
	T_designation v0;
	T_initializer v1;
	T_initializer_list v2;
	S_initializer_list(T_designation a0, T_initializer a1, T_initializer_list a2);
	void print(int tab);
};
struct S_iteration_statement {
	enum {WHILE_ = 0, DO_WHILE = 1, FOR1 = 2, FOR2 = 3, FOR3 = 4, FOR4 = 5, } kind;
	union {
		struct { T_expression v0; T_statement v1; } while_;
		struct { T_statement v0; T_expression v1; } do_while;
		struct { T_expression_statement v0; T_expression_statement v1; T_statement v2; } for1;
		struct { T_expression_statement v0; T_expression_statement v1; T_expression v2; T_statement v3; } for2;
		struct { T_declaration v0; T_expression_statement v1; T_statement v2; } for3;
		struct { T_declaration v0; T_expression_statement v1; T_expression v2; T_statement v3; } for4;
	};
	S_iteration_statement(T_declaration a0, T_expression_statement a1, T_expression a2, T_statement a3);
	S_iteration_statement(T_declaration a0, T_expression_statement a1, T_statement a2);
	S_iteration_statement(T_expression a0, T_statement a1);
	S_iteration_statement(T_expression_statement a0, T_expression_statement a1, T_expression a2, T_statement a3);
	S_iteration_statement(T_expression_statement a0, T_expression_statement a1, T_statement a2);
	S_iteration_statement(T_statement a0, T_expression a1);
	void print(int tab);
};
struct S_jump_statement {
	enum {GOTO = 0, CONT = 1, BREAK_ = 2, RETURN_ = 3, RETUR_EXPR = 4, } kind;
	union {
		struct { T_strval v0; } goto;
		struct { T_expression v0; } retur_expr;
	};
	S_jump_statement(int enum_kind);
	S_jump_statement(T_expression a0);
	S_jump_statement(T_strval a0);
	void print(int tab);
};
struct S_labeled_statement {
	enum {IDENTIFIER = 0, CASE_ = 1, DEFAULT_ = 2, } kind;
	union {
		struct { T_strval v0; T_statement v1; } identifier;
		struct { T_constant_expression v0; T_statement v1; } case_;
		struct { T_statement v0; } default_;
	};
	S_labeled_statement(T_constant_expression a0, T_statement a1);
	S_labeled_statement(T_statement a0);
	S_labeled_statement(T_strval a0, T_statement a1);
	void print(int tab);
};
struct S_parameter_declaration {
	enum {DECL = 0, ABST_DECL = 1, NONE = 2, } kind;
	union {
		struct { T_declaration_specifiers v0; T_declarator v1; } decl;
		struct { T_declaration_specifiers v0; T_abstract_declarator v1; } abst_decl;
		struct { T_declaration_specifiers v0; } none;
	};
	S_parameter_declaration(T_declaration_specifiers a0);
	S_parameter_declaration(T_declaration_specifiers a0, T_abstract_declarator a1);
	S_parameter_declaration(T_declaration_specifiers a0, T_declarator a1);
	void print(int tab);
};
struct S_parameter_list {
	T_parameter_declaration v0;
	T_parameter_list v1;
	S_parameter_list(T_parameter_declaration a0, T_parameter_list a1);
	void print(int tab);
};
struct S_parameter_type_list {
	enum {ELLIPSIS = 0, NO_ELLIPSIS = 1, } kind;
	T_parameter_list v0;
	S_parameter_type_list(T_parameter_list a0, int enum_kind);
	void print(int tab);
};
struct S_pointer {
	T_type_qualifier_list v0;
	T_pointer v1;
	S_pointer(T_type_qualifier_list a0, T_pointer a1);
	void print(int tab);
};
struct S_primary_expression {
	enum {IDENTIFIER = 0, CONSTANT = 1, STRING_ = 2, BRACKETED_EXPR = 3, GENERIC_SEL = 4, } kind;
	union {
		struct { T_strval v0; } identifier;
		struct { T_constant v0; } constant;
		struct { T_string v0; } string_;
		struct { T_expression v0; } bracketed_expr;
		struct { T_generic_selection v0; } generic_sel;
	};
	S_primary_expression(T_constant a0);
	S_primary_expression(T_expression a0);
	S_primary_expression(T_generic_selection a0);
	S_primary_expression(T_string a0);
	S_primary_expression(T_strval a0);
	void print(int tab);
};
struct S_selection_statement {
	enum {IF_ELSE = 0, IF_ = 1, SWITCH_ = 2, } kind;
	union {
		struct { T_expression v0; T_statement v1; T_statement v2; } if_else;
		struct { T_expression v0; T_statement v1; } if_;
		struct { T_expression v0; T_statement v1; } switch_;
	};
	S_selection_statement(T_expression a0, T_statement a1, int enum_kind);
	S_selection_statement(T_expression a0, T_statement a1, T_statement a2);
	void print(int tab);
};
struct S_specifier_qualifier_list {
	enum {SPEC = 0, SPEC_END = 1, QUAL = 2, QUAL_END = 3, } kind;
	union {
		struct { T_type_specifier v0; T_specifier_qualifier_list v1; } spec;
		struct { T_type_specifier v0; } spec_end;
		struct { T_type_qualifier v0; T_specifier_qualifier_list v1; } qual;
		struct { T_type_qualifier v0; } qual_end;
	};
	S_specifier_qualifier_list(T_type_qualifier a0);
	S_specifier_qualifier_list(T_type_qualifier a0, T_specifier_qualifier_list a1);
	S_specifier_qualifier_list(T_type_specifier a0);
	S_specifier_qualifier_list(T_type_specifier a0, T_specifier_qualifier_list a1);
	void print(int tab);
};
struct S_statement {
	enum {LABELED = 0, COMPOUND = 1, EXPRESSION = 2, SELECTION = 3, ITERATION = 4, JUMP = 5, } kind;
	union {
		struct { T_labeled_statement v0; } labeled;
		struct { T_compound_statement v0; } compound;
		struct { T_expression_statement v0; } expression;
		struct { T_selection_statement v0; } selection;
		struct { T_iteration_statement v0; } iteration;
		struct { T_jump_statement v0; } jump;
	};
	S_statement(T_compound_statement a0);
	S_statement(T_expression_statement a0);
	S_statement(T_iteration_statement a0);
	S_statement(T_jump_statement a0);
	S_statement(T_labeled_statement a0);
	S_statement(T_selection_statement a0);
	void print(int tab);
};
struct S_static_assert_declaration {
	T_constant_expression v0;
	T_strval v1;
	S_static_assert_declaration (T_constant_expression a0, T_strval a1);
	void print(int tab);
};
struct S_storage_class_specifier {
	enum {TYPEDEF_ = 0, EXTERN_ = 1, STATIC_ = 2, THREAD_LOCAL_ = 3, AUTO_ = 4, REGISTER_ = 5, } kind;
	S_storage_class_specifier(int enum_kind);
	void print(int tab);
};
struct S_string {
	enum {STRING_LITERAL = 0, FUN_NAME = 1, } kind;
	T_strval v0;
	S_string(T_strval a0, int enum_kind);
	void print(int tab);
};
struct S_struct_declaration {
	enum {SPEC_QUAL = 0, SPEC_QUAL_DECL = 1, STATIC_ASSERT_ = 2, } kind;
	union {
		struct { T_specifier_qualifier_list v0; } spec_qual;
		struct { T_specifier_qualifier_list v0; T_struct_declarator_list v1; } spec_qual_decl;
		struct { T_static_assert_declaration v0; } static_assert_;
	};
	S_struct_declaration(T_specifier_qualifier_list a0);
	S_struct_declaration(T_specifier_qualifier_list a0, T_struct_declarator_list a1);
	S_struct_declaration(T_static_assert_declaration a0);
	void print(int tab);
};
struct S_struct_declaration_list {
	T_struct_declaration v0;
	T_struct_declaration_list v1;
	S_struct_declaration_list(T_struct_declaration a0, T_struct_declaration_list a1);
	void print(int tab);
};
struct S_struct_declarator {
	enum {NO_DECL = 0, BOTH = 1, NO_CONST_EXPR = 2, } kind;
	T_constant_expression v0;
	T_declarator v1;
	S_struct_declarator(T_constant_expression a0, T_declarator a1, int enum_kind);
	void print(int tab);
};
struct S_struct_declarator_list {
	T_struct_declarator v0;
	T_struct_declarator_list v1;
	S_struct_declarator_list(T_struct_declarator a0, T_struct_declarator_list a1);
	void print(int tab);
};
struct S_struct_or_union {
	enum {STRUCT_ = 0, UNION_ = 1, } kind;
	S_struct_or_union(int enum_kind);
	void print(int tab);
};
struct S_struct_or_union_specifier {
	enum {NO_ID = 0, ID_AND_LIST = 1, NO_LIST = 2, } kind;
	T_struct_or_union v0;
	T_struct_declaration_list v1;
	T_strval v2;
	S_struct_or_union_specifier(T_struct_or_union a0, T_struct_declaration_list a1, T_strval a2, int enum_kind);
	void print(int tab);
};
struct S_translation_unit {
	T_external_declaration v0;
	T_translation_unit v1;
	S_translation_unit(T_external_declaration a0, T_translation_unit a1);
	void print(int tab);
};
struct S_type_name {
	T_specifier_qualifier_list v0;
	T_abstract_declarator v1;
	S_type_name(T_specifier_qualifier_list a0, T_abstract_declarator a1);
	void print(int tab);
};
struct S_type_qualifier {
	enum {CONST_ = 0, RESTRICT_ = 1, VOLATILE_ = 2, ATOMIC_ = 3, } kind;
	S_type_qualifier(int enum_kind);
	void print(int tab);
};
struct S_type_qualifier_list {
	T_type_qualifier v0;
	T_type_qualifier_list v1;
	S_type_qualifier_list(T_type_qualifier a0, T_type_qualifier_list a1);
	void print(int tab);
};
struct S_type_specifier {
	enum {VOID_ = 0, CHAR_ = 1, SHORT_ = 2, INT_ = 3, LONG_ = 4, FLOAT_ = 5, DOUBLE_ = 6, SIGNED_ = 7, UNSIGNED_ = 8, BOOL_ = 9, COMPLEX_ = 10, IMAGINARY_ = 11, ATOMIC_ = 12, STRUCT_OR_UNION = 13, ENUM_ = 14, TYPEDEF_ = 15, } kind;
	union {
		struct { T_atomic_type_specifier v0; } atomic_;
		struct { T_struct_or_union_specifier v0; } struct_or_union;
		struct { T_enum_specifier v0; } enum_;
	};
	S_type_specifier(int enum_kind);
	S_type_specifier(T_atomic_type_specifier a0);
	S_type_specifier(T_enum_specifier a0);
	S_type_specifier(T_struct_or_union_specifier a0);
	void print(int tab);
};
struct S_unary_expression {
	enum {CAST = 0, NONE = 1, INDEX = 2, CALL = 3, DOT = 4, PTR = 5, POST_INC = 6, POST_DEC = 7, CAST_LIST = 8, PRE_INC = 9, PRE_DEC = 10, UNARY_OP = 11, SIZEOF = 12, SIZEOF_TYPE = 13, ALIGNOF = 14, } kind;
	union {
		struct { T_type_name v0; T_unary_expression v1; } cast;
		struct { T_primary_expression v0; } none;
		struct { T_unary_expression v0; T_expression v1; } index;
		struct { T_unary_expression v0; T_argument_expression_list v1; } call;
		struct { T_unary_expression v0; T_strval v1; } dot;
		struct { T_unary_expression v0; T_strval v1; } ptr;
		struct { T_unary_expression v0; } post_inc;
		struct { T_unary_expression v0; } post_dec;
		struct { T_type_name v0; T_initializer_list v1; } cast_list;
		struct { T_unary_expression v0; } pre_inc;
		struct { T_unary_expression v0; } pre_dec;
		struct { T_unary_operator v0; T_unary_expression v1; } unary_op;
		struct { T_unary_expression v0; } sizeof;
		struct { T_type_name v0; } sizeof_type;
		struct { T_type_name v0; } alignof;
	};
	S_unary_expression(T_primary_expression a0);
	S_unary_expression(T_type_name a0, int enum_kind);
	S_unary_expression(T_type_name a0, T_initializer_list a1);
	S_unary_expression(T_type_name a0, T_unary_expression a1);
	S_unary_expression(T_unary_expression a0, int enum_kind);
	S_unary_expression(T_unary_expression a0, T_argument_expression_list a1);
	S_unary_expression(T_unary_expression a0, T_expression a1);
	S_unary_expression(T_unary_expression a0, T_strval a1, int enum_kind);
	S_unary_expression(T_unary_operator a0, T_unary_expression a1);
	void print(int tab);
};
struct S_unary_operator {
	enum {AND = 0, OR = 1, PLUS = 2, MINUS = 3, NEG = 4, NOT = 5, } kind;
	S_unary_operator(int enum_kind);
	void print(int tab);
};
