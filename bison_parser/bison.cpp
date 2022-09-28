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

map<string, T_rule> non_terminals;
map<string, string> token_types;

static void usage()
{
  printf("Usage: bison <prog.c>\n");
}

void create_ast () {
  set<string> remaining_nts;
  while (true) {
    cout << "remaining requeired non-terminals are:" << endl;
    for (string s: remaining_nts){
      cout << s << ", ";
    }
    cout << endl;
    cout << "enter non-terminal name to evaluate, 0 to exit, 1 to list all non-terminals" << endl;
    string nt;
    cin >> nt;
    if (nt == "0"){
      break;
    }
    else if (nt == "1") {
      for (auto [s1, s2]: non_terminals){
      cout << s1 << ", ";
      }
      cout << endl;
      continue;
    }
    if (remaining_nts.find(nt) != remaining_nts.end()){
      remaining_nts.erase(nt);
    }
    auto x = non_terminals.find(nt);
    if (x == non_terminals.end()){
      cout << "error: non terminal " + nt + " not found" << endl;
      continue;
    }
    auto & [temp1, rule]  = *x;
    rule->print_pretty();
    set<int> chosen_reds;
    for (int i = 0; i < rule->reductions->reds.size(); i ++){
      T_reduction r = rule->reductions->reds[i];
      cout << "Do you want to include the following reduction? enter y/n" << endl;
      r->print_pretty();
      string ch;
      cin >> ch;
      if (ch == "y"){
	chosen_reds.insert(i);
      }
      else if (ch != "n"){
	cout << "please respond in y/n" << endl;
	i--;
      }
    }
    if (chosen_reds.size() == 0){
      cout << "no reduction chosen, continuing" << endl;
      continue;
    }
    // cout << "do you want to merge any reductions together? merged rules will have the same function call and will be treated as one. Make sure that the two merged reductions have the same meaning and the same variables to be stored." << endl;
    string op;

choose_option:

    cout << "enter implementation style" << endl;
    cout << "options: \nn for normal (use when only one type of reduction)\ne for enum\nu for union+enum\nl for list\nm for manual" << endl;
    cin >> op;
    if (op == "n"){
      if (chosen_reds.size() > 1){
	cout << "more than one reduction, cannot make normal form" << endl;
	goto choose_option;
      }
      cout << "struct: " << endl;
      string con_struct_ed = "";
      con_struct_ed += "struct S_" + nt + " {\n";
      auto& v = rule->reductions->reds[*chosen_reds.begin()];
      for (int i = 0; i < v->non_terminals_values.size(); i ++) {
        con_struct_ed += "\tT_" + v->non_terminals_values[i] + " v" + to_string(i) + ";\n";
      }
      string constructor_decl = "S_" + nt + " (";
      for (int i = 0; i < v->non_terminals_values.size(); i ++) {
	constructor_decl += "T_" + v->non_terminals_values[i] + " a" + to_string(i);
	if (i != v->non_terminals_values.size()-1) constructor_decl += ", ";
      }
      constructor_decl += ")";
      con_struct_ed += "\t" + constructor_decl + ";\n";
      con_struct_ed += "\tvoid print(int tab);\n";
      // con_struct_ed += "\tvoid print_fancy(int tab);\n";
      con_struct_ed += "};\n";
      cout << con_struct_ed << endl;
      cout << "functions: " << endl;

      string constructor = "";
      constructor += "S_" + nt + "::" + constructor_decl + " {\n";
      for (int i = 0; i < v->non_terminals_values.size(); i ++) {
	constructor += "\tv" + to_string(i) + " = " + "a" + to_string(i) + ";\n";
      }
      constructor += "}\n";
      cout << constructor << endl;
      
      string printer = "void S_" + nt + "::" + "print(int tab) {\n";
      printer += "\tprint_tab(tab);\n";
      printer += "\tcout << \"+" + nt + "\" << endl;\n";
      for (int i = 0; i < v->non_terminals_values.size(); i ++) {
	printer += "\tv" + to_string(i) + "->print(tab+1);\n";
      }
      printer += "}\n";

      cout << printer << endl;

      cout << "bison reduction actions:" << endl;
      
      string red_act = nt + "\n";
      
      for (int i = 0; i < rule->reductions->reds.size(); i ++){
	if (i == 0) red_act +=  "        : ";
	else red_act += "        | ";
	red_act += rule->reductions->reds[i]->toString();
	if (chosen_reds.find(i) == chosen_reds.end()) red_act += " { throw \"not implemented\"; } \n";
	else {
	  red_act += " { $$ = new S_" + nt + "(";
	  for (auto ntp: rule->reductions->reds[i]->non_terminal_pos) {
	    red_act += "$" + to_string(ntp) + ", ";
	  }
	  red_act += "); }\n";
	}
      }
      red_act += "        ;\n";
      
      cout << red_act << endl;

    }
    else if (op == "e") {
      
      cout << "enter enum names for each chosen reduction (make it ALL CAPS)" << endl;
      vector<string> enums;
      for (int cr: chosen_reds) {
	rule->reductions->reds[cr]->print_pretty();
	string en;
	cin >> en;
	enums.push_back(en);
      }
      
      map<string, int> all_types_set;
      for (int cr: chosen_reds) {
	auto& v = rule->reductions->reds[cr];
	for (string s: v->non_terminals_values) {
	  if (all_types_set.find(s) == all_types_set.end()) {
	    all_types_set[s] = all_types_set.size();
	  }
	}
      }
      vector<string> all_types = vector<string> (all_types_set.size());
      
      for (auto &[ty, num]: all_types_set) {
	all_types[num] = ty;
      }

      cout << "struct: " << endl;
      string con_struct_ed = "struct S_" + nt + " {\n";
      con_struct_ed += "\tenum {";
      int id = 0;
      for (string e: enums) {
	con_struct_ed += e + " = " + to_string(id) + ", ";
	id ++;
      }
      con_struct_ed += "} kind;\n";
      for (int num = 0; num < all_types.size(); num ++) {
	con_struct_ed += "\tT_"+ all_types[num] + " v" + to_string(num) + ";\n";
      }
      string constructor_decl = "S_" + nt + "(";
      for (int num = 0; num < all_types.size(); num ++) {
	constructor_decl += "T_" + all_types[num] + " a" + to_string(num);
	constructor_decl += ", ";
      }
      constructor_decl += "int enum_kind)";
      con_struct_ed += "\t" + constructor_decl + ";\n";
      con_struct_ed += "\tvoid print(int tab);\n};\n";

      cout << con_struct_ed;
      
      cout << "functions:" << endl;
      string constructor = "S_" + nt + "::" + constructor_decl + "{\n";

      for (int i = 0; i < all_types.size(); i ++) {
	constructor += "\tv" + to_string(i) + " = " + "a" + to_string(i) + ";\n";
      }
      constructor += "\tkind = enum_kind;\n";
      constructor += "}\n";
      cout << constructor << endl;
      
      string printer = "void S_" + nt + "::print(int tab) {\n";
      printer += "\tprint_tab(tab);\n";
      printer += "\tcout << \"+" + nt + " type: \" << kind << endl;\n";
      for (int i = 0; i < all_types.size(); i ++) {
	printer += "\tif (v" + to_string(i) + " != NULL) v" + to_string(i) + "->print(tab+1);\n";
      }
      printer += "}\n";
      
      cout << printer << endl;
      
      cout << "bison reduction actions:" << endl;
      
      string red_act = nt + "\n";
      
      for (int i = 0; i < rule->reductions->reds.size(); i ++){
	if (i == 0) red_act +=  "        : ";
	else red_act += "        | ";
	red_act += rule->reductions->reds[i]->toString();
	if (chosen_reds.find(i) == chosen_reds.end()) red_act += " { throw \"not implemented\"; } \n";
	else {
	  red_act += " { $$ = new S_" + nt + "(";
	  for (auto ntp: all_types) {
	    int x = rule->reductions->reds[i]->findIdx(ntp);
	    if (x == -1) {
	      red_act += "NULL, ";
	    }
	    else {
	      red_act += "$" + to_string(x) + ", ";
	    }
	  }
	  red_act += to_string(i) + "); }\n";
	}
      }
      red_act += "        ;\n";
      
      cout << red_act << endl;
      
    }   
    else if (op == "u"){   // could have implemented this by inheriting everything with a AST_node class, but that means dynamic type checking and casts, virtual tables and other shit. If I am maintaining an enum anyways then it is better to implement a union instead (will also be compatible with C with minor changes as a bonus)
      
      cout << "enter enum names for each chosen reduction (make it ALL CAPS)" << endl;
      vector<string> enums;
      for (int cr: chosen_reds) {
	rule->reductions->reds[cr]->print_pretty();
	string en;
	cin >> en;
	enums.push_back(en);
	// for (auto s: rule->reductions->reds[cr]->non_terminals_values) {
	//   cout << "union for token: " << s << endl;
	//   int x;
	//   cin >> x;
	//   union_members[x].insert(
	// }
      }

      cout << "struct: " << endl;
      string con_struct_ed = "struct S_" + nt + " {\n";
      con_struct_ed += "\tenum {";
      int id = 0;
      for (string e: enums) {
	con_struct_ed += e + " = " + to_string(id) + ", ";
	id ++;
      }
      con_struct_ed += "} kind;\n";
      con_struct_ed += "\tunion {\n";
      int count = 0;
      for (int cr: chosen_reds) { 
	if (rule->reductions->reds[cr]->non_terminals_values.size() == 0) {
	  count ++;
	  continue;
	}
	con_struct_ed += "\t\tstruct { ";
	int i = 0;
	for (auto s: rule->reductions->reds[cr]->non_terminals_values) {
	  con_struct_ed += s + " v" + to_string(i) + "; ";
	  i++;
	}
	con_struct_ed += "} ";
	string temp = enums[count];
	transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	con_struct_ed += temp + ";\n";
	count ++;
      }
      con_struct_ed += "};\n";
      
      // multiple constructors
      // maybe store vector of strings and then see from that
      // yeah should work
      string constructor_decl = "S_" + nt + "(";
      for (int num = 0; num < all_types.size(); num ++) {
	constructor_decl += "T_" + all_types[num] + " a" + to_string(num);
	constructor_decl += ", ";
      }
      constructor_decl += "int enum_kind)";
      con_struct_ed += "\t" + constructor_decl + ";\n";
      con_struct_ed += "\tvoid print(int tab);\n};\n";

      cout << con_struct_ed;
      
      cout << "functions:" << endl;
      string constructor = "S_" + nt + "::" + constructor_decl + "{\n";

      for (int i = 0; i < all_types.size(); i ++) {
	constructor += "\tv" + to_string(i) + " = " + "a" + to_string(i) + ";\n";
      }
      constructor += "\tkind = enum_kind;\n";
      constructor += "}\n";
      cout << constructor << endl;
      
      string printer = "void S_" + nt + "::print(int tab) {\n";
      printer += "\tprint_tab(tab);\n";
      printer += "\tcout << \"+" + nt + " type: \" << kind << endl;\n";
      for (int i = 0; i < all_types.size(); i ++) {
	printer += "\tif (v" + to_string(i) + " != NULL) v" + to_string(i) + "->print(tab+1);\n";
      }
      printer += "}\n";
      
      cout << printer << endl;
      
      cout << "bison reduction actions:" << endl;
      
      string red_act = nt + "\n";
      
      for (int i = 0; i < rule->reductions->reds.size(); i ++){
	if (i == 0) red_act +=  "        : ";
	else red_act += "        | ";
	red_act += rule->reductions->reds[i]->toString();
	if (chosen_reds.find(i) == chosen_reds.end()) red_act += " { throw \"not implemented\"; } \n";
	else {
	  red_act += " { $$ = new S_" + nt + "(";
	  for (auto ntp: all_types) {
	    int x = rule->reductions->reds[i]->findIdx(ntp);
	    if (x == -1) {
	      red_act += "NULL, ";
	    }
	    else {
	      red_act += "$" + to_string(x) + ", ";
	    }
	  }
	  red_act += to_string(i) + "); }\n";
	}
      }
      red_act += "        ;\n";
      
      cout << red_act << endl;
      
    }
    else if (op == "l") {
      
    }
    else if (op == "m") {

    }
    else {
      cout << "please enter a valid option" << endl;
      goto choose_option;
    }
  }
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
  create_ast();
  exit(0);
}
