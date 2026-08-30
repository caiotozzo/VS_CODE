#include <stdio.h>
#include <stdint.h>
#include <windows.h>

#define ESTOQUE_MAXIMO 500
#define ESTOQUE_MINIMO 10
#define DESCONTO 10

typedef float real;

int main() {
    system("cls");
    SetConsoleOutputCP(65001);
    
    uint8_t quantidade = 25;
    real preco = 19.90;
    real valorFinal;

    valorFinal = preco - (preco * DESCONTO / 100);

    printf("Quantidade em estoque: %u\n", quantidade);
    printf("Quantidade máxima de produtos no Estoque: %d\n", ESTOQUE_MAXIMO);
    printf("Quantidade minímo de produtos no Estoque: %d\n", ESTOQUE_MINIMO);
    printf("Preço inteiro do produto: R$ %.2f\n", preco);
    printf("Desconto do produto: %d%%\n", DESCONTO);
    printf("Preço Final com desconto: R$ %.2f\n", valorFinal);
    

    return 0;
}