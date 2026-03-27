#include <stdio.h>
#include <string.h>

typedef struct {
    char s[20];
    int top;
} stack_t;

static stack_t st;

static int isempty(void) {
    return (st.top == 0);
}

static void push(char p) {
    st.s[st.top++] = p;
}

static void disp(void) {
    for (int i = 0; i < st.top; i++) printf("%c", st.s[i]);
}

static int reduce(char rp[10][10], int n, char lp[10]) {
    for (int i = 0; i < st.top; i++) {
        int len = st.top - i;
        char u[20];
        strncpy(u, &st.s[i], len);
        u[len] = '\0';

        for (int k = 0; k < n; k++) {
            if (strcmp(rp[k], u) == 0) {
                st.top = i;
                push(lp[k]);
                return k;
            }
        }
    }
    return 99;
}

static void shift(char ip[], int *j) {
    push(ip[*j]);
    (*j)++;
}

int main(void) {
    int n, i, j = 0, h;
    char lp[10], ip[20], rp[10][10];

    st.top = 0;

    printf("Login Name: kowshik 108\n");
    printf("Experiment 6 - Shift Reduce Parser\n");

    printf("Enter the number of productions: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter left side: ");
        scanf(" %c", &lp[i]);
        printf("Enter right side: ");
        scanf("%9s", rp[i]);
    }

    printf("Enter input string: ");
    scanf("%19s", ip);

    strcat(ip, "$");
    push('$');

    printf("\nSTACK\tINPUT\tACTION\n");
    printf("--------------------------------------\n");

    while (1) {
        disp();
        printf("\t%s\t", &ip[j]);

        h = reduce(rp, n, lp);
        if (h != 99) {
            printf("Reduce %c->%s\n", lp[h], rp[h]);
        } else if (ip[j] != '\0') {
            printf("Shift %c\n", ip[j]);
            shift(ip, &j);
        }

        if (st.top == 2 && st.s[0] == '$' && st.s[1] == lp[0] && ip[j] == '$') {
            disp();
            printf("\t\t%s\taccept\n", &ip[j]);
            break;
        }

        if (ip[j] == '\0') {
            printf("\nRejected\n");
            break;
        }
    }

    printf("\nLogin Name: kowshik 108\n");
    return 0;
}
