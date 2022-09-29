C   [A-Z_]
S   [a-z_]
L   [a-zA-Z_]
N   [0-9]
WS  [ \t\v\n\f]
ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
%{
#include <stdio.h>
#include "bison_ast.h"
#include "bison.tab.hpp"

extern void yyerror(const char *);
extern void set_var(const char *);

static void comment(void);
#define YY_DECL extern "C" int yylex()
%}p

%%
"/*"                        { comment(); }
"//".*                      {}
"%token"                    { return(TERMINAL_DECL); }
{C}*                        { yylval.strval = tostrval(yytext); return(TERMINAL); }
{S}*                        { yylval.strval = tostrval(yytext); return(NON_TERMINAL); }
"'"([^'\\\n]|{ES})+"'"      { yylval.strval = tostrval(yytext); return(CHARACTER); }
":"                         { return(':'); }
"|"                         { return('|'); }
";"                         { return(';'); }
"%%"                        { return(DELIMITER); }					  
"<"{L}+">"                  { yylval.strval = typetostrval(yytext); return(TYPE); }
{WS}+	                    {}
.                           {}
%%

int yywrap(void)        /* called at end of input */
{
    return 1;           /* terminate now */
}
static void comment(void)
{
    int c;

    while ((c = yyinput()) != 0)
        if (c == '*')
        {
            while ((c = yyinput()) == '*')
                ;

            if (c == '/')
                return;

            if (c == 0)
                break;
        }
    yyerror("unterminated comment");
}
