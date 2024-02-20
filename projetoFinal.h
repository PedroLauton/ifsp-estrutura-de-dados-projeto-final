//Criação da estrutura que irá armazenar os dados dos clientes.
typedef struct clientes {
    int codigo;
    char nome[51];
    char empresa[51];
    char departamento[51];
    char telefone[20];
    char celular[20];
    char email[51];
} CLIENTES;

//Renomeando a estrutura presente no "projetoFinal.c"
typedef struct unidade* Lista;

//Declaração das funções criadas e utilizadas.
Lista *criaLista();
int listaVazia(Lista *li);
void inserir_clientes(Lista *li);
int insere_lista_ordenada(Lista *li, CLIENTES *info);
void consulta_lista_total (Lista *li);
void consulta_lista_identificador (Lista *li);
void consulta_lista_nome(Lista *li);
void remove_lista (Lista *li);
void imprime_lista_total(Lista *li);
int imprime_lista (struct unidade *no);
void edicao_dados(Lista *li);
void encerra_lista(Lista *li, FILE *dados);
int recupera_dados(Lista *li, FILE *dados);
