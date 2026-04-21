#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include "TAD-Vetorzao.h"

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "pt_BR.UTF8");

    int vet[100000];
    int vetbase[100000];
    int cont = 0;
    double somaTemposBubble = 0, somaTemposInsertion = 0, somaTemposSelection = 0, somaTemposQuick = 0, somaTemposMerge = 0;
    double temposBubble[10], temposInsertion[10], temposSelection[10], temposQuick[10], temposMerge[10];
    double media;
    struct timespec inicio, fim;
    double tempoAtual;

    for (cont = 0; cont < 10; cont++)
    {
        printf("\n");
        printf("=====================\n");
        printf("Rodada n°%d\n", (cont + 1));
        criaVetordeIntDesordenado(vetbase, 100000);

        copiaVetor(vetbase, vet, 100000);

        clock_gettime(CLOCK_REALTIME, &inicio);
        bubbleSort(vet, 100000);
        clock_gettime(CLOCK_REALTIME, &fim);
        tempoAtual = tempoDeExecucao(inicio, fim);
        printf("Tempo de execução bubble sort: %.6lf milissegundos\n", tempoAtual);
        temposBubble[cont] = tempoAtual;
        somaTemposBubble += tempoAtual;

        copiaVetor(vetbase, vet, 100000);

        clock_gettime(CLOCK_REALTIME, &inicio);
        insercaoDireta(vet, 100000);
        clock_gettime(CLOCK_REALTIME, &fim);
        tempoAtual = tempoDeExecucao(inicio, fim);
        printf("Tempo de execução inserção direta: %.6lf milissegundos\n", tempoAtual);
        temposInsertion[cont] = tempoAtual;
        somaTemposInsertion += tempoAtual;

        copiaVetor(vetbase, vet, 100000);

        clock_gettime(CLOCK_REALTIME, &inicio);
        selecaoDireta(vet, 100000);
        clock_gettime(CLOCK_REALTIME, &fim);
        tempoAtual = tempoDeExecucao(inicio, fim);
        printf("Tempo de execução seleção Direta: %.6lf milissegundos\n", tempoAtual);
        temposSelection[cont] = tempoAtual;
        somaTemposSelection += tempoAtual;

        copiaVetor(vetbase, vet, 100000);

        clock_gettime(CLOCK_REALTIME, &inicio);
        quicksort(vet, 0, 100000 - 1);
        clock_gettime(CLOCK_REALTIME, &fim);
        tempoAtual = tempoDeExecucao(inicio, fim);
        printf("Tempo de execução quicksort: %.6lf milissegundos\n", tempoAtual);
        temposQuick[cont] = tempoAtual;
        somaTemposQuick += tempoAtual;

        copiaVetor(vetbase, vet, 100000);

        clock_gettime(CLOCK_REALTIME, &inicio);
        merge_sort(vet, 100000 - 1);
        clock_gettime(CLOCK_REALTIME, &fim);
        tempoAtual = tempoDeExecucao(inicio, fim);
        printf("Tempo de execução merge sort: %.6lf milissegundos\n", tempoAtual);
        temposMerge[cont] = tempoAtual;
        somaTemposMerge += tempoAtual;
        printf("=====================\n");
    }

    printf("\n");
    printf("=====================\n");
    media = somaTemposBubble / 10;
    printf("Média das execuções (BUBBLE SORT): %.6lf milissegundos\n", media);
    printf("=====================\n");

    printf("\n");
    printf("=====================\n");
    media = somaTemposInsertion / 10;
    printf("Média das execuções (INSERTION SORT): %.6lf milissegundos\n", media);
    printf("=====================\n");

    printf("\n");
    printf("=====================\n");
    media = somaTemposSelection / 10;
    printf("Média das execuções (SELECTION SORT): %.6lf milissegundos\n", media);
    printf("=====================\n");

    printf("\n");
    printf("=====================\n");
    media = somaTemposQuick / 10;
    printf("Média das execuções (QUICK SORT): %.6lf milissegundos\n", media);
    printf("=====================\n");

    printf("\n");
    printf("=====================\n");
    media = somaTemposMerge / 10;
    printf("Média das execuções (MERGE SORT): %.6lf milissegundos\n", media);
    printf("=====================\n");

    // Preparar dados para salvar em JSON
    DadosAlgoritmo algoritmos[5];

    // Bubble Sort
    algoritmos[0].nome = "Bubble Sort";
    algoritmos[0].algoritmo = "BUBBLE SORT";
    algoritmos[0].media = somaTemposBubble / 10;
    algoritmos[0].desvio_padrao = desvioPadrao(temposBubble, algoritmos[0].media);
    algoritmos[0].numero_execucoes = 10;
    algoritmos[0].tempos = temposBubble;

    // Insertion Sort
    algoritmos[1].nome = "Insertion Sort";
    algoritmos[1].algoritmo = "INSERTION SORT";
    algoritmos[1].media = somaTemposInsertion / 10;
    algoritmos[1].desvio_padrao = desvioPadrao(temposInsertion, algoritmos[1].media);
    algoritmos[1].numero_execucoes = 10;
    algoritmos[1].tempos = temposInsertion;

    // Selection Sort
    algoritmos[2].nome = "Selection Sort";
    algoritmos[2].algoritmo = "SELECTION SORT";
    algoritmos[2].media = somaTemposSelection / 10;
    algoritmos[2].desvio_padrao = desvioPadrao(temposSelection, algoritmos[2].media);
    algoritmos[2].numero_execucoes = 10;
    algoritmos[2].tempos = temposSelection;

    // Quick Sort
    algoritmos[3].nome = "Quick Sort";
    algoritmos[3].algoritmo = "QUICK SORT";
    algoritmos[3].media = somaTemposQuick / 10;
    algoritmos[3].desvio_padrao = desvioPadrao(temposQuick, algoritmos[3].media);
    algoritmos[3].numero_execucoes = 10;
    algoritmos[3].tempos = temposQuick;

    // Merge Sort
    algoritmos[4].nome = "Merge Sort";
    algoritmos[4].algoritmo = "MERGE SORT";
    algoritmos[4].media = somaTemposMerge / 10;
    algoritmos[4].desvio_padrao = desvioPadrao(temposMerge, algoritmos[4].media);
    algoritmos[4].numero_execucoes = 10;
    algoritmos[4].tempos = temposMerge;

    // Salvar em JSON usando função genérica
    salvarDadosJSON("questao03_dados.json", "questao03", algoritmos, 5);

    return 0;
}