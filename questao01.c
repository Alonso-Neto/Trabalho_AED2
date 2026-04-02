#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "TAD-Vetorzao.h"



int main() {

    struct timespec inicio, fim;
    int res,i;
    double somaTempos = 0, media = 0;
    double tempos[30];
    setlocale(LC_ALL,"pt_BR.UTF8");
    
    printf("VETOR DESORDENADO !!\n");
    criaVetorDesordenado();
    
    printf("BUSCA POR ELEMENTO NO VETOR!!\n");
    for(i=0; i<15; i++){
            clock_gettime(CLOCK_REALTIME, &inicio);
            buscaSequencial(sortearElementoNoVetor());
            clock_gettime(CLOCK_REALTIME, &fim);
            tempoDeExecucao(inicio,fim);
            somaTempos += tempoDeExecucao(inicio, fim);
            tempos[i] = tempoDeExecucao(inicio,fim);
    }
    printf("********************************************Média das 15 execuções: %.6lf\n",somaTempos/15);

    printf("BUSCA POR ELEMENTO ALEATÓRIO\n");
    for(i=0; i<15; i++){
        clock_gettime(CLOCK_REALTIME, &inicio);
        buscaSequencial(sortearElemento());
        clock_gettime(CLOCK_REALTIME, &fim);
        tempoDeExecucao(inicio,fim);
        somaTempos += tempoDeExecucao(inicio, fim);
        tempos[15+i] = tempoDeExecucao(inicio,fim);
    }
    printf("*******************************************Média das 15 execuções: %.6lf\n",somaTempos/15);
    
    media = somaTempos/30;
    printf("=====================\n");
    printf("Média das 30 execuções: %.6lf\n",media);
    printf("=====================\n");



    //Segunda parte nesta bosta
    somaTempos = 0;
    media = 0;

    printf("VETOR ORDENADO !!!!\n");
    criaVetorOrdenado();
    printf("BUSCA POR ELEMENTO NO VETOR\n");
    for(i=0; i<15; i++){
            clock_gettime(CLOCK_REALTIME, &inicio);
            buscaBinaria(sortearElementoNoVetor());
            clock_gettime(CLOCK_REALTIME, &fim);
            tempoDeExecucao(inicio,fim);
            somaTempos += tempoDeExecucao(inicio, fim);
    }
    printf("********************************************Média das 15 execuções: %.6lf\n",somaTempos/15);

    printf("BUSCA POR ELEMENTO ALEATÓRIO\n");
    for(i=0; i<15; i++){
        clock_gettime(CLOCK_REALTIME, &inicio);
        buscaBinaria(sortearElemento());
        clock_gettime(CLOCK_REALTIME, &fim);
        tempoDeExecucao(inicio,fim);
        somaTempos += tempoDeExecucao(inicio, fim);
    }
    printf("*******************************************Média das 15 execuções: %.6lf\n",somaTempos/15);

    media = somaTempos/30;
    printf("=====================\n");
    printf("Média das 30 execuções: %.6lf milissegundos\n",media);
    printf("=====================\n");
    


    desvioPadrao(tempos,media);


    printf("Final do programa !!\n");
    return 0;
}