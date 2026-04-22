#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "TAD-Vetorzao.h"

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

void insercaoDireta(int vet[], int tam) {
    int i, chave, j;
    for (i = 1; i < tam; i++) {
        chave = vet[i];
        j = i - 1;

        while (j >= 0 && vet[j] > chave) {
            vet[j + 1] = vet[j];
            j = j - 1;
        }
        vet[j + 1] = chave;
    }
}

/*parte do quicksort*/
void selecaoDireta(int vet[], int num) {
    int i, j, min, temp;
    for (i = 0; i < num - 1; i++) {
        min = i;
        for (j = i + 1; j < num; j++) {
            if (vet[j] < vet[min]) {
                min = j;
            }
        }
        temp = vet[min];
        vet[min] = vet[i];
        vet[i] = temp;
    }
}

/*parte do quicksort*/

void trocar(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/*parte do quicksort*/

int particiona(int vet[], int inicio, int fim) {
    int pivo = vet[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        if (vet[j] <= pivo) {
            i++;
            trocar(&vet[i], &vet[j]);
        }
    }
    trocar(&vet[i + 1], &vet[fim]);
    return (i + 1);
}

void quicksort(int vet[], int inicio, int fim) {
    if (inicio < fim) {
        int pi = particiona(vet, inicio, fim);

        quicksort(vet, inicio, pi - 1);
        quicksort(vet, pi + 1, fim);
    }
}

/*parte do bogosort*/
int esta_ordenado(int vet[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        if (vet[i] > vet[i + 1]) {
            return 0;
        }
    }
    return 1;
}

/*parte do bogosort*/
void embaralhar(int vet[], int tam) {
    for (int i = 0; i < tam; i++) {
        int temp = vet[i];
        int j = rand() % tam;
        vet[i] = vet[j];
        vet[j] = temp;
    }
}

void bogoSort(int vet[], int tam) {
    while (!esta_ordenado(vet, tam)) {
        embaralhar(vet, tam);
    }
}

void copiaVetor(int vetbase[], int vet[], int tam){
    for (int i = 0; i < tam; i++) {
        vet[i] = vetbase[i];
    }
}

void merge(int vet[], int esq, int meio, int dir) {
    int i, j, k;
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = vet[esq + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = vet[meio + 1 + j];
    }

    i = 0;
    j = 0;
    k = esq;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vet[k] = L[i];
            i++;
        } else {
            vet[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vet[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vet[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort_recursivo(int vet[], int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;

        merge_sort_recursivo(vet, esq, meio);
        merge_sort_recursivo(vet, meio + 1, dir);

        merge(vet, esq, meio, dir);
    }
}

void merge_sort(int vet[], int tam) {
    if (tam > 1) {
        merge_sort_recursivo(vet, 0, tam - 1);
    }
}

/*Função genérica para salvar dados de algoritmos em JSON*/
void salvarDadosJSON(const char *nomeArquivo, const char *questao, 
                     DadosAlgoritmo *algoritmos, int num_algoritmos) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if(arquivo != NULL) {
        setlocale(LC_NUMERIC, "C"); // Usar ponto decimal
        
        fprintf(arquivo, "{\n");
        fprintf(arquivo, "  \"questao\": \"%s\",\n", questao);
        fprintf(arquivo, "  \"algoritmos\": [\n");
        
        for(int i = 0; i < num_algoritmos; i++) {
            fprintf(arquivo, "    {\n");
            fprintf(arquivo, "      \"nome\": \"%s\",\n", algoritmos[i].nome);
            fprintf(arquivo, "      \"tamanho\": %d,\n", algoritmos[i].tamanho);
            fprintf(arquivo, "      \"algoritmo\": \"%s\",\n", algoritmos[i].algoritmo);
            fprintf(arquivo, "      \"media\": %.6lf,\n", algoritmos[i].media);
            fprintf(arquivo, "      \"desvio_padrao\": %.6lf,\n", algoritmos[i].desvio_padrao);
            fprintf(arquivo, "      \"numero_execucoes\": %d,\n", algoritmos[i].numero_execucoes);
            fprintf(arquivo, "      \"tempos_execucao\": [");
            
            for(int j = 0; j < algoritmos[i].numero_execucoes; j++) {
                fprintf(arquivo, "%.6lf", algoritmos[i].tempos[j]);
                if(j < algoritmos[i].numero_execucoes - 1) fprintf(arquivo, ", ");
            }
            fprintf(arquivo, "]\n");
            fprintf(arquivo, "    }");
            
            if(i < num_algoritmos - 1) fprintf(arquivo, ",");
            fprintf(arquivo, "\n");
        }
        
        fprintf(arquivo, "  ],\n");
        fprintf(arquivo, "  \"timestamp\": \"2026-04-19\"\n");
        fprintf(arquivo, "}\n");
        fclose(arquivo);
        
        setlocale(LC_NUMERIC, "pt_BR.UTF8"); // Restaurar locale
        printf("Dados salvos em %s\n", nomeArquivo);
    }
}


