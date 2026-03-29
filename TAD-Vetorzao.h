/*Vetor global acessível entre módulos*/
extern long int vetor[];
extern const int N;

/*Inicializa o vetor com valores aleatórios até 1.000.000*/
void criaVetorDesordenado();

/*Inicializa o vetor com valores aleatórios porém ordenados de forma crescente*/
void criaVetorOrdenado();

/*Sorteia um valor aleatório contido no vetor*/
unsigned long long int sortearElementoNoVetor();

/*Sorteia um valor aleatório para ser a chave de busca*/
unsigned long int sortearElemento();

/*Busca Sequencial no Vetor*/
int buscaSequencial(long int chave);

/*Busca Binária no Vetor Ordenado*/
long int buscaBinaria(long int chave);
 
/*Mostra o tempo de execução do programa */
void tempoDeExecucao(struct timespec inicio, struct timespec fim);