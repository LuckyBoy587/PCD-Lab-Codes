#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int is_keyword(const char *str) {
    const char *keywords[] = {
        "int", "float", "char", "while", "do", "for", "if", "else", "double", "return"
    };
    int n = (int)(sizeof(keywords) / sizeof(keywords[0]));
    for (int i = 0; i < n; i++) {
        if (strcmp(keywords[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

int main(void) {
    FILE *f1, *f2, *f3, *f4;
    char c, str[128];
    int num[256], tokenvalue = 0;
    int i = 0, k = 0;

    printf("Login Name: kowshik 108\n");
    printf("Experiment 1a - Lexical Analyzer using C\n\n");

    f1 = fopen("exp1a_input.c", "r");
    if (!f1) {
        printf("Unable to open exp1a_input.c\n");
        return 1;
    }

    f2 = fopen("identifier.txt", "w");
    f3 = fopen("specialchar.txt", "w");
    f4 = fopen("operators.txt", "w");

    if (!f2 || !f3 || !f4) {
        printf("Unable to create intermediate files\n");
        fclose(f1);
        return 1;
    }

    while ((c = (char)getc(f1)) != EOF) {
        if (isdigit((unsigned char)c)) {
            tokenvalue = c - '0';
            c = (char)getc(f1);
            while (isdigit((unsigned char)c)) {
                tokenvalue = tokenvalue * 10 + (c - '0');
                c = (char)getc(f1);
            }
            num[i++] = tokenvalue;
            ungetc(c, f1);
        } else if (isalpha((unsigned char)c) || c == '_') {
            putc(c, f2);
            c = (char)getc(f1);
            while (isalnum((unsigned char)c) || c == '_' || c == '$') {
                putc(c, f2);
                c = (char)getc(f1);
            }
            putc(' ', f2);
            ungetc(c, f1);
        } else if (c == '+' || c == '-' || c == '*' || c == '<' || c == '>' || c == '/' ||
                   c == '&' || c == '%' || c == '^' || c == '=' || c == '!') {
            putc(c, f4);
        } else if (!isspace((unsigned char)c)) {
            putc(c, f3);
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    printf("Constants: ");
    for (int j = 0; j < i; j++) {
        printf("%d ", num[j]);
    }
    printf("\n\nKeywords and Identifiers:\n");

    f2 = fopen("identifier.txt", "r");
    if (f2) {
        while ((c = (char)getc(f2)) != EOF) {
            if (c != ' ') {
                str[k++] = c;
            } else if (k > 0) {
                str[k] = '\0';
                printf("%s : %s\n", str, is_keyword(str) ? "keyword" : "identifier");
                k = 0;
            }
        }
        fclose(f2);
    }

    printf("\nSpecial Characters: ");
    f3 = fopen("specialchar.txt", "r");
    if (f3) {
        while ((c = (char)getc(f3)) != EOF) {
            printf("%c ", c);
        }
        fclose(f3);
    }

    printf("\nOperators: ");
    f4 = fopen("operators.txt", "r");
    if (f4) {
        while ((c = (char)getc(f4)) != EOF) {
            printf("%c ", c);
        }
        fclose(f4);
    }

    printf("\n\nLogin Name: kowshik 108\n");
    return 0;
}
