#include <stdio.h>

#define NUMEROS 5

int main() {
    int matriz[NUMEROS][NUMEROS];
    int i, j, maior, linhaMaior = 0, colunaMaior = 0;

    printf("Digite os %d elementos da matriz:\n", NUMEROS * NUMEROS);

    for (i = 0; i < NUMEROS; i++) {
        for (j = 0; j < NUMEROS; j++) {
            printf("matriz[%d][%d]: ", i, j);
            scanf("%d", &matriz[i][j]);

            if (i == 0 && j == 0) {
                maior = matriz[i][j];
            } else if (matriz[i][j] > maior) {
                maior = matriz[i][j];
                linhaMaior = i;
                colunaMaior = j;
            }
        }
    }

    printf("\nMaior elemento: %d\n", maior);
    printf("Linha: %d\n", linhaMaior);
    printf("Coluna: %d\n", colunaMaior);

    return 0;
}