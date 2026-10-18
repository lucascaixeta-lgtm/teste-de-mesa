#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tamanho 20

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
    return 0;
}