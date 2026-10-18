#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tamanho 20

int selmin(int vetor[], int i, int tam){
    int j, k = i;
    for(j = i + 1; j < tam; j++){
        if(vetor[j] < vetor[k]){
            k = j;
        }
    }
    return k;
}

void selectSort(int vetor[], int tam){
    int i, k, x;

    for(i = 0; i < tam; i++){
        k=selmin(vetor, i, tam);
        x=vetor[i];
        vetor[i]=vetor[k];
        vetor[k]=x;
    }
}


int main(){
    int V[tamanho];

    srand(time(NULL));

    for(int i = 0; i < tamanho; i++){
        V[i] = (rand() % 100) + 1;
    }

    /*
    printf("Lista de numeros dessordenados: \n");
    for (int i = 0; i < tamanho; i++){
        printf("%d ", V[i]);
    }
    */
    printf("\n");

    int indice_do_menor = selmin(V, 0, tamanho);
    printf("O menor valor encontrado na lista desordenada eh: %d\n\n", V[indice_do_menor]);


    selectSort(V, tamanho);

    printf("Lista de numeros ordenados: \n");
    for(int i = 0; i < tamanho; i++){
       printf("%d ", V[i]);
    }

    printf("\n\n");

    int start_time = clock() / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %d segundos no selection sort\n", start_time);
    
    
    return 0;
}