/*Armazenar, de forma randômica, valores inteiros em uma matriz 5x6. A seguir,
exibir o conteúdo da matriz e o percentual de valores pares.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIN 5
#define COL 6

int main() {

    int mat[LIN][COL];

    srand(time(NULL));
    for (int l = 0; l < LIN; l++) {
        for (int c = 0; c < COL; c++) {
            mat[l][c] = rand() % 100;
        }
    }

    int cont, somaPar;
    float percent;

    printf("\n--- Sua matriz ---\n");
    for (int l =0; l < LIN; l++) {
        for (int c = 0; c < COL; c++) {
            if(mat[l][c] % 2 == 0) {
                somaPar += mat[l][c];
                cont++;
            }
            printf("%4d", mat[l][c]);
        }
        printf("\n");
    }

    if (cont == 0) {
        printf("Nenhum valor encontrado!");
    } else {
        percent = ((float)cont / (LIN * COL)) * 100;
        printf("A porcentagem dos pares foi de %.2f%%",percent);
    }

    return 0;
}