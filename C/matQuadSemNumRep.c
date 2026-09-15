/*Armazenar 25 valores inteiros em uma matriz quadrada (supor que são distintos). A
seguir, ler um valor qualquer e verificar se ele se encontra ou não na matriz. Se ele
estiver presente, então informar sua posição.*/

#include <stdio.h>

#define X 5
#define Y 5

int main() {

    int mat[X][Y];

    printf("Vamos gerar uma matriz com %d espaços\n", X*Y);
    
    for (int l=0; l<X; l++) {
        for (int c=0; c<Y; c++) {
            printf("[%d][%d]: ", l, c); scanf("%d", &mat[l][c]);
        }
    }

    int n;

    do {
        printf("Você deseja saber a posição de qual numero (Digite -1 para sair): \n"); scanf("%d", &n);

            if (n == -1) {
                break;
            }

            int encontrado = 0;

            for (int l = 0; l < X; l++) {
                for (int c = 0; c < Y; c++) {
                    if (n == mat[l][c]) {
                        printf("O numero %d foi encontrado na posição [%d][%d]\n", n, l, c);
                        encontrado = 1;
                        break;
                    }
                }

                if (encontrado) {
                    break;
                }
            }

            if (!encontrado) {
                printf("Numero não encontrado\n");
            }
    } while (n != -1);


    printf("\n --- Sua Matriz --- \n");
    for (int l=0; l<X; l++) {
        for (int c=0; c<Y; c++) {
            printf("%4d", mat[l][c]);
        }
        printf("\n");
    }

    return 0;
}