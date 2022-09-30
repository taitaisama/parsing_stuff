#include <bits/stdc++.h>
using namespace std;

typedef struct S_reduction* T_reduction;
typedef struct S_reduction_list* T_reduction_list;
typedef struct S_rule* T_rule;
typedef struct S_rule_list* T_rule_list;
typedef struct S_terminal_list* T_terminal_list;
typedef struct S_token_decl* T_token_decl;
typedef struct S_token_decl_list* T_token_decl_list;
typedef struct S_prog* T_prog;

void print(int tab, string str, string extra);
void print(int tab, string str);

struct S_reduction {
  vector<string> values;
  vector<string> non_terminals_values;
  vector<int> non_terminal_pos;
  void add (string str);
  S_reduction ();
  void print(int tab);
  void print_pretty();
  string toString();
  string toStringReplaced(map<string, string> &mp) {
  int findIdx (string nt);
  T_reduction dup();
  void exchange (string ct, set<string> &cf);
};

struct S_reduction_list {
  vector<T_reduction> reds;
  S_reduction_list();
  void add (T_reduction red);
  void print(int tab);
  void print_pretty();
  T_reduction_list dup();
  void remove_dups();
};

struct S_rule {
  T_reduction_list reductions;
  string product;
  void print(int tab);
  void print_pretty();
  T_rule dup();
  void remove_dups();
};

struct S_rule_list {
  vector<T_rule> rules;
  S_rule_list ();
  void add (T_rule r);
  void print(int tab);
};

struct S_terminal_list {
  vector<string> tds;
  S_terminal_list();
  void add (string t);
  void print(int tab);
};

struct S_token_decl {
  T_terminal_list tl;
  string type = "";
  void print(int tab);
};

struct S_token_decl_list {
  vector<T_token_decl> decls;
  S_token_decl_list();
  void add (T_token_decl decl);
  void print(int tab);
};

struct S_prog {
  T_token_decl_list tdl;
  T_rule_list rl;
  void print();
};

extern map<string, T_rule> non_terminals;
extern map<string, string> token_types;
extern map<string, int> nt_order;

T_terminal_list T_create_terminal_list(char* t);

T_terminal_list T_add_to_terminal_list(T_terminal_list tl, char* t);

T_reduction T_create_reduction_terminal(char* name);

T_reduction T_create_reduction_non_terminal(char* name);

T_reduction T_create_reduction_character(char* name);

T_reduction T_add_to_reduction_non_terminal(T_reduction red, char* name);

T_reduction T_add_to_reduction_terminal(T_reduction red, char* name);

T_reduction T_add_to_reduction_character(T_reduction red, char* name);

T_reduction_list T_create_reduction_list (T_reduction red);

T_reduction_list T_add_to_reduction_list (T_reduction_list rl, T_reduction r);

T_rule T_create_rule(char* nt, T_reduction_list redl);

T_rule_list T_create_rule_list(T_rule rule);

T_rule_list T_add_to_rule_list(T_rule_list r, T_rule rule);

T_token_decl T_create_token_decl(T_terminal_list tl);

T_token_decl T_create_token_decl(char* type, T_terminal_list tl);

T_token_decl_list T_create_token_decl_list(T_token_decl td);

T_token_decl_list T_add_to_token_decl_list(T_token_decl_list tdl, T_token_decl td);

T_prog T_create_prog(T_token_decl_list tdl, T_rule_list rl);

char* tostrval(char *yytext);

char* typetostrval(char *yytext);

