#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "projetoFinal.h"

//Cricação da estrutura da lista, possuindo a estrutura que armazena os dados e um ponteiro que armazena o endereço da próxima estrutura.
typedef struct unidade{
    CLIENTES dados;
    struct unidade *prox;
}UNIDADE;

//Criação e alocação de memória para a lista. a lista é do mesmo tipo UNIDADE, mas chamado por outro nome. Essa função retorna o ponteiro para o main, um ponteiro indicando o inicio da lista.
Lista *criaLista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));
    //Teste verificando se a alocação deu certo, e logo após atribuindo o valor nulo para que o ponteiro não pegue qualquer endereço de memória.
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

//Verifica se a lista está vazia, caso esteja, a função de inserir toma alguma providencia, caso não, toma outra providencia.
int listaVazia(Lista *li){
    if(li == NULL){
        return 1;
    }
    if(*li == NULL){
        return 1;
    }
    return 0;
}

//Função para padronizar os nomes inseridos pelo usuário.
void nomePadronizado(char *str) {

    // Definir que a próxima letra é a primeira de uma palavra
    int primeiraLetra = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        // Verificar se o caractere atual é uma letra
        if (isalpha(str[i])) {
            // Se for a primeira letra, capitalizar
            if (primeiraLetra) {
                str[i] = toupper(str[i]);
                primeiraLetra = 0;  // A primeira letra foi capitalizada
            } else {
                str[i] = tolower(str[i]);  // Demais letras em minúsculo.
            }
        } else {
            // Se não for uma letra, a próxima letra será a primeira de uma palavra
            primeiraLetra = 1;
        }
    }
}

//Função para cadastrar os clientes.
void inserir_clientes(Lista *li) {

    //Verificação de segurança.
    if(li == NULL){
        printf("\nNao foi possivel inserir. Lista não criada.\n\n");
        system("pause");
        return;
    }

    //Variável que verifica se ocorreu erro ou não. Recebe valor da função de inserir ordenadamente.
    int notificacao = 0;

    //Alocação de memória.
    CLIENTES *informacoes;
    informacoes = (CLIENTES *)malloc(sizeof(CLIENTES));

    //Captação dos dados.
    system("cls");
    printf("===========================\n\n");
    printf("---- Dados clientes ----");
    printf("\n\nCodigo..........");
    scanf("%d", &informacoes->codigo);
    getchar();
    printf("Nome............");
    gets(informacoes->nome);

    //Passando o nome para a função de padronização de nomes.
    nomePadronizado(informacoes->nome);

    printf("Empresa.........");
    gets(informacoes->empresa);
    printf("Departamento....");
    gets(informacoes->departamento);
    printf("Telefone........");
    gets(informacoes->telefone);
    printf("Celular.........");
    gets(informacoes->celular);
    printf("Email...........");
    gets(informacoes->email);

    //Passando a estrutura para a função "insere_lista_ordenada", bem como o ponteiro de "li".
    notificacao = insere_lista_ordenada(li, informacoes);
    printf("\n===========================\n");

    //Retorno da conclusão da inserção.
    if(notificacao){
        printf("\nInserido com sucesso!\n");
        printf("\n===========================\n\n\n");
        system("pause");
    }else{
        printf("\nErro em cadastrar.\n");
        printf("\n===========================\n\n\n");
        system("pause");
    }
    //liberação de memória.
    free(informacoes);
}

//Função de inserção ordenada.
int insere_lista_ordenada(Lista *li, CLIENTES *info){
    //Verificação de segurança, para caso a lista não existir voltar ao menu principal.
    if(li == NULL){
        printf("\nNao foi possivel inserir. Lista não criada.\n\n");
        system("pause");
        //Retorna 0 para a função de cadastro de clientes, indicando que algo não deu certo.
        return 0;
    }
    //Alocação de memória para o "no" que irá receber os dados da estrutura.
    UNIDADE *no = (UNIDADE*) malloc(sizeof(UNIDADE));

    //verificação de segurança, para caso o "no" não ser alocado.
    if(no == NULL){
        printf("\nNao foi possivel inserir.\n\n");
        system("pause");
        return 0;
    }

    //Recebendo os dados da estrutura "info".
    no->dados = *info;

    //Caso a lista esteja vazia, o endereço do "prox" é atribuido ao conteúdo de "li", que no caso é null.
    if(listaVazia(li)){
        no->prox = (*li);
        *li = no;
        return 1;
    }else{

        //Caso não seja, aloca-se duas variáveis do tipo UNIDADE para percorrer a lista, uma mantendo o endereço passado e outra avançando.
        UNIDADE *ant, *atual = *li;
        //While que verifica se a posição atual é diferente de nula, pois, caso não seja, chegou-se ao final da lista; além de estar verificando se o codigo do cliente da lista é menor que o codigo que irá ser inserido.
        //utiliza-se duas variáveis para isso, pois enquanto uma avança, a outra se torna o porto seguro da função.
        while(atual != NULL && atual->dados.codigo < info->codigo){
            ant = atual;
            atual = atual->prox;
        }
        //Se a posição a ser alocada for logo no início, ou seja, na memória onde "li" aponta primeiramente, passa-se o endereço para o "prox" do "no" e atribui ao "li" o endereço do "no".
        if(atual == *li){
            no->prox = (*li);
            *li = no;
        }else{
            //Caso a posição não seja no início, o "prox" do "no" atribui o "ant->prox", e o encereço do "no" é atribuido ao "ant->prox".
            no->prox = ant->prox;
            ant->prox = no;
        }
        //Retorna 1 para a função de cadastro de clientes, indicando que deu tudo certo.
        return 1;
    }
}

//Função para impressão da lista total.
void imprime_lista_total(Lista *li){
    //Verificação de segurança.
    if(li == NULL){
        printf("\nNao foi possivel consultar. Lista nao criada.\n\n");
        system("pause");
        return;
    }

    //Atribui o endereço de "li" ao "no", pois é ele quem vai percorer a lista, mantendo o "li" guardando o início da lista.
    UNIDADE *no = *li;

    //Verificação de segurança.
    if(no == NULL){
        printf("\nNao foi possivel buscar, adicione clientes.\n\n");
        system("pause");
        return;
    }

    //Impressão. Enquanto "no" for diferente de nulo quer dizer que a lista não acabou, imprimindo assim toda a lista.
    system("cls");
    printf("=====================================================\n\n");
    printf("---- Relatorio total ----\n\n");

    while(no != NULL){
        printf("=====================================================");
        printf("\nCodigo:..........%d", no->dados.codigo);
        printf("\nNome:............%s", no->dados.nome);
        printf("\nEmpresa:.........%s", no->dados.empresa);
        printf("\nDepartamento:....%s", no->dados.departamento);
        printf("\nTelefone:........%s", no->dados.telefone);
        printf("\nCelular:.........%s", no->dados.celular);
        printf("\nEmail:...........%s\n", no->dados.email);
        printf("=====================================================\n\n");
        no = no->prox;
    }
    system("pause");
}

//Outra função de impresão, mas essa utiliza apenas um endereço de memória passado em seu argumento.
int imprime_lista (UNIDADE *no){
    //Verificação de segurança.
    if(no == NULL){
        printf("\nNao foi possivel buscar, esse codigo nao existe na base de dados.\n\n");
        system("pause");
        return 0;
    }
    //Caso não encontre problemas, a função imprimi os dados do endereço de "no".
    printf("\n=====================================================");
    printf("\nCodigo:..........%d", no->dados.codigo);
    printf("\nNome:............%s", no->dados.nome);
    printf("\nEmpresa:.........%s", no->dados.empresa);
    printf("\nDepartamento:....%s", no->dados.departamento);
    printf("\nTelefone:........%s", no->dados.telefone);
    printf("\nCelular:.........%s", no->dados.celular);
    printf("\nEmail:...........%s\n", no->dados.email);
    printf("=====================================================\n");

    //Retorna 1 para indicar que tudo deu certo.
    return 1;
}

//Função que percorre toda a lista em busca do cliente, por meio do codigo ou identificador.
void consulta_lista_identificador (Lista *li){
    //Verificação de segurança.
    if(li == NULL){
        printf("\nNao foi possivel consultar. Lista nao criada.\n\n");
        system("pause");
        return;
    }

    //Atribui o endereço de "li" ao "no", pois é ele quem vai percorer a lista, mantendo o "li" guardando o início da lista.
    UNIDADE *no = *li;

    //Verificação de segurança.
    if(no == NULL){
        printf("\nNao foi possivel buscar, adicione clientes.\n\n");
        system("pause");
        return;
    }

    //Variável que irá salvar o código digitado pelo usuário, bem como a variável que irá indicar erro.
    int codigo = 0, erro = 0;

    system("cls");
    printf("=====================================================\n\n");
    printf("---- Busca por codigo ----\n\n");
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo);

    //percorre-se toda a lista verificando onde está o código. Ao encontrar, o "no" permanece com o endereço da estrutura. Caso não encontre, fica com o valor nulo.
    while(no != NULL && no->dados.codigo != codigo){
        no = no->prox;
    }

    //Manda o "no" para impressão.
    erro = imprime_lista(no);

    //Ajuste para exibição em tela. Caso não encontre o cliente, função "imprime_lista" já retorna para o menu, não sendo necessário ou "system("pause").
    if(erro){
        printf("\n");
        system("pause");
    }
}

//Função que percorre toda a lista em busca do cliente, por meio do nome digitado pelo usuário.
void consulta_lista_nome(Lista *li){
    //Verificação de segurança.
    if(li == NULL){
        printf("\nNao foi possivel buscar. Lista nao criada.\n\n");
        system("pause");
        return;
    }

    //Atribui o endereço de "li" ao "no", pois é ele quem vai percorer a lista, mantendo o "li" guardando o início da lista.
    UNIDADE *no = *li;

    //Verificação de segurança.
    if(no == NULL){
        printf("\nNao foi possivel buscar, adicione clientes.\n\n");
        system("pause");
        return;
    }

    //Variável que verifica se a função de impressão foi chamada.
    int n_encontrado = 0;
    //String que armazena o nome que será buscado.
    char pesquisa[25];

    system("cls");
    printf("=====================================================\n\n");
    printf("---- Busca por nome ----\n\n");
    printf("Digite o nome do cliente: ");
    getchar();
    gets(pesquisa);

    //While que irá percorrer toda a lista.
    while(no != NULL){
        //Copia-se o nome da estrutura "dados" do respectivo endereço para "busca".
        char busca[25];
        strcpy(busca, no->dados.nome);

        //Verifica-se se a string "pesquisa" encontra-se presente em algum momento na string "busca"
        if(strstr(strupr(busca), strupr(pesquisa))){
            //Caso esteja, é passado o endereço de "no" para impressão, bem como incrementado a variável que verifica se a função foi chamanda. Fora isso, o endereço de "no" é passado a diante, para se verificar novamente.
            imprime_lista(no);
            n_encontrado++;
            no = no->prox;
        }else{
            //Caso não seja encontrado na string, somente passa-se o endereço de "no" para o próximo, para continuar a verificação até que se chegue ao fim da lista.
            no = no->prox;
        }
    }
    //Caso o "if" não seja verdade nenhuma vez, a seguinte mensagem é impressa.
    if(!n_encontrado){
       printf("\nSem nomes correspondentes.\n");
    }
    printf("\n");
    system("pause");
}

//Função para edição de dados.
void edicao_dados(Lista *li){
    //Verificação de segurança.
     if(li == NULL){
        printf("\nNao foi possivel consultar. Lista nao criada.\n\n");
        system("pause");
        return;
    }

    //Atribui o endereço de "li" ao "no", pois é ele quem vai percorer a lista, mantendo o "li" guardando o início da lista.
    UNIDADE *no = *li;

    //Verificação de segurança.
    if(no == NULL){
        printf("\nNao foi possivel buscar, adicione clientes.\n\n");
        system("pause");
        return;
    }

    //Variáveis para pegar o código do cliente, a confirmação ou não da edição e mensagem de erro.
    int codigo = 0, escolha = 0, erro = 0;

    system("cls");
    printf("=====================================================\n\n");
    printf("---- Edicao por codigo ----\n\n");
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo);

    //percorre-se toda a lista verificando onde está o código. Ao encontrar, o "no" permanece com o endereço da estrutura. Caso não encontre, fica com o valor nulo.
    while(no != NULL && no->dados.codigo != codigo){
        no = no->prox;
    }

    //Esse comando existe porque caso o código informado não exista na lista, o "no" terá um valor nulo, retornando erro da função de imprimir, mas nessa função o programa irá prosseguir. Por isso, caso retorne erro, o "if" verifica e termina a função por aqui mesmo.
    erro = imprime_lista(no);
    if(erro == 0){
        return;
    }

    //Confirmação do usuário.
    printf("\n\n=====================================================\n");
    printf("\nDeseja realmente editar o cliente %d?\n\n", codigo);
    printf("[1]...Sim\n[2]...Nao");
    printf("\n\nEscolha: ");
    scanf("%d", &escolha);
    printf("\n=====================================================\n");

    //Caso ele escolha "sim", o "if" é realizado.
    if(escolha == 1){
        system("cls");
        printf("=====================================================\n\n");
        printf("---- Edicao por codigo ----\n");
        //mostra-se a estrutura para facilitar a edição.
        imprime_lista(no);

        //Capta-se os dados.
        getchar();
        printf("\nNome............");
        gets(no->dados.nome);

        nomePadronizado(no->dados.nome);

        printf("Empresa.........");
        gets(no->dados.empresa);
        printf("Departamento....");
        gets(no->dados.departamento);
        printf("Telefone........");
        gets(no->dados.telefone);
        printf("Celular.........");
        gets(no->dados.celular);
        printf("Email...........");
        gets(no->dados.email);

        printf("\n=====================================================\n");
        printf("\nEdicao feita com sucesso!\n\n");
        system("pause");
    }else if(escolha == 2){
        //Caso escolha "não", a função acaba.
        printf("\nEdicao cancelada\n\n");
        system("pause");
    }

}

//Função para remover um cliente da lista.
void remove_lista (Lista *li){
    //Verificação de segurança.
    if(li == NULL){
        printf("\nNao foi possivel buscar. Lista nao criada.\n\n");
        system("pause");
        return;
    }

    //Atribui o endereço de "li" ao "no", pois é ele quem vai percorer a lista, mantendo o "li" guardando o início da lista, além de usar "ant" como auxiliar na exclusão.
    UNIDADE *ant, *no = *li;

    //Verificação de segurança.
    if(no == NULL){
        printf("\nNao foi possivel buscar, adicione clientes.\n\n");
        system("pause");
        return;
    }

    //Variáveis para pegar o código do cliente, a escolha de realment excluir ou não e a mensagem de erro.
    int codigo = 0, escolha = 0, erro = 0;

    system("cls");
    printf("=====================================================\n\n");
    printf("---- Exclusao ----\n\n");
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo);

    //percorre-se toda a lista verificando onde está o código, ao encontrar, o "no" permanece com o endereço da estrutura. Caso não encontre, fica com o valor nulo. Além disso, o "ant" vem salvando o endereço anterior, para que posteriormente um novo endereço seja passado para essa estrutura, pois o seguinte será excluido.
    while(no != NULL && no ->dados.codigo != codigo){
        ant = no;
        no = no->prox;
    }

    //Esse comando existe porque caso o código informado não exista na lista, o "no" terá um valor nulo, retornando erro da função imprimir, mas nessa função o programa irá prosseguir. Por isso, caso retorne erro, o "if" verifica e termina a função por aqui mesmo.
    erro = imprime_lista(no);
    if(erro == 0){
        return;
    }

    //Confirmação do usuário.
    printf("\n\n=====================================================\n");
    printf("\nDeseja excluir o cliente %d?\n\n", codigo);
    printf("[1]...Sim\n[2]...Nao");
    printf("\n\nEscolha: ");
    scanf("%d", &escolha);
    printf("\n=====================================================\n");

    //Caso a escolha seja "sim", realiza-se o "if".
    if(escolha == 1){
        //Caso a exclusão seja no primeiro cliente da lista, passa-se o endereço do "no->prox" para o "li", indicando o endereço do novo primeiro cliente.
        if(no == *li){
            *li = no->prox;
        }else{
            //Caso a exclusão não seja no primeiro cliente, o "ant->prox" recebe o endereço de "no->prox". Utiliza-se o "ant" e "no" para se ter o endereço de exclusão com o "no" e poder passar o novo próximo endereço para o "ant", pois caso contrário o endereço "prox" de "ant" não pertenceria a lista, e lista acabaria ali mesmo, por mais que poderiam existir mais elementos.
            ant->prox = no->prox;
        }
        //Liberação da memória.
        free(no);
        printf("\nExclusao feita com sucesso!\n\n");
        system("pause");
    }else if(escolha == 2){
        //Caso a escolha seja "não", a função é encerrada.
        printf("\nOperacao cancelada.\n\n");
        system("pause");
    }
}

//Função de encerramento da lista, e gravação dos dados.
void encerra_lista(Lista *li, FILE *dados){
    //Caso "li" seja diferente de nulo, realiza-se o "if".
    if(li != NULL){
        UNIDADE *no;

        //Enquanto o conteúdo de "li" for diferente de nulo, realiza-se o While.
        while((*li) != NULL){
            //Atribui-se no "no" o conteúdo de "li".
            no = *li;
            //Escreve no arquivo a struct "dados" do "no".
            fwrite(&(no->dados), sizeof(CLIENTES), 1, dados);
            //Passa-se o "li" para o próximo endereço.
            *li = (*li)->prox;
            //Libera a memória.
            free(no);
        }
        //Após salvar todos os elementos e chegar ao final, libera-se a lista.
        free(li);
    }else{
        //Caso "li" seja nulo, aparece a seguinte mensagem de erro.
        printf("\nErro.\n\n");
        system("pause");
    }
}

//Função que recupera os dados.
int recupera_dados(Lista *li, FILE *dados){
    //Verificação de segurança na abertura no arquivo.
    if (dados == NULL) {
        printf("\nErro na abertura do arquivo.\n\n");
        exit(1);
    }

    //Verificação de segurança.
    if(li == NULL){
        printf("\nErro, lista nao criada.\n\n");
        system("pause");
        //Usou-se "exit" porque se a lista não for criada logo de início o programa nem inicia. Mas caso a lista exista e por algum motivo deixe de funcionar durante o programa, o usuário ainda pode tentar algo.
        exit(1);
    }

    //Alocação de memória para a estrutura clientes.
    CLIENTES *info;
    info = (CLIENTES *)malloc(sizeof(CLIENTES));

    int total_lido = 0;

    //Nesse While é lido as informações do arquivo "dados", e escreve as estruturas nele presentes na struct CLIENTES *info. A função fread retorna 1 caso a leitura de uma estrutura aconteça corretamente, então, enquanto a leitura ocorrer, o While é mantido e a estrutura passada para "info" é mandanda...
    //para a função de "insere_lista_ordenada", salvando e colocando de maneira correta todos os clientes.
    while (fread(info, sizeof(CLIENTES), 1, dados) == 1) {
        insere_lista_ordenada(li, info);
        //Incrementa a variável para se ssber quantos clientes foram recuperados.
        total_lido++;
    }
    //liberação da estrutura "info".
    free(info);
    return total_lido;
}


