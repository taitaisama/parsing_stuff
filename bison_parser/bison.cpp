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
map<string, string> mergers;
map<string, int> nt_order;
map<string, string> token_types;
int indent = 85;
// ofstream struct_names{"struct_names.h"};
// ofstream typedefs{"typedefs.h"};
// ofstream funcs{"functions.cpp"};
// ofstream redrules{"reduction_rules.y"};
ofstream ast_header{"ast.h"};
ofstream ast_cpp{"ast.cpp"};
ofstream bison_file{"reductions.y"};
ofstream inputs{"inputs.txt"};


struct nt_features {
  string struct_definition;
  string functions;
  string bison_actions;
};

string takeInputTillEnd() {
  string line;
  string func = "";
  while (getline(cin, line)) {
    if (line == "end") {
      break;
    }
    func += line;
  }
  return func;
}
  
map<string, nt_features> done_nt_features;

map<string, T_rule> merged_non_terminals;

void merge_states() {
  for (auto& [st, r]: non_terminals) {
    merged_non_terminals[st] = r->dup();
  }
  while (true) {
    cout << "enter name of merged non terminal. 0 to exit" << endl;
    string x;
    cin >> x;
    inputs << x << endl;
    if (x == "0") break;
    cout << "enter non terminals to merge, 0 to specify done" << endl;
    set<string> mnts;
    while (true) {
      string m;
      cin >> m;
      inputs << m << endl;
      if (m == "0") {
	break;
      }
      else {
	if (merged_non_terminals.find(m) == merged_non_terminals.end()){
	  cout << m + " not found" << endl;
	  continue;
	}
	mnts.insert(m);
      }
    }
    for (auto st: mnts) {
      mergers[st] = x;
    }
    T_rule new_rule = new S_rule();
    new_rule->product = x;
    T_reduction_list nrl = new S_reduction_list();
    new_rule->reductions = nrl;
    for (auto nt: mnts) {
      T_rule r = merged_non_terminals[nt];
      for (auto re: r->reductions->reds) {
	nrl->add(re->dup());
      }
    }
    for (auto nt: mnts) {
      merged_non_terminals.erase(nt);
    }
    merged_non_terminals[x] = new_rule;
    for (auto &[st, tr]: merged_non_terminals) { 
      for (auto r: tr->reductions->reds) {
	r->exchange(x, mnts);
      }
    }
    new_rule->remove_dups();
  }
  swap(non_terminals, merged_non_terminals);
  for (auto& [st, k]: merged_non_terminals) {
    cout << st << ", ";
  }
  cout << endl;
}

void create_ast () {
  set<string> remaining_nts;
  set<string> done_nts;
  while (true) {
    cout << "remaining requeired non-terminals are:" << endl;
    for (string s: remaining_nts){
      cout << s << ", ";
    }
    cout << endl;
    cout << "enter non-terminal name to evaluate, 0 to exit, 1 to list all non-terminals" << endl;
    string nt;
    cin >> nt;
    inputs << nt << endl;
    
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
      inputs << ch << endl;
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
    
    string op;
    
    string con_struct_ed, functions, red_act;

choose_option:

    cout << "enter implementation style" << endl;
    cout << "options: \nn for normal (use when only one type of reduction)\ne for enum\nm for multiple with no enum (also uses default constructor, useful for empty list situations)\nu for union+enum\nl for list\nd for do it yourself" << endl;
    cin >> op;
    inputs << op << endl;
    
    if (op == "n"){
      if (chosen_reds.size() > 1){
	cout << "more than one reduction, cannot make normal form" << endl;
	goto choose_option;
      }
      cout << "struct: " << endl;
      con_struct_ed = "";
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
	if (non_terminals.find(v->non_terminals_values[i]) == non_terminals.end()) {
	  printer += "\tprint_tab(tab+1);\n";
	  printer += "\tcout << v" + to_string(i) + " << endl;\n";
	}
	else
	  printer += "\tv" + to_string(i) + "->print(tab+1);\n";
      }
      printer += "}\n";

      cout << printer << endl;

      functions = constructor + printer;

      cout << "bison reduction actions:" << endl;
      
      red_act = nt + "\n";
      
      for (int i = 0; i < rule->reductions->reds.size(); i ++){
	if (i == 0) red_act +=  "        : ";
	else red_act += "        | ";
	string redstring = rule->reductions->reds[i]->toString();
	red_act += redstring;
	for (int i = redstring.size(); i <= indent; i ++){
	  red_act += " ";
	}
	if (chosen_reds.find(i) == chosen_reds.end()) red_act += " { throw \"not implemented " + nt + "\"; } \n";
	else {
	  red_act += " { $$ = new S_" + nt + "(";
	  int nums = 0;
	  for (auto ntp: rule->reductions->reds[i]->non_terminal_pos) {
	    red_act += "$" + to_string(ntp);
	    nums ++;
	    if (nums != rule->reductions->reds[i]->non_terminal_pos.size())
	      red_act += ", ";
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
	inputs << en << endl;
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
      con_struct_ed = "struct S_" + nt + " {\n";
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
      constructor += "\tkind = static_cast<typeof(kind)>(enum_kind);\n";
      constructor += "}\n";
      cout << constructor << endl;
      
      string printer = "void S_" + nt + "::print(int tab) {\n";
      printer += "\tprint_tab(tab);\n";
      printer += "\tcout << \"+" + nt + "\";\n";
      printer += "\tswitch(kind) {\n";
      for (int i = 0; i < enums.size(); i ++) {
	printer += "\tcase " + to_string(i) + ":\n";
	printer += "\t\tcout << \" type: " + enums[i] + "\" << endl;\n";
	printer += "\t\tbreak;\n";
      }
      printer += "\t}\n";
      for (int i = 0; i < all_types.size(); i ++) {
	if (non_terminals.find(all_types[i]) == non_terminals.end()) {
	  printer += "\tprint_tab(tab+1);\n";
	  printer += "\tcout << v" + to_string(i) + " << endl;\n";
	}
	else 
	  printer += "\tif (v" + to_string(i) + " != NULL)\tv" + to_string(i) + "->print(tab+1);\n";
      }
      printer += "}\n";
      
      cout << printer << endl;

      functions = constructor + printer;
      
      cout << "bison reduction actions:" << endl;
      
      red_act = nt + "\n";
      
      for (int i = 0; i < rule->reductions->reds.size(); i ++){
	if (i == 0) red_act +=  "        : ";
	else red_act += "        | ";
	string redstring = rule->reductions->reds[i]->toString();
	red_act += redstring;
	for (int i = redstring.size(); i <= indent; i ++){
	  red_act += " ";
	}
	if (chosen_reds.find(i) == chosen_reds.end()) red_act += " { throw \"not implemented " + nt + "\"; } \n";
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
	inputs << en << endl;
	enums.push_back(en);
      }

      cout << "struct: " << endl;
      con_struct_ed = "struct S_" + nt + " {\n";
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
      int idx = 0;
      for (int cr: chosen_reds) {
	constructor_map[rule->reductions->reds[cr]->non_terminals_values].push_back(idx);
	idx ++;
      }
      
      vector<string> constructor_decls;
      vector<int> chosen_reds_vec;
      for (auto cr: chosen_reds){
	chosen_reds_vec.push_back(cr);
      }

      for (auto& [vec_types, vec_int]: constructor_map) {
	string constructor_decl = "S_" + nt + "(";
	for (int i = 0; i < vec_types.size(); i ++){
	  constructor_decl += "T_" + vec_types[i] + " a" + to_string(i);
	  if (i != vec_types.size() - 1) {
	    constructor_decl += ", ";
	  }
	}
	if (vec_int.size() > 1) {
	  if (vec_types.size() == 0)
	    constructor_decl += "int enum_kind";
	  else
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
	for (int i = 0; i < rule->reductions->reds[chosen_reds_vec[vi]]->non_terminals_values.size(); i ++){
	  constructor += "\t" + temp + ".v" + to_string(i) + " = a" + to_string(i) + ";\n";
	}
	if (vec_int.size() == 1) 
	  constructor += "\tkind = " + enums[vi] + ";\n}\n";
	else 
	  constructor += "\tkind = static_cast<typeof(kind)>(enum_kind);\n}\n";
	constructors.push_back(constructor);
	con_num ++;
      }
      string printer = "void S_" + nt + "::print(int tab) {\n";
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
	    if (non_terminals.find(vec_types[i]) == non_terminals.end()) {
	      printer += "\tprint_tab(tab+1);\n";
	      printer += "\tcout << " + temp + ".v" + to_string(i) + " << endl;\n";
	    }
	    else
	      printer += "\t\t" + temp + ".v" + to_string(i) + "->print(tab+1);\n";
	  }
	  printer += "\t\tbreak;\n";
	}
      }
      printer += "\t}\n}\n";
      functions = "";
      for (string con: constructors) {
	cout << con << endl;
	functions += con;
      }
      cout << printer << endl;
      functions += printer;


      cout << "bison reduction actions:" << endl;
      
      red_act = nt + "\n";
      
      for (int i = 0; i < rule->reductions->reds.size(); i ++){
	if (i == 0) red_act +=  "        : ";
	else red_act += "        | ";
	string redstring = rule->reductions->reds[i]->toString();
	red_act += redstring;
	for (int i = redstring.size(); i <= indent; i ++){
	  red_act += " ";
	}
	if (chosen_reds.find(i) == chosen_reds.end()) red_act += " { throw \"not implemented " + nt + "\"; } \n";
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
	  if (vei.size() > 1) {
	    if (rule->reductions->reds[i]->non_terminals_values.size() == 0)
	      red_act += to_string(i) + "); }\n";
	    else
	      red_act += ", " + to_string(i) + "); }\n";
	  }
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
      if (rule->reductions->reds[p1]->non_terminals_values.size() == 1 && rule->reductions->reds[p2]->non_terminals_values.size() == 2) {
	v1 = rule->reductions->reds[p1]->non_terminals_values;
	v2 = rule->reductions->reds[p2]->non_terminals_values;
      }
      else if (rule->reductions->reds[p1]->non_terminals_values.size() == 2 && rule->reductions->reds[p2]->non_terminals_values.size() == 1) {
	v1 = rule->reductions->reds[p2]->non_terminals_values;
	v2 = rule->reductions->reds[p1]->non_terminals_values;
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
      cout << "struct:" << endl;
      con_struct_ed = "struct S_" + nt + " {\n\tvector<T_" + v1[0] + "> v;\n";
      con_struct_ed += "\tT_" + nt + " add(T_" + v1[0] + " a);\n";
      con_struct_ed += "\tprint(int tab);\n}";
      cout << con_struct_ed << endl;
      cout << "functions:" << endl;
      string add_func = "T_" + nt + " S_" + nt + "::add(T_" + v1[0] + " a) {\n";
      add_func += "\tv.push_back(a);\n\treturn this;\n}\n";
      string printer = "void S_" + nt + "::print(int tab) {\n\tprint_tab(tab);\n\tcout << \"+" + nt + "\" << endl;\n\tfor(auto e: v) e->print(tab+1);\n}\n";
      
      cout << add_func << endl;
      cout << printer << endl;

      functions = add_func + printer;
      
      cout << "bison reduction actions:" << endl;
      
      red_act = nt + "\n";
      
      for (int i = 0; i < rule->reductions->reds.size(); i ++){
	if (i == 0) red_act +=  "        : ";
	else red_act += "        | ";
	string redstring = rule->reductions->reds[i]->toString();
	red_act += redstring;
	for (int i = redstring.size(); i <= indent; i ++){
	  red_act += " ";
	}
	if (chosen_reds.find(i) == chosen_reds.end()) red_act += " { throw \"not implemented " + nt + "\"; } \n";
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
      con_struct_ed = "struct S_" + nt + " {\n";
      for (int num = 0; num < all_types.size(); num ++) {
	con_struct_ed += "\tT_"+ all_types[num] + " v" + to_string(num) + ";\n";
      }
      string constructor_decl = "S_" + nt + "(";
      for (int num = 0; num < all_types.size(); num ++) {
	constructor_decl += "T_" + all_types[num] + " a" + to_string(num);
	if (num != all_types.size()-1)
	  constructor_decl += ", ";
      }
      constructor_decl += ")";
      con_struct_ed += "\t" + constructor_decl + ";\n";
      con_struct_ed += "\tvoid print(int tab);\n};\n";

      cout << con_struct_ed;
      
      cout << "functions:" << endl;
      string constructor = "S_" + nt + "::" + constructor_decl + "{\n";

      for (int i = 0; i < all_types.size(); i ++) {
	constructor += "\tv" + to_string(i) + " = " + "a" + to_string(i) + ";\n";
      }
      constructor += "}\n";
      cout << constructor << endl;
      
      string printer = "void S_" + nt + "::print(int tab) {\n";
      printer += "\tprint_tab(tab);\n";
      printer += "\tcout << \"+" + nt + "\" << endl;\n";
      for (int i = 0; i < all_types.size(); i ++) {
	if (non_terminals.find(all_types[i]) == non_terminals.end()) {
	  printer += "\tprint_tab(tab+1);\n";
	  printer += "\tcout << v" + to_string(i) + " << endl;\n";
	}
	else
	  printer += "\tif (v" + to_string(i) + " != NULL) v" + to_string(i) + "->print(tab+1);\n";
      }
      printer += "}\n";
      
      cout << printer << endl;

      functions = constructor + printer;
      
      cout << "bison reduction actions:" << endl;
      
      red_act = nt + "\n";
      
      for (int i = 0; i < rule->reductions->reds.size(); i ++){
	if (i == 0) red_act +=  "        : ";
	else red_act += "        | ";
	string redstring = rule->reductions->reds[i]->toString();
	red_act += redstring;
	for (int i = redstring.size(); i <= indent; i ++){
	  red_act += " ";
	}
	if (chosen_reds.find(i) == chosen_reds.end()) red_act += " { throw \"not implemented " + nt + "\"; } \n";
	else {
	  red_act += " { $$ = new S_" + nt + "(";
	  for (auto ntp: all_types) {
	    int x = rule->reductions->reds[i]->findIdx(ntp);
	    if (x == -1) {
	      red_act += "NULL";
	    }
	    else {
	      red_act += "$" + to_string(x);
	    }
	    if (ntp != all_types[all_types.size()-1]) {
	      red_act += ", ";
	    }
	  }
	  red_act += "); }\n";
	}
      }
      red_act += "        ;\n";
      cout << red_act << endl;
    }
    else if (op == "d") {
      cout << "write \"end\" when you have finished writing your stuff" << endl;
      cout << "write the struct definition" << endl;
      con_struct_ed = takeInputTillEnd();
      cout << "write the functions" << endl;
      functions = takeInputTillEnd();
      cout << "write the bison reduction actions" << endl;
      red_act = takeInputTillEnd();
    }
    else {
      cout << "please enter a valid option" << endl;
      goto choose_option;
    }

    cout << "do you want to confirm these generated fucntions? y/n" << endl;
    string yn; cin >> yn;
    inputs << yn << endl;
    if (yn == "y") {
      cout << "ok, writing functions to file" << endl;
      for (auto cr: chosen_reds) {
	for (string nont: rule->reductions->reds[cr]->non_terminals_values) {
	  if (done_nts.find(nont) == done_nts.end()){
	    if (non_terminals.find(nont) != non_terminals.end()) {
	      remaining_nts.insert(nont);
	    }
	  }
	}
      }
      remaining_nts.erase(nt);
      done_nts.insert(nt);
      done_nt_features[nt] = {con_struct_ed, functions, red_act};
    }
    else {
      cout << "discarding functions, continuing" << endl;
    }
    
  }
  ast_header << "#include <bits/stdc++.h>\nusing namespace std;\n\n";
  ast_header << "typedef char* T_intval;\ntypedef char* T_strval;\ntypedef char* T_floatval;\n";
  ast_cpp << "#include \"ast.h\"\n\n";
  ast_header << "void print_tab(int tab);\n";
  ast_cpp << "void print_tab(int tab) {\n\tfor(int i = 0; i < tab; i ++) {\n\t\tcout << \"|\";\n\t}\n}\n";

  
  bison_file << "%union value {\n";
  bison_file << "\tchar* strval;\n";
  bison_file << "\tchar* intval;\n";
  bison_file << "\tchar* floatval;\n";
  for (auto& nt: done_nts) {
    bison_file << "\tT_" + nt + " val_" + nt + ";\n";
  }
  bison_file << "};\n";
  for (auto& nt: done_nts) {
    bison_file << "%nterm <val_" + nt + "> " + nt + ";\n";
  }
  bison_file << endl;
  
  for (auto &[n_t, ntf]: done_nt_features) {
    ast_header << "struct S_" + n_t + ";\n";
  }
  for (auto &[n_t, ntf]: done_nt_features) {
    ast_header << "typedef struct S_" + n_t + "* T_" + n_t + ";\n";
  }
  for (auto &[n_t, ntf]: done_nt_features) {
    ast_header << ntf.struct_definition;
    ast_cpp << ntf.functions;
  }
  
  // bison_file << ntf.bison_actions;
  cout << "not done: " << endl;
  for (auto& [nt, rule]: non_terminals) {
    if (done_nts.find(nt) == done_nts.end()) {
      cout << nt << endl;
    }
    else continue;
    string red_act = nt + "\n";
    for (int i = 0; i < rule->reductions->reds.size(); i ++){
      if (i == 0) red_act +=  "        : ";
      else red_act += "        | ";
      string redstring = rule->reductions->reds[i]->toString();
      red_act += redstring;
      for (int i = redstring.size(); i <= indent; i ++){
	red_act += " ";
      }
      red_act += " { throw \"not implemented " + nt + "\"; } \n";
    }
    red_act += "        ;\n\n";
    done_nt_features[nt] = {"", "", red_act};
    // bison_file << red_act;
  }

  vector<pair<int, string>> ordered;
  for (auto &[nt_s, nt_n]: nt_order) {
    ordered.push_back({nt_n, nt_s});
  }
  sort(ordered.begin(), ordered.end());
  for (auto &[nt_n, nt]: ordered) {
    bison_file << done_nt_features[nt].bison_actions;
  }
  bison_file << endl;
}

int
main(int argc, char **argv)
{
  if (argc != 2) {
    exit(1);
  }
  char const *filename = argv[1];
  yyin = fopen(filename, "r");
  assert(yyin);
  int ret = yyparse();
  printf("retv = %d\n", ret);
  // prog_ast->print();
  merge_states();
  for (auto& [st, tr]: merged_non_terminals) {
    tr->print_pretty();
    cout << endl;
  }
  create_ast();
  exit(0);
}
