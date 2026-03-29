#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include "TAD-Vetorzao.h"


int main() {

    struct timespec inicio, fim;
    int res;

    setlocale(LC_ALL,"pt_BR.UTF8");

    while(1){
    printf("**************************\n");
    printf("O que você que fazer ?\n");
    printf("1.Criar um vetor desordenado\n2.Criar um vetor ordenado\n0.Sair\n");
    printf("Digite um número: ");
    scanf("%d",&res);
    printf("**************************\n");
    if(res == 1){
        criaVetorDesordenado();
        printf("**************************\n");
        printf("O que você que fazer agora ?\n");
        printf("1.Realizar uma busca sequencial por um elemento no vetor?\n2.Realizar uma busca sequencial por um elemento aleatório?(pode estar ou não no vetor)\n");
        printf("Digite um número: ");
        scanf("%d",&res);
         printf("**************************\n");
        if(res == 1){
            clock_gettime(CLOCK_REALTIME, &inicio);
            buscaSequencial(sortearElementoNoVetor());
            clock_gettime(CLOCK_REALTIME, &fim);
            tempoDeExecucao(inicio,fim);
            continue;
        }
        else if(res == 2){
            clock_gettime(CLOCK_REALTIME, &inicio);
            buscaSequencial(sortearElemento());
            clock_gettime(CLOCK_REALTIME, &fim);
            tempoDeExecucao(inicio,fim);
            continue;
        }
        else{continue;}

    }else if(res == 2){
        criaVetorOrdenado();
        printf("**************************\n");
        printf("O que você que fazer agora ?\n");
        printf("1.Realizar uma busca binária por um elemento no vetor?\n2.Realizar uma busca binária por um elemento aleatório?(pode estar ou não no vetor)\n");
        printf("Digite um número: ");
        scanf("%d",&res);
        printf("**************************\n");
        if(res == 1){
            clock_gettime(CLOCK_REALTIME, &inicio);
            buscaBinaria(sortearElementoNoVetor());
            clock_gettime(CLOCK_REALTIME, &fim);
            tempoDeExecucao(inicio,fim);
            continue;
        }
        else if(res == 2){
            clock_gettime(CLOCK_REALTIME, &inicio);
            buscaBinaria(sortearElemento());
            clock_gettime(CLOCK_REALTIME, &fim);
            tempoDeExecucao(inicio,fim);
            continue;
        }else{continue;}
    }else if(res == 0){break;}
 }
    printf("Final do programa !!\n");
    return 0;
}