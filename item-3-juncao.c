#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Protótipos das funções
void intercala(int a[], int na, int b[], int nb, int c[]);
void mergesort(int v[], int n);
void insertion_sort(int v[], int n);
void gerar_vetor_aleatorio(int v[], int n);

int main() {
    // Inicializa a semente aleatória
    srand(time(NULL));

    // Tamanhos exigidos pelo enunciado
    int tamanhos[] = {1000, 10000, 100000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    printf("%-12s | %-18s | %-18s\n", "Tamanho (N)", "Insertion Sort", "Merge Sort");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        
        // Aloca os vetores dinamicamente para evitar estouro de pilha em N=100.000
        int *v_base = (int *)malloc(n * sizeof(int));
        int *v_test = (int *)malloc(n * sizeof(int));
        
        gerar_vetor_aleatorio(v_base, n);

        //Teste do Insertion Sort
        memcpy(v_test, v_base, n * sizeof(int)); // Copia o vetor original
        clock_t start_ins = clock();
        insertion_sort(v_test, n);
        clock_t end_ins = clock();
        double tempo_ins = (double)(end_ins - start_ins) / CLOCKS_PER_SEC;

        //Teste do Merge Sort
        memcpy(v_test, v_base, n * sizeof(int)); // Reseta o vetor com os mesmos dados aleatórios
        clock_t start_mrg = clock();
        mergesort(v_test, n);
        clock_t end_mrg = clock();
        double tempo_mrg = (double)(end_mrg - start_mrg) / CLOCKS_PER_SEC;

        //Imprime os resultados formatados
        printf("%-12d | %-15.5f s | %-15.5f s\n", n, tempo_ins, tempo_mrg);

        //Libera a memória alocada
        free(v_base);
        free(v_test);
    }
    printf("====================================================\n");

    return 0;
}

// --- ITEM 3.1: Função intercala isolada requisitada pelo enunciado ---
void intercala(int a[], int na, int b[], int nb, int c[]) {
    int i = 0, j = 0, k = 0;

    //Percorre ambos os vetores comparando elemento a elemento
    while (i < na && j < nb) {
        if (a[i] <= b[j]) {
            c[k] = a[i];
            i++;
        } else {
            c[k] = b[j];
            j++;
        }
        k++;
    }

    //Copia os elementos restantes de 'a', se houver
    while (i < na) {
        c[k] = a[i];
        i++;
        k++;
    }

    //Copia os elementos restantes de 'b', se houver
    while (j < nb) {
        c[k] = b[j];
        j++;
        k++;
    }
}

//ITEM 3.2: Implementação do Mergesort usando a função intercala
void mergesort(int v[], int n) {
    if (n < 2) return; // Caso base: vetor com 0 ou 1 elemento já está ordenado

    int meio = n / 2;

    //Divide e ordena a primeira metade de forma recursiva
    mergesort(v, meio);
    
    //Divide e ordena a segunda metade de forma recursiva
    mergesort(v + meio, n - meio);

    // Aloca vetor auxiliar dinamicamente para a intercalação
    int *aux = (int *)malloc(n * sizeof(int));
    
    //Intercala as duas metades ordenadas dentro do vetor auxiliar
    intercala(v, meio, v + meio, n - meio, aux);

    //Copia o resultado de volta para o vetor original
    memcpy(v, aux, n * sizeof(int));
    
    free(aux);
}

//Função Insertion Sort tradicional para comparação
void insertion_sort(int v[], int n) {
    for (int j = 1; j < n; ++j) {
        int x = v[j];
        int i = j - 1;
        while (i >= 0 && v[i] > x) {
            v[i + 1] = v[i];
            i--;
        }
        v[i + 1] = x;
    }
}

//Função utilitária para gerar dados aleatórios 
void gerar_vetor_aleatorio(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100000;
    }
}
