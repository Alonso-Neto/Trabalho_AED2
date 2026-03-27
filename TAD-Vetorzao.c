#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 1000000

void criaDesordenado(int vetor[]) {
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        vetor[i] = rand() % 1000000;
        printf("%d\n", vetor[i]);
    }
}

int main() {
    int vet[N];

    printf(" :C \n");
    criaDesordenado(vet);

    return 0;
}