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
    
    clock_gettime(CLOCK_REALTIME,&inicio);
    bubbleSort(vet,100000);
    clock_gettime(CLOCK_REALTIME,&fim);
    printf("Tempo de execução bubble sort: %.6lf milissegundos\n",tempoDeExecucao(inicio,fim));


}