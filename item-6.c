#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar o intervalo de uma reunião
typedef struct {
    int ini;
    int fim;
} Reuniao;

// Função de intercalação do Merge Sort adaptada para structs (ordena por 'ini')
void intercala_reunioes(Reuniao a[], int na, Reuniao b[], int nb, Reuniao c[]) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        // Ordena com base no horário de INÍCIO da reunião
        if (a[i].ini <= b[j].ini) {
            c[k++] = a[i++];
        } else {
            c[k++] = b[j++];
        }
    }
    while (i < na) c[k++] = a[i++];
    while (j < nb) c[k++] = b[j++];
}

// Algoritmo Merge Sort para ordenar as reuniões por horário de início
void mergesort_reunioes(Reuniao v[], int n) {
    if (n < 2) return;
    int meio = n / 2;
    mergesort_reunioes(v, meio);
    mergesort_reunioes(v + meio, n - meio);
    
    Reuniao *aux = (Reuniao *)malloc(n * sizeof(Reuniao));
    intercala_reunioes(v, meio, v + meio, n - meio, aux);
    
    for (int i = 0; i < n; i++) {
        v[i] = aux[i];
    }
    free(aux);
}

// Função principal que une as sobreposições e calcula o tempo total
void processar_reunioes(Reuniao v[], int n) {
    if (n <= 0) {
        printf("Nenhuma reunião agendada.\nTempo total: 0 minutos.\n");
        return;
    }

    // Passo 1: Ordenar as reuniões pelo horário de início O(n log n)
    mergesort_reunioes(v, n);

    printf("Intervalos ordenados antes da fusão:\n");
    for (int i = 0; i < n; i++) {
        printf("[%d, %d] ", v[i].ini, v[i].fim);
    }
    printf("\n\n");

    printf("Intervalos resultantes após a fusão:\n");

    // Inicializa o primeiro intervalo como o bloco atual de comparação
    Reuniao atual = v[0];
    int tempo_total = 0;

    // Passo 2: Varredura linear O(n) para mesclar os intervalos
    for (int i = 1; i < n; i++) {
        // Se a próxima reunião começa ANTES ou EXATAMENTE quando a atual termina, há sobreposição
        if (v[i].ini <= atual.fim) {
            // O fim do intervalo atual passa a ser o maior fim entre os dois
            if (v[i].fim > atual.fim) {
                atual.fim = v[i].fim;
            }
        } else {
            // Se não sobrepõe, imprime o bloco que acabou de fechar
            printf("[%d, %d] ", atual.ini, atual.fim);
            // Acumula a duração desse bloco fechado
            tempo_total += (atual.fim - atual.ini);
            // Começa um novo bloco com a reunião atual
            atual = v[i];
        }
    }
    
    // Imprime e acumula o último bloco processado
    printf("[%d, %d]\n", atual.ini, atual.fim);
    tempo_total += (atual.fim - atual.ini);

    printf("\nTempo total que o profissional passa em reunião: %d minutos.\n", tempo_total);
}

int main() {
    // Exemplo de teste do enunciado adicionando mais alguns casos
    //, [11,13], [15,16] -> Esperado: [9,13] e [15,16]
    Reuniao agenda[] = {
        {11, 13},
        {15, 16},
        {9, 12},
        {12, 14} // Adicionada para testar limite contínuo colado
    };
    int n = sizeof(agenda) / sizeof(agenda[0]);

    
    processar_reunioes(agenda, n);
    
    return 0;
}
