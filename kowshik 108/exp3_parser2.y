%{
#include <stdio.h>

int yylex(void);
int yyerror(const char *msg);
%}

%token NAME NUMBER

%%
stmt : E { printf("SUCCESS\n"); } ;

E : E '+' T
  | T
  ;

T : T '*' F
  | F
  ;

F : '(' E ')'
  | NAME
  | NUMBER
  ;
%%

int main(void) {
    printf("Experiment 3 (Program 2) - Expression Parser\n");
    yyparse();
    return 0;
}

int yyerror(const char *msg) {
    return fprintf(stderr, "YACC: %s\n", msg);
}
