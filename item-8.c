#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_M 50 // Tamanho máximo de uma palavra

// Estrutura solicitada pelo enunciado
typedef struct {
    char original[MAX_M];
    char chave[MAX_M];
} Palavra;

//1. Funções para ordenar as LETRAS de uma palavra (Insertion Sort - eficiente para strings pequenas) 
void ordenar_letras(char str[]) {
    int n = strlen(str);
    for (int j = 1; j < n; ++j) {
        char x = str[j];
        int i = j - 1;
        while (i >= 0 && str[i] > x) {
            str[i + 1] = str[i];
            i--;
        }
        str[i + 1] = x;
    }
}

//2. Funções do Merge Sort para ordenar o vetor de STRUCTS com base na 'chave' 
void intercala_structs(Palavra a[], int na, Palavra b[], int nb, Palavra c[]) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (strcmp(a[i].chave, b[j].chave) <= 0) {
            c[k++] = a[i++];
        } else {
            c[k++] = b[j++];
        }
    }
    while (i < na) c[k++] = a[i++];
    while (j < nb) c[k++] = b[j++];
}

void mergesort_structs(Palavra v[], int n) {
    if (n < 2) return;
    int meio = n / 2;
    mergesort_structs(v, meio);
    mergesort_structs(v + meio, n - meio);
    
    Palavra *aux = (Palavra *)malloc(n * sizeof(Palavra));
    intercala_structs(v, meio, v + meio, n - meio, aux);
    
    for (int i = 0; i < n; i++) v[i] = aux[i];
    free(aux);
}

//3. Função para agrupar e imprimir os anagramas
void agrupar_anagramas(Palavra lista[], int n) {
    // Passo 1: Gerar a chave para cada palavra
    for (int i = 0; i < n; i++) {
        // Copia e converte para minúsculas
        int tam = strlen(lista[i].original);
        for (int j = 0; j < tam; j++) {
            lista[i].chave[j] = tolower(lista[i].original[j]);
        }
        lista[i].chave[tam] = '\0';
        
        // Ordena as letras para criar a chave única do anagrama
        ordenar_letras(lista[i].chave);
    }

    // Passo 2: Ordenar a lista de structs pela chave O(n log n)
    mergesort_structs(lista, n);

    // Passo 3: Varredura linear O(n) para imprimir os grupos agrupados
    printf("Grupos de Anagramas encontrados:\n");
    printf("[ %s ", lista[0].original);
    
    for (int i = 1; i < n; i++) {
        // Se a chave mudou, fecha o grupo anterior e inicia um novo
        if (strcmp(lista[i].chave, lista[i - 1].chave) != 0) {
            printf("]\n[ %s ", lista[i].original);
        } else {
            printf(", %s ", lista[i].original);
        }
    }
    printf("]\n");
}

int main() {
    // Vetor de testes baseado no enunciado
    Palavra lista[] = {
        {"amor"}, {"Roma"}, {"computador"}, {"ramo"}, 
        {"mora"}, {"pedra"}, {"perda"}, {"padre"}
    };
    int n = sizeof(lista) / sizeof(lista[0]);

    agrupar_anagramas(lista, n);

    return 0;
}
