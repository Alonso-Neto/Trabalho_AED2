#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "TAD-Vetorzao.h"

int main(){
    setlocale(LC_ALL,"pt_BR.UTF8");
    srand(time(NULL));
    
    int i;
    struct timespec inicio, fim;
    unsigned long int chaveDeBusca = 0;
    double somaTemposVetor = 0, somaTemposLista = 0;
    double mediaVetor = 0, mediaLista = 0;
    double temposVetor[30];
    double temposLista[30];
    tipoLista *lista;

    lista = iniciaLista();
    copiaArquivorParaLista(lista);
    copiaArquivoParaVetor(vetor);

    /*Busca por um elemento que vai estar nas duas estruturas de dados  */
    for(i=0; i< 15; i++){
        printf("======================\n");
        chaveDeBusca = sortearElementoNoVetor();
        printf("Chave de Busca:[%ld]",chaveDeBusca);

        clock_gettime(CLOCK_REALTIME,&inicio);
        buscaSequencial(chaveDeBusca);
        clock_gettime(CLOCK_REALTIME,&fim);
        temposVetor[i] = tempoDeExecucao(inicio,fim);
        printf("Tempo de execução da busca no Vetor: %.6lf\n",temposVetor[i]);
        somaTemposVetor += temposVetor[i];

        clock_gettime(CLOCK_REALTIME,&inicio);
        buscaNaLista(chaveDeBusca,lista);
        clock_gettime(CLOCK_REALTIME,&fim);
        temposLista[i] = tempoDeExecucao(inicio,fim);
        printf("Tempo de execução da busca na lista: %.6lf\n",temposLista[i]);
        somaTemposLista += temposLista[i];

        printf("======================\n");

    }

    for(i=0; i< 15; i++){
        
        printf("*******************************\n");
        chaveDeBusca = sortearElemento();

        clock_gettime(CLOCK_REALTIME,&inicio);
        buscaSequencial(chaveDeBusca);
        clock_gettime(CLOCK_REALTIME,&fim);
        temposVetor[15+i] = tempoDeExecucao(inicio,fim);
        printf("Tempo de execução da busca no Vetor: %.6lf\n",temposVetor[15+i]);
        somaTemposVetor += temposVetor[15+i];

        clock_gettime(CLOCK_REALTIME,&inicio);
        buscaNaLista(chaveDeBusca,lista);
        clock_gettime(CLOCK_REALTIME,&fim);
        temposLista[15+i] = tempoDeExecucao(inicio,fim);
        printf("Tempo de execução da busca na lista: %.6lf\n",temposLista[15+i]);
        somaTemposLista += temposLista[15+i];

        printf("*******************************\n");

    }

    printf("\n");
    printf("=====================\n");
    mediaVetor = somaTemposVetor / 30;
    printf("Média das 30 execuções (VETOR): %.6lf milissegundos\n", mediaVetor);
    printf("=====================\n");
    desvioPadrao(temposVetor, mediaVetor);
    
    printf("\n");
    printf("=====================\n");
    mediaLista = somaTemposLista / 30;
    printf("Média das 30 execuções (LISTA): %.6lf milissegundos\n", mediaLista);
    printf("=====================\n");
    desvioPadrao(temposLista, mediaLista);

    return 0;
}