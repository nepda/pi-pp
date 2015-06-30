#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* invertiert Bit i in Zeichkette str */
int toggle(char *str, int i) {
    if (str[i] == '0')
        str[i] = '1';
    else
        str[i] = '0';
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Benutzung:  %s [Quelle] [Ziel] \n", argv[0]);
        exit(-1);
    }

    char *quelle = argv[1];
    char *ziel = argv[2];

    int k = strlen(quelle);
    if (k != strlen(ziel)) {
        fprintf(stderr, "Beide Bitstrings müssen die gleiche Länge haben!\n");
        exit(-1);
    }

    char *str = (char *) malloc(k + 1);

    for (int i = 0; i < k; i++) {
        printf("%s ", quelle);
        strncpy(str, quelle, k + 1);

        /* i-tes Bit gleich -> Dimensionswechsel hin und zurück */
        if (quelle[i] == ziel[i]) {
            /* Dimensionswechsel hin */
            toggle(str, i);
            printf(" -> %s", str);

            /* gehe direkten Pfad */
            for (int j = 0; j < k; j++) {
                if (quelle[j] != ziel[j] && j != i) {
                    toggle(str, j);
                    printf(" -> %s", str);
                }
            }

            /* Dimensionswechsel zurück */
            toggle(str, i);
            printf(" -> %s", str);
        } else {
            /* i-tes Bit ungleich -> gehe direkten Pfad */
            for (int j = 0; j < k; j++) {
                int bit = (i + j) % k;
                if (quelle[bit] != ziel[bit]) {
                    toggle(str, bit);
                    printf(" -> %s", str);
                }
            }
        }
        printf("\n");
    }
    free(str);
}
