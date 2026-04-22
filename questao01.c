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
    
    // Preparar dados para salvar em JSON
    double desvioSeq = desvioPadrao(temposSeq, mediaSeq);
    double desvioBin = desvioPadrao(temposBin, mediaBin);
    
    DadosAlgoritmo algoritmos[2];
    
    // Busca Sequencial
    algoritmos[0].nome = "Busca Sequencial";
    algoritmos[0].algoritmo = "Busca Sequencial";
    algoritmos[0].tamanho = 1000000;
    algoritmos[0].media = mediaSeq;
    algoritmos[0].desvio_padrao = desvioSeq;
    algoritmos[0].numero_execucoes = 30;
    algoritmos[0].tempos = temposSeq;
    
    // Busca Binária
    algoritmos[1].nome = "Busca Binária";
    algoritmos[1].algoritmo = "Busca Binária";
    algoritmos[1].tamanho = 1000000;
    algoritmos[1].media = mediaBin;
    algoritmos[1].desvio_padrao = desvioBin;
    algoritmos[1].numero_execucoes = 30;
    algoritmos[1].tempos = temposBin;
    
    // Salvar em JSON usando função genérica
    salvarDadosJSON("questao01_dados.json", "questao01", algoritmos, 2);
    
    return 0;
}