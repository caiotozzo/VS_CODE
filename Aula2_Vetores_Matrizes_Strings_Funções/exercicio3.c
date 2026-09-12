#include <stdio.h>

#define NUMEROS 15

int main() {
    int vetor[NUMEROS];
    int i, numero, encontrado = 0, posicao = 0;

    printf("Digite %d numeros inteiros:\n", NUMEROS);
    for (i = 0; i < NUMEROS; i++) {
        printf("Numero %d: ", i + 1);
        scanf("%d", &vetor[i]);
    }

    printf("\nDigite um numero para pesquisar: ");
    scanf("%d", &numero);

    for (i = 0; i < NUMEROS; i++) {
        if (vetor[i] == numero) {
            encontrado = 1;
            posicao = i;
            break;
        }
    }

    if (encontrado) {
        printf("Numero encontrado! Posição (indice): %d\n", posicao);
    } else {
        printf("Numero não encontrado no vetor.\n");
    }

    return 0;
}