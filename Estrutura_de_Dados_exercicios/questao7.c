#include <stdio.h>
#include <windows.h>  

int main() {
    system("cls");
    SetConsoleOutputCP(65001);

    printf("char: %zu byte(s)\n", sizeof(char));
    printf("short: %zu byte(s)\n", sizeof(short));
    printf("int: %zu byte(s)\n", sizeof(int));
    printf("long: %zu byte(s)\n", sizeof(long));
    printf("long long: %zu byte(s)\n", sizeof(long long));
    printf("float: %zu byte(s)\n", sizeof(float));
    printf("double: %zu byte(s)\n", sizeof(double));
    printf("long double: %zu byte(s)\n", sizeof(long double));

    return 0;
}

/*O (%zu) é usado para mostrar o valor retornado pelo sizeof()*/