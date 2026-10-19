#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Protótipos das funções do Merge Sort (reaproveitadas da questão 3)
void intercala(int a[], int na, int b[], int nb, int c[]);
void mergesort(int v[], int n);

// Funções da Questão 4
void solucao_ingenua(int v[], int n, int *distintos, int *moda, int *max_frequencia);
void solucao_ordenada(int v[], int n, int *distintos, int *moda, int *max_frequencia);
void gerar_vetor_aleatorio(int v[], int n);

int main() {
    srand(time(NULL));

    int tamanhos[] = {10000, 100000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos);


    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        
        int *v_base = (int *)malloc(n * sizeof(int));
        int *v_test = (int *)malloc(n * sizeof(int));
        gerar_vetor_aleatorio(v_base, n);

        int dist_ing, moda_ing, freq_ing;
        int dist_ord, moda_ord, freq_ord;

        printf("\nTestando para N = %d elementos\n", n);
        
        memcpy(v_test, v_base, n * sizeof(int));
        clock_t start_ing = clock();
        solucao_ingenua(v_test, n, &dist_ing, &moda_ing, &freq_ing);
        clock_t end_ing = clock();
        double tempo_ing = (double)(end_ing - start_ing) / CLOCKS_PER_SEC;
        
        printf("  [Ingênua]  Tempo: %7.5f s | Distintos: %d | Moda: %d (%d vezes)\n", 
               tempo_ing, dist_ing, moda_ing, freq_ing);

        //2. Teste da Solução Ordenada
        memcpy(v_test, v_base, n * sizeof(int));
        clock_t start_ord = clock();
        
        // Passo 1: Ordenar primeiro
        mergesort(v_test, n);
        // Passo 2: Varredura única
        solucao_ordenada(v_test, n, &dist_ord, &moda_ord, &freq_ord);
        
        clock_t end_ord = clock();
        double tempo_ord = (double)(end_ord - start_ord) / CLOCKS_PER_SEC;
        
        printf("  [Ordenada] Tempo: %7.5f s | Distintos: %d | Moda: %d (%d vezes)\n", 
               tempo_ord, dist_ord, moda_ord, freq_ord);

        free(v_base);
        free(v_test);
    }

    return 0;
}

//ABORDAGEM INGÊNUA: Dois laços aninhados O(N²)
void solucao_ingenua(int v[], int n, int *distintos, int *moda, int *max_frequencia) {
    int cont_distintos = 0;
    int m_valor = v[0];
    int m_freq = 0;

    for (int i = 0; i < n; i++) {
        int freq_atual = 0;
        int ja_visto = 0;

        // Verifica se o elemento já apareceu antes para não contar duplicado nos 'distintos'
        for (int j = 0; j < i; j++) {
            if (v[i] == v[j]) {
                ja_visto = 1;
                break;
            }
        }

        if (!ja_visto) {
            cont_distintos++;
        }

        // Conta quantas vezes v[i] aparece no vetor inteiro
        for (int j = 0; j < n; j++) {
            if (v[i] == v[j]) {
                freq_atual++;
            }
        }

        // Atualiza a moda
        if (freq_atual > m_freq) {
            m_freq = freq_atual;
            m_valor = v[i];
        }
    }

    *distintos = cont_distintos;
    *moda = m_valor;
    *max_frequencia = m_freq;
}

//  ABORDAGEM INTELIGENTE: Varredura única O(N) após ordenação
void solucao_ordenada(int v[], int n, int *distintos, int *moda, int *max_frequencia) {
    // Como o vetor está ordenado, elementos iguais ficam grudados um no outro
    int cont_distintos = 1; // Se o vetor tem elementos, há pelo menos 1 distinto
    int m_valor = v[0];
    int m_freq = 1;

    int freq_atual = 1;

    for (int i = 1; i < n; i++) {
        if (v[i] != v[i - 1]) {
            // Se mudou de valor, significa que encontramos um novo número distinto
            cont_distintos++;
            
            // Verifica se o bloco que acabou de fechar é a maior frequência (moda)
            if (freq_atual > m_freq) {
                m_freq = freq_atual;
                m_valor = v[i - 1];
            }
            freq_atual = 1; // Reseta o contador para o novo número
        } else {
            // Se for igual ao anterior, incrementa a repetição consecutiva
            freq_atual++;
        }
    }

    // Checagem final para o último bloco de elementos do vetor
    if (freq_atual > m_freq) {
        m_freq = freq_atual;
        m_valor = v[n - 1];
    }

    *distintos = cont_distintos;
    *moda = m_valor;
    *max_frequencia = m_freq;
}

//Funções Auxiliares do Merge Sort (Exigido para a solução ordenada)
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

// Popula o vetor com números de 0 a 999 conforme solicitado
void gerar_vetor_aleatorio(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 1000;
    }
}