#include <stdio.h>

#define TABULEIRO 3

void inicializarTabuleiro(char tabuleiro[TABULEIRO][TABULEIRO]);
void exibirTabuleiro(char tabuleiro[TABULEIRO][TABULEIRO]);
int jogadaValida(char tabuleiro[TABULEIRO][TABULEIRO], int linha, int coluna);
void realizarJogada(char tabuleiro[TABULEIRO][TABULEIRO], int linha, int coluna, char jogador);
int verificarVencedor(char tabuleiro[TABULEIRO][TABULEIRO], char jogador);

int main() {
    char tabuleiro[TABULEIRO][TABULEIRO];
    char jogadorAtual = 'X';
    int linha, coluna;
    int vencedor = 0;
    int jogadas = 0;

    inicializarTabuleiro(tabuleiro);

    printf("=== JOGO DA VELHA ===\n");
    printf("Linhas e colunas vao de 0 a 2.\n");

    while (vencedor == 0 && jogadas < TABULEIRO * TABULEIRO) {
        exibirTabuleiro(tabuleiro);

        printf("\nJogador %c, digite a linha e a coluna (de 0 á 2): ", jogadorAtual);
        scanf("%d %d", &linha, &coluna);

        if (jogadaValida(tabuleiro, linha, coluna) == 0) {
            printf("Jogada invalida! Posicao ocupada ou fora do tabuleiro.\n");
        } else {
            realizarJogada(tabuleiro, linha, coluna, jogadorAtual);
            jogadas++;

            vencedor = verificarVencedor(tabuleiro, jogadorAtual);

            if (vencedor == 1) {
                exibirTabuleiro(tabuleiro);
                printf("\nO jogador %c venceu!\n", jogadorAtual);
            } else if (jogadas == TABULEIRO * TABULEIRO) {
                exibirTabuleiro(tabuleiro);
                printf("\nEmpate!\n");
            } else {
                if (jogadorAtual == 'X') {
                    jogadorAtual = 'O';
                } else {
                    jogadorAtual = 'X';
                }
            }
        }
    }

    return 0;
}

void inicializarTabuleiro(char tabuleiro[TABULEIRO][TABULEIRO]) {
    int i, j;
    for (i = 0; i < TABULEIRO; i++) {
        for (j = 0; j < TABULEIRO; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void exibirTabuleiro(char tabuleiro[TABULEIRO][TABULEIRO]) {
    int i, j;
    printf("\n");
    for (i = 0; i < TABULEIRO; i++) {
        for (j = 0; j < TABULEIRO; j++) {
            printf(" %c ", tabuleiro[i][j]);
            if (j < TABULEIRO - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < TABULEIRO - 1) {
            printf("-----------\n");
        }
    }
}

int jogadaValida(char tabuleiro[TABULEIRO][TABULEIRO], int linha, int coluna) {
    if (linha < 0 || linha >= TABULEIRO || coluna < 0 || coluna >= TABULEIRO) {
        return 0;
    }
    if (tabuleiro[linha][coluna] != ' ') {
        return 0;
    }
    return 1;
}

void realizarJogada(char tabuleiro[TABULEIRO][TABULEIRO], int linha, int coluna, char jogador) {
    tabuleiro[linha][coluna] = jogador;
}

int verificarVencedor(char tabuleiro[TABULEIRO][TABULEIRO], char jogador) {
    int i;

/* Ver as linhas e colunas */
    for (i = 0; i < TABULEIRO; i++) {
        if (tabuleiro[i][0] == jogador && tabuleiro[i][1] == jogador && tabuleiro[i][2] == jogador) {
            return 1;
        }
        if (tabuleiro[0][i] == jogador && tabuleiro[1][i] == jogador && tabuleiro[2][i] == jogador) {
            return 1;
        }
    }

/* Ver as diagonais */
    if (tabuleiro[0][0] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][2] == jogador) {
        return 1;
    }
    if (tabuleiro[0][2] == jogador && tabuleiro[1][1] == jogador && tabuleiro[2][0] == jogador) {
        return 1;
    }

    return 0;
}