#include <stdio.h>
#include <string.h>

#define NOMES 100

int main() {
    char nome1[NOMES], nome2[NOMES];
    int resultado, tamanho;

    printf("Digite o primeiro nome: ");
    fgets(nome1, NOMES, stdin);
    tamanho = strlen(nome1);
    if (tamanho > 0 && nome1[tamanho - 1] == '\n') {
        nome1[tamanho - 1] = '\0';
    }

   printf("Digite o segundo nome: ");
    fgets(nome2, NOMES, stdin);
    tamanho = strlen(nome2);
    if (tamanho > 0 && nome2[tamanho - 1] == '\n') {
        nome2[tamanho - 1] = '\0';
    }

    resultado = strncmp(nome1, nome2, NOMES);

    if (resultado == 0) {
        printf("\nOs nomes sao iguais.\n");
    } else if (resultado < 0) {
        printf("\nOs nomes sao diferentes.\n");
        printf("\"%s\" e alfabeticamente maior que \"%s\".\n", nome2, nome1);
    } else {
        printf("\nOs nomes sao diferentes.\n");
        printf("\"%s\" e alfabeticamente maior que \"%s\".\n", nome1, nome2);
    }

    return 0;
}