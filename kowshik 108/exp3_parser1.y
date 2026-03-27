%{
#include <stdio.h>

int yylex(void);
int yyerror(const char *msg);
%}

%token NAME NUMBER

%%
stmt : S { printf("SUCCESS\n"); } ;

S : '(' L ')'
  | NAME
  | NUMBER
  ;

L : L ',' S
  | S
  ;
%%

int main(void) {
    printf("Experiment 3 (Program 1) - Parser using LEX and YACC\n");
    yyparse();
    return 0;
}

int yyerror(const char *msg) {
    return fprintf(stderr, "YACC: %s\n", msg);
}
