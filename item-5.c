#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Protótipos do Merge Sort (Estratégia A)
void intercala(int a[], int na, int b[], int nb, int c[]);
void mergesort(int v[], int n);

// Estratégias da Questão 5
int mediana_via_mergesort(int v[], int n);
int mediana_via_selection_parcial(int v[], int n, int k);

// Função utilitária para gerar números únicos e embaralhados
void gerar_vetor_distintos(int v[], int n);

int main() {
    srand(time(NULL));

    // Testando com um tamanho médio para observar a diferença de tempo de forma nítida
    int n = 20000; 
    int k = (n - 1) / 2 + 1; // Definição de k dada pelo enunciado

    int *v_base = (int *)malloc(n * sizeof(int));
    int *v_test = (int *)malloc(n * sizeof(int));
    gerar_vetor_distintos(v_base, n);


    // Teste da Estratégia A: Ordenar tudo com Merge Sort
    memcpy(v_test, v_base, n * sizeof(int));
    clock_t start_mrg = clock();
    int med_mrg = mediana_via_mergesort(v_test, n);
    clock_t end_mrg = clock();
    double tempo_mrg = (double)(end_mrg - start_mrg) / CLOCKS_PER_SEC;
    printf("  [Estratégia A - Merge Sort] Tempo: %7.5f s | Mediana: %d\n", tempo_mrg, med_mrg);

    // Teste da Estratégia B: Selection Sort Parcial 
    memcpy(v_test, v_base, n * sizeof(int));
    clock_t start_sel = clock();
    int med_sel = mediana_via_selection_parcial(v_test, n, k);
    clock_t end_sel = clock();
    double tempo_sel = (double)(end_sel - start_sel) / CLOCKS_PER_SEC;
    printf("  [Estratégia B - Sel Parcial] Tempo: %7.5f s | Mediana: %d\n", tempo_sel, med_sel);


    free(v_base);
    free(v_test);
    return 0;
}

//ESTRATÉGIA A: Ordenar tudo e pegar o elemento central O(n log n)
int mediana_via_mergesort(int v[], int n) {
    mergesort(v, n);
    return v[(n - 1) / 2];
}

//ESTRATÉGIA B: Executar apenas as primeiras k passadas do Selection Sort O(k * n)
int mediana_via_selection_parcial(int v[], int n, int k) {
    for (int i = 0; i < k; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min_idx]) {
                min_idx = j;
            }
        }
        // Troca o menor elemento encontrado com a posição atual i
        int temp = v[i];
        v[i] = v[min_idx];
        v[min_idx] = temp;
    }
    // O k-ésimo menor elemento estará exatamente na posição k-1 após k passadas
    return v[k - 1];
}

// Funções Auxiliares do Merge Sort
void intercala(int a[], int na, int b[], int nb, int c[]) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i] <= b[j]) c[k++] = a[i++];
        else c[k++] = b[j++];
    }
    while (i < na) c[k++] = a[i++];
    while (j < nb) c[k++] = b[j++];
}

void mergesort(int v[], int n) {
    if (n < 2) return;
    int meio = n / 2;
    mergesort(v, meio);
    mergesort(v + meio, n - meio);
    int *aux = (int *)malloc(n * sizeof(int));
    intercala(v, meio, v + meio, n - meio, aux);
    memcpy(v, aux, n * sizeof(int));
    free(aux);
}

// Preenche o vetor com valores de 0 a n-1 e depois embaralha (garante inteiros distintos)
void gerar_vetor_distintos(int v[], int n) {
    for (int i = 0; i < n; i++) v[i] = i;
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }
}
