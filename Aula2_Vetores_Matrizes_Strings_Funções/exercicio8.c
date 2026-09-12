#include <stdio.h>

int maior(int a, int b);
int menor(int a, int b);
float media(float a, float b);
int fatorial(int n);

int main() {
    int x, y;
    float f1, f2;
    int n;

    printf("Digite dois numeros inteiros: ");
    scanf("%d %d", &x, &y);
    printf("Maior: %d\n", maior(x, y));
    printf("Menor: %d\n", menor(x, y));

    printf("\nDigite dois numeros reais: ");
    scanf("%f %f", &f1, &f2);
    printf("Media: %.2f\n", media(f1, f2));

    printf("\nDigite um numero para calcular o fatorial: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Fatorial não definido para numeros negativos.\n");
    } else {
        printf("Fatorial de %d: %d\n", n, fatorial(n));
    }

    return 0;
}

/*Funções Criadas*/
int maior(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int menor(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

float media(float a, float b) {
    return (a + b) / 2.0;
}

int fatorial(int n) {
    int resultado = 1;
    int i;

    for (i = 1; i <= n; i++) {
        resultado = resultado * i;
    }

    return resultado;
}