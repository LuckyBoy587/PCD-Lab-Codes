#include <stdio.h>
#include <string.h>

typedef struct {
    char op;   /* S, R, A, or - */
    int value;
    char set;
} table_entry;

static table_entry ta[50][50];

int main(void) {
    char nt[20], t[20], ip[50], s[100];
    char prod[20][20], rhs[20][20], lhs[20][20];
    int non, not, ni, np;
    int i, j, l, tos, temp1;

    printf("Experiment 7 - SLR Parser\n");

    printf("Enter number of non-terminals: ");
    scanf("%d", &non);
    for (i = 0; i < non; i++) {
        printf("Enter non-terminal: ");
        scanf(" %c", &nt[i]);
    }

    printf("Enter number of terminals: ");
    scanf("%d", &not);
    for (i = 0; i < not; i++) {
        printf("Enter terminal: ");
        scanf(" %c", &t[i]);
        nt[non + i] = t[i];
    }
    nt[non + not] = '$';
    nt[non + not + 1] = '\0';

    printf("Enter number of states: ");
    scanf("%d", &ni);

    for (i = 0; i < ni; i++) {
        int entries;
        printf("Enter number of entries in state %d: ", i);
        scanf("%d", &entries);

        for (l = 0; l < entries; l++) {
            char symbol;
            int col = -1;

            printf("Enter symbol: ");
            scanf(" %c", &symbol);

            for (j = 0; nt[j] != '\0'; j++) {
                if (nt[j] == symbol) {
                    col = j;
                    break;
                }
            }

            if (col == -1) continue;

            printf("Enter operation (S/R/A): ");
            scanf(" %c", &ta[i][col].op);
            printf("Enter step: ");
            scanf("%d", &ta[i][col].value);
            ta[i][col].set = 't';
        }
    }

    printf("\nParsing Table:\n");
    for (i = 0; nt[i] != '\0'; i++) printf("%c\t", nt[i]);
    printf("\n");
    for (i = 0; i < ni; i++) {
        for (j = 0; nt[j] != '\0'; j++) {
            if (ta[i][j].set == 't') printf("%c%d\t", ta[i][j].op, ta[i][j].value);
            else printf("\t");
        }
        printf("\n");
    }

    printf("Enter number of productions: ");
    scanf("%d", &np);
    for (i = 0; i < np; i++) {
        printf("Enter production (e.g. E->E+T): ");
        scanf("%19s", prod[i]);
        lhs[i][0] = prod[i][0];
        lhs[i][1] = '\0';
        strcpy(rhs[i], prod[i] + 3);
    }

    int ch_flag = 1;
    while (ch_flag == 1) {
        printf("\nEnter input string: ");
        scanf("%49s", ip);

        int len = (int)strlen(ip);
        ip[len] = '$';
        ip[len + 1] = '\0';

        strcpy(s, "$0");
        tos = 1;
        i = 0;

        printf("\nStack\tInput\tAction\n");
        while (1) {
            printf("%s\t%s\t", s, ip + i);
            int state = s[tos] - '0';
            int col = -1;

            for (j = 0; nt[j] != '\0'; j++) {
                if (nt[j] == ip[i]) {
                    col = j;
                    break;
                }
            }

            if (col == -1) {
                printf("ERROR\n");
                break;
            }

            char action = ta[state][col].op;
            temp1 = ta[state][col].value;

            if (action == 'S') {
                printf("SHIFT %d\n", temp1);
                s[++tos] = ip[i++];
                s[++tos] = (char)(temp1 + '0');
                s[tos + 1] = '\0';
            } else if (action == 'R') {
                int prodIndex = temp1 - 1;
                int popCount = 2 * (int)strlen(rhs[prodIndex]);

                printf("REDUCE %s->%s\n", lhs[prodIndex], rhs[prodIndex]);
                while (popCount--) s[tos--] = '\0';

                int prevState = s[tos] - '0';
                s[++tos] = lhs[prodIndex][0];

                int gotoCol = -1;
                for (j = 0; nt[j] != '\0'; j++) {
                    if (nt[j] == lhs[prodIndex][0]) {
                        gotoCol = j;
                        break;
                    }
                }

                int gotoState = ta[prevState][gotoCol].value;
                s[++tos] = (char)(gotoState + '0');
                s[tos + 1] = '\0';
            } else if (action == 'A') {
                printf("ACCEPTED\n");
                break;
            } else {
                printf("ERROR\n");
                break;
            }
        }

        printf("Do you want to enter another string? (1/0): ");
        scanf("%d", &ch_flag);
    }

    return 0;
}
