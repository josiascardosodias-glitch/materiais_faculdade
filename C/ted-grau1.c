// Josias
/* Programa para armazenar valores inteiros randômicos em matriz 4x5
e analisar frequências e valores distintos */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINHAS 4
#define COLUNAS 5

int main() {
    int matriz[LINHAS][COLUNAS];
    int frequencia[50] = {0};  // Array para contar frequências (0 a 49)
    int valoresDistintos[50];  // Array para armazenar valores distintos
    int countDistintos = 0;
    int maiorFrequencia = 0;
    int i, j, k;
    
    // Inicializa semente para números aleatórios
    srand(time(NULL));
    
    // Preenche a matriz com valores randômicos entre 0 e 49
    printf("Preenchendo a matriz com valores aleatórios entre 0 e 49...\n\n");
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            matriz[i][j] = rand() % 50;
            frequencia[matriz[i][j]]++;  // Conta a frequência de cada valor
        }
    }
    
    // Exibe a matriz no formato pedido
    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            printf("[%4d]", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    // Encontra a maior frequência
    for (i = 0; i < 50; i++) {
        if (frequencia[i] > maiorFrequencia) {
            maiorFrequencia = frequencia[i];
        }
    }
    
    // Coleta valores distintos e conta quantos têm maior frequência
    int countMaiorFrequencia = 0;
    for (i = 0; i < 50; i++) {
        if (frequencia[i] > 0) {
            // Adiciona aos valores distintos
            valoresDistintos[countDistintos] = i;
            countDistintos++;
            
            // Conta quantos valores têm a maior frequência
            if (frequencia[i] == maiorFrequencia) {
                countMaiorFrequencia++;
            }
        }
    }
    
    // Exibe resultado com formatação correta
    printf("O valor");
    int primeiroMaior = 1;
    for (i = 0; i < 50; i++) {
        if (frequencia[i] == maiorFrequencia) {
            if (!primeiroMaior) {
                printf(" e o");
            }
            printf(" %d", i);
            primeiroMaior = 0;
        }
    }
    
    // Formata mensagem (singular ou plural)
    if (countMaiorFrequencia > 1) {
        printf(" são os valores que mais aparecem na matriz com %d ocorrências\n", maiorFrequencia);
    } else {
        printf(" que mais aparece na matriz com %d ocorrência", maiorFrequencia);
        if (maiorFrequencia > 1) {
            printf("s");
        }
        printf("\n");
    }
    
    // Exibe valores distintos
    printf("Existem %d valor", countDistintos);
    if (countDistintos != 1) {
        printf("es");
    }
    printf(" diferentes na matriz: ");
    
    for (i = 0; i < countDistintos; i++) {
        printf("%d", valoresDistintos[i]);
        if (i < countDistintos - 1) {
            printf(", ");
        }
    }
    printf("\n");
    
    return 0;
}