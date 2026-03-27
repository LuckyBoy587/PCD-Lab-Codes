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
    char postfix[256];
    char opstack[128];
    char valstack[128][32];
    int opTop = -1, postLen = 0, valTop = -1, tempNo = 1;

    printf("Experiment 8 - Three Address Code Generation\n");
    printf("Enter assignment expression (e.g., a=b+c*d-e): ");
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

    printf("\nGenerated Three Address Code:\n");

    for (int i = 0; i < postLen; i++) {
        char tok = postfix[i];
        if (tok == ' ') continue;

        if (isalnum((unsigned char)tok)) {
            valstack[++valTop][0] = tok;
            valstack[valTop][1] = '\0';
        } else {
            char right[32], left[32], temp[32];
            strcpy(right, valstack[valTop--]);
            strcpy(left, valstack[valTop--]);
            snprintf(temp, sizeof(temp), "t%d", tempNo++);
            printf("%s = %s %c %s\n", temp, left, tok, right);
            strcpy(valstack[++valTop], temp);
        }
    }

    if (valTop >= 0) {
        printf("%s = %s\n", lhs, valstack[valTop]);
    }

    return 0;
}
