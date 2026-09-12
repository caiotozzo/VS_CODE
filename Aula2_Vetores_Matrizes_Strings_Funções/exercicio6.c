#include <stdio.h>
#include <string.h>

#define NOMES 100

int main() {
    char nome[NOMES];
    int i, tamanho;
    int vogais = 0, consoantes = 0, espacos = 0;

    printf("Digite o nome completo: ");
    fgets(nome, NOMES, stdin);

   
    tamanho = strlen(nome); // conta os caracteres, incluindo o Enter (\n) que o fgets guardou
    if (tamanho > 0 && nome[tamanho - 1] == '\n') {  /*verifica se o ultimo caractere da string é o Enter*/
        nome[tamanho - 1] = '\0'; /*troca o Enter pelo caractere nulo*/
        tamanho--; /* ja que um caractere foi removido, atualiza o tamanho*/
    }

    for (i = 0; i < tamanho; i++) {
        char c = nome[i];

        if (c == ' ') {
            espacos++;
        } else if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                   c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            vogais++;
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            consoantes++;
        }
    }

    printf("\nQuantidade de caracteres: %d\n", tamanho);
    printf("Quantidade de vogais: %d\n", vogais);
    printf("Quantidade de consoantes: %d\n", consoantes);
    printf("Quantidade de espaços em branco: %d\n", espacos);

    return 0;
}