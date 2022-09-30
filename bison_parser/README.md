# AST Generation helper

Compile using the given Makefile by typeing make.

Then type "./a.out c_test.y".

This would start an interactive terminal program which can be used to generate code for the ast for the given bison grammar (in this case C grammar in c_test.y).

You can merge multiple non\_terminals into one AST node in the first part. This would reduce the complexity of the AST. Enter the name of the merged AST node followed by non\_terminals from the bison grammar you want to merge. 

After this the interface will switch to generation of code for each AST node. There are 4 basic types of structures I have defined, one for when there is only one production (n), one for when there are multiple productions but you dont require an enum to distinguish between them (m), one for when you have multiple productions and you want an enum is your node (e) and one for defining union type nodes (u). Sometimes you might have to slightly change the output to get the desired results. 

I have an example input to the program given in inputs.txt, you can just copy past it into the interative part of the program in the terminal if you want to generate ast.h, ast.cpp and reductions.y. These will be very similar to the files I have submitted, albiet with some minor changes. 
