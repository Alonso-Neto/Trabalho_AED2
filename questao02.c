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
    
    for(i=0;i<30;i++){
        printf("%.6lf ",temposVetor[i]);
    }

    // Preparar dados para salvar em JSON
    double desvioVet = desvioPadrao(temposVetor, mediaVetor);
    double desvioLst = desvioPadrao(temposLista, mediaLista);
    
    DadosAlgoritmo algoritmos[2];
    
    // Busca em Vetor
    algoritmos[0].nome = "Busca em Vetor";
    algoritmos[0].algoritmo = "Vetor";
    algoritmos[0].tamanho = 1000000;
    algoritmos[0].media = mediaVetor;
    algoritmos[0].desvio_padrao = desvioVet;
    algoritmos[0].numero_execucoes = 30;
    algoritmos[0].tempos = temposVetor;
    
    // Busca em Lista
    algoritmos[1].nome = "Busca em Lista";
    algoritmos[1].algoritmo = "Lista Encadeada";
    algoritmos[1].tamanho = 1000000;
    algoritmos[1].media = mediaLista;
    algoritmos[1].desvio_padrao = desvioLst;
    algoritmos[1].numero_execucoes = 30;
    algoritmos[1].tempos = temposLista;
    
    // Salvar em JSON usando função genérica
    salvarDadosJSON("questao02_dados.json", "questao02", algoritmos, 2);

    return 0;
} 