%{
#include <stdio.h>
#include <stdlib.h>

int flag = 0;
int yylex(void);
int yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'

%%
ArithmeticExpression:
    E { printf("\nResult = %d\n", $1); }
    ;

E:
      E '+' E   { $$ = $1 + $3; }
    | E '-' E   { $$ = $1 - $3; }
    | E '*' E   { $$ = $1 * $3; }
    | E '/' E   { $$ = $1 / $3; }
    | E '%' E   { $$ = $1 % $3; }
    | '(' E ')' { $$ = $2; }
    | NUMBER    { $$ = $1; }
    ;
%%

int main(void) {
    printf("Experiment 2 - Calculator using LEX and YACC\n");
    printf("Enter Arithmetic Expression:\n");

    yyparse();

    if (flag == 0) {
        printf("Valid Expression\n");
    }
    return 0;
}

int yyerror(const char *s) {
    (void)s;
    printf("Invalid Expression\n");
    flag = 1;
    return 0;
}
