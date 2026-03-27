#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int main(void) {
    char expr[128], rhs[128], lhs[32] = "result";
    char postfix[256], opstack[128];
    int regStack[128];
    int opTop = -1, postLen = 0, regTop = -1, regNo = 1;

    FILE *fp = fopen("exp9_out.asm", "w");
    if (!fp) {
        printf("Unable to create exp9_out.asm\n");
        return 1;
    }

    printf("Login Name: kowshik 108\n");
    printf("Experiment 9 - Backend Code Generation\n");
    printf("Enter assignment expression (e.g., a=b+c*d): ");
    scanf("%127s", expr);

    char *eq = strchr(expr, '=');
    if (eq) {
        int l = (int)(eq - expr);
        strncpy(lhs, expr, l);
        lhs[l] = '\0';
        strcpy(rhs, eq + 1);
    } else {
        strcpy(rhs, expr);
    }

    for (int i = 0; rhs[i] != '\0'; i++) {
        char ch = rhs[i];
        if (isalnum((unsigned char)ch)) {
            postfix[postLen++] = ch;
            postfix[postLen++] = ' ';
        } else if (ch == '(') {
            opstack[++opTop] = ch;
        } else if (ch == ')') {
            while (opTop >= 0 && opstack[opTop] != '(') {
                postfix[postLen++] = opstack[opTop--];
                postfix[postLen++] = ' ';
            }
            if (opTop >= 0 && opstack[opTop] == '(') opTop--;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (opTop >= 0 && precedence(opstack[opTop]) >= precedence(ch)) {
                postfix[postLen++] = opstack[opTop--];
                postfix[postLen++] = ' ';
            }
            opstack[++opTop] = ch;
        }
    }

    while (opTop >= 0) {
        postfix[postLen++] = opstack[opTop--];
        postfix[postLen++] = ' ';
    }
    postfix[postLen] = '\0';

    printf("\nPseudo Assembly:\n");

    for (int i = 0; i < postLen; i++) {
        char tok = postfix[i];
        if (tok == ' ') continue;

        if (isalnum((unsigned char)tok)) {
            int r = regNo++;
            if (isdigit((unsigned char)tok)) {
                printf("MOV #%c, R%d\n", tok, r);
                fprintf(fp, "MOV #%c, R%d\n", tok, r);
            } else {
                printf("MOV %c, R%d\n", tok, r);
                fprintf(fp, "MOV %c, R%d\n", tok, r);
            }
            regStack[++regTop] = r;
        } else {
            int r2 = regStack[regTop--];
            int r1 = regStack[regTop--];
            if (tok == '+') {
                printf("ADD R%d, R%d\n", r2, r1);
                fprintf(fp, "ADD R%d, R%d\n", r2, r1);
            } else if (tok == '-') {
                printf("SUB R%d, R%d\n", r2, r1);
                fprintf(fp, "SUB R%d, R%d\n", r2, r1);
            } else if (tok == '*') {
                printf("MUL R%d, R%d\n", r2, r1);
                fprintf(fp, "MUL R%d, R%d\n", r2, r1);
            } else if (tok == '/') {
                printf("DIV R%d, R%d\n", r2, r1);
                fprintf(fp, "DIV R%d, R%d\n", r2, r1);
            }
            regStack[++regTop] = r1;
        }
    }

    if (regTop >= 0) {
        printf("MOV R%d, %s\n", regStack[regTop], lhs);
        fprintf(fp, "MOV R%d, %s\n", regStack[regTop], lhs);
    }

    fclose(fp);
    printf("\nAssembly also saved in exp9_out.asm\n");
    printf("Login Name: kowshik 108\n");
    return 0;
}
