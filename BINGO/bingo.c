#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 5

typedef enum {
    B = 1,
    I = 16,
    N = 31,
    G = 46,
    O = 61
} BINGO;

int gerarNumero(int minimo, int maximo) {
    return minimo + rand() % (maximo - minimo + 1);
}

int numeroExiste(int cartela[5][5], int coluna, int numero) {

    for (int linha = 0; linha < 5; linha++) {

        if (cartela[linha][coluna] == numero) {
            return 1;
        }
    }


    return 0;
}

void gerarCartela(int cartela[5][5]) {

    BINGO colunas[5] = {B, I, N, G, O};

    for (int coluna = 0; coluna < 5; coluna++) {

        int minimo = colunas[coluna];
        int maximo = minimo + 14;

        for (int linha = 0; linha < 5; linha++) {

            if (linha == 2 && coluna == 2) {
                cartela[linha][coluna] = 0;
            } else {

                int numero;

                do {
                    numero = gerarNumero(minimo, maximo);
                } while (numeroExiste(cartela, coluna, numero));

                cartela[linha][coluna] = numero;
            }
        }
    }
}

void imprimirCartela(int cartela[5][5]) {

    printf("\n B    I    N    G    O\n\n");

    for (int linha = 0; linha < 5; linha++) {

        for (int coluna = 0; coluna < 5; coluna++) {

            if (cartela[linha][coluna] == 0) {
                printf(" X   ");
            } else {
                printf("%2d   ", cartela[linha][coluna]);
            }
        }

        printf("\n");
    }
}

int main() {

    int cartela[5][5];

    srand(time(NULL));

    gerarCartela(cartela);
    imprimirCartela(cartela);

    return 0;
}