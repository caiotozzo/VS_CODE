
#include <stdio.h>

#define NUMEROS 20

int main() {
    int vetor[NUMEROS];
    int i, maior, menor, par = 0, impar = 0;
    float soma = 0, media;

    printf("Digite %d numeros inteiros:\n", NUMEROS);
   
    for (i = 0; i < NUMEROS; i++) {
        printf("Numero %d: ", i + 1);
        scanf("%d", &vetor[i]);
    }

    maior = vetor[0];
    menor = vetor[0];

    for (i = 0; i < NUMEROS; i++) {
        if (vetor[i] > maior) maior = vetor[i];
        if (vetor[i] < menor) menor = vetor[i];

        soma = soma + vetor[i];

        if (vetor[i] % 2 == 0)
            par = par + 1;
        else
            impar = impar + 1;
    }

    media = soma / NUMEROS;

    printf("\nMaior valor: %d\n", maior);
    printf("Menor valor: %d\n", menor);
    printf("Media: %.2f\n", media);
    printf("Quantidade de numeros pares: %d\n", par);
    printf("Quantidade de numeros impares: %d\n", impar);

    return 0;
}