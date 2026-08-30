#include <stdio.h> 
#include <windows.h>

typedef char byte; 
typedef int inteiro; 
typedef float real; 

int main() {
    system("cls");
    SetConsoleOutputCP(65001);

    byte a = 10; 
    inteiro b = 100; 
    real c = 10.56; 
    
    printf("Byte: %d\n", a); 
    printf("Inteiro: %d\n", b);
    printf("Real: %.2f\n", c); 
    
    return 0; 
}
     