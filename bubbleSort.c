#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tamanho 5

void bubbleSort(int vetor[], int tam){
    int i, j;
    for(i = 1; i < tam; i++){
        for(j =0; j < tam - 1; j++){
            if( vetor[j] > vetor[j+1]){
                int x = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = x;
            }
        }
    }
}

 
int main(){
    int V[tamanho];

    srand(time(NULL));

    for(int i = 0; i < tamanho; i++){
        V[i] = (rand() % 100) + 1;
    }

    
    printf("Lista de numeros dessordenados: \n");
    for (int i = 0; i < tamanho; i++){
        printf("%d ", V[i]);
    }
    printf("\n");
    

    bubbleSort(V, tamanho);

    printf("Lista de numeros ordenados: \n");
    for(int i = 0; i < tamanho; i++){
        printf("%d ", V[i]);
    }

    printf("\n\n");

    int start_time = clock() / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %d segundos no bubble sort\n", start_time);
    
    
    return 0;
}
