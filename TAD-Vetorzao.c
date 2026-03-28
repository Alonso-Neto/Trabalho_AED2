#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>



#define N 1000000
long int vetor[N];


void criaVetorDesordenado() {
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        vetor[i] = (rand() % N);
    }
}

void criaVetorOrdenado(){
    srand(time(NULL));
    int incremento;

    vetor[0] = rand() % N;

    for(int i = 1; i < N; i++){
        incremento = rand() % N;
        vetor[i] = vetor[i-1] + incremento;
    }
}

long int sortearElementoNoVetor(){
    int indiceAleatorio = rand() % N;
    return vetor[indiceAleatorio];
}

int buscaSequencial(long int chave){
    int i = 0;
    while(i < N){
        if(vetor[i] == chave){
            printf("Elemento encontrado na posição: %d do vetor", i);            
            return i;}
        else{i++;}
    }
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
        return meio;}
    }
     printf("Achado na posição %ld", meio);
}
