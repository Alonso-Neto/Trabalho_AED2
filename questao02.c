#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include "TAD-Vetorzao.h"

int main(){

    tipoLista *lista;

    lista = iniciaLista();
    copiaArquivorParaLista(lista);

    printf("Tamanho final da lista: %d",lista->tamanho);


    
}