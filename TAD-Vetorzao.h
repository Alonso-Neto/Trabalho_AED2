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

/*Função de busca de um elemento na lista encadeada*/
int buscaNaLista(unsigned long int chave,tipoLista *pLista);

/*Cria um vetor de inteiros desordenado*/
void criaVetordeIntDesordenado(int v[],int tam);

/*Método de ordenação bubble sort*/
void bubbleSort(int vet[], int tam);

/*Método de ordenação inserção direta*/
void insercaoDireta(int vet[], int tam);

/*Método de ordenação seleção Direta*/
void selecaoDireta(int vet[], int num);

/*Método de ordenação quicksort*/

void quicksort(int vet[], int inicio, int fim);

/*Método de ordenação bogo sort*/
void bogoSort(int vet[], int tam);

/*volta o vet pro original*/
void copiaVetor(int vetbase[], int vet[], int tamanho);

/*Método de ordenação mergesort*/
void merge_sort(int vet[], int tam);

/*Estrutura para armazenar dados de um algoritmo*/
typedef struct {
    char *nome;                 /*Nome exibível do algoritmo*/
    int tamanho;
    char *algoritmo;            /*Tipo/categoria do algoritmo*/
    double media;               /*Média dos tempos*/
    double desvio_padrao;       /*Desvio padrão*/
    int numero_execucoes;       /*Quantidade de execuções*/
    double *tempos;             /*Array de tempos individuais*/
} DadosAlgoritmo;

/*Salva dados dos algoritmos em arquivo JSON*/
void salvarDadosJSON(const char *nomeArquivo, const char *questao, 
                     DadosAlgoritmo *algoritmos, int num_algoritmos);
