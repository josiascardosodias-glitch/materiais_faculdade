/*Armazenar 100 valores inteiros em uma matriz quadrada. Após, armazenar os
valores pares existentes na matriz no vetor VPAR. No final, escrever o conteúdo do
vetor VPAR (somente os valores armazenados).*/

#include <stdio.h>

#define X 10
#define Y 10

int main() {

    int mat[X][Y];

    printf("Vamos criar uma matriz com %d espaços\n", X*Y);
    for (int l=0; l<X; l++) {
        for (int c=0; c<Y; c++) {
            printf("[%d][%d]: ", l,c); scanf("%d", &mat[l][c]); 
        }
    }

    int vpar[X*Y];
    int pos=0;

    printf("\n--- Sua Matriz ---\n");
    for (int l=0; l<X; l++) {
        for (int c=0; c<Y; c++) {
            if (mat[l][c] % 2 == 0) {
                vpar[pos] = mat[l][c];
                pos++;
            }
            printf("%4d", mat[l][c]);
        }
        printf("\n");
    }
    printf("\n--- Vetor de Numeros Pares ---\n");
    for (int i=0; i<pos; i++)
        printf("[%d]", vpar[i]);

    return 0;
}