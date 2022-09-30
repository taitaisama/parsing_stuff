#include "ast.h"

void print_tab(int tab) {
	for(int i = 0; i < tab; i ++) {
		cout << "|";
	}
}
S_abstract_declarator::S_abstract_declarator(T_pointer a0, T_direct_abstract_declarator a1){
	v0 = a0;
	v1 = a1;
}
void S_abstract_declarator::print(int tab) {
	print_tab(tab);
	cout << "+abstract_declarator" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_alignment_specifier::S_alignment_specifier(T_constant_expression a0) {
	const_expr.v0 = a0;
	kind = CONST_EXPR;
}
S_alignment_specifier::S_alignment_specifier(T_type_name a0) {
	type_name.v0 = a0;
	kind = TYPE_NAME;
}
void S_alignment_specifier::print(int tab) {
	print_tab(tab);
	cout << "+alignment_specifier";
	switch(kind) {
	case 1:
		cout << " kind = CONST_EXPR" << endl;
		if (const_expr.v0 != NULL) const_expr.v0->print(tab+1);
		break;
	case 0:
		cout << " kind = TYPE_NAME" << endl;
		if (type_name.v0 != NULL) type_name.v0->print(tab+1);
		break;
	}
}
S_argument_expression_list::S_argument_expression_list(T_assignment_expression a0, T_argument_expression_list a1){
	v0 = a0;
	v1 = a1;
}
void S_argument_expression_list::print(int tab) {
	print_tab(tab);
	cout << "+argument_expression_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_assignment_expression::S_assignment_expression(T_conditional_expression a0) {
	none.v0 = a0;
	kind = NONE;
}
S_assignment_expression::S_assignment_expression(T_unary_expression a0, T_assignment_operator a1, T_assignment_expression a2) {
	assignment.v0 = a0;
	assignment.v1 = a1;
	assignment.v2 = a2;
	kind = ASSIGNMENT;
}
void S_assignment_expression::print(int tab) {
	print_tab(tab);
	cout << "+assignment_expression";
	switch(kind) {
	case 0:
		cout << " kind = NONE" << endl;
		if (none.v0 != NULL) none.v0->print(tab+1);
		break;
	case 1:
		cout << " kind = ASSIGNMENT" << endl;
		if (assignment.v0 != NULL) assignment.v0->print(tab+1);
		if (assignment.v1 != NULL) assignment.v1->print(tab+1);
		if (assignment.v2 != NULL) assignment.v2->print(tab+1);
		break;
	}
}
S_assignment_operator::S_assignment_operator(int enum_kind){
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_assignment_operator::print(int tab) {
	print_tab(tab);
	cout << "+assignment_operator";
	switch(kind) {
	case 0:
		cout << " type: ASS" << endl;
		break;
	case 1:
		cout << " type: MUL_ASS" << endl;
		break;
	case 2:
		cout << " type: DIV_ASS" << endl;
		break;
	case 3:
		cout << " type: MOD_ASS" << endl;
		break;
	case 4:
		cout << " type: ADD_ASS" << endl;
		break;
	case 5:
		cout << " type: SUB_ASS" << endl;
		break;
	case 6:
		cout << " type: LEFT_ASS" << endl;
		break;
	case 7:
		cout << " type: RIGHT_ASS" << endl;
		break;
	case 8:
		cout << " type: AND_ASS" << endl;
		break;
	case 9:
		cout << " type: XOR_ASS" << endl;
		break;
	case 10:
		cout << " type: OR_ASS" << endl;
		break;
	}
}
S_atomic_type_specifier::S_atomic_type_specifier (T_type_name a0) {
	v0 = a0;
}
void S_atomic_type_specifier::print(int tab) {
	print_tab(tab);
	cout << "+atomic_type_specifier" << endl;
	if (v0 != NULL) v0->print(tab+1);
}
S_binary_expression::S_binary_expression(T_binary_expression a0, T_binary_expression a1, int enum_kind) {
	add.v0 = a0;
	add.v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_binary_expression::S_binary_expression(T_binary_expression a0, T_unary_expression a1, int enum_kind) {
	mult.v0 = a0;
	mult.v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_binary_expression::S_binary_expression(T_unary_expression a0) {
	none.v0 = a0;
	kind = NONE;
}
void S_binary_expression::print(int tab) {
	print_tab(tab);
	cout << "+binary_expression";
	switch(kind) {
	case 0:
		cout << " kind = ADD" << endl;
		if (add.v0 != NULL) add.v0->print(tab+1);
		if (add.v1 != NULL) add.v1->print(tab+1);
		break;
	case 1:
		cout << " kind = SUB" << endl;
		if (sub.v0 != NULL) sub.v0->print(tab+1);
		if (sub.v1 != NULL) sub.v1->print(tab+1);
		break;
	case 2:
		cout << " kind = BIT_AND" << endl;
		if (bit_and.v0 != NULL) bit_and.v0->print(tab+1);
		if (bit_and.v1 != NULL) bit_and.v1->print(tab+1);
		break;
	case 3:
		cout << " kind = EQU" << endl;
		if (equ.v0 != NULL) equ.v0->print(tab+1);
		if (equ.v1 != NULL) equ.v1->print(tab+1);
		break;
	case 4:
		cout << " kind = NEQ" << endl;
		if (neq.v0 != NULL) neq.v0->print(tab+1);
		if (neq.v1 != NULL) neq.v1->print(tab+1);
		break;
	case 5:
		cout << " kind = BIT_XOR" << endl;
		if (bit_xor.v0 != NULL) bit_xor.v0->print(tab+1);
		if (bit_xor.v1 != NULL) bit_xor.v1->print(tab+1);
		break;
	case 6:
		cout << " kind = BIT_OR" << endl;
		if (bit_or.v0 != NULL) bit_or.v0->print(tab+1);
		if (bit_or.v1 != NULL) bit_or.v1->print(tab+1);
		break;
	case 7:
		cout << " kind = LOGIC_AND" << endl;
		if (logic_and.v0 != NULL) logic_and.v0->print(tab+1);
		if (logic_and.v1 != NULL) logic_and.v1->print(tab+1);
		break;
	case 8:
		cout << " kind = LOGIC_OR" << endl;
		if (logic_or.v0 != NULL) logic_or.v0->print(tab+1);
		if (logic_or.v1 != NULL) logic_or.v1->print(tab+1);
		break;
	case 13:
		cout << " kind = LTH" << endl;
		if (lth.v0 != NULL) lth.v0->print(tab+1);
		if (lth.v1 != NULL) lth.v1->print(tab+1);
		break;
	case 14:
		cout << " kind = GTH" << endl;
		if (gth.v0 != NULL) gth.v0->print(tab+1);
		if (gth.v1 != NULL) gth.v1->print(tab+1);
		break;
	case 15:
		cout << " kind = LTE" << endl;
		if (lte.v0 != NULL) lte.v0->print(tab+1);
		if (lte.v1 != NULL) lte.v1->print(tab+1);
		break;
	case 16:
		cout << " kind = GTE" << endl;
		if (gte.v0 != NULL) gte.v0->print(tab+1);
		if (gte.v1 != NULL) gte.v1->print(tab+1);
		break;
	case 17:
		cout << " kind = LEFT_SHIFT" << endl;
		if (left_shift.v0 != NULL) left_shift.v0->print(tab+1);
		if (left_shift.v1 != NULL) left_shift.v1->print(tab+1);
		break;
	case 18:
		cout << " kind = RIGHT_SHIFT" << endl;
		if (right_shift.v0 != NULL) right_shift.v0->print(tab+1);
		if (right_shift.v1 != NULL) right_shift.v1->print(tab+1);
		break;
	case 10:
		cout << " kind = MULT" << endl;
		if (mult.v0 != NULL) mult.v0->print(tab+1);
		if (mult.v1 != NULL) mult.v1->print(tab+1);
		break;
	case 11:
		cout << " kind = DIV" << endl;
		if (div.v0 != NULL) div.v0->print(tab+1);
		if (div.v1 != NULL) div.v1->print(tab+1);
		break;
	case 12:
		cout << " kind = MOD" << endl;
		if (mod.v0 != NULL) mod.v0->print(tab+1);
		if (mod.v1 != NULL) mod.v1->print(tab+1);
		break;
	case 9:
		cout << " kind = NONE" << endl;
		if (none.v0 != NULL) none.v0->print(tab+1);
		break;
	}
}
S_block_item::S_block_item(T_declaration a0) {
	declaration.v0 = a0;
	kind = DECLARATION;
}
S_block_item::S_block_item(T_statement a0) {
	statement.v0 = a0;
	kind = STATEMENT;
}
void S_block_item::print(int tab) {
	print_tab(tab);
	cout << "+block_item";
	switch(kind) {
	case 0:
		cout << " kind = DECLARATION" << endl;
		if (declaration.v0 != NULL) declaration.v0->print(tab+1);
		break;
	case 1:
		cout << " kind = STATEMENT" << endl;
		if (statement.v0 != NULL) statement.v0->print(tab+1);
		break;
	}
}
S_block_item_list::S_block_item_list(T_block_item a0, T_block_item_list a1){
	v0 = a0;
	v1 = a1;
}
void S_block_item_list::print(int tab) {
	print_tab(tab);
	cout << "+block_item_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_compound_statement::S_compound_statement(T_block_item_list a0){
	v0 = a0;
}
void S_compound_statement::print(int tab) {
	print_tab(tab);
	cout << "+compound_statement" << endl;
if (v0 != NULL) v0->print(tab+1);
}
S_conditional_expression::S_conditional_expression(T_binary_expression a0) {
	binary.v0 = a0;
	kind = BINARY;
}
S_conditional_expression::S_conditional_expression(T_binary_expression a0, T_expression a1, T_conditional_expression a2) {
	terrinary.v0 = a0;
	terrinary.v1 = a1;
	terrinary.v2 = a2;
	kind = TERRINARY;
}
void S_conditional_expression::print(int tab) {
	print_tab(tab);
	cout << "+conditional_expression";
	switch(kind) {
	case 0:
		cout << " kind = BINARY" << endl;
		if (binary.v0 != NULL) binary.v0->print(tab+1);
		break;
	case 1:
		cout << " kind = TERRINARY" << endl;
		if (terrinary.v0 != NULL) terrinary.v0->print(tab+1);
		if (terrinary.v1 != NULL) terrinary.v1->print(tab+1);
		if (terrinary.v2 != NULL) terrinary.v2->print(tab+1);
		break;
	}
}
S_constant::S_constant() {
	kind = ENUM_CONST;
}
S_constant::S_constant(T_floatval a0) {
	float_.v0 = a0;
	kind = FLOAT_;
}
S_constant::S_constant(T_intval a0) {
	integer.v0 = a0;
	kind = INTEGER;
}
void S_constant::print(int tab) {
	print_tab(tab);
	cout << "+constant";
	switch(kind) {
	case 2:
		cout << " kind = ENUM_CONST" << endl;
		break;
	case 1:
		cout << " kind = FLOAT_" << endl;
	print_tab(tab+1);
	cout << float_.v0 << endl;
		break;
	case 0:
		cout << " kind = INTEGER" << endl;
	print_tab(tab+1);
	cout << integer.v0 << endl;
		break;
	}
}
S_constant_expression::S_constant_expression (T_conditional_expression a0) {
	v0 = a0;
}
void S_constant_expression::print(int tab) {
	print_tab(tab);
	cout << "+constant_expression" << endl;
	if (v0 != NULL) v0->print(tab+1);
}
S_declaration::S_declaration(T_declaration_specifiers a0, T_init_declarator_list a1) {
	normal.v0 = a0;
	normal.v1 = a1;
	kind = NORMAL;
}
S_declaration::S_declaration(T_static_assert_declaration a0) {
	static_assert_.v0 = a0;
	kind = STATIC_ASSERT_;
}
void S_declaration::print(int tab) {
	print_tab(tab);
	cout << "+declaration";
	switch(kind) {
	case 0:
		cout << " kind = NORMAL" << endl;
		if (normal.v0 != NULL) normal.v0->print(tab+1);
		if (normal.v1 != NULL) normal.v1->print(tab+1);
		break;
	case 1:
		cout << " kind = STATIC_ASSERT_" << endl;
		if (static_assert_.v0 != NULL) static_assert_.v0->print(tab+1);
		break;
	}
}
S_declaration_list::S_declaration_list(T_declaration a0, T_declaration_list a1){
	v0 = a0;
	v1 = a1;
}
void S_declaration_list::print(int tab) {
	print_tab(tab);
	cout << "+declaration_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_declaration_specifiers::S_declaration_specifiers(T_alignment_specifier a0, T_declaration_specifiers a1) {
	alightment_spec.v0 = a0;
	alightment_spec.v1 = a1;
	kind = ALIGHTMENT_SPEC;
}
S_declaration_specifiers::S_declaration_specifiers(T_function_specifier a0, T_declaration_specifiers a1) {
	function_spec.v0 = a0;
	function_spec.v1 = a1;
	kind = FUNCTION_SPEC;
}
S_declaration_specifiers::S_declaration_specifiers(T_storage_class_specifier a0, T_declaration_specifiers a1) {
	storage.v0 = a0;
	storage.v1 = a1;
	kind = STORAGE;
}
S_declaration_specifiers::S_declaration_specifiers(T_type_qualifier a0, T_declaration_specifiers a1) {
	type_qual.v0 = a0;
	type_qual.v1 = a1;
	kind = TYPE_QUAL;
}
S_declaration_specifiers::S_declaration_specifiers(T_type_specifier a0, T_declaration_specifiers a1) {
	type_spec.v0 = a0;
	type_spec.v1 = a1;
	kind = TYPE_SPEC;
}
void S_declaration_specifiers::print(int tab) {
	print_tab(tab);
	cout << "+declaration_specifiers";
	switch(kind) {
	case 4:
		cout << " kind = ALIGHTMENT_SPEC" << endl;
		if (alightment_spec.v0 != NULL) alightment_spec.v0->print(tab+1);
		if (alightment_spec.v1 != NULL) alightment_spec.v1->print(tab+1);
		break;
	case 3:
		cout << " kind = FUNCTION_SPEC" << endl;
		if (function_spec.v0 != NULL) function_spec.v0->print(tab+1);
		if (function_spec.v1 != NULL) function_spec.v1->print(tab+1);
		break;
	case 0:
		cout << " kind = STORAGE" << endl;
		if (storage.v0 != NULL) storage.v0->print(tab+1);
		if (storage.v1 != NULL) storage.v1->print(tab+1);
		break;
	case 2:
		cout << " kind = TYPE_QUAL" << endl;
		if (type_qual.v0 != NULL) type_qual.v0->print(tab+1);
		if (type_qual.v1 != NULL) type_qual.v1->print(tab+1);
		break;
	case 1:
		cout << " kind = TYPE_SPEC" << endl;
		if (type_spec.v0 != NULL) type_spec.v0->print(tab+1);
		if (type_spec.v1 != NULL) type_spec.v1->print(tab+1);
		break;
	}
}
S_declarator::S_declarator(T_pointer a0, T_direct_declarator a1, int enum_kind){
	v0 = a0;
	v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_declarator::print(int tab) {
	print_tab(tab);
	cout << "+declarator";
	switch(kind) {
	case 0:
		cout << " type: POINTER" << endl;
		break;
	case 1:
		cout << " type: NO_POINTER" << endl;
		break;
	}
	if (v0 != NULL)	v0->print(tab+1);
	if (v1 != NULL)	v1->print(tab+1);
}
S_designation::S_designation (T_designator_list a0) {
	v0 = a0;
}
void S_designation::print(int tab) {
	print_tab(tab);
	cout << "+designation" << endl;
	if (v0 != NULL) v0->print(tab+1);
}
S_designator::S_designator(T_constant_expression a0) {
	index.v0 = a0;
	kind = INDEX;
}
S_designator::S_designator(T_strval a0) {
	dot.v0 = a0;
	kind = DOT;
}
void S_designator::print(int tab) {
	print_tab(tab);
	cout << "+designator";
	switch(kind) {
	case 0:
		cout << " kind = INDEX" << endl;
		if (index.v0 != NULL) index.v0->print(tab+1);
		break;
	case 1:
		cout << " kind = DOT" << endl;
	print_tab(tab+1);
	cout << dot.v0 << endl;
		break;
	}
}
S_designator_list::S_designator_list(T_designator a0, T_designator_list a1){
	v0 = a0;
	v1 = a1;
}
void S_designator_list::print(int tab) {
	print_tab(tab);
	cout << "+designator_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_direct_abstract_declarator::S_direct_abstract_declarator(int enum_kind) {
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_direct_abstract_declarator::S_direct_abstract_declarator(T_abstract_declarator a0) {
	decl1.v0 = a0;
	kind = DECL1;
}
S_direct_abstract_declarator::S_direct_abstract_declarator(T_assignment_expression a0, int enum_kind) {
	decl5.v0 = a0;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_direct_abstract_declarator::S_direct_abstract_declarator(T_direct_abstract_declarator a0, int enum_kind) {
	decl10.v0 = a0;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_direct_abstract_declarator::S_direct_abstract_declarator(T_direct_abstract_declarator a0, T_assignment_expression a1, int enum_kind) {
	decl13.v0 = a0;
	decl13.v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_direct_abstract_declarator::S_direct_abstract_declarator(T_direct_abstract_declarator a0, T_parameter_type_list a1) {
	decl21.v0 = a0;
	decl21.v1 = a1;
	kind = DECL21;
}
S_direct_abstract_declarator::S_direct_abstract_declarator(T_direct_abstract_declarator a0, T_type_qualifier_list a1) {
	decl16.v0 = a0;
	decl16.v1 = a1;
	kind = DECL16;
}
S_direct_abstract_declarator::S_direct_abstract_declarator(T_direct_abstract_declarator a0, T_type_qualifier_list a1, T_assignment_expression a2, int enum_kind) {
	decl12.v0 = a0;
	decl12.v1 = a1;
	decl12.v2 = a2;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_direct_abstract_declarator::S_direct_abstract_declarator(T_parameter_type_list a0) {
	decl19.v0 = a0;
	kind = DECL19;
}
S_direct_abstract_declarator::S_direct_abstract_declarator(T_type_qualifier_list a0) {
	decl8.v0 = a0;
	kind = DECL8;
}
S_direct_abstract_declarator::S_direct_abstract_declarator(T_type_qualifier_list a0, T_assignment_expression a1, int enum_kind) {
	decl4.v0 = a0;
	decl4.v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_direct_abstract_declarator::print(int tab) {
	print_tab(tab);
	cout << "+direct_abstract_declarator";
	switch(kind) {
	case 1:
		cout << " kind = DECL2" << endl;
		break;
	case 2:
		cout << " kind = DECL3" << endl;
		break;
	case 17:
		cout << " kind = DECL18" << endl;
		break;
	case 0:
		cout << " kind = DECL1" << endl;
		if (decl1.v0 != NULL) decl1.v0->print(tab+1);
		break;
	case 4:
		cout << " kind = DECL5" << endl;
		if (decl5.v0 != NULL) decl5.v0->print(tab+1);
		break;
	case 8:
		cout << " kind = DECL9" << endl;
		if (decl9.v0 != NULL) decl9.v0->print(tab+1);
		break;
	case 9:
		cout << " kind = DECL10" << endl;
		if (decl10.v0 != NULL) decl10.v0->print(tab+1);
		break;
	case 10:
		cout << " kind = DECL11" << endl;
		if (decl11.v0 != NULL) decl11.v0->print(tab+1);
		break;
	case 19:
		cout << " kind = DECL20" << endl;
		if (decl20.v0 != NULL) decl20.v0->print(tab+1);
		break;
	case 12:
		cout << " kind = DECL13" << endl;
		if (decl13.v0 != NULL) decl13.v0->print(tab+1);
		if (decl13.v1 != NULL) decl13.v1->print(tab+1);
		break;
	case 16:
		cout << " kind = DECL17" << endl;
		if (decl17.v0 != NULL) decl17.v0->print(tab+1);
		if (decl17.v1 != NULL) decl17.v1->print(tab+1);
		break;
	case 20:
		cout << " kind = DECL21" << endl;
		if (decl21.v0 != NULL) decl21.v0->print(tab+1);
		if (decl21.v1 != NULL) decl21.v1->print(tab+1);
		break;
	case 15:
		cout << " kind = DECL16" << endl;
		if (decl16.v0 != NULL) decl16.v0->print(tab+1);
		if (decl16.v1 != NULL) decl16.v1->print(tab+1);
		break;
	case 11:
		cout << " kind = DECL12" << endl;
		if (decl12.v0 != NULL) decl12.v0->print(tab+1);
		if (decl12.v1 != NULL) decl12.v1->print(tab+1);
		if (decl12.v2 != NULL) decl12.v2->print(tab+1);
		break;
	case 13:
		cout << " kind = DECL14" << endl;
		if (decl14.v0 != NULL) decl14.v0->print(tab+1);
		if (decl14.v1 != NULL) decl14.v1->print(tab+1);
		if (decl14.v2 != NULL) decl14.v2->print(tab+1);
		break;
	case 14:
		cout << " kind = DECL15" << endl;
		if (decl15.v0 != NULL) decl15.v0->print(tab+1);
		if (decl15.v1 != NULL) decl15.v1->print(tab+1);
		if (decl15.v2 != NULL) decl15.v2->print(tab+1);
		break;
	case 18:
		cout << " kind = DECL19" << endl;
		if (decl19.v0 != NULL) decl19.v0->print(tab+1);
		break;
	case 7:
		cout << " kind = DECL8" << endl;
		if (decl8.v0 != NULL) decl8.v0->print(tab+1);
		break;
	case 3:
		cout << " kind = DECL4" << endl;
		if (decl4.v0 != NULL) decl4.v0->print(tab+1);
		if (decl4.v1 != NULL) decl4.v1->print(tab+1);
		break;
	case 5:
		cout << " kind = DECL6" << endl;
		if (decl6.v0 != NULL) decl6.v0->print(tab+1);
		if (decl6.v1 != NULL) decl6.v1->print(tab+1);
		break;
	case 6:
		cout << " kind = DECL7" << endl;
		if (decl7.v0 != NULL) decl7.v0->print(tab+1);
		if (decl7.v1 != NULL) decl7.v1->print(tab+1);
		break;
	}
}
S_direct_declarator::S_direct_declarator(T_declarator a0) {
	decl1.v0 = a0;
	kind = DECL1;
}
S_direct_declarator::S_direct_declarator(T_direct_declarator a0, int enum_kind) {
	decl2.v0 = a0;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_direct_declarator::S_direct_declarator(T_direct_declarator a0, T_assignment_expression a1, int enum_kind) {
	decl5.v0 = a0;
	decl5.v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_direct_declarator::S_direct_declarator(T_direct_declarator a0, T_identifier_list a1) {
	decl13.v0 = a0;
	decl13.v1 = a1;
	kind = DECL13;
}
S_direct_declarator::S_direct_declarator(T_direct_declarator a0, T_parameter_type_list a1) {
	decl11.v0 = a0;
	decl11.v1 = a1;
	kind = DECL11;
}
S_direct_declarator::S_direct_declarator(T_direct_declarator a0, T_type_qualifier_list a1, int enum_kind) {
	decl6.v0 = a0;
	decl6.v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_direct_declarator::S_direct_declarator(T_direct_declarator a0, T_type_qualifier_list a1, T_assignment_expression a2, int enum_kind) {
	decl4.v0 = a0;
	decl4.v1 = a1;
	decl4.v2 = a2;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_direct_declarator::S_direct_declarator(T_strval a0) {
	identifier.v0 = a0;
	kind = IDENTIFIER;
}
void S_direct_declarator::print(int tab) {
	print_tab(tab);
	cout << "+direct_declarator";
	switch(kind) {
	case 1:
		cout << " kind = DECL1" << endl;
		if (decl1.v0 != NULL) decl1.v0->print(tab+1);
		break;
	case 2:
		cout << " kind = DECL2" << endl;
		if (decl2.v0 != NULL) decl2.v0->print(tab+1);
		break;
	case 3:
		cout << " kind = DECL3" << endl;
		if (decl3.v0 != NULL) decl3.v0->print(tab+1);
		break;
	case 12:
		cout << " kind = DECL12" << endl;
		if (decl12.v0 != NULL) decl12.v0->print(tab+1);
		break;
	case 5:
		cout << " kind = DECL5" << endl;
		if (decl5.v0 != NULL) decl5.v0->print(tab+1);
		if (decl5.v1 != NULL) decl5.v1->print(tab+1);
		break;
	case 10:
		cout << " kind = DECL10" << endl;
		if (decl10.v0 != NULL) decl10.v0->print(tab+1);
		if (decl10.v1 != NULL) decl10.v1->print(tab+1);
		break;
	case 13:
		cout << " kind = DECL13" << endl;
		if (decl13.v0 != NULL) decl13.v0->print(tab+1);
		if (decl13.v1 != NULL) decl13.v1->print(tab+1);
		break;
	case 11:
		cout << " kind = DECL11" << endl;
		if (decl11.v0 != NULL) decl11.v0->print(tab+1);
		if (decl11.v1 != NULL) decl11.v1->print(tab+1);
		break;
	case 6:
		cout << " kind = DECL6" << endl;
		if (decl6.v0 != NULL) decl6.v0->print(tab+1);
		if (decl6.v1 != NULL) decl6.v1->print(tab+1);
		break;
	case 9:
		cout << " kind = DECL9" << endl;
		if (decl9.v0 != NULL) decl9.v0->print(tab+1);
		if (decl9.v1 != NULL) decl9.v1->print(tab+1);
		break;
	case 4:
		cout << " kind = DECL4" << endl;
		if (decl4.v0 != NULL) decl4.v0->print(tab+1);
		if (decl4.v1 != NULL) decl4.v1->print(tab+1);
		if (decl4.v2 != NULL) decl4.v2->print(tab+1);
		break;
	case 7:
		cout << " kind = DECL7" << endl;
		if (decl7.v0 != NULL) decl7.v0->print(tab+1);
		if (decl7.v1 != NULL) decl7.v1->print(tab+1);
		if (decl7.v2 != NULL) decl7.v2->print(tab+1);
		break;
	case 8:
		cout << " kind = DECL8" << endl;
		if (decl8.v0 != NULL) decl8.v0->print(tab+1);
		if (decl8.v1 != NULL) decl8.v1->print(tab+1);
		if (decl8.v2 != NULL) decl8.v2->print(tab+1);
		break;
	case 0:
		cout << " kind = IDENTIFIER" << endl;
	print_tab(tab+1);
	cout << identifier.v0 << endl;
		break;
	}
}
S_enum_specifier::S_enum_specifier(T_enumerator_list a0, T_strval a1, int enum_kind){
	v0 = a0;
	v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_enum_specifier::print(int tab) {
	print_tab(tab);
	cout << "+enum_specifier";
	switch(kind) {
	case 0:
		cout << " type: NO_IDEN" << endl;
		break;
	case 1:
		cout << " type: WITH_IDEN" << endl;
		break;
	case 2:
		cout << " type: DECL" << endl;
		break;
	}
	if (v0 != NULL)	v0->print(tab+1);
	print_tab(tab+1);
	cout << v1 << endl;
}
S_enumeration_constant::S_enumeration_constant (T_strval a0) {
	v0 = a0;
}
void S_enumeration_constant::print(int tab) {
	print_tab(tab);
	cout << "+enumeration_constant" << endl;
	print_tab(tab+1);
	cout << v0 << endl;
}
S_enumerator::S_enumerator(T_enumeration_constant a0, T_constant_expression a1){
	v0 = a0;
	v1 = a1;
}
void S_enumerator::print(int tab) {
	print_tab(tab);
	cout << "+enumerator" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_enumerator_list::S_enumerator_list(T_enumerator a0, T_enumerator_list a1){
	v0 = a0;
	v1 = a1;
}
void S_enumerator_list::print(int tab) {
	print_tab(tab);
	cout << "+enumerator_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_expression::S_expression(T_assignment_expression a0, T_expression a1){
	v0 = a0;
	v1 = a1;
}
void S_expression::print(int tab) {
	print_tab(tab);
	cout << "+expression" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_expression_statement::S_expression_statement(T_expression a0){
	v0 = a0;
}
void S_expression_statement::print(int tab) {
	print_tab(tab);
	cout << "+expression_statement" << endl;
if (v0 != NULL) v0->print(tab+1);
}
S_external_declaration::S_external_declaration(T_declaration a0) {
	declaration.v0 = a0;
	kind = DECLARATION;
}
S_external_declaration::S_external_declaration(T_function_definition a0) {
	function_definition.v0 = a0;
	kind = FUNCTION_DEFINITION;
}
void S_external_declaration::print(int tab) {
	print_tab(tab);
	cout << "+external_declaration";
	switch(kind) {
	case 1:
		cout << " kind = DECLARATION" << endl;
		if (declaration.v0 != NULL) declaration.v0->print(tab+1);
		break;
	case 0:
		cout << " kind = FUNCTION_DEFINITION" << endl;
		if (function_definition.v0 != NULL) function_definition.v0->print(tab+1);
		break;
	}
}
S_function_definition::S_function_definition(T_declaration_specifiers a0, T_declarator a1, T_declaration_list a2, T_compound_statement a3){
	v0 = a0;
	v1 = a1;
	v2 = a2;
	v3 = a3;
}
void S_function_definition::print(int tab) {
	print_tab(tab);
	cout << "+function_definition" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
if (v2 != NULL) v2->print(tab+1);
if (v3 != NULL) v3->print(tab+1);
}
S_function_specifier::S_function_specifier(int enum_kind){
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_function_specifier::print(int tab) {
	print_tab(tab);
	cout << "+function_specifier";
	switch(kind) {
	case 0:
		cout << " type: INLINE" << endl;
		break;
	case 1:
		cout << " type: NORETURN" << endl;
		break;
	}
}
S_generic_assoc_list::S_generic_assoc_list(T_generic_association a0, T_generic_assoc_list a1){
	v0 = a0;
	v1 = a1;
}
void S_generic_assoc_list::print(int tab) {
	print_tab(tab);
	cout << "+generic_assoc_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_generic_association::S_generic_association(T_type_name a0, T_assignment_expression a1, int enum_kind){
	v0 = a0;
	v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_generic_association::print(int tab) {
	print_tab(tab);
	cout << "+generic_association";
	switch(kind) {
	case 0:
		cout << " type: TYPE_NAME" << endl;
		break;
	case 1:
		cout << " type: DEFAULT" << endl;
		break;
	}
	if (v0 != NULL)	v0->print(tab+1);
	if (v1 != NULL)	v1->print(tab+1);
}
S_generic_selection::S_generic_selection (T_assignment_expression a0, T_generic_assoc_list a1) {
	v0 = a0;
	v1 = a1;
}
void S_generic_selection::print(int tab) {
	print_tab(tab);
	cout << "+generic_selection" << endl;
	if (v0 != NULL) v0->print(tab+1);
	if (v1 != NULL) v1->print(tab+1);
}
S_identifier_list::S_identifier_list(T_strval a0, T_identifier_list a1){
	v0 = a0;
	v1 = a1;
}
void S_identifier_list::print(int tab) {
	print_tab(tab);
	cout << "+identifier_list" << endl;
	print_tab(tab+1);
	cout << v0 << endl;
if (v1 != NULL) v1->print(tab+1);
}
S_init_declarator::S_init_declarator(T_declarator a0, T_initializer a1, int enum_kind){
	v0 = a0;
	v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_init_declarator::print(int tab) {
	print_tab(tab);
	cout << "+init_declarator";
	switch(kind) {
	case 0:
		cout << " type: INITIALISED" << endl;
		break;
	case 1:
		cout << " type: UNINITIALISED" << endl;
		break;
	}
	if (v0 != NULL)	v0->print(tab+1);
	if (v1 != NULL)	v1->print(tab+1);
}
S_init_declarator_list::S_init_declarator_list(T_init_declarator a0, T_init_declarator_list a1){
	v0 = a0;
	v1 = a1;
}
void S_init_declarator_list::print(int tab) {
	print_tab(tab);
	cout << "+init_declarator_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_initializer::S_initializer(T_assignment_expression a0) {
	ass_expr.v0 = a0;
	kind = ASS_EXPR;
}
S_initializer::S_initializer(T_initializer_list a0) {
	init_list.v0 = a0;
	kind = INIT_LIST;
}
void S_initializer::print(int tab) {
	print_tab(tab);
	cout << "+initializer";
	switch(kind) {
	case 1:
		cout << " kind = ASS_EXPR" << endl;
		if (ass_expr.v0 != NULL) ass_expr.v0->print(tab+1);
		break;
	case 0:
		cout << " kind = INIT_LIST" << endl;
		if (init_list.v0 != NULL) init_list.v0->print(tab+1);
		break;
	}
}
S_initializer_list::S_initializer_list(T_designation a0, T_initializer a1, T_initializer_list a2){
	v0 = a0;
	v1 = a1;
	v2 = a2;
}
void S_initializer_list::print(int tab) {
	print_tab(tab);
	cout << "+initializer_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
if (v2 != NULL) v2->print(tab+1);
}
S_iteration_statement::S_iteration_statement(T_declaration a0, T_expression_statement a1, T_expression a2, T_statement a3) {
	for4.v0 = a0;
	for4.v1 = a1;
	for4.v2 = a2;
	for4.v3 = a3;
	kind = FOR4;
}
S_iteration_statement::S_iteration_statement(T_declaration a0, T_expression_statement a1, T_statement a2) {
	for3.v0 = a0;
	for3.v1 = a1;
	for3.v2 = a2;
	kind = FOR3;
}
S_iteration_statement::S_iteration_statement(T_expression a0, T_statement a1) {
	while_.v0 = a0;
	while_.v1 = a1;
	kind = WHILE_;
}
S_iteration_statement::S_iteration_statement(T_expression_statement a0, T_expression_statement a1, T_expression a2, T_statement a3) {
	for2.v0 = a0;
	for2.v1 = a1;
	for2.v2 = a2;
	for2.v3 = a3;
	kind = FOR2;
}
S_iteration_statement::S_iteration_statement(T_expression_statement a0, T_expression_statement a1, T_statement a2) {
	for1.v0 = a0;
	for1.v1 = a1;
	for1.v2 = a2;
	kind = FOR1;
}
S_iteration_statement::S_iteration_statement(T_statement a0, T_expression a1) {
	do_while.v0 = a0;
	do_while.v1 = a1;
	kind = DO_WHILE;
}
void S_iteration_statement::print(int tab) {
	print_tab(tab);
	cout << "+iteration_statement";
	switch(kind) {
	case 5:
		cout << " kind = FOR4" << endl;
		if (for4.v0 != NULL) for4.v0->print(tab+1);
		if (for4.v1 != NULL) for4.v1->print(tab+1);
		if (for4.v2 != NULL) for4.v2->print(tab+1);
		if (for4.v3 != NULL) for4.v3->print(tab+1);
		break;
	case 4:
		cout << " kind = FOR3" << endl;
		if (for3.v0 != NULL) for3.v0->print(tab+1);
		if (for3.v1 != NULL) for3.v1->print(tab+1);
		if (for3.v2 != NULL) for3.v2->print(tab+1);
		break;
	case 0:
		cout << " kind = WHILE_" << endl;
		if (while_.v0 != NULL) while_.v0->print(tab+1);
		if (while_.v1 != NULL) while_.v1->print(tab+1);
		break;
	case 3:
		cout << " kind = FOR2" << endl;
		if (for2.v0 != NULL) for2.v0->print(tab+1);
		if (for2.v1 != NULL) for2.v1->print(tab+1);
		if (for2.v2 != NULL) for2.v2->print(tab+1);
		if (for2.v3 != NULL) for2.v3->print(tab+1);
		break;
	case 2:
		cout << " kind = FOR1" << endl;
		if (for1.v0 != NULL) for1.v0->print(tab+1);
		if (for1.v1 != NULL) for1.v1->print(tab+1);
		if (for1.v2 != NULL) for1.v2->print(tab+1);
		break;
	case 1:
		cout << " kind = DO_WHILE" << endl;
		if (do_while.v0 != NULL) do_while.v0->print(tab+1);
		if (do_while.v1 != NULL) do_while.v1->print(tab+1);
		break;
	}
}
S_jump_statement::S_jump_statement(int enum_kind) {
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_jump_statement::S_jump_statement(T_expression a0) {
	retur_expr.v0 = a0;
	kind = RETUR_EXPR;
}
S_jump_statement::S_jump_statement(T_strval a0) {
	goto_.v0 = a0;
	kind = GOTO_;
}
void S_jump_statement::print(int tab) {
	print_tab(tab);
	cout << "+jump_statement";
	switch(kind) {
	case 1:
		cout << " kind = CONT" << endl;
		break;
	case 2:
		cout << " kind = BREAK_" << endl;
		break;
	case 3:
		cout << " kind = RETURN_" << endl;
		break;
	case 4:
		cout << " kind = RETUR_EXPR" << endl;
		if (retur_expr.v0 != NULL) retur_expr.v0->print(tab+1);
		break;
	case 0:
		cout << " kind = GOTO_" << endl;
	print_tab(tab+1);
	cout << goto_.v0 << endl;
		break;
	}
}
S_labeled_statement::S_labeled_statement(T_constant_expression a0, T_statement a1) {
	case_.v0 = a0;
	case_.v1 = a1;
	kind = CASE_;
}
S_labeled_statement::S_labeled_statement(T_statement a0) {
	default_.v0 = a0;
	kind = DEFAULT_;
}
S_labeled_statement::S_labeled_statement(T_strval a0, T_statement a1) {
	identifier.v0 = a0;
	identifier.v1 = a1;
	kind = IDENTIFIER;
}
void S_labeled_statement::print(int tab) {
	print_tab(tab);
	cout << "+labeled_statement";
	switch(kind) {
	case 1:
		cout << " kind = CASE_" << endl;
		if (case_.v0 != NULL) case_.v0->print(tab+1);
		if (case_.v1 != NULL) case_.v1->print(tab+1);
		break;
	case 2:
		cout << " kind = DEFAULT_" << endl;
		if (default_.v0 != NULL) default_.v0->print(tab+1);
		break;
	case 0:
		cout << " kind = IDENTIFIER" << endl;
	print_tab(tab+1);
	cout << identifier.v0 << endl;
		if (identifier.v1 != NULL) identifier.v1->print(tab+1);
		break;
	}
}
S_parameter_declaration::S_parameter_declaration(T_declaration_specifiers a0) {
	none.v0 = a0;
	kind = NONE;
}
S_parameter_declaration::S_parameter_declaration(T_declaration_specifiers a0, T_abstract_declarator a1) {
	abst_decl.v0 = a0;
	abst_decl.v1 = a1;
	kind = ABST_DECL;
}
S_parameter_declaration::S_parameter_declaration(T_declaration_specifiers a0, T_declarator a1) {
	decl.v0 = a0;
	decl.v1 = a1;
	kind = DECL;
}
void S_parameter_declaration::print(int tab) {
	print_tab(tab);
	cout << "+parameter_declaration";
	switch(kind) {
	case 2:
		cout << " kind = NONE" << endl;
		if (none.v0 != NULL) none.v0->print(tab+1);
		break;
	case 1:
		cout << " kind = ABST_DECL" << endl;
		if (abst_decl.v0 != NULL) abst_decl.v0->print(tab+1);
		if (abst_decl.v1 != NULL) abst_decl.v1->print(tab+1);
		break;
	case 0:
		cout << " kind = DECL" << endl;
		if (decl.v0 != NULL) decl.v0->print(tab+1);
		if (decl.v1 != NULL) decl.v1->print(tab+1);
		break;
	}
}
S_parameter_list::S_parameter_list(T_parameter_declaration a0, T_parameter_list a1){
	v0 = a0;
	v1 = a1;
}
void S_parameter_list::print(int tab) {
	print_tab(tab);
	cout << "+parameter_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_parameter_type_list::S_parameter_type_list(T_parameter_list a0, int enum_kind){
	v0 = a0;
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_parameter_type_list::print(int tab) {
	print_tab(tab);
	cout << "+parameter_type_list";
	switch(kind) {
	case 0:
		cout << " type: ELLIPSIS" << endl;
		break;
	case 1:
		cout << " type: NO_ELLIPSIS" << endl;
		break;
	}
	if (v0 != NULL)	v0->print(tab+1);
}
S_pointer::S_pointer(T_type_qualifier_list a0, T_pointer a1){
	v0 = a0;
	v1 = a1;
}
void S_pointer::print(int tab) {
	print_tab(tab);
	cout << "+pointer" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_primary_expression::S_primary_expression(T_constant a0) {
	constant.v0 = a0;
	kind = CONSTANT;
}
S_primary_expression::S_primary_expression(T_expression a0) {
	bracketed_expr.v0 = a0;
	kind = BRACKETED_EXPR;
}
S_primary_expression::S_primary_expression(T_generic_selection a0) {
	generic_sel.v0 = a0;
	kind = GENERIC_SEL;
}
S_primary_expression::S_primary_expression(T_string a0) {
	string_.v0 = a0;
	kind = STRING_;
}
S_primary_expression::S_primary_expression(T_strval a0) {
	identifier.v0 = a0;
	kind = IDENTIFIER;
}
void S_primary_expression::print(int tab) {
	print_tab(tab);
	cout << "+primary_expression";
	switch(kind) {
	case 1:
		cout << " kind = CONSTANT" << endl;
		if (constant.v0 != NULL) constant.v0->print(tab+1);
		break;
	case 3:
		cout << " kind = BRACKETED_EXPR" << endl;
		if (bracketed_expr.v0 != NULL) bracketed_expr.v0->print(tab+1);
		break;
	case 4:
		cout << " kind = GENERIC_SEL" << endl;
		if (generic_sel.v0 != NULL) generic_sel.v0->print(tab+1);
		break;
	case 2:
		cout << " kind = STRING_" << endl;
		if (string_.v0 != NULL) string_.v0->print(tab+1);
		break;
	case 0:
		cout << " kind = IDENTIFIER" << endl;
	print_tab(tab+1);
	cout << identifier.v0 << endl;
		break;
	}
}
S_selection_statement::S_selection_statement(T_expression a0, T_statement a1, int enum_kind) {
	if_.v0 = a0;
	if_.v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_selection_statement::S_selection_statement(T_expression a0, T_statement a1, T_statement a2) {
	if_else.v0 = a0;
	if_else.v1 = a1;
	if_else.v2 = a2;
	kind = IF_ELSE;
}
void S_selection_statement::print(int tab) {
	print_tab(tab);
	cout << "+selection_statement";
	switch(kind) {
	case 1:
		cout << " kind = IF_" << endl;
		if (if_.v0 != NULL) if_.v0->print(tab+1);
		if (if_.v1 != NULL) if_.v1->print(tab+1);
		break;
	case 2:
		cout << " kind = SWITCH_" << endl;
		if (switch_.v0 != NULL) switch_.v0->print(tab+1);
		if (switch_.v1 != NULL) switch_.v1->print(tab+1);
		break;
	case 0:
		cout << " kind = IF_ELSE" << endl;
		if (if_else.v0 != NULL) if_else.v0->print(tab+1);
		if (if_else.v1 != NULL) if_else.v1->print(tab+1);
		if (if_else.v2 != NULL) if_else.v2->print(tab+1);
		break;
	}
}
S_specifier_qualifier_list::S_specifier_qualifier_list(T_type_qualifier a0) {
	qual_end.v0 = a0;
	kind = QUAL_END;
}
S_specifier_qualifier_list::S_specifier_qualifier_list(T_type_qualifier a0, T_specifier_qualifier_list a1) {
	qual.v0 = a0;
	qual.v1 = a1;
	kind = QUAL;
}
S_specifier_qualifier_list::S_specifier_qualifier_list(T_type_specifier a0) {
	spec_end.v0 = a0;
	kind = SPEC_END;
}
S_specifier_qualifier_list::S_specifier_qualifier_list(T_type_specifier a0, T_specifier_qualifier_list a1) {
	spec.v0 = a0;
	spec.v1 = a1;
	kind = SPEC;
}
void S_specifier_qualifier_list::print(int tab) {
	print_tab(tab);
	cout << "+specifier_qualifier_list";
	switch(kind) {
	case 3:
		cout << " kind = QUAL_END" << endl;
		if (qual_end.v0 != NULL) qual_end.v0->print(tab+1);
		break;
	case 2:
		cout << " kind = QUAL" << endl;
		if (qual.v0 != NULL) qual.v0->print(tab+1);
		if (qual.v1 != NULL) qual.v1->print(tab+1);
		break;
	case 1:
		cout << " kind = SPEC_END" << endl;
		if (spec_end.v0 != NULL) spec_end.v0->print(tab+1);
		break;
	case 0:
		cout << " kind = SPEC" << endl;
		if (spec.v0 != NULL) spec.v0->print(tab+1);
		if (spec.v1 != NULL) spec.v1->print(tab+1);
		break;
	}
}
S_statement::S_statement(T_compound_statement a0) {
	compound.v0 = a0;
	kind = COMPOUND;
}
S_statement::S_statement(T_expression_statement a0) {
	expression.v0 = a0;
	kind = EXPRESSION;
}
S_statement::S_statement(T_iteration_statement a0) {
	iteration.v0 = a0;
	kind = ITERATION;
}
S_statement::S_statement(T_jump_statement a0) {
	jump.v0 = a0;
	kind = JUMP;
}
S_statement::S_statement(T_labeled_statement a0) {
	labeled.v0 = a0;
	kind = LABELED;
}
S_statement::S_statement(T_selection_statement a0) {
	selection.v0 = a0;
	kind = SELECTION;
}
void S_statement::print(int tab) {
	print_tab(tab);
	cout << "+statement";
	switch(kind) {
	case 1:
		cout << " kind = COMPOUND" << endl;
		if (compound.v0 != NULL) compound.v0->print(tab+1);
		break;
	case 2:
		cout << " kind = EXPRESSION" << endl;
		if (expression.v0 != NULL) expression.v0->print(tab+1);
		break;
	case 4:
		cout << " kind = ITERATION" << endl;
		if (iteration.v0 != NULL) iteration.v0->print(tab+1);
		break;
	case 5:
		cout << " kind = JUMP" << endl;
		if (jump.v0 != NULL) jump.v0->print(tab+1);
		break;
	case 0:
		cout << " kind = LABELED" << endl;
		if (labeled.v0 != NULL) labeled.v0->print(tab+1);
		break;
	case 3:
		cout << " kind = SELECTION" << endl;
		if (selection.v0 != NULL) selection.v0->print(tab+1);
		break;
	}
}
S_static_assert_declaration::S_static_assert_declaration (T_constant_expression a0, T_strval a1) {
	v0 = a0;
	v1 = a1;
}
void S_static_assert_declaration::print(int tab) {
	print_tab(tab);
	cout << "+static_assert_declaration" << endl;
	if (v0 != NULL) v0->print(tab+1);
	print_tab(tab+1);
	cout << v1 << endl;
}
S_storage_class_specifier::S_storage_class_specifier(int enum_kind){
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_storage_class_specifier::print(int tab) {
	print_tab(tab);
	cout << "+storage_class_specifier";
	switch(kind) {
	case 0:
		cout << " type: TYPEDEF_" << endl;
		break;
	case 1:
		cout << " type: EXTERN_" << endl;
		break;
	case 2:
		cout << " type: STATIC_" << endl;
		break;
	case 3:
		cout << " type: THREAD_LOCAL_" << endl;
		break;
	case 4:
		cout << " type: AUTO_" << endl;
		break;
	case 5:
		cout << " type: REGISTER_" << endl;
		break;
	}
}
S_string::S_string(T_strval a0, int enum_kind){
	v0 = a0;
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_string::print(int tab) {
	print_tab(tab);
	cout << "+string";
	switch(kind) {
	case 0:
		cout << " type: STRING_LITERAL" << endl;
		break;
	case 1:
		cout << " type: FUN_NAME" << endl;
		break;
	}
	print_tab(tab+1);
	cout << v0 << endl;
}
S_struct_declaration::S_struct_declaration(T_specifier_qualifier_list a0) {
	spec_qual.v0 = a0;
	kind = SPEC_QUAL;
}
S_struct_declaration::S_struct_declaration(T_specifier_qualifier_list a0, T_struct_declarator_list a1) {
	spec_qual_decl.v0 = a0;
	spec_qual_decl.v1 = a1;
	kind = SPEC_QUAL_DECL;
}
S_struct_declaration::S_struct_declaration(T_static_assert_declaration a0) {
	static_assert_.v0 = a0;
	kind = STATIC_ASSERT_;
}
void S_struct_declaration::print(int tab) {
	print_tab(tab);
	cout << "+struct_declaration";
	switch(kind) {
	case 0:
		cout << " kind = SPEC_QUAL" << endl;
		if (spec_qual.v0 != NULL) spec_qual.v0->print(tab+1);
		break;
	case 1:
		cout << " kind = SPEC_QUAL_DECL" << endl;
		if (spec_qual_decl.v0 != NULL) spec_qual_decl.v0->print(tab+1);
		if (spec_qual_decl.v1 != NULL) spec_qual_decl.v1->print(tab+1);
		break;
	case 2:
		cout << " kind = STATIC_ASSERT_" << endl;
		if (static_assert_.v0 != NULL) static_assert_.v0->print(tab+1);
		break;
	}
}
S_struct_declaration_list::S_struct_declaration_list(T_struct_declaration a0, T_struct_declaration_list a1){
	v0 = a0;
	v1 = a1;
}
void S_struct_declaration_list::print(int tab) {
	print_tab(tab);
	cout << "+struct_declaration_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_struct_declarator::S_struct_declarator(T_constant_expression a0, T_declarator a1, int enum_kind){
	v0 = a0;
	v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_struct_declarator::print(int tab) {
	print_tab(tab);
	cout << "+struct_declarator";
	switch(kind) {
	case 0:
		cout << " type: NO_DECL" << endl;
		break;
	case 1:
		cout << " type: BOTH" << endl;
		break;
	case 2:
		cout << " type: NO_CONST_EXPR" << endl;
		break;
	}
	if (v0 != NULL)	v0->print(tab+1);
	if (v1 != NULL)	v1->print(tab+1);
}
S_struct_declarator_list::S_struct_declarator_list(T_struct_declarator a0, T_struct_declarator_list a1){
	v0 = a0;
	v1 = a1;
}
void S_struct_declarator_list::print(int tab) {
	print_tab(tab);
	cout << "+struct_declarator_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_struct_or_union::S_struct_or_union(int enum_kind){
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_struct_or_union::print(int tab) {
	print_tab(tab);
	cout << "+struct_or_union";
	switch(kind) {
	case 0:
		cout << " type: STRUCT_" << endl;
		break;
	case 1:
		cout << " type: UNION_" << endl;
		break;
	}
}
S_struct_or_union_specifier::S_struct_or_union_specifier(T_struct_or_union a0, T_struct_declaration_list a1, T_strval a2, int enum_kind){
	v0 = a0;
	v1 = a1;
	v2 = a2;
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_struct_or_union_specifier::print(int tab) {
	print_tab(tab);
	cout << "+struct_or_union_specifier";
	switch(kind) {
	case 0:
		cout << " type: NO_ID" << endl;
		break;
	case 1:
		cout << " type: ID_AND_LIST" << endl;
		break;
	case 2:
		cout << " type: NO_LIST" << endl;
		break;
	}
	if (v0 != NULL)	v0->print(tab+1);
	if (v1 != NULL)	v1->print(tab+1);
	print_tab(tab+1);
	cout << v2 << endl;
}
S_translation_unit::S_translation_unit(T_external_declaration a0, T_translation_unit a1){
	v0 = a0;
	v1 = a1;
}
void S_translation_unit::print(int tab) {
	print_tab(tab);
	cout << "+translation_unit" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_type_name::S_type_name(T_specifier_qualifier_list a0, T_abstract_declarator a1){
	v0 = a0;
	v1 = a1;
}
void S_type_name::print(int tab) {
	print_tab(tab);
	cout << "+type_name" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_type_qualifier::S_type_qualifier(int enum_kind){
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_type_qualifier::print(int tab) {
	print_tab(tab);
	cout << "+type_qualifier";
	switch(kind) {
	case 0:
		cout << " type: CONST_" << endl;
		break;
	case 1:
		cout << " type: RESTRICT_" << endl;
		break;
	case 2:
		cout << " type: VOLATILE_" << endl;
		break;
	case 3:
		cout << " type: ATOMIC_" << endl;
		break;
	}
}
S_type_qualifier_list::S_type_qualifier_list(T_type_qualifier a0, T_type_qualifier_list a1){
	v0 = a0;
	v1 = a1;
}
void S_type_qualifier_list::print(int tab) {
	print_tab(tab);
	cout << "+type_qualifier_list" << endl;
if (v0 != NULL) v0->print(tab+1);
if (v1 != NULL) v1->print(tab+1);
}
S_type_specifier::S_type_specifier(int enum_kind) {
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_type_specifier::S_type_specifier(T_atomic_type_specifier a0) {
	atomic_.v0 = a0;
	kind = ATOMIC_;
}
S_type_specifier::S_type_specifier(T_enum_specifier a0) {
	enum_.v0 = a0;
	kind = ENUM_;
}
S_type_specifier::S_type_specifier(T_struct_or_union_specifier a0) {
	struct_or_union.v0 = a0;
	kind = STRUCT_OR_UNION;
}
void S_type_specifier::print(int tab) {
	print_tab(tab);
	cout << "+type_specifier";
	switch(kind) {
	case 0:
		cout << " kind = VOID_" << endl;
		break;
	case 1:
		cout << " kind = CHAR_" << endl;
		break;
	case 2:
		cout << " kind = SHORT_" << endl;
		break;
	case 3:
		cout << " kind = INT_" << endl;
		break;
	case 4:
		cout << " kind = LONG_" << endl;
		break;
	case 5:
		cout << " kind = FLOAT_" << endl;
		break;
	case 6:
		cout << " kind = DOUBLE_" << endl;
		break;
	case 7:
		cout << " kind = SIGNED_" << endl;
		break;
	case 8:
		cout << " kind = UNSIGNED_" << endl;
		break;
	case 9:
		cout << " kind = BOOL_" << endl;
		break;
	case 10:
		cout << " kind = COMPLEX_" << endl;
		break;
	case 11:
		cout << " kind = IMAGINARY_" << endl;
		break;
	case 15:
		cout << " kind = TYPEDEF_" << endl;
		break;
	case 12:
		cout << " kind = ATOMIC_" << endl;
		if (atomic_.v0 != NULL) atomic_.v0->print(tab+1);
		break;
	case 14:
		cout << " kind = ENUM_" << endl;
		if (enum_.v0 != NULL) enum_.v0->print(tab+1);
		break;
	case 13:
		cout << " kind = STRUCT_OR_UNION" << endl;
		if (struct_or_union.v0 != NULL) struct_or_union.v0->print(tab+1);
		break;
	}
}
S_unary_expression::S_unary_expression(T_primary_expression a0) {
	none.v0 = a0;
	kind = NONE;
}
S_unary_expression::S_unary_expression(T_type_name a0, int enum_kind) {
	sizeof_type.v0 = a0;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_unary_expression::S_unary_expression(T_type_name a0, T_initializer_list a1) {
	cast_list.v0 = a0;
	cast_list.v1 = a1;
	kind = CAST_LIST;
}
S_unary_expression::S_unary_expression(T_type_name a0, T_unary_expression a1) {
	cast.v0 = a0;
	cast.v1 = a1;
	kind = CAST;
}
S_unary_expression::S_unary_expression(T_unary_expression a0, int enum_kind) {
	post_inc.v0 = a0;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_unary_expression::S_unary_expression(T_unary_expression a0, T_argument_expression_list a1) {
	call.v0 = a0;
	call.v1 = a1;
	kind = CALL;
}
S_unary_expression::S_unary_expression(T_unary_expression a0, T_expression a1) {
	index.v0 = a0;
	index.v1 = a1;
	kind = INDEX;
}
S_unary_expression::S_unary_expression(T_unary_expression a0, T_strval a1, int enum_kind) {
	dot.v0 = a0;
	dot.v1 = a1;
	kind = static_cast<typeof(kind)>(enum_kind);
}
S_unary_expression::S_unary_expression(T_unary_operator a0, T_unary_expression a1) {
	unary_op.v0 = a0;
	unary_op.v1 = a1;
	kind = UNARY_OP;
}
void S_unary_expression::print(int tab) {
	print_tab(tab);
	cout << "+unary_expression";
	switch(kind) {
	case 1:
		cout << " kind = NONE" << endl;
		if (none.v0 != NULL) none.v0->print(tab+1);
		break;
	case 13:
		cout << " kind = SIZEOF_TYPE" << endl;
		if (sizeof_type.v0 != NULL) sizeof_type.v0->print(tab+1);
		break;
	case 14:
		cout << " kind = ALIGNOF_" << endl;
		if (alignof_.v0 != NULL) alignof_.v0->print(tab+1);
		break;
	case 8:
		cout << " kind = CAST_LIST" << endl;
		if (cast_list.v0 != NULL) cast_list.v0->print(tab+1);
		if (cast_list.v1 != NULL) cast_list.v1->print(tab+1);
		break;
	case 0:
		cout << " kind = CAST" << endl;
		if (cast.v0 != NULL) cast.v0->print(tab+1);
		if (cast.v1 != NULL) cast.v1->print(tab+1);
		break;
	case 6:
		cout << " kind = POST_INC" << endl;
		if (post_inc.v0 != NULL) post_inc.v0->print(tab+1);
		break;
	case 7:
		cout << " kind = POST_DEC" << endl;
		if (post_dec.v0 != NULL) post_dec.v0->print(tab+1);
		break;
	case 9:
		cout << " kind = PRE_INC" << endl;
		if (pre_inc.v0 != NULL) pre_inc.v0->print(tab+1);
		break;
	case 10:
		cout << " kind = PRE_DEC" << endl;
		if (pre_dec.v0 != NULL) pre_dec.v0->print(tab+1);
		break;
	case 12:
		cout << " kind = SIZEOF_" << endl;
		if (sizeof_.v0 != NULL) sizeof_.v0->print(tab+1);
		break;
	case 3:
		cout << " kind = CALL" << endl;
		if (call.v0 != NULL) call.v0->print(tab+1);
		if (call.v1 != NULL) call.v1->print(tab+1);
		break;
	case 2:
		cout << " kind = INDEX" << endl;
		if (index.v0 != NULL) index.v0->print(tab+1);
		if (index.v1 != NULL) index.v1->print(tab+1);
		break;
	case 4:
		cout << " kind = DOT" << endl;
		if (dot.v0 != NULL) dot.v0->print(tab+1);
	print_tab(tab+1);
	cout << dot.v1 << endl;
		break;
	case 5:
		cout << " kind = PTR" << endl;
		if (ptr.v0 != NULL) ptr.v0->print(tab+1);
	print_tab(tab+1);
	cout << ptr.v1 << endl;
		break;
	case 11:
		cout << " kind = UNARY_OP" << endl;
		if (unary_op.v0 != NULL) unary_op.v0->print(tab+1);
		if (unary_op.v1 != NULL) unary_op.v1->print(tab+1);
		break;
	}
}
S_unary_operator::S_unary_operator(int enum_kind){
	kind = static_cast<typeof(kind)>(enum_kind);
}
void S_unary_operator::print(int tab) {
	print_tab(tab);
	cout << "+unary_operator";
	switch(kind) {
	case 0:
		cout << " type: AND" << endl;
		break;
	case 1:
		cout << " type: OR" << endl;
		break;
	case 2:
		cout << " type: PLUS" << endl;
		break;
	case 3:
		cout << " type: MINUS" << endl;
		break;
	case 4:
		cout << " type: NEG" << endl;
		break;
	case 5:
		cout << " type: NOT" << endl;
		break;
	}
}
