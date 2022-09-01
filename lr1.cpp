#include<bits/stdc++.h>

using namespace std;

struct symbol{
  int id;
  bool operator< (const symbol &x) const {
    return id < x.id;
  }
  bool operator== (const symbol &x) const {
    return id == x.id;
  }
};

vector<string> map_symbol;

bool file_given = false;
ifstream inputstream;

struct rule {
  int id;
  symbol lhs;
  vector<symbol> rhs; // empty means epsilon production
  void print (int pointer){
    cout << map_symbol[lhs.id] << " -> ";
    for (int i = 0; i < pointer; i ++){
      cout << map_symbol[rhs[i].id];
    }
    cout << ".";
    for (int i = pointer; i < rhs.size(); i ++){
      cout << map_symbol[rhs[i].id];
    }
  }
};

map<string, symbol> symbol_map;

vector<rule> rules;

vector<vector<int>> non_terminal_rules;

vector<bool> is_terminal;

vector<set<int>> first, follow;
vector<bool> nullable;

int start_symbol;

struct lr1_item {
  int rule_num;
  int pointer;
  bool operator< (const lr1_item &x) const {
    if (x.rule_num == rule_num) {
      return x.pointer < pointer;
    }
    return x.rule_num < rule_num;
  }
  symbol current_symbol () const {
    if (pointer < rules[rule_num].rhs.size()){
      return rules[rule_num].rhs[pointer];
    }
    return {-1};
  }
};

struct lr1_state {
  int state_num;
  map<lr1_item, set<symbol>> lr1_items; // maps a rule and a pointer with the end terminals
  bool operator< (const lr1_state &x) const {
    return lr1_items < x.lr1_items;
  }
  void print () const {
    cout << "STATE " << state_num << endl;
    for (auto& [item, ends]: lr1_items){
      rules[item.rule_num].print(item.pointer);
      cout << ", ";
      auto en = ends.begin();
      cout << map_symbol[(*en).id];
      en ++;
      for (; en != ends.end(); en++){
	cout << "/" << map_symbol[(*en).id];
      }
      cout << endl;
    }
  }
  map<symbol, lr1_state> get_transitions () const {
    // already expanded
    map<symbol, lr1_state> trans;
    for (auto &[li, ends]: lr1_items){
      symbol sy = li.current_symbol();
      if (sy.id != -1){
	auto shifted_li = li;
	shifted_li.pointer ++;
	trans[sy].lr1_items[shifted_li] = ends;
      }
    }
    for (auto & [sy, ls]: trans){
      ls.expand();
    }
    return trans;
  }
  void expand(){
    bool changed = false;
    for (auto& item_end_pair: lr1_items){
      auto& item = item_end_pair.first;
      if (item.pointer < rules[item.rule_num].rhs.size()){
	symbol next_sym = rules[item.rule_num].rhs[item.pointer];
	if (!is_terminal[next_sym.id]){
	  // have to add the productions of next_sym in the lr1 state
	  // have to see what the ends are, lets see
	  set<symbol> new_ends;
	  // check nullability of the leftover string and add the ends in item_end_pair if it is nullable
	  // otherwise add the firsts of all of the things till last non-nullable
	  int start_p = item.pointer + 1;
	  for (; start_p < rules[item.rule_num].rhs.size(); start_p ++){
	    // add the first of this thing to new_ends
	    for (auto fi: first[rules[item.rule_num].rhs[start_p].id]){
	      new_ends.insert({fi});
	    }
	    if (!nullable[rules[item.rule_num].rhs[start_p].id]){
	      break;
	    }
	  }
	  if (start_p == rules[item.rule_num].rhs.size()){
	    // add the ends of item_end_pair
	    auto& this_ends = item_end_pair.second;
	    for (auto en: this_ends){
	      new_ends.insert(en);
	    }
	  }
	  // now for all production rules of the next_sym
	  for (auto rr: non_terminal_rules[next_sym.id]){
	    lr1_item ni = {rr, 0};
	    if (lr1_items.find(ni) == lr1_items.end()){
	      changed = true;
	      lr1_items[ni] = new_ends;
	    }
	    else {
	      for (auto nee: new_ends){
		if (lr1_items[ni].find(nee) == lr1_items[ni].end()){
		  lr1_items[ni].insert(nee);
		  changed = true;
		}
	      }
	    }
	  }
	}
      }
    }
    if (changed){
      expand();
    }
  }
};


void print_grammar (){
  for (auto& r: rules){
    cout << map_symbol[r.lhs.id] << " -> ";
    for (auto& s: r.rhs){
      cout << map_symbol[s.id];
    }
    cout << endl;
  }
  cout << "NON TERMINAL RULES" << endl;
  for (int i = 0; i < non_terminal_rules.size(); i ++){
    for (int j = 0; j < non_terminal_rules[i].size(); j ++){
      if (!is_terminal[i]){
	cout << map_symbol[i] << "    ";
	auto r = rules[non_terminal_rules[i][j]];
	cout << map_symbol[r.lhs.id] << " -> ";
	for (auto& s: r.rhs){
	  cout << map_symbol[s.id];
	}
	cout << endl;
      }
    }
  }
  cout << "nullable: " << endl;
  for (int i = 0; i < nullable.size(); i ++){
    cout << map_symbol[i] << " " << nullable[i] << endl;
  }
  cout << "first: " << endl;
  for (int i = 0; i < first.size(); i ++){
    cout << map_symbol[i] << " ";
    for (auto j: first[i]){
      cout << map_symbol[j] << ", ";
    }
    cout << endl;
  }
  
  cout << "follow: " << endl;
  for (int i = 0; i < follow.size(); i ++){
    cout << map_symbol[i] << " ";
    for (auto j: follow[i]){
      cout << map_symbol[j] << ", ";
    }
    cout << endl;
  }
  
}

vector<string> split (string s){
  s += " ";
  vector<string> sp;
  int np = 0;
  string cs = "";
  while (np < s.size()){
    if (s[np] == ' ' || s[np] == '\n') {
      if (cs.size() > 0){
	sp.push_back(cs);
	cs = "";
      }
      np ++;
    }
    else {
      cs += s[np];
      np ++;
    }
  }
  return sp;
}

void input_declaration (){
  cout << "General rules:\nDo not add the $ symbol for eof, however do make a start symbol which isn't produced" << endl;
  cout << "enter declaration, (format NT name | T name | END)" << endl;
  while (true){
    string s;
    if (file_given)
      getline(inputstream, s);
    else
      getline(cin, s);
    if (s == "END"){
      break;
    }
    auto v = split(s);
    if (v.size() != 2){
      throw ("invalid format for declaration");
    }
    if (symbol_map.find(v[1]) != symbol_map.end()){
      throw (v[1] + " already declared");
    }
    if (v[1] == "$"){
      throw ("$ will be used automatially as eof character, donot declare it as a symbol");
    }
    if (v[0] == "NT"){
      symbol_map[v[1]] = {map_symbol.size()};
      map_symbol.push_back(v[1]);
      is_terminal.push_back(false);
      non_terminal_rules.push_back(vector<int>());
    }
    else if (v[0] == "T") {
      symbol_map[v[1]] = {map_symbol.size()};
      is_terminal.push_back(true);
      map_symbol.push_back(v[1]);
      non_terminal_rules.push_back(vector<int>());
    }
    else {
      throw ("invalid format for declaration");
    }
  }
}

bool input_single_rule (){
  string s;
  if (file_given)
    getline(inputstream, s);
  else
    getline(cin, s);
  if (s == "END"){
    return false;
  }
  auto v = split(s);
  if (v.size() < 3){
    throw ("invalid rule format");
  }
  rule r = rule();
  r.id = rules.size();
  auto nt = v[0];
  if (symbol_map.find(nt) == symbol_map.end() || is_terminal[symbol_map[nt].id]){
    throw ("non terminal " + nt + " not declared, invalid rule");
  }
  non_terminal_rules[symbol_map[v[0]].id].push_back(r.id);
  r.lhs = symbol_map[nt];
  rules.push_back(r);
  if (v[1] != "->"){
    throw ("expected ->, invalid rule");
  }
  for (int i = 2; i < v.size(); i ++){
    if (v[i] == "|"){
      rule nr = rule();
      nr.id = rules.size();
      non_terminal_rules[symbol_map[v[0]].id].push_back(nr.id);
      nr.lhs = symbol_map[nt];
      rules.push_back(nr);
    }
    else if (v[i] == "eps"){
      continue;
    }
    else {
      if (symbol_map.find(v[i]) == symbol_map.end()){
	throw (v[i] + " neither a terminal or a non-terminal, invalid rule");
      }
      else {
	rules[rules.size()-1].rhs.push_back(symbol_map[v[i]]);
      }
    }
  }
  return true;
}

void input_rules (){
  cout << "enter production rules " << endl
       << "(END to exit)" << endl
       << "(rule format: NT -> a B c | e F | eps | ..., \neach symbol separated by a space,\nfor empty string just have space in between two | or use eps)" << endl;
  while (input_single_rule());
  cout << "Enter the starting Non-terminal name" << endl;
  string s;
  if (file_given)
    inputstream >> s;
  else
    cin >> s;
  if (symbol_map.find(s) == symbol_map.end() || is_terminal[symbol_map[s].id]){
    throw ("start symbol not a non-terminal");
  }
  int st_id = symbol_map[s].id;
  if (non_terminal_rules[st_id].size() != 1){
    throw ("start symbol has more than one or zero rules");
  }
  symbol_map["$"] = {map_symbol.size()};
  map_symbol.push_back("$");
  is_terminal.push_back(true);  
  non_terminal_rules.push_back(vector<int>());
  start_symbol = st_id;
}

void rec_null (){
  bool changed = false;
  for (int i = 0; i < nullable.size(); i ++){
    if (nullable[i]){
      continue;
    }
    if (!is_terminal[i]){
      for (auto r: non_terminal_rules[i]){
	bool isn = true;
	for (auto symb: rules[r].rhs){
	  if (!nullable[symb.id]){
	    isn = false;
	    break;
	  }
	}
	if (isn){
	  changed = true;
	  nullable[i] = true;
	  break;
	}
      }
    }
  }
  if (!changed){
    return;
  }
  rec_null();
}

void make_nullable (){
  nullable = vector<bool>(is_terminal.size());
  for (int i = 0; i < nullable.size(); i ++){
    nullable[i] = false;
    if (!is_terminal[i]){
      for (auto r: non_terminal_rules[i]){
	if (rules[r].rhs.size() == 0){
	  nullable[i] = true;
	  break;
	}
      }
    }
  }
  rec_null();
}

void rec_first (){
  bool changed = false;
  for (int i = 0; i < first.size(); i ++){
    if (!is_terminal[i]){
      for (auto r: non_terminal_rules[i]){
	for (auto symb: rules[r].rhs){
	  for (auto s_fir: first[symb.id]){
	    if (first[i].find(s_fir) == first[i].end()){
	      changed = true;
	      first[i].insert(s_fir);
	    }
	  }
	  if (!nullable[symb.id]){
	    break;
	  }
	}
      }
    }
  }
  if (!changed){
    return;
  }
  rec_first();
}

void make_first (){
  first = vector<set<int>>(is_terminal.size());
  for (int i = 0; i < first.size(); i ++){
    if (is_terminal[i]){
      first[i].insert(i);
    }
  }
  rec_first();
}

void rec_follow (){
  bool changed = false;
  for (int i = 0; i < follow.size(); i ++){
    if (!is_terminal[i]){
      for (auto r: non_terminal_rules[i]){
	int u ;
	if (rules[r].rhs.size() == 0){ // epsilon production
	  // cant do anything
	  continue;
	}
	for (u = rules[r].rhs.size()-1; u >= 0; u --){
	  if (!nullable[rules[r].rhs[u].id]){
	    break;
	  }
	}
	for (int j = rules[r].rhs.size()-1; j >= max(u, 0); j --){
	  // follow of rules[r].rhs[j] contains follow of u
	  if (rules[r].rhs[j].id == i){
	    continue;
	  }
	  for (auto f1: follow[i]){
	    if (follow[rules[r].rhs[j].id].find(f1) == follow[rules[r].rhs[j].id].end()){
	      changed = true;
	      follow[rules[r].rhs[j].id].insert(f1);
	    }
	  }
	}
	for (int j = 0; j < rules[r].rhs.size()-1; j ++){
	  // follow of rules[r][rhs[j]] contains first of rules[r][rhs[j+1]]
	  if (rules[r].rhs[j].id == i){
	    continue;
	  }
	  for (auto f1: first[rules[r].rhs[j+1].id]){
	    if (follow[rules[r].rhs[j].id].find(f1) == follow[rules[r].rhs[j].id].end()){
	      changed = true;
	      follow[rules[r].rhs[j].id].insert(f1);
	    }
	  }
	}
      }
    }
  }
  if (!changed){
    return;
  }
  rec_follow();
}

void make_follow (){
  follow = vector<set<int>>(is_terminal.size());
  follow[start_symbol].insert(is_terminal.size()-1); // last one is dollar symbol
  rec_follow();
}

set<lr1_state> make_new_states () {
  set<lr1_state> all_states;
  queue<lr1_state> q;
  lr1_state s0;
  int state_num = 0;
  int rnum = non_terminal_rules[start_symbol][0];
  s0.lr1_items[{rnum, 0}].insert({is_terminal.size()-1}); // dollar
  s0.expand();
  q.push(s0);
  while (q.size() > 0){
    auto & curr_state = q.front();
    if (all_states.find(curr_state) != all_states.end()){
      q.pop();
      continue;
    }
    curr_state.state_num = state_num;
    state_num ++;
    all_states.insert(curr_state);
    auto mp = curr_state.get_transitions();
    for (auto &[sym, lr1s]: mp){
      q.push(lr1s);
    }
    q.pop();
  }
  return all_states;
}


map<pair<int, symbol>, int> get_all_transitions (set<lr1_state> & all_states){
  map<pair<int, symbol>, int> trans;
  for (auto & st: all_states){
    auto mp = st.get_transitions();
    for (auto &[sy, lr1s]: mp){
      trans[{st.state_num, sy}] = (*all_states.find(lr1s)).state_num;
    }
  }
  return trans;
}

int main (int argc, char *argv[]){
  try {
    if (argc > 1){
      file_given = true;
      inputstream.open(argv[1]);
    }
    input_declaration();
    input_rules();
    cout << "nullable" << endl;
    make_nullable();
    cout << "first" << endl;
    make_first();
    cout << "follow" << endl;
    make_follow();
    print_grammar();
    set<lr1_state> all_states = make_new_states();
    vector<lr1_state> sorted_states;
    for (auto & st: all_states){
      sorted_states.push_back(st);
    }
    sort (sorted_states.begin(), sorted_states.end(), [](const lr1_state& a, const lr1_state& b) {return a.state_num < b.state_num;});
    for (auto & st: sorted_states){
      st.print();
      cout << endl;
    }
    auto trans = get_all_transitions(all_states);
    for (auto & [stsym, nst]: trans){
      auto& [st, sym] = stsym;
      cout << st << ", " << map_symbol[sym.id] << " => " << nst << endl;
    }
  }
  catch (char const * err){
    cout << err << endl;
  }  
}
