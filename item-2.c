#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_EXECUCOES 600000

void insertionsort_al(int n, int v[]) {
    for (int j = 1; j < n; ++j) {
        int x = v[j];
        int i;
        for (i = j - 1; i >= 0; --i) {
            if (rand() > RAND_MAX / 2)
                v[i + 1] = v[i];
            else 
                break;
        }
        v[i + 1] = x;
    }
}

// Função auxiliar para converter o vetor em um identificador inteiro
int obter_id_permutacao(int v[]) {
    return v[0] * 100 + v[1] * 10 + v[2];
}

int main() {
    // Inicializa os contadores para as 6 permutações possíveis
    int c_123 = 0, c_132 = 0, c_213 = 0, c_231 = 0, c_312 = 0, c_321 = 0;
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("Executando o embaralhamento %d vezes...\n\n", TOTAL_EXECUCOES);

    for (int i = 0; i < TOTAL_EXECUCOES; i++) {
        // Reinicializa o vetor original antes de cada embaralhamento
        int v[3] = {1, 2, 3};
        
        // Aplica o algoritmo de embaralhamento do enunciado
        insertionsort_al(3, v);
        
        // Identifica qual permutação foi gerada e incrementa o respectivo contador
        int id = obter_id_permutacao(v);
        switch (id) {
            case 123: c_123++; break;
            case 132: c_132++; break;
            case 213: c_213++; break;
            case 231: c_231++; break;
            case 312: c_312++; break;
            case 321: c_321++; break;
            default:  printf("Erro: Permutacao invalida %d\n", id); break;
        }
    }

    // Exibe os resultados obtidos

    printf("  {1, 2, 3} |   %7d   |   %6.2f%%\n", c_123, (c_123 * 100.0) / TOTAL_EXECUCOES);
    printf("  {1, 3, 2} |   %7d   |   %6.2f%%\n", c_132, (c_132 * 100.0) / TOTAL_EXECUCOES);
    printf("  {2, 1, 3} |   %7d   |   %6.2f%%\n", c_213, (c_213 * 100.0) / TOTAL_EXECUCOES);
    printf("  {2, 3, 1} |   %7d   |   %6.2f%%\n", c_231, (c_231 * 100.0) / TOTAL_EXECUCOES);
    printf("  {3, 1, 2} |   %7d   |   %6.2f%%\n", c_312, (c_312 * 100.0) / TOTAL_EXECUCOES);
    printf("  {3, 2, 1} |   %7d   |   %6.2f%%\n", c_321, (c_321 * 100.0) / TOTAL_EXECUCOES);
    printf("-----------------------------------------\n");
    printf(" Ideal Esperado: 100.000 (16.67%%) por permutacao.\n");

    return 0;
}