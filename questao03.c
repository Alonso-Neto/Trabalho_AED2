#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "TAD-Vetorzao.h"

int main(){
    srand(time(NULL));
    setlocale(LC_ALL,"pt_BR.UTF8");

    int vet[100000];
    struct timespec inicio, fim;

    criaVetordeIntDesordenado(vet,100000);
    
    //clock_gettime(CLOCK_REALTIME,&inicio);
    //bubbleSort(vet,100000);
    //clock_gettime(CLOCK_REALTIME,&fim);
    //printf("Tempo de execução bubble sort: %.6lf milissegundos\n",tempoDeExecucao(inicio,fim));

    //clock_gettime(CLOCK_REALTIME,&inicio);
    //insercaoDireta(vet,100000);
    //clock_gettime(CLOCK_REALTIME,&fim);
    //printf("Tempo de execução inserção direta: %.6lf milissegundos\n",tempoDeExecucao(inicio,fim));

    //clock_gettime(CLOCK_REALTIME,&inicio);
    //selecaoDireta(vet,100000);
    //clock_gettime(CLOCK_REALTIME,&fim);
    //printf("Tempo de execução seleção Direta: %.6lf milissegundos\n",tempoDeExecucao(inicio,fim));

    //clock_gettime(CLOCK_REALTIME,&inicio);
    //quicksort(vet,0, 100000-1);
    //clock_gettime(CLOCK_REALTIME,&fim);
    //printf("Tempo de execução quicksort: %.6lf milissegundos\n",tempoDeExecucao(inicio,fim));

    clock_gettime(CLOCK_REALTIME,&inicio);
    bogoSort(vet,100000);
    clock_gettime(CLOCK_REALTIME,&fim);
    printf("Tempo de execução bogo sort: %.6lf milissegundos\n",tempoDeExecucao(inicio,fim));



}