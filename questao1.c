#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include "TAD-Vetorzao.h"

int main() {
    setlocale(LC_ALL,"pt_BR.UTF8");
    printf("Antes de criar o vetor\n");

    criaVetorOrdenado();

    buscaBinaria(sortearElementoNoVetor());
    

    return 0;
}