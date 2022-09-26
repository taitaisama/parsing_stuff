bison: bison.cpp bison.tab.cpp bison.lex.cpp
	g++ bison.tab.cpp bison.lex.cpp bison.cpp -lm -ll -lfl -o $@

bison.tab.cpp bison.tab.hpp: bison.y
	bison -o bison.tab.cpp -d bison.y

bison.lex.cpp: bison.l bison.tab.hpp
	flex -o bison.lex.cpp -l bison.l

clean::
	rm -f bison.tab.cpp bison.tab.hpp bison.lex.cpp bison.output *~ bison
