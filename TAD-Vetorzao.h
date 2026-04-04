/*Definindo o tipoNo*/
typedef struct tipoNo {
    unsigned long int dado;
    struct tipoNo *prox;
} tipoNo;

/*Definindo o tipoLista*/
typedef struct tipoLista {
    tipoNo *prim;
    int tamanho;
} tipoLista;

/*Vetor global acessível entre módulos*/
extern unsigned long int vetor[];
extern const int N;

/*Inicializa o vetor com valores aleatórios até 1.000.000*/
void criaVetorDesordenado();

/*Inicializa o vetor com valores aleatórios porém ordenados de forma crescente*/
void criaVetorOrdenado();

/*Sorteia um valor aleatório contido no vetor*/
unsigned long int sortearElementoNoVetor();

/*Sorteia um valor aleatório para ser a chave de busca*/
unsigned long int sortearElemento();

/*Busca Sequencial no Vetor*/
int buscaSequencial(unsigned long int chave);

/*Busca Binária no Vetor Ordenado*/
long int buscaBinaria(unsigned long int chave);

/*Mostra o tempo de execução do programa */
double tempoDeExecucao(struct timespec inicio, struct timespec fim);

/*Calcula o desvio padrão*/
double desvioPadrao(double tempos[], double media);

/*Salva o vetor desordenado*/
void copiaVetorParaArquivo(unsigned long int vetor[]);

/*copia o vetor do arquivo para a memória*/
void copiaArquivoParaVetor(unsigned long int vetorDestino[]);

/*Inicializa a lista encadeada*/
tipoLista* iniciaLista();
/*Insere elementos na lista*/
void inserir(tipoLista *pLista, unsigned long int valor);

/*Copia o vetor do arquivo para a lista encadeada*/
void copiaArquivorParaLista(tipoLista *pLista);