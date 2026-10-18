#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tamanho 20

void merger(int V[], int inicio, int fim);
void intercalacao(int V[], int inicio, int fim, int meio);

int main()
{
    int vector[tamanho];
    srand(time(NULL));

    for(int i = 0; i < tamanho; i++){
        vector[i] = (rand() % 100) + 1;
    }

    /*
    printf("Vetor original:");
    for(int i = 0; i < tamanho; i++){
        printf(" %d", vector[i]);
    }
    printf("\n");
    */

    merger(vector, 0, tamanho - 1);

    printf("Vetor ordenado:");

    for(int i = 0; i < tamanho; i++){
        printf(" %d", vector[i]);
    }
    printf("\n");

     int start_time = clock() / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %d segundos no merge sort\n", start_time);

    return 0;
}

void merger(int V[], int inicio, int fim)
{
    int meio;

    if(inicio < fim){
        meio = (inicio + fim) / 2;
        merger(V, inicio, meio);
        merger(V, meio + 1, fim);
        intercalacao(V, inicio, fim, meio);
    }
}

void intercalacao(int V[], int inicio, int fim, int meio)
{
    int aux[tamanho];
    int pos, inicio_v1, inicio_v2;
    inicio_v1 = inicio;
    inicio_v2 = meio + 1;
    pos = inicio;

    while(inicio_v1 <= meio && inicio_v2 <= fim){
        if(V[inicio_v1] <= V[inicio_v2]){
            aux[pos] = V[inicio_v1];
            inicio_v1++;
        }
        else{
            aux[pos] = V[inicio_v2];
            inicio_v2++;
        }
        pos++;
    }

    while(inicio_v1 <= meio){
        aux[pos] = V[inicio_v1];
        inicio_v1++;
        pos++;
    }

    while(inicio_v2 <= fim){
        aux[pos] = V[inicio_v2];
        inicio_v2++;
        pos++;
    }

    for(int i = inicio; i <= fim; i++){
        V[i] = aux[i];
    }
}