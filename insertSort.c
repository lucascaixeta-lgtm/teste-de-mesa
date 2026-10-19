#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tamanho 100000

void insertSort(int vetor[], int tam){

    int i, j, chave;
    for(i = 1; i < tam; i++){ //O(N)
        chave = vetor[i]; // O(N - 1)
        j = i - 1; //O(N - 1)
        while(j >= 0 && vetor[j] > chave){  //O(N)
            vetor[j + 1] = vetor[j];
            j--;
        }
        
        vetor[j + 1] = chave;
    }
}

int main(){
    int V[tamanho];

    srand(time(NULL));

    for(int i = 0; i < tamanho; i++){
        V[i] = (rand() % 10000) + 1;
    }

    
    printf("Lista de numeros dessordenados: \n");
    for (int i = 0; i < tamanho; i++){
        printf("%d ", V[i]);
    }
    printf("\n\n");
    

    insertSort(V, tamanho);

    
    printf("Lista de numeros ordenados: \n");
    for(int i = 0; i < tamanho; i++){
        printf("%d ", V[i]);
    }
    
    printf("\n\n");

    int start_time = clock() / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %d segundos no insert sort\n", start_time);


    return 0;
}