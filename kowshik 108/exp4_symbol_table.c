#include <stdio.h>
#include <string.h>

typedef struct {
    int lineno;
    char var[25];
    char dt[25];
    char val[25];
} symtab;

int main(void) {
    FILE *fp;
    char s[25], type[25];
    symtab sa[50];
    int i = 0, line = 0;

    printf("Login Name: kowshik 108\n");
    printf("Experiment 4 - Symbol Table\n\n");

    fp = fopen("exp4_input.txt", "r");
    if (!fp) {
        printf("Unable to open exp4_input.txt\n");
        return 1;
    }

    printf("SYMBOL TABLE\n");
    printf("Variable\tDatatype\tLine No\tValue\n");

    while (fscanf(fp, "%24s", s) != EOF) {
        if (strcmp(s, "int") == 0 || strcmp(s, "float") == 0 || strcmp(s, "char") == 0) {
            strcpy(type, s);
            line++;

            while (fscanf(fp, "%24s", s) != EOF && strcmp(s, ";") != 0) {
                if (strcmp(s, ",") == 0) {
                    continue;
                }

                i++;
                sa[i].lineno = line;
                strcpy(sa[i].var, s);
                strcpy(sa[i].dt, type);

                if (fscanf(fp, "%24s", s) == EOF) {
                    strcpy(sa[i].val, "garbage");
                    break;
                }

                if (strcmp(s, "=") == 0) {
                    if (fscanf(fp, "%24s", s) == EOF) {
                        strcpy(sa[i].val, "garbage");
                    } else {
                        strcpy(sa[i].val, s);
                    }
                } else {
                    strcpy(sa[i].val, "garbage");
                    if (strcmp(s, ";") == 0) {
                        break;
                    }
                    if (strcmp(s, ",") != 0) {
                        /* token belongs to next variable or declaration */
                    }
                }
            }
        }
    }

    for (int j = 1; j <= i; j++) {
        printf("%s\t\t%s\t\t%d\t\t%s\n", sa[j].var, sa[j].dt, sa[j].lineno, sa[j].val);
    }

    fclose(fp);
    printf("\nLogin Name: kowshik 108\n");
    return 0;
}
