#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "TAD-Vetorzao.h"

// --- ESTRUTURAS E FUNÇÕES LOCAIS PARA A Q5 ---
// Criamos funções locais de busca para garantir que elas parem
// exatamente no 'tamanho' atual do loop (já que as do TAD usam o N global)
typedef struct NoQ5 {
    long int valor;
    struct NoQ5 *prox;
} NoQ5;

NoQ5* inserir_inicio_lista(NoQ5* inicio, long int valor) {
    NoQ5* novo = (NoQ5*)malloc(sizeof(NoQ5));
    novo->valor = valor;
    novo->prox = inicio;
    return novo;
}

void liberar_lista(NoQ5* inicio) {
    NoQ5* atual = inicio;
    while (atual != NULL) {
        NoQ5* prox = atual->prox;
        free(atual);
        atual = prox;
    }
}

void busca_sequencial_vetor_limite(int *vet, int tamanho, int chave) {
    for(int i = 0; i < tamanho; i++) if(vet[i] == chave) return;
}

void busca_binaria_vetor_limite(int *vet, int tamanho, int chave) {
    int esq = 0, dir = tamanho - 1;
    while(esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        if(vet[meio] == chave) return;
        if(vet[meio] < chave) esq = meio + 1;
        else dir = meio - 1;
    }
}

void busca_sequencial_lista_limite(NoQ5* inicio, int chave) {
    NoQ5* atual = inicio;
    while (atual != NULL) {
        if (atual->valor == chave) return;
        atual = atual->prox;
    }
}

int comparar_q5(const void *a, const void *b) { return (*(int*)a - *(int*)b); }

int main() {
    srand(time(NULL));
    setlocale(LC_ALL, "pt_BR.UTF8");

    struct timespec inicio, fim;
    printf("==================================================\n");
    printf("QUESTÃO 5 - GERADOR DE GRÁFICOS (ORDENAÇÃO E BUSCA)\n");
    printf("==================================================\n");

    // ==============================================================
    // PARTE 1: GRÁFICOS DE ORDENAÇÃO (10k a 100k)
    // ==============================================================
    printf("\n[1/2] Gerando dados de ORDENAÇÃO (10.000 a 100.000)...\n");
    
    DadosAlgoritmo dadosOrd[50]; // 5 algoritmos * 10 tamanhos
    int idxOrd = 0;
    
    int *vetOrdBase = (int*)malloc(100000 * sizeof(int));
    int *vetOrdTrabalho = (int*)malloc(100000 * sizeof(int));

    for (int t = 10000; t <= 100000; t += 10000) {
        printf(" -> Ordenando tamanho: %d\n", t);
        criaVetordeIntDesordenado(vetOrdBase, t);
        double tempos[5]; 
        char* nomesOrd[] = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Quick Sort", "Merge Sort"};
        char* codigosOrd[] = {"BUBBLE SORT", "INSERTION SORT", "SELECTION SORT", "QUICK SORT", "MERGE SORT"};

        // 1. Bubble
        copiaVetor(vetOrdBase, vetOrdTrabalho, t);
        clock_gettime(CLOCK_REALTIME, &inicio);
        bubbleSort(vetOrdTrabalho, t);
        clock_gettime(CLOCK_REALTIME, &fim);
        tempos[0] = tempoDeExecucao(inicio, fim);

        // 2. Insertion
        copiaVetor(vetOrdBase, vetOrdTrabalho, t);
        clock_gettime(CLOCK_REALTIME, &inicio);
        insercaoDireta(vetOrdTrabalho, t);
        clock_gettime(CLOCK_REALTIME, &fim);
        tempos[1] = tempoDeExecucao(inicio, fim);

        // 3. Selection
        copiaVetor(vetOrdBase, vetOrdTrabalho, t);
        clock_gettime(CLOCK_REALTIME, &inicio);
        selecaoDireta(vetOrdTrabalho, t);
        clock_gettime(CLOCK_REALTIME, &fim);
        tempos[2] = tempoDeExecucao(inicio, fim);

        // 4. Quick
        copiaVetor(vetOrdBase, vetOrdTrabalho, t);
        clock_gettime(CLOCK_REALTIME, &inicio);
        quicksort(vetOrdTrabalho, 0, t - 1);
        clock_gettime(CLOCK_REALTIME, &fim);
        tempos[3] = tempoDeExecucao(inicio, fim);

        // 5. Merge
        copiaVetor(vetOrdBase, vetOrdTrabalho, t);
        clock_gettime(CLOCK_REALTIME, &inicio);
        merge_sort(vetOrdTrabalho, t); // Passando t (o TAD já faz t-1 internamente se for recursivo)
        clock_gettime(CLOCK_REALTIME, &fim);
        tempos[4] = tempoDeExecucao(inicio, fim);

        // Preencher Structs
        for (int i = 0; i < 5; i++) {
            dadosOrd[idxOrd].nome = nomesOrd[i];
            dadosOrd[idxOrd].algoritmo = codigosOrd[i];
            dadosOrd[idxOrd].tamanho = t;
            dadosOrd[idxOrd].media = tempos[i];
            dadosOrd[idxOrd].desvio_padrao = 0.0;
            dadosOrd[idxOrd].numero_execucoes = 1;
            dadosOrd[idxOrd].tempos = (double*)malloc(sizeof(double));
            dadosOrd[idxOrd].tempos[0] = tempos[i];
            idxOrd++;
        }
    }
    
    salvarDadosJSON("questao05_ordena_dados.json", "questao05_ordena", dadosOrd, 50);
    free(vetOrdBase); free(vetOrdTrabalho);
    for(int i=0; i<50; i++) free(dadosOrd[i].tempos);


    // ==============================================================
    // PARTE 2: GRÁFICOS DE BUSCA (100k a 1 Milhão)
    // ==============================================================
    printf("\n[2/2] Gerando dados de BUSCA (100.000 a 1.000.000). Isso pode demorar...\n");
    
    DadosAlgoritmo dadosBusca[30]; // 3 algoritmos * 10 tamanhos
    int idxBusca = 0;

    int *vetDesordenado = (int*)malloc(1000000 * sizeof(int));
    int *vetOrdenado = (int*)malloc(1000000 * sizeof(int));
    for(int i = 0; i < 1000000; i++) vetDesordenado[i] = rand() % 10000000;

    for (int t = 100000; t <= 1000000; t += 100000) {
        printf(" -> Buscando tamanho: %d\n", t);
        
        for(int i = 0; i < t; i++) vetOrdenado[i] = vetDesordenado[i];
        qsort(vetOrdenado, t, sizeof(int), comparar_q5);

        NoQ5* inicio_lista = NULL;
        for(int i = t - 1; i >= 0; i--) inicio_lista = inserir_inicio_lista(inicio_lista, vetDesordenado[i]);

        int chave = -1; // Pior caso para forçar a busca linear a percorrer tudo
        double temposBusca[3];
        char* nomesBusca[] = {"Busca Sequencial (Vetor)", "Busca Binária (Vetor)", "Busca Sequencial (Lista)"};
        char* codigosBusca[] = {"SEQ_VET", "BIN_VET", "SEQ_LST"};

        clock_gettime(CLOCK_REALTIME, &inicio);
        busca_sequencial_vetor_limite(vetDesordenado, t, chave);
        clock_gettime(CLOCK_REALTIME, &fim);
        temposBusca[0] = tempoDeExecucao(inicio, fim);

        clock_gettime(CLOCK_REALTIME, &inicio);
        busca_binaria_vetor_limite(vetOrdenado, t, chave);
        clock_gettime(CLOCK_REALTIME, &fim);
        temposBusca[1] = tempoDeExecucao(inicio, fim);

        clock_gettime(CLOCK_REALTIME, &inicio);
        busca_sequencial_lista_limite(inicio_lista, chave);
        clock_gettime(CLOCK_REALTIME, &fim);
        temposBusca[2] = tempoDeExecucao(inicio, fim);

        liberar_lista(inicio_lista);

        for (int i = 0; i < 3; i++) {
            dadosBusca[idxBusca].nome = nomesBusca[i];
            dadosBusca[idxBusca].algoritmo = codigosBusca[i];
            dadosBusca[idxBusca].tamanho = t;
            dadosBusca[idxBusca].media = temposBusca[i];
            dadosBusca[idxBusca].desvio_padrao = 0.0;
            dadosBusca[idxBusca].numero_execucoes = 1;
            dadosBusca[idxBusca].tempos = (double*)malloc(sizeof(double));
            dadosBusca[idxBusca].tempos[0] = temposBusca[i];
            idxBusca++;
        }
    }
    
    salvarDadosJSON("questao05_busca_dados.json", "questao05_busca", dadosBusca, 30);
    free(vetDesordenado); free(vetOrdenado);
    for(int i=0; i<30; i++) free(dadosBusca[i].tempos);

    printf("\n✅ Tudo concluído! Ficheiros 'questao05_ordena_dados.json' e 'questao05_busca_dados.json' gerados.\n");
    return 0;
}