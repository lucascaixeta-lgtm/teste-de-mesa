#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 100000

// Protótipos das funções
void intercala(int a[], int na, int b[], int nb, int c[]);
void mergesort_hibrido(int v[], int n, int k);
void insertion_sort(int v[], int inicio, int fim);
void gerar_vetor_aleatorio(int v[], int n);

int main() {
    srand(time(NULL));

    // Vetores de teste
    int *v_base = (int *)malloc(N * sizeof(int));
    int *v_test = (int *)malloc(N * sizeof(int));
    gerar_vetor_aleatorio(v_base, N);

    // Valores de k exigidos pelo enunciado
    int valores_k[] = {1, 4, 8, 16, 32, 64, 128};
    int num_k = sizeof(valores_k) / sizeof(valores_k[0]);

    for (int i = 0; i < num_k; i++) {
        int k = valores_k[i];
        
        // Copia o vetor base original para garantir o mesmo cenário de teste
        memcpy(v_test, v_base, N * sizeof(int));

        clock_t start = clock();
        mergesort_hibrido(v_test, N, k);
        clock_t end = clock();

        double tempo = (double)(end - start) / CLOCKS_PER_SEC;
        printf("     k = %-3d    |   %10.5f s\n", k, tempo);
    }

    free(v_base);
    free(v_test);
    return 0;
}

//Insertion Sort modificado para ordenar um intervalo específico [inicio..fim] 
void insertion_sort(int v[], int inicio, int fim) {
    for (int j = inicio + 1; j <= fim; ++j) {
        int x = v[j];
        int i = j - 1;
        while (i >= inicio && v[i] > x) {
            v[i + 1] = v[i];
            i--;
        }
        v[i + 1] = x;
    }
}

// Merge Sort 
void mergesort_hibrido(int v[], int n, int k) {
    // 💡 MODIFICAÇÃO PRINCIPAL: Se o tamanho do bloco for menor ou igual a k, usa Insertion Sort
    if (n <= k) {
        insertion_sort(v, 0, n - 1);
        return;
    }

    int meio = n / 2;

    // Continua a divisão recursiva
    mergesort_hibrido(v, meio, k);
    mergesort_hibrido(v + meio, n - meio, k);

    // Aloca vetor auxiliar para a intercalação
    int *aux = (int *)malloc(n * sizeof(int));
    intercala(v, meio, v + meio, n - meio, aux);
    memcpy(v, aux, n * sizeof(int));
    free(aux);
}

// Função intercala padrão O(n)
void intercala(int a[], int na, int b[], int nb, int c[]) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i] <= b[j]) c[k++] = a[i++];
        else c[k++] = b[j++];
    }
    while (i < na) c[k++] = a[i++];
    while (j < nb) c[k++] = b[j++];
}

void gerar_vetor_aleatorio(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100000;
    }
}
