%{
#include <stdio.h>
int c = 0, w = 0, l = 0, s = 0;
%}
%%
\n             { l++; s++; }
[\t ]         { s++; }
[^ \t\n]+     { w++; c += yyleng; }
%%
int main(int argc, char *argv[]) {
    printf("Experiment 1b - Count words/chars/spaces/lines using LEX\n");

    if (argc != 2) {
        printf("Usage: ./a.out <input-file>\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("Cannot open input file\n");
        return 1;
    }

    yylex();

    printf("Number of spaces = %d\n", s);
    printf("Number of characters = %d\n", c);
    printf("Number of lines = %d\n", l + 1);
    printf("Number of words = %d\n", w);
    fclose(yyin);
    return 0;
}

int yywrap(void) {
    return 1;
}
