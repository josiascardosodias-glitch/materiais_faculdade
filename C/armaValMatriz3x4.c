/*Armazenar valores inteiros em uma matriz 3x4. Exibir o conteúdo da matriz.*/

#include <stdio.h>

#define L 3
#define C 4
// cria uma constante com as cordenadas da matriz
int main() {
    int mat[L][C]; // declara a matriz

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            printf("Digite um numero: ");
            scanf("%d", &mat[i][j]);
        }
    }

    printf("\n--- Sua Matriz ---\n");
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            printf("%4d", mat[i][j]);
        }
        printf("\n");
    }

    return 0;
}