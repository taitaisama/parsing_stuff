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
      printer += "\tcout << \"+" + nt + ";\n";
      printer += "\tswitch(kind) {\n";
      for (int i = 0; i < enums.size(); i ++) {
	printer += "\tcase " + to_string(i) + ":\n";
	printer += "\t\tcout << \" type: " + enums[i] + "\" << endl;\n";
	printer += "\t\tbreak;\n";
      }
      printer += "\t}\n";
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
	  con_struct_ed += "T_" + s + " v" + to_string(i) + "; ";
	  i++;
	}
	con_struct_ed += "} ";
	string temp = enums[count];
	transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	con_struct_ed += temp + ";\n";
	count ++;
      }
      con_struct_ed += "\t};\n";
      
      // multiple constructors
      // maybe store vector of strings and then see from that
      // yeah should work
      // auto vec_comp = [](vector<string> a, vector<string> b) { sort(a.begin(), a.end()); sort(b.begin(), b.end()); return a < b; };
      map<vector<string>, vector<int>> constructor_map;

      for (int cr: chosen_reds) {
	constructor_map[rule->reductions->reds[cr]->non_terminals_values].push_back(cr);
      }
      
      vector<string> constructor_decls;

      for (auto& [vec_types, vec_int]: constructor_map) {
	string constructor_decl = "S_" + nt + "(";
	for (int i = 0; i < vec_types.size(); i ++){
	  constructor_decl += "T_" + vec_types[i] + " a" + to_string(i);
	  if (i != vec_types.size() - 1) {
	    constructor_decl += ", ";
	  }
	}
	if (vec_int.size() > 1) {
	  constructor_decl += ", int enum_kind";
	}
	constructor_decl += ")";
	constructor_decls.push_back(constructor_decl);
      }
      
      for (string c: constructor_decls) {
	con_struct_ed += "\t" + c + ";\n";
      }

      con_struct_ed += "\tvoid print(int tab);\n};\n";

      cout << con_struct_ed;
      
      cout << "functions:" << endl;

      vector<string> constructors;
      int con_num = 0;
      for (auto& [vec_types, vec_int]: constructor_map) {
	string constructor = "S_" + nt + "::" + constructor_decls[con_num] + " {\n";
	int vi = vec_int[0];
	string temp = enums[vi];
	transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	for (int i = 0; i < rule->reductions->reds[vi]->non_terminals_values.size(); i ++){
	  constructor += "\t" + temp + ".v" + to_string(i) + " = a" + to_string(i) + ";\n";
	}
	if (vec_int.size() == 1) 
	  constructor += "\tkind = " + enums[vi] + ";\n}\n";
	else 
	  constructor += "\tkind = enum_kind;\n}\n";
	constructors.push_back(constructor);
	con_num ++;
      }
      string printer = "S_" + nt + "::print(tab) {\n";
      printer += "\tprint_tab(tab);\n";
      printer += "\tcout << \"+" + nt + "\";\n";
      printer += "\tswitch(kind) {\n";
      for (auto& [vec_types, vec_int]: constructor_map) {
	for (auto vi: vec_int) {
	  printer += "\tcase " + to_string(vi) + ":\n";
	  printer += "\t\tcout << \" kind = " + enums[vi] + "\" << endl;\n";
	  string temp = enums[vi];
	  transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
	  for (int i = 0; i < vec_types.size(); i ++) {
	    printer += "\t\t" + temp + ".v" + to_string(i) + "->print(tab+1);\n";
	  }
	  printer += "\t\tbreak;\n";
	}
      }
      printer += "\t}\n}\n";

      for (string con: constructors) {
	cout << con << endl;
      }
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
	  auto & vei = constructor_map[rule->reductions->reds[i]->non_terminals_values];
	  for (int k = 0; k < rule->reductions->reds[i]->non_terminals_values.size(); k ++) {
	    auto ntp = rule->reductions->reds[i]->non_terminals_values[k];
	    int x = rule->reductions->reds[i]->findIdx(ntp);
	    red_act += "$" + to_string(x);
	    if (k != rule->reductions->reds[i]->non_terminals_values.size()-1){
	      red_act += ", ";
	    }
	  }
	  if (vei.size() > 1)
	    red_act += ", " + to_string(i) + "); }\n";
	  else
	    red_act += "); }\n";
	}
      }
      red_act += "        ;\n";
      
      cout << red_act << endl;
      
    }
    else if (op == "l") {
      if (chosen_reds.size() != 2) {
	cout << "rule doesn't match list construction, use manual ig" << endl;
	goto choose_option;
      }
      vector<string> v1, v2;
      auto it = chosen_reds.begin();
      int p1 = *it;
      int p2 = *(++it);
      if (rule->reductions->reds[p1]->values.size() == 1 && rule->reductions->reds[p2]->values.size() == 2) {
	v1 = rule->reductions->reds[p1]->values;
	v2 = rule->reductions->reds[p2]->values;
      }
      else if (rule->reductions->reds[p1]->values.size() == 2 && rule->reductions->reds[p2]->values.size() == 1) {
	v1 = rule->reductions->reds[p2]->values;
	v2 = rule->reductions->reds[p1]->values;
      }
      else {
	cout << "rule doesn't match list construction, use manual ig" << endl;
	goto choose_option;
      }
      string elem;
      bool prefix = false;
      if (v2[0] == nt) {
	prefix = true;
	if (v1[0] != v2[1]) {
	  cout << "rule doesn't match list construction, use manual ig" << endl;
	  goto choose_option;
	}
      }
      else if (v2[1] == nt) {
	if (v1[0] != v2[0]) {
	  cout << "rule doesn't match list construction, use manual ig" << endl;
	  goto choose_option;
	}
      }
      else {
	cout << "rule doesn't match list construction, use manual ig" << endl;
	goto choose_option;
      }
      //  {\n\tvector<T_" + v1[0] + "> v;\n\t
      
      cout << "struct:" << endl;
      string con_struct_ed = "struct S_" + nt + " {\n\tvector<T_" + v1[0] + "> v;\n";
      con_struct_ed += "\tT_" + nt + " add(T_" + v1[0] + " a);\n";
      con_struct_ed += "\tprint(int tab);\n}";
      cout << con_struct_ed << endl;
      cout << "functions:" << endl;
      string add_func = "T_" + nt + " S_" + nt + "::add(T_" + v1[0] + " a) {\n";
      add_func += "\tv.push_back(a);\n\treturn this;\n}\n";
      string printer = "void S_" + nt + "::print(int tab) {\n\tprint_tab(tab);\n\tcout << \"+" + nt + "\" << endl;\n\tfor(auto e: v) e->print(tab+1);\n}\n";
      // cout << constructor << endl;
      cout << add_func << endl;
      cout << printer << endl;
      
      cout << "bison reduction actions:" << endl;
      
      string red_act = nt + "\n";
      
      for (int i = 0; i < rule->reductions->reds.size(); i ++){
	if (i == 0) red_act +=  "        : ";
	else red_act += "        | ";
	red_act += rule->reductions->reds[i]->toString();
	if (chosen_reds.find(i) == chosen_reds.end()) red_act += " { throw \"not implemented\"; } \n";
	else {
	  if (rule->reductions->reds[i]->non_terminals_values.size() == 1) {
	    red_act += "{ $$ = new S_" + nt + "(); $$ = $$.add($1); }\n";
	  }
	  else {
	    if (prefix) {
	      red_act += "{ $$ = $1.add($2); }\n";
	    }
	    else {
	      red_act += "{ $$ = $2.add($1); }\n";
	    }
	  }
	}
      }
      red_act += "        ;\n";
      cout << red_act << endl;
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
