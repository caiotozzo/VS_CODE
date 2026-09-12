#include <stdio.h>

#define NUMEROS 10

int main() {
    int vetor[NUMEROS];
    int i;

    printf("Digite %d numeros inteiros:\n", NUMEROS);
    for (i = 0; i < NUMEROS; i++) {
        printf("Numero %d: ", i + 1);
        scanf("%d", &vetor[i]);
    }

    printf("\nValores na ordem digitada:\n");
    for (i = 0; i < NUMEROS; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n\nValores na ordem inversa:\n");
    for (i = NUMEROS - 1; i >= 0; i--) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}
