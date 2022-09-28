#include "bison_ast.h"


bool hasValue(string s){
  if (s[0] == '\''){
    return false;
  }
  if (s[0] <= 'z' && s[0] >= 'a'){ // non-terminal
    return true;
  }
  else { // terminal, check if it has value
    // TODO
    return false;
  }
}

void S_reduction::add (string str){
  values.push_back(str);
  if (hasValue(str)){
    // for (auto str2: non_terminals_values){
    //   if (str == str2) {
    // 	cout << "repeated " << str << endl;
    //   }
    // }
    non_terminals_values.push_back(str);
    non_terminal_pos.push_back(values.size());
  }
}

int S_reduction::findIdx (string nt) {
  for (int i = 0; i < non_terminals_values.size(); i ++){
    if (non_terminals_values[i] == nt) {
      return non_terminal_pos[i];
    }
  }
  return -1;
}

S_reduction::S_reduction (){
  values = vector<string>();
}

S_reduction_list::S_reduction_list() {
  reds = vector<T_reduction>();
}
void S_reduction_list::add (T_reduction red){
  reds.push_back(red);
}

S_rule_list::S_rule_list () {
  rules = vector<T_rule>();
}
void S_rule_list::add (T_rule r){
  rules.push_back(r);
}

S_token_decl_list::S_token_decl_list() {
  decls = vector<T_token_decl>();
}
void S_token_decl_list::add (T_token_decl decl){
  decls.push_back(decl);
}

S_terminal_list::S_terminal_list(){
  tds = vector<string>();
}
void S_terminal_list::add (string t){
  tds.push_back(t);
}

void print_str(int tab, string str, const string extra){
  for (int i = 0; i < tab; i ++){
    cout << "|";
  }
  cout << "+" << extra << str << endl;
}

void print_str(int tab, string str){
  for (int i = 0; i < tab; i ++){
    cout << "|";
  }
  cout << "+" << str << endl;
}

void S_prog::print() {
  cout << "+program" << endl;
  tdl->print(1);
  rl->print(1);
}

void S_reduction::print(int tab){
  for (int i = 0; i < tab; i ++){
    cout << "|";
  }
  cout << "+reduction" << endl;
  for (int i = 0; i < values.size(); i ++){
    print_str(tab+1, values[i]);
  }
}

void S_reduction_list::print(int tab){
  for (int i = 0; i < tab; i ++){
    cout << "|";
  }
  cout << "+reduction_list" << endl;
  for (T_reduction re: reds){
    re->print(tab+1);
  }
}

void S_rule::print(int tab){
  for (int i = 0; i < tab; i ++){
    cout << "|";
  }
  cout << "+rule" << endl;
  print_str(tab+1, product, "product: ");
  reductions->print(tab+1);
}

void S_rule_list::print(int tab){
  for (int i = 0; i < tab; i ++){
    cout << "|";
  }
  cout << "+rule_list" << endl;
  for (T_rule re: rules){
    re->print(tab+1);
  }
}

void S_terminal_list::print(int tab){
  for (int i = 0; i < tab; i ++){
    cout << "|";
  }
  cout << "+terminal_list" << endl;
  for (string ch: tds){
    print_str(tab+1, ch);
  }
}

void S_token_decl::print(int tab){
  for (int i = 0; i < tab; i ++){
    cout << "|";
  }
  cout << "+token_decl" << endl;
  tl->print(tab+1);
}

void S_token_decl_list::print(int tab){
  for (int i = 0; i < tab; i ++){
    cout << "|";
  }
  cout << "+token_decl_list" << endl;
  for (T_token_decl td: decls){
    td->print(tab+1);
  }
}

void S_reduction::print_pretty(){
  for (string s: values){
    cout << s << " ";
  }
  cout << endl;
}

string S_reduction::toString() {
  string a = "";
  for (string s: values){
    a += s + " ";
  }
  return a;
}

void S_reduction_list::print_pretty() {
  for (int i = 0; i < reds.size(); i ++){
    cout << "        ";
    if (i == 0) cout << ": ";
    else cout << "| ";
    reds[i]->print_pretty();
  }
  cout << "        ;" << endl;
}

void S_rule::print_pretty() {
  cout << product << endl;
  reductions->print_pretty();
}

T_terminal_list T_create_terminal_list(char* t) {
  T_terminal_list tl = new S_terminal_list();
  tl->add(t);
  return tl;
}

T_terminal_list T_add_to_terminal_list(T_terminal_list tl, char* t) {
  tl->add(t);
  return tl;
}

T_reduction T_create_reduction_terminal(char* name) {
  T_reduction red = new S_reduction();
  red->add(name);
  return red;
}

T_reduction T_create_reduction_non_terminal(char* name) {
  T_reduction red = new S_reduction();
  red->add(name);
  return red;
}

T_reduction T_create_reduction_character(char* name) {
  T_reduction red = new S_reduction();
  red->add(name);
  return red;
}

T_reduction T_add_to_reduction_non_terminal(T_reduction red, char* name) {
  red->add(name);
  return red;
}

T_reduction T_add_to_reduction_terminal(T_reduction red, char* name) {
  red->add(name);
  return red;
}

T_reduction T_add_to_reduction_character(T_reduction red, char* name) {
  red->add(name);
  return red;
}

T_reduction_list T_create_reduction_list (T_reduction red) {
  T_reduction_list rl = new S_reduction_list();
  rl->add(red);
  return rl;
}

T_reduction_list T_add_to_reduction_list (T_reduction_list rl, T_reduction r) {
  rl->add(r);
  return rl;
}

T_rule T_create_rule(char* nt, T_reduction_list redl){
  T_rule r = new S_rule();
  r->reductions = redl;
  r->product = nt;
  if (non_terminals.find(nt) != non_terminals.end()){
    cout << "non terminal already " + string(nt) + " has more than one reductions" << endl;
    exit(0);
  }
  non_terminals[nt] = r;
  return r;
}

T_rule_list T_create_rule_list(T_rule rule){
  T_rule_list r = new S_rule_list();
  r->add(rule);
  return r;
}

T_rule_list T_add_to_rule_list(T_rule_list r, T_rule rule){
  r->add(rule);
  return r;
}

T_token_decl T_create_token_decl(T_terminal_list tl){
  return T_create_token_decl("", tl);
}

T_token_decl T_create_token_decl(char* type, T_terminal_list tl){
  T_token_decl td = new S_token_decl();
  td->tl = tl;
  td->type = type;
  for (string term: tl->tds){
    if (token_types.find(term) != token_types.end()){
      cout << "token " + term + " declared more than once" << endl;
      exit(0);
    }
    token_types[term] = type;
  }
  return td;
}

T_token_decl_list T_create_token_decl_list(T_token_decl td){
  T_token_decl_list tdl = new S_token_decl_list();
  tdl->add(td);
  return tdl;
}

T_token_decl_list T_add_to_token_decl_list(T_token_decl_list tdl, T_token_decl td){
  tdl->add(td);
  return tdl;
}

T_prog T_create_prog(T_token_decl_list tdl, T_rule_list rl){
  T_prog pg = new S_prog();
  pg->tdl = tdl;
  pg->rl = rl;
  return pg;
}

char* tostrval(char *yytext) {
  size_t len = strlen(yytext);
  char *strval = (char*) malloc(sizeof(char *) * len + 1);  // add one for the end character
  strval = strncpy(strval, yytext, len);
  strval[len] = '\0';
  return strval;
}
