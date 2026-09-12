#include <stdio.h>

#define LINHAS 3
#define COLUNAS 3

int main()
{
    int a[LINHAS][COLUNAS];
    int b[LINHAS][COLUNAS];
    int soma[LINHAS][COLUNAS];
    int i, j;

    /*A*/
    printf("Digite os 9 elementos da matriz A:\n");
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }

    /*B*/
    printf("\nDigite os 9 elementos da matriz B:\n");
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &b[i][j]);
        }
    }

    /*Soma = A + B*/
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            soma[i][j] = a[i][j] + b[i][j];
        }
    }

    /*Valores de A*/
    printf("\nMatriz A:\n");
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    /*Valores de B*/
    printf("\nMatriz B:\n");
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }

    /*Resultado da Soma*/
    printf("\nMatriz Soma (A + B):\n");
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COLUNAS; j++)
        {
            printf("%d ", soma[i][j]);
        }
        printf("\n");
    }

    return 0;
}