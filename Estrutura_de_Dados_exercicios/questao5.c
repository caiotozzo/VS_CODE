#include <stdio.h>
#include <windows.h>

#define MAX_ALUNOS 40
#define MAX_PRODUTOS 500
#define PI 3.1415926535
#define ANO_ATUAL 2026

int main() {
    system("cls");
    SetConsoleOutputCP(65001);

    printf("Numero maximo de alunos: %d\n", MAX_ALUNOS);
    printf("Quantidade maxima de produtos: %d\n", MAX_PRODUTOS);
    printf("Valor de PI: %.10lf\n", PI);
    printf("Ano atual: %d\n", ANO_ATUAL);

    return 0;
}