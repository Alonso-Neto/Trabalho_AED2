#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>



const int N = 1000000;
unsigned long int vetor[1000000];


void criaVetorDesordenado() {
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        vetor[i] = (rand() % N);
    }
    printf("Último elemento = %lu\n",vetor[999999]);
}

void criaVetorOrdenado(){
    srand(time(NULL));
    int incremento;

    vetor[0] = rand() % 1000;

    for(int i = 1; i < N; i++){
        incremento = rand() % 100;
        vetor[i] = vetor[i-1] + incremento;
    }
}

unsigned long int sortearElementoNoVetor(){
    int indiceAleatorio = rand() % N;
    return vetor[indiceAleatorio];
}

unsigned long int sortearElemento(){
    srand(time(NULL));
    unsigned long int aleatorio = rand() % N ;
    printf("Chave de busca: [%lu]\n",aleatorio);
    return aleatorio;
}

int buscaSequencial(long int chave){
    int i = 0;
    while(i < N){
        if(vetor[i] == chave){
            printf("\nElemento encontrado na posição: %d do vetor\n", i);         
            return i;}
        else{i++;}
    }
    printf("\nElemento não encontrado\n");
    return 0;

}

long int buscaBinaria(long int chave){
    int inicio, fim, meio;
    inicio = 0; fim = N-1;
    
    while(inicio <= fim){
        meio = (inicio+fim)/2;
        if(chave > vetor[meio]){inicio = meio + 1;}
        else if(chave < vetor[meio]){fim = meio -1;}
        else{
            printf("\nAchado na posição %d", meio);
            return meio;
        }
    }
    printf("\nNão achado!");
}


void tempoDeExecucao(struct timespec inicio, struct timespec fim){
    long long tempoNano;
    double tempoMili, tempoSeg;
    tempoNano = (fim.tv_sec - inicio.tv_sec) * 1000000000LL + (fim.tv_nsec - inicio.tv_nsec);
    tempoMili = tempoNano / 1000000.0;
    tempoSeg = tempoNano / 1000000000.0;
    printf("\n========================\n");
    printf("Tempo de execução:\n");
    printf("  %lld nanosegundos\n", tempoNano);
    printf("  %.3lf milissegundos\n", tempoMili);
    printf("  %.6lf segundos\n", tempoSeg);
    printf("========================\n");
}
