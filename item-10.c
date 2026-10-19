#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHO_TESTE 10000

void mergesort_in_place(int v[], int inicio, int fim);
void intercala_in_place(int v[], int inicio, int meio, int fim);
void gerar_vetor_aleatorio(int v[], int n);

int main() {
    srand(time(NULL));

    int *v_base = (int *)malloc(TAMANHO_TESTE * sizeof(int));
    int *v_test = (int *)malloc(TAMANHO_TESTE * sizeof(int));
    
    if (v_base == NULL || v_test == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }
    
    gerar_vetor_aleatorio(v_base, TAMANHO_TESTE);

    printf("Testando com N = %d elementos...\n", TAMANHO_TESTE);

    memcpy(v_test, v_base, TAMANHO_TESTE * sizeof(int));

    clock_t start = clock();
    mergesort_in_place(v_test, 0, TAMANHO_TESTE - 1);
    clock_t end = clock();

    double tempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tempo de execucao (In-Place): %7.5f segundos\n", tempo);
    printf("====================================================\n");

    // Validação rápida: checa se o vetor foi ordenado corretamente mesmo
    int ordenado = 1;
    for (int i = 0; i < TAMANHO_TESTE - 1; i++) {
        if (v_test[i] > v_test[i + 1]) {
            ordenado = 0;
            break;
        }
    }
    if (ordenado) printf("Resultado: Vetor ordenado com sucesso!\n");
    else printf("Resultado: Erro na ordenacao!\n");
    printf("====================================================\n");

    free(v_base);
    free(v_test);
    return 0;
}

// Algoritmo de divisão corrigido
void mergesort_in_place(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergesort_in_place(v, inicio, meio);
        mergesort_in_place(v, meio + 1, fim); // CORRIGIDO: Passa 'v' diretamente sem somar ponteiros

        intercala_in_place(v, inicio, meio, fim);
    }
}

void intercala_in_place(int v[], int inicio, int meio, int fim) {
    int inicio2 = meio + 1;

    // Se o último elemento da primeira metade já for menor ou igual ao primeiro da segunda,
    // significa que os dois blocos já estão perfeitamente ordenados entre si.
    if (v[meio] <= v[inicio2]) {
        return;
    }

    // Dois ponteiros correndo pelos subvetores
    while (inicio <= meio && inicio2 <= fim) {
        
        // Se o elemento no bloco 1 está no lugar certo
        if (v[inicio] <= v[inicio2]) {
            inicio++;
        } 
        else {
            int valor_menor = v[inicio2];
            int idx = inicio2;

            // Desloca todos os elementos entre v[inicio] e v[inicio2-1] uma posição para a direita
            while (idx != inicio) {
                v[idx] = v[idx - 1];
                idx--;
            }
            // Coloca o menor valor na sua posição correta ordenada
            v[inicio] = valor_menor;

            // Atualiza os ponteiros, já que tudo foi movido uma casa para a direita
            inicio++;
            meio++;
            inicio2++;
        }
    }
}

void gerar_vetor_aleatorio(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100000;
    }
}