#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

/*Definindo o tipoNo*/
typedef struct tipoNo {
    unsigned long int dado;
    struct tipoNo *prox;
}tipoNo;

/*Definindo o tipoLista*/
typedef struct tipoLista{
    tipoNo *prim;
    int tamanho;
}tipoLista;

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
    unsigned long int aleatorio;
    
    aleatorio = rand() + rand();
    printf("\nChave de busca: [%lu]\n",aleatorio);
    return aleatorio;
    
}

int buscaSequencial(unsigned long int chave){
    int i = 0;
    while(i < N){
        if(vetor[i] == chave){
            printf("Elemento encontrado na posição: %d do vetor\n", i);         
            return i;}
        else{i++;}
    }
    printf("Elemento não encontrado\n");
    return 0;

}

long int buscaBinaria(unsigned long int chave){
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
    printf("\nNão achado!\n");
}


double tempoDeExecucao(struct timespec inicio, struct timespec fim){
    long long tempoNano;
    double tempoMili, tempoSeg;
    tempoNano = (fim.tv_sec - inicio.tv_sec) * 1000000000LL + (fim.tv_nsec - inicio.tv_nsec);
    tempoMili = tempoNano / 1000000.0;
    tempoSeg = tempoNano / 1000000000.0;
    /*printf("\n========================\n");
    printf("Tempo de execução:\n");
    printf("  %lld nanosegundos\n", tempoNano);
    printf("  %.3lf milissegundos\n", tempoMili);
    printf("  %.6lf segundos\n", tempoSeg);
    printf("========================\n");*/
    return tempoMili;

}

double desvioPadrao(double tempos[], double media){
    double somatorio = 0, variancia = 0, desvioPadrao = 0;
    for(int i = 0; i < 30;i++){
        somatorio += pow(tempos[i] - media, 2);
    }
    printf("Somatório = %.6lf milissegundos\n",somatorio);
    variancia  = (somatorio / 29);
    printf("Variancia = %.6lf\n",variancia);
    desvioPadrao = sqrt(variancia);
    printf("Desvio Padrão = %.6lf milissegundos\n",desvioPadrao);
    return desvioPadrao;
}

void copiaVetorParaArquivo(unsigned long int vetor[]){
    FILE *fd;
    fd = fopen("CopiaVetor","wb+");

    if(fd == NULL) {
        printf("Não consegui abrir o arquivo!!! :( \n");
        exit(1);
    }

    if( fwrite(vetor,sizeof(unsigned long int),1000000,fd) == 1000000) {
        printf("Dados do vetor gravados com sucesso!\n");
    }
    fclose(fd);

}

void copiaArquivoParaVetor(unsigned long int vetorDestino[]){
    FILE *fd;
    fd = fopen("CopiaVetor","r");

    if(fd == NULL){
        printf("Não consegui abrir o arquivo!!! :( \n");
        exit(1);
    }
    if(fread(vetorDestino,sizeof(unsigned long int),1000000,fd) == 1000000){
        printf("Dados recuperados com sucesso! \n");
    }
    fclose(fd);

}


tipoLista* iniciaLista(){
   tipoLista *pLista = (tipoLista*)malloc(sizeof(tipoLista));
   if(pLista != NULL){
    pLista->prim = NULL;
    pLista->tamanho = 0;
   }
   return pLista;
}

void inserirNaLista(tipoLista *pLista, unsigned long int valor){
    tipoNo *aux;
    aux = (tipoNo*) malloc(sizeof(tipoNo));
    aux->dado = valor;
    aux->prox = pLista->prim;
    pLista->prim = aux;
    pLista->tamanho++;
}

void copiaArquivorParaLista(tipoLista *pLista){
    FILE *fd;
    unsigned long int temp;
    fd = fopen("CopiaVetor","rb");

    if(fd == NULL){
        printf("Não consegui abrir o arquivo!!! :( \n");
        exit(1);
    }
    while(fread(&temp,sizeof(unsigned long int),1,fd) == 1){
        inserirNaLista(pLista,temp);
    }
    fclose(fd);
}

int buscaNaLista(unsigned long int chave,tipoLista *pLista){
    int i = 0;
    tipoNo *aux;
    aux = pLista->prim;
    while(aux != NULL){
        if(aux->dado == chave){
            printf("\nElemento encontrado na posição: %d da lista\n", i);         
            return i;
        }else{
            aux = aux->prox;
            i++;}
    }
    printf("\nElemento não encontrado na lista\n");
    return 0;

}


void criaVetordeIntDesordenado(int v[],int tam) {
    for (int i = 0; i < tam; i++) {
        v[i] = (rand() % tam+rand());
    }
}

void bubbleSort(int vet[], int tam){
    int i, j,aux;
    for (i = 0; i < tam - 1; i++) {
        for (j = 0; j < tam - i - 1; j++) {
            if (vet[j] > vet[j + 1]) {
                aux = vet[j];
                vet[j]= vet[j + 1];
                vet[j + 1] = aux;
            }
        }
    }
}



