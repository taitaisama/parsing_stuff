bison: bison.cpp bison.tab.cpp bison.lex.cpp
	g++ -g bison_ast.cpp bison.tab.cpp bison.lex.cpp bison.cpp  -I.

bison.tab.cpp bison.tab.hpp: bison.y
	bison -o bison.tab.cpp -v -d bison.y

bison.lex.cpp: bison.l bison.tab.hpp
	flex -o bison.lex.cpp -l bison.l

clean::
	rm -f bison.tab.cpp bison.tab.hpp bison.lex.cpp bison.output *~ bison
