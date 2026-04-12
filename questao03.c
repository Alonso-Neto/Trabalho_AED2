#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "TAD-Vetorzao.h"

int main(){
    srand(time(NULL));
    int vet[100000];
    criaVetordeIntDesordenado(vet,100000);
   
    bubbleSort(vet,100000);
    for(int i=0;i<100000;i++){
        printf("[%d] ",vet[i]);
    }
}