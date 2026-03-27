%{
#include <stdio.h>
%}

letter              [a-zA-Z]
digit               [0-9]
operators           [+*/=%&|<>-]
specialcharacters   [();{}"]

%%
#include<stdio.h>|void|main|int|float|char|printf|while|do|for|if|else|double|break|continue|scanf|switch|case   { printf("Keyword\n"); }
{letter}({letter}|{digit})*                                                                                         { printf("Variable\n"); }
{digit}+                                                                                                            { printf("Number\n"); }
{operators}+                                                                                                        { printf("Operator\n"); }
{specialcharacters}+                                                                                                { printf("Special Character\n"); }
[ \t\n]+                                                                                                          { }
.                                                                                                                   { printf("Unknown Token\n"); }
%%

int main(int argc, char *argv[]) {
    printf("Experiment 1b - Lexical Analyzer using LEX\n");

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

    fclose(yyin);
    return 0;
}

int yywrap(void) {
    return 1;
}
