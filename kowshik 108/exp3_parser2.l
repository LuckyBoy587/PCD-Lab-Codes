%{
#include "y.tab.h"
#include <stdlib.h>
%}
%%
[0-9]+      { yylval = atoi(yytext); printf("Scanned number: %d\n", yylval); return NUMBER; }
[a-zA-Z]+   { printf("Scanned a name\n"); return NAME; }
[\t ]       { }
\n          { return 0; }
.           { printf("Found token: %s\n", yytext); return yytext[0]; }
%%
int yywrap(void) {
    return 1;
}
