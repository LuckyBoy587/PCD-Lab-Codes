#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char node;
    int n, k, g, fi, fo;
    char t[10][20];
    char first[20], follow[20];
    char par[20][20];
} tran;

static tran b[20];
static int count = 0, c = 0;
static char a[10][20], t[20], stack_arr[50], input_string[50], choice;

static void add_unique(char *arr, int *len, char val) {
    for (int i = 0; i < *len; i++) {
        if (arr[i] == val) return;
    }
    arr[(*len)++] = val;
}

static void first_set(int x) {
    b[x].k = 1;
    for (int i = 0; i <= b[x].n; i++) {
        char sym = b[x].t[i][0];
        if (!isupper((unsigned char)sym)) {
            add_unique(b[x].first, &b[x].fi, sym);
        } else {
            for (int j = 0; j < count; j++) {
                if (b[j].node == sym) {
                    if (b[j].k == 0) first_set(j);
                    for (int k = 0; k < b[j].fi; k++) {
                        if (b[j].first[k] != '@') {
                            add_unique(b[x].first, &b[x].fi, b[j].first[k]);
                        }
                    }
                }
            }
        }
    }
}

static void follow_set(int x) {
    b[x].g = 1;
    if (x == 0) add_unique(b[x].follow, &b[x].fo, '$');

    for (int i = 0; i < count; i++) {
        for (int j = 0; j <= b[i].n; j++) {
            for (int k = 0; k < (int)strlen(b[i].t[j]); k++) {
                if (b[i].t[j][k] == b[x].node) {
                    if (b[i].t[j][k + 1] != '\0') {
                        char next = b[i].t[j][k + 1];
                        if (!isupper((unsigned char)next)) {
                            add_unique(b[x].follow, &b[x].fo, next);
                        } else {
                            for (int l = 0; l < count; l++) {
                                if (b[l].node == next) {
                                    for (int m = 0; m < b[l].fi; m++) {
                                        if (b[l].first[m] != '@') {
                                            add_unique(b[x].follow, &b[x].fo, b[l].first[m]);
                                        }
                                    }
                                    for (int m = 0; m < b[l].fi; m++) {
                                        if (b[l].first[m] == '@') {
                                            if (b[i].g == 0) follow_set(i);
                                            for (int n = 0; n < b[i].fo; n++) {
                                                add_unique(b[x].follow, &b[x].fo, b[i].follow[n]);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (b[i].g == 0) follow_set(i);
                        for (int l = 0; l < b[i].fo; l++) {
                            add_unique(b[x].follow, &b[x].fo, b[i].follow[l]);
                        }
                    }
                }
            }
        }
    }
}

static void build_parse_table(void) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j <= b[i].n; j++) {
            char first_sym = b[i].t[j][0];
            if (first_sym == '@') {
                for (int k = 0; k < b[i].fo; k++) {
                    for (int n = 0; n < c; n++) {
                        if (t[n] == b[i].follow[k]) strcpy(b[i].par[n], "@");
                    }
                }
            } else if (!isupper((unsigned char)first_sym)) {
                for (int n = 0; n < c; n++) {
                    if (t[n] == first_sym) strcpy(b[i].par[n], b[i].t[j]);
                }
            } else {
                for (int l = 0; l < count; l++) {
                    if (b[l].node == first_sym) {
                        for (int k = 0; k < b[l].fi; k++) {
                            if (b[l].first[k] != '@') {
                                for (int n = 0; n < c; n++) {
                                    if (t[n] == b[l].first[k]) strcpy(b[i].par[n], b[i].t[j]);
                                }
                            } else {
                                for (int m = 0; m < b[i].fo; m++) {
                                    for (int n = 0; n < c; n++) {
                                        if (t[n] == b[i].follow[m]) strcpy(b[i].par[n], "@");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

static void parse_input(void) {
    while (1) {
        int top = 0, i = 0;
        printf("\nEnter the string: ");
        scanf("%49s", input_string);
        strcat(input_string, "$");

        stack_arr[top++] = '$';
        stack_arr[top++] = b[0].node;

        printf("\nSTACK\tINPUT\n");
        while (top > 0) {
            for (int k = 0; k < top; k++) printf("%c", stack_arr[k]);
            printf("\t%s\n", &input_string[i]);

            char top_sym = stack_arr[top - 1];
            char curr = input_string[i];

            if (top_sym == curr) {
                top--;
                i++;
            } else if (isupper((unsigned char)top_sym)) {
                int idx = -1, col = -1;
                for (int j = 0; j < count; j++) if (b[j].node == top_sym) idx = j;
                for (int k = 0; k < c; k++) if (t[k] == curr) col = k;

                if (idx != -1 && col != -1 && b[idx].par[col][0] != '\0') {
                    top--;
                    if (strcmp(b[idx].par[col], "@") != 0) {
                        for (int n = (int)strlen(b[idx].par[col]) - 1; n >= 0; n--) {
                            stack_arr[top++] = b[idx].par[col][n];
                        }
                    }
                } else {
                    printf("\n**String not accepted**\n");
                    break;
                }
            } else {
                printf("\n**String not accepted**\n");
                break;
            }

            if (top > 0 && stack_arr[top - 1] == '$' && input_string[i] == '$') {
                printf("\n***String accepted***\n");
                break;
            }
        }

        printf("\nDo you want to enter another string (Y/N): ");
        scanf(" %c", &choice);
        if (choice != 'Y' && choice != 'y') break;
    }
}

int main(void) {
    printf("Experiment 5 - Predictive Parser\n");
    printf("Enter productions like E->TR (use @ for epsilon), type quit to stop.\n");

    for (count = 0;; count++) {
        scanf("%19s", a[count]);
        if (strcmp(a[count], "quit") == 0) break;

        b[count].node = a[count][0];
        b[count].n = 0;
        b[count].fi = 0;
        b[count].fo = 0;
        b[count].k = 0;
        b[count].g = 0;

        int j = 0;
        for (int i = 3; i < (int)strlen(a[count]); i++) {
            if (a[count][i] == '/') {
                b[count].t[b[count].n][j] = '\0';
                b[count].n++;
                j = 0;
            } else {
                if (!isupper((unsigned char)a[count][i]) && a[count][i] != '@') {
                    add_unique(t, &c, a[count][i]);
                }
                b[count].t[b[count].n][j++] = a[count][i];
            }
        }
        b[count].t[b[count].n][j] = '\0';
    }

    add_unique(t, &c, '$');

    for (int i = 0; i < count; i++) if (b[i].k == 0) first_set(i);
    for (int i = 0; i < count; i++) if (b[i].g == 0) follow_set(i);

    build_parse_table();

    printf("\nParsing Table:\nNT\t");
    for (int i = 0; i < c; i++) printf("%c\t", t[i]);
    printf("\n---------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%c\t", b[i].node);
        for (int j = 0; j < c; j++) {
            if (b[i].par[j][0]) printf("%c->%s\t", b[i].node, b[i].par[j]);
            else printf("-\t");
        }
        printf("\n");
    }

    parse_input();
    return 0;
}
