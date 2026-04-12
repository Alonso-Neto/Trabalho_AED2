#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "TAD-Vetorzao.h"



int main() {

    srand(time(NULL));
    struct timespec inicio, fim;
    int res,i;
    double somaTemposSeq = 0, somaTemposBin = 0;
    double mediaSeq = 0, mediaBin = 0;
    double temposSeq[30];
    double temposBin[30];
    setlocale(LC_ALL,"pt_BR.UTF8");
    
    printf("VETOR DESORDENADO !!\n");
    criaVetorDesordenado();

    copiaVetorParaArquivo(vetor);
    
    printf("BUSCA SEQUENCIAL - ELEMENTO NO VETOR!!\n");
    for(i=0; i<15; i++){
            clock_gettime(CLOCK_REALTIME, &inicio);
            buscaSequencial(sortearElementoNoVetor());
            clock_gettime(CLOCK_REALTIME, &fim);
            temposSeq[i] = tempoDeExecucao(inicio,fim);
            somaTemposSeq += temposSeq[i];
    }

    printf("BUSCA SEQUENCIAL - ELEMENTO ALEATÓRIO\n");
    for(i=0; i<15; i++){
        clock_gettime(CLOCK_REALTIME, &inicio);
        buscaSequencial(sortearElemento());
        clock_gettime(CLOCK_REALTIME, &fim);
        temposSeq[15+i] = tempoDeExecucao(inicio,fim);
        somaTemposSeq += temposSeq[15+i];
    }

    printf("\nVETOR ORDENADO !!!!\n");
    criaVetorOrdenado();
    printf("BUSCA BINÁRIA - ELEMENTO NO VETOR\n");
    for(i=0; i<15; i++){
            clock_gettime(CLOCK_REALTIME, &inicio);
            buscaBinaria(sortearElementoNoVetor());
            clock_gettime(CLOCK_REALTIME, &fim);
            temposBin[i] = tempoDeExecucao(inicio,fim);
            somaTemposBin += temposBin[i];
    }

    printf("\nBUSCA BINÁRIA - ELEMENTO ALEATÓRIO\n");
    for(i=0; i<15; i++){
        clock_gettime(CLOCK_REALTIME, &inicio);
        buscaBinaria(sortearElemento());
        clock_gettime(CLOCK_REALTIME, &fim);
        temposBin[i+15] = tempoDeExecucao(inicio,fim);
        somaTemposBin += temposBin[i+15];
    }

    printf("\n\n");
    printf("=====================\n");
    printf("RESUMO FINAL - BUSCA SEQUENCIAL\n");
    printf("=====================\n");
    mediaSeq = somaTemposSeq / 30;
    printf("Média das 30 execuções: %.6lf milissegundos\n", mediaSeq);
    printf("=====================\n");
    desvioPadrao(temposSeq, mediaSeq);
    
    printf("\n");
    printf("=====================\n");
    printf("RESUMO FINAL - BUSCA BINÁRIA\n");
    printf("=====================\n");
    mediaBin = somaTemposBin / 30;
    printf("Média das 30 execuções: %.6lf milissegundos\n", mediaBin);
    printf("=====================\n");
    desvioPadrao(temposBin, mediaBin);

    printf("\n");
    printf("Final do programa !!\n");
    return 0;
}