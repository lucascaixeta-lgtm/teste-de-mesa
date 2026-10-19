#include <stdio.h>
#include <stdlib.h>

// Funções padrão do Merge Sort para ordenação linear O(n log n)
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
    for (int i = 0; i < n; i++) v[i] = aux[i];
    free(aux);
}

int main() {
    // Exemplo: 4 tarefas com tempos de execução misturados
    int tarefas[] = {10, 3, 5, 2}; // Tarefas: T1=10min, T2=3min, T3=5min, T4=2min
    int n = sizeof(tarefas) / sizeof(tarefas[0]);
    
    printf("Tempos das tarefas originais: ");
    for(int i = 0; i < n; i++) printf("%d ", tarefas[i]);
    printf("\n");

    // Aplicando a estratégia gulosa: ordenar de forma crescente
    mergesort(tarefas, n);

    printf("Ordem ótima de execução (SPT): ");
    for(int i = 0; i < n; i++) printf("%d ", tarefas[i]);
    printf("\n\n");

    // Calculando os tempos de conclusão individuais e o total
    int tempo_atual = 0;
    int soma_tempos_conclusao = 0;

    printf("Fluxo de execução:\n");
    for (int i = 0; i < n; i++) {
        tempo_atual += tarefas[i];
        soma_tempos_conclusao += tempo_atual;
        printf("  -> Tarefa %d (duracao %d) concluiu no instante: %d min\n", i + 1, tarefas[i], tempo_atual);
    }

    double media = (double)soma_tempos_conclusao / n;
    printf("\nSoma dos tempos de conclusão: %d\n", soma_tempos_conclusao);
    printf("Tempo médio de conclusão mínimo: %.2f minutos\n", media);

    return 0;
}
