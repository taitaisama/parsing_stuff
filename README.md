# parsing_stuff

Try it out: type g++ lr1.cpp on your terminal, then enter a grammar. 
Example:
paste this into terminal after ./a.out

NT S

NT T

NT E

T (

T )

T +

T *

T int

END

S -> E

E -> T + E | T

T -> int * T | int | ( E )

END

S

