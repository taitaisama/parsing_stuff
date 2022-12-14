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
  bool is_reduction () const {
    return (pointer == rules[rule_num].rhs.size());
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
  vector<pair<int, symbol>> get_reductions () const {
    vector<pair<int, symbol>> reds;
    for (auto & [lri, ss]: lr1_items){
      if (lri.is_reduction()){
	for (auto symb: ss){
	  reds.push_back({lri.rule_num, symb});
	}
      }
    }
    return reds;
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

struct lalr_intermediate {
  set<lr1_item> noends;
  int state_num = 0;
  lalr_intermediate (const lr1_state & x){
    state_num = x.state_num;
    for (auto & [lri, ends]: x.lr1_items){
      noends.insert(lri);
    }
  }
  lalr_intermediate (const lalr_intermediate & x){
    state_num = x.state_num;
    noends = x.noends;
  }
  lalr_intermediate (){
    
  }
  bool operator< (const lalr_intermediate & x) const {
    return noends < x.noends;
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
      symbol_map[v[1]] = {(int)map_symbol.size()};
      map_symbol.push_back(v[1]);
      is_terminal.push_back(false);
      non_terminal_rules.push_back(vector<int>());
    }
    else if (v[0] == "T") {
      symbol_map[v[1]] = {(int)map_symbol.size()};
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
  symbol_map["$"] = {(int)map_symbol.size()};
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
  s0.lr1_items[{rnum, 0}].insert({((int)is_terminal.size())-1}); // dollar
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

enum type {
  shift = 0,
  reduc = 1,
  go_to = 2,
  err = 3
};
 
vector<vector<pair<int, type>>> make_transition_table (map<pair<int, symbol>, int> & trans, set<lr1_state> & all_states){
  int nstates = all_states.size();
  vector<vector<pair<int, type>>> table(nstates, vector<pair<int, type>>(is_terminal.size(), {0, err}));
  for (int state = 0; state < nstates; state ++){
    for (int sym = 0; sym < is_terminal.size(); sym ++){
      if (trans.find({state, {sym}}) != trans.end()){
	if (is_terminal[sym])
	  table[state][sym] = {trans[{state, {sym}}], shift};
	else
	  table[state][sym] = {trans[{state, {sym}}], go_to};
      }
    }
  }
  for (auto st: all_states){
    vector<pair<int, symbol>> reds = st.get_reductions(); // rule number and symbol
    for (auto [rule_num, sym]: reds) {
      if (table[st.state_num][sym.id].second != err){
	if (table[st.state_num][sym.id].second == shift){
	  throw ("LR(1) incompatible grammer, shift reduce conflict in state " + to_string(st.state_num) + " for symbol " + map_symbol[sym.id]);
	}
	else {
	  throw ("LR(1) incompatible grammer, reduce reduce conflict in state " + to_string(st.state_num) + " for symbol " + map_symbol[sym.id]);
	}
      }
      table[st.state_num][sym.id] = {rule_num, reduc};
    }
  }
  return table;
}

void write_transition_table (vector<vector<pair<int, type>>> & table){
  vector<int> reorder;
  for (int i = 0; i < is_terminal.size(); i ++){
    reorder.push_back(i);
  }
  sort(reorder.begin(), reorder.end(), [](int a, int b) { return is_terminal[a] > is_terminal[b]; });
  // reorder = {8, 7, 5, 6, 3, 4, 0, 2, 1};
  cout << "\\hline\n";
  cout << "\\diagbox{state}{token} ";
  for (int sym = 0; sym < is_terminal.size(); sym ++){
    if (map_symbol[reorder[sym]] == "$"){  
      cout << " & \\" <<  map_symbol[reorder[sym]];
    }
    else {
      cout << " & " <<  map_symbol[reorder[sym]];
    }
  }
  cout << "\\\\\n\\hline\n\\hline\n";
  for (int state = 0; state < table.size(); state ++){
    cout << state;
    for (int sym = 0; sym < is_terminal.size(); sym ++){
      if (table[state][reorder[sym]].second == err){
	cout << " & ";
      }
      else if (table[state][reorder[sym]].second == reduc){
	cout << " & $r_{" << table[state][reorder[sym]].first << "}$";
      }
      else if (table[state][reorder[sym]].second == shift){
	cout << " & $s_{" << table[state][reorder[sym]].first << "}$";
      }
      else {	
	cout << " & $" << table[state][reorder[sym]].first << "$";
      }
    }
    cout << "\\\\\n\\hline\n";
  }
  cout << endl;
}

vector<vector<pair<int, type>>> make_lalr (vector<vector<pair<int, type>>> & table, vector<lr1_state> & sorted_states){
  set<lalr_intermediate> lalr1_states;
  vector <lalr_intermediate> intermediate_map(sorted_states.size());
  for (auto & ls: sorted_states){
    auto lai = lalr_intermediate(ls);
    intermediate_map[ls.state_num] = lai;
    if (lalr1_states.find(lai) == lalr1_states.end()){
      lalr1_states.insert(lai);
    }
  }
  vector<int> compress_map(sorted_states.size());
  vector<string> compress_sets_string(sorted_states.size(), "");
  cout << "lalr state compression\n";
  for (int sn = 0; sn < sorted_states.size(); sn++){
    auto & li = intermediate_map[sn];
    compress_map[sn] = (*lalr1_states.find(li)).state_num;
    auto & str = compress_sets_string[(*lalr1_states.find(li)).state_num];
    if (str.size() != 0)
      compress_sets_string[(*lalr1_states.find(li)).state_num] += ", " + to_string(sn);
    else
      compress_sets_string[(*lalr1_states.find(li)).state_num] += to_string(sn);
    cout << sn << ": " << compress_map[sn] << endl;
  }
  vector<vector<pair<int, type>>> new_table(sorted_states.size(), vector<pair<int, type>>(is_terminal.size(), {0, err}));
  for (int s1 = 0; s1 < compress_map.size(); s1 ++){
    // s1 -> s2
    int s2 = compress_map[s1];
    int idx = 0;
    for (auto [num, ty]: table[s1]){
      if (ty == err){
	idx ++;
	continue;
      }
      if (ty == reduc){
	if (new_table[s2][idx].second == err){
	  new_table[s2][idx] = {num, ty};
	}
	else if (new_table[s2][idx].second == reduc){
	  if (new_table[s2][idx].first != num){
	    throw ("reduce reduce conflict in LALR(1) table generation when merging state set {" + compress_sets_string[s2] + "} at the symbol " + map_symbol[idx]);
	  }
	}
	else if (new_table[s2][idx].second == shift){
	  throw ("shift reduce conflict in LALR(1) table generation when merging state set {" + compress_sets_string[s2] + "} at the symbol " + map_symbol[idx]);
	}
      }
      else if (ty == shift){
	if (new_table[s2][idx].second == err){
	  new_table[s2][idx] = {compress_map[num], ty};
	}
	else if (new_table[s2][idx].second == reduc){
	  throw ("shift reduce conflict in LALR(1) table generation when merging state set {" + compress_sets_string[s2] + "} at the symbol " + map_symbol[idx]);
	}
	else if (new_table[s2][idx].second == shift){
	  if (new_table[s2][idx].first != compress_map[num]){
	    throw ("shift shift conflict in LALR(1) table generation when merging state set {" + compress_sets_string[s2] + "} at the symbol " + map_symbol[idx]); // this really shouldn't happen tho
	  }
	}
      }
      else { // ty = goto, so we have err and goto only from non-terminal
	if (new_table[s2][idx].second == err){
	  new_table[s2][idx] = {compress_map[num], ty};
	}
	else if (new_table[s2][idx].second == go_to){
	  if (new_table[s2][idx].first != compress_map[num]){
	    throw ("shift shift (goto) conflict in LALR(1) table generation when merging state set {" + compress_sets_string[s2] + "} at the symbol " + map_symbol[idx]);
	  }
	}
      }
      idx ++;
    }
  }
  return new_table;
}

vector<vector<pair<int, type>>> table_remove (vector<vector<pair<int, type>>> & table){
  vector<vector<pair<int, type>>> stmp;
  vector<int> sm(table.size(), 0);
  for (int i = 0; i < table.size(); i ++){
    // check if the row is empty (all errors)
    bool is_empty = true;
    for (auto [nm, ty]: table[i]){
      if (ty != err) {is_empty = false; break;}
    }
    if (!is_empty){      
      sm[i] = stmp.size();
      stmp.push_back(table[i]);
    }
  }
  for (int i = 0; i < stmp.size(); i ++){
    for (auto & [num, ty] : stmp[i]){
      if (ty == shift || ty == go_to){
	num = sm[num];
      }
    }
  }
  return stmp;
}

vector<vector<pair<int, type>>> reorder_states (vector<vector<pair<int, type>>> & table, vector<int> & reorder) {
  vector<vector<pair<int, type>>> new_table(table.size());
  for (int i = 0; i < table.size(); i ++){
    new_table[i] = table[reorder[i]];
    for (auto & [nm, ty] : new_table[i]){
      if (ty == shift || ty == go_to){
	nm = reorder[nm];
      }
    }
  }
  return new_table;
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
    auto table = make_transition_table(trans, all_states);
    write_transition_table(table);
    auto new_table = make_lalr(table, sorted_states);
    write_transition_table(new_table);
    auto reduced_table = table_remove(new_table);
    write_transition_table(reduced_table);
    // vector<int> sm(11, 0);
    // sm[4] = 1;
    // sm[3] = 2;
    // sm[2] = 3;
    // sm[1] = 4;
    // sm[5] = 7;
    // sm[6] = 6;
    // sm[7] = 5;
    // sm[8] = 10;
    // sm[9] = 9;
    // sm[10] = 8;
    // sm[0] = 0;
    // cout << reduced_table.size() << endl;
    // auto final_table = reorder_states(reduced_table, sm);
    // write_transition_table(final_table);
  }
  catch (string err){
    cout << err << endl;
  }
  catch (char const * err){
    cout << err << endl;
  }
}
