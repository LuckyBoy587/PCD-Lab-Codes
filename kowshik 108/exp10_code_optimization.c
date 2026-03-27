#include <stdio.h>
#include <string.h>

typedef struct {
    char l;
    char r[20];
} op_t;

int main(void) {
    op_t op[10], pr[10];
    int i, j, n, z = 0;
    char *p, temp;

    printf("Login Name: kowshik 108\n");
    printf("Experiment 10 - Code Optimization\n");

    printf("\nEnter the number of values: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nLeft: ");
        scanf(" %c", &op[i].l);
        printf("Right: ");
        scanf("%19s", op[i].r);
    }

    printf("\nIntermediate code\n");
    for (i = 0; i < n; i++) {
        printf("%c = %s\n", op[i].l, op[i].r);
    }

    for (i = 0; i < n; i++) {
        temp = op[i].l;
        p = NULL;
        for (j = 0; j < n; j++) {
            p = strchr(op[j].r, temp);
            if (p) {
                pr[z].l = op[i].l;
                strcpy(pr[z].r, op[i].r);
                z++;
                break;
            }
        }
    }

    printf("\nAfter dead code elimination\n");
    for (i = 0; i < z; i++) {
        printf("%c = %s\n", pr[i].l, pr[i].r);
    }

    for (i = 0; i < z; i++) {
        for (j = i + 1; j < z; j++) {
            if (strcmp(pr[i].r, pr[j].r) == 0) {
                char tempStr[2];
                tempStr[0] = pr[i].l;
                tempStr[1] = '\0';
                strcpy(pr[j].r, tempStr);
            }
        }
    }

    printf("\nEliminate common expression\n");
    for (i = 0; i < z; i++) {
        printf("%c = %s\n", pr[i].l, pr[i].r);
    }

    printf("\nOptimized code\n");
    for (i = 0; i < z; i++) {
        if (pr[i].l != '\0') {
            printf("%c = %s\n", pr[i].l, pr[i].r);
        }
    }

    printf("\nLogin Name: kowshik 108\n");
    return 0;
}
