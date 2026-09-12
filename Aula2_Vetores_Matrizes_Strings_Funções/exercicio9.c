#include <stdio.h>

#define NOTAS 30

void lerNotas(float notas[], int quantidade);
float calcularMedia(float notas[], int quantidade);
float encontrarMaiorNota(float notas[], int quantidade);
float encontrarMenorNota(float notas[], int quantidade);
void imprimirRelatorio(float notas[], int quantidade);

int main() {
    float notas[NOTAS];
    int quantidade;

    printf("Quantos alunos deseja cadastrar (max %d)? ", NOTAS);
    scanf("%d", &quantidade);

    lerNotas(notas, quantidade);
    imprimirRelatorio(notas, quantidade);

    return 0;
}

void lerNotas(float notas[], int quantidade) {
    int i;
    for (i = 0; i < quantidade; i++) {
        printf("Nota do aluno %d: ", i + 1);
        scanf("%f", &notas[i]);
    }
}

float calcularMedia(float notas[], int quantidade) {
    float soma = 0;
    int i;
    for (i = 0; i < quantidade; i++) {
        soma = soma + notas[i];
    }
    return soma / quantidade;
}

float encontrarMaiorNota(float notas[], int quantidade) {
    float maior = notas[0];
    int i;
    for (i = 1; i < quantidade; i++) {
        if (notas[i] > maior) {
            maior = notas[i];
        }
    }
    return maior;
}

float encontrarMenorNota(float notas[], int quantidade) {
    float menor = notas[0];
    int i;
    for (i = 1; i < quantidade; i++) {
        if (notas[i] < menor) {
            menor = notas[i];
        }
    }
    return menor;
}

void imprimirRelatorio(float notas[], int quantidade) {
    int i;
    printf("\n===== RELATORIO DA TURMA =====\n");
    for (i = 0; i < quantidade; i++) {
        printf("Aluno %d: %.2f\n", i + 1, notas[i]);
    }
    printf("\nMedia da turma: %.2f\n", calcularMedia(notas, quantidade));
    printf("Maior nota: %.2f\n", encontrarMaiorNota(notas, quantidade));
    printf("Menor nota: %.2f\n", encontrarMenorNota(notas, quantidade));
}