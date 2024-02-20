#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "projetoFinal.h"

//Crica��o da estrutura da lista, possuindo a estrutura que armazena os dados e um ponteiro que armazena o endere�o da pr�xima estrutura.
typedef struct unidade{
    CLIENTES dados;
    struct unidade *prox;
}UNIDADE;

//Cria��o e aloca��o de mem�ria para a lista. a lista � do mesmo tipo UNIDADE, mas chamado por outro nome. Essa fun��o retorna o ponteiro para o main, um ponteiro indicando o inicio da lista.
Lista *criaLista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));
    //Teste verificando se a aloca��o deu certo, e logo ap�s atribuindo o valor nulo para que o ponteiro n�o pegue qualquer endere�o de mem�ria.
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

//Verifica se a lista est� vazia, caso esteja, a fun��o de inserir toma alguma providencia, caso n�o, toma outra providencia.
int listaVazia(Lista *li){
    if(li == NULL){
        return 1;
    }
    if(*li == NULL){
        return 1;
    }
    return 0;
}

//Fun��o para padronizar os nomes inseridos pelo usu�rio.
void nomePadronizado(char *str) {

    // Definir que a pr�xima letra � a primeira de uma palavra
    int primeiraLetra = 1;

    for (int i = 0; str[i] != '\0'; i++) {
        // Verificar se o caractere atual � uma letra
        if (isalpha(str[i])) {
            // Se for a primeira letra, capitalizar
            if (primeiraLetra) {
                str[i] = toupper(str[i]);
                primeiraLetra = 0;  // A primeira letra foi capitalizada
            } else {
                str[i] = tolower(str[i]);  // Demais letras em min�sculo.
            }
        } else {
            // Se n�o for uma letra, a pr�xima letra ser� a primeira de uma palavra
            primeiraLetra = 1;
        }
    }
}

//Fun��o para cadastrar os clientes.
void inserir_clientes(Lista *li) {

    //Verifica��o de seguran�a.
    if(li == NULL){
        printf("\nNao foi possivel inserir. Lista n�o criada.\n\n");
        system("pause");
        return;
    }

    //Vari�vel que verifica se ocorreu erro ou n�o. Recebe valor da fun��o de inserir ordenadamente.
    int notificacao = 0;

    //Aloca��o de mem�ria.
    CLIENTES *informacoes;
    informacoes = (CLIENTES *)malloc(sizeof(CLIENTES));

    //Capta��o dos dados.
    system("cls");
    printf("===========================\n\n");
    printf("---- Dados clientes ----");
    printf("\n\nCodigo..........");
    scanf("%d", &informacoes->codigo);
    getchar();
    printf("Nome............");
    gets(informacoes->nome);

    //Passando o nome para a fun��o de padroniza��o de nomes.
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

    //Passando a estrutura para a fun��o "insere_lista_ordenada", bem como o ponteiro de "li".
    notificacao = insere_lista_ordenada(li, informacoes);
    printf("\n===========================\n");

    //Retorno da conclus�o da inser��o.
    if(notificacao){
        printf("\nInserido com sucesso!\n");
        printf("\n===========================\n\n\n");
        system("pause");
    }else{
        printf("\nErro em cadastrar.\n");
        printf("\n===========================\n\n\n");
        system("pause");
    }
    //libera��o de mem�ria.
    free(informacoes);
}

//Fun��o de inser��o ordenada.
int insere_lista_ordenada(Lista *li, CLIENTES *info){
    //Verifica��o de seguran�a, para caso a lista n�o existir voltar ao menu principal.
    if(li == NULL){
        printf("\nNao foi possivel inserir. Lista n�o criada.\n\n");
        system("pause");
        //Retorna 0 para a fun��o de cadastro de clientes, indicando que algo n�o deu certo.
        return 0;
    }
    //Aloca��o de mem�ria para o "no" que ir� receber os dados da estrutura.
    UNIDADE *no = (UNIDADE*) malloc(sizeof(UNIDADE));

    //verifica��o de seguran�a, para caso o "no" n�o ser alocado.
    if(no == NULL){
        printf("\nNao foi possivel inserir.\n\n");
        system("pause");
        return 0;
    }

    //Recebendo os dados da estrutura "info".
    no->dados = *info;

    //Caso a lista esteja vazia, o endere�o do "prox" � atribuido ao conte�do de "li", que no caso � null.
    if(listaVazia(li)){
        no->prox = (*li);
        *li = no;
        return 1;
    }else{

        //Caso n�o seja, aloca-se duas vari�veis do tipo UNIDADE para percorrer a lista, uma mantendo o endere�o passado e outra avan�ando.
        UNIDADE *ant, *atual = *li;
        //While que verifica se a posi��o atual � diferente de nula, pois, caso n�o seja, chegou-se ao final da lista; al�m de estar verificando se o codigo do cliente da lista � menor que o codigo que ir� ser inserido.
        //utiliza-se duas vari�veis para isso, pois enquanto uma avan�a, a outra se torna o porto seguro da fun��o.
        while(atual != NULL && atual->dados.codigo < info->codigo){
            ant = atual;
            atual = atual->prox;
        }
        //Se a posi��o a ser alocada for logo no in�cio, ou seja, na mem�ria onde "li" aponta primeiramente, passa-se o endere�o para o "prox" do "no" e atribui ao "li" o endere�o do "no".
        if(atual == *li){
            no->prox = (*li);
            *li = no;
        }else{
            //Caso a posi��o n�o seja no in�cio, o "prox" do "no" atribui o "ant->prox", e o encere�o do "no" � atribuido ao "ant->prox".
            no->prox = ant->prox;
            ant->prox = no;
        }
        //Retorna 1 para a fun��o de cadastro de clientes, indicando que deu tudo certo.
        return 1;
    }
}

//Fun��o para impress�o da lista total.
void imprime_lista_total(Lista *li){
    //Verifica��o de seguran�a.
    if(li == NULL){
        printf("\nNao foi possivel consultar. Lista nao criada.\n\n");
        system("pause");
        return;
    }

    //Atribui o endere�o de "li" ao "no", pois � ele quem vai percorer a lista, mantendo o "li" guardando o in�cio da lista.
    UNIDADE *no = *li;

    //Verifica��o de seguran�a.
    if(no == NULL){
        printf("\nNao foi possivel buscar, adicione clientes.\n\n");
        system("pause");
        return;
    }

    //Impress�o. Enquanto "no" for diferente de nulo quer dizer que a lista n�o acabou, imprimindo assim toda a lista.
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

//Outra fun��o de impres�o, mas essa utiliza apenas um endere�o de mem�ria passado em seu argumento.
int imprime_lista (UNIDADE *no){
    //Verifica��o de seguran�a.
    if(no == NULL){
        printf("\nNao foi possivel buscar, esse codigo nao existe na base de dados.\n\n");
        system("pause");
        return 0;
    }
    //Caso n�o encontre problemas, a fun��o imprimi os dados do endere�o de "no".
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

//Fun��o que percorre toda a lista em busca do cliente, por meio do codigo ou identificador.
void consulta_lista_identificador (Lista *li){
    //Verifica��o de seguran�a.
    if(li == NULL){
        printf("\nNao foi possivel consultar. Lista nao criada.\n\n");
        system("pause");
        return;
    }

    //Atribui o endere�o de "li" ao "no", pois � ele quem vai percorer a lista, mantendo o "li" guardando o in�cio da lista.
    UNIDADE *no = *li;

    //Verifica��o de seguran�a.
    if(no == NULL){
        printf("\nNao foi possivel buscar, adicione clientes.\n\n");
        system("pause");
        return;
    }

    //Vari�vel que ir� salvar o c�digo digitado pelo usu�rio, bem como a vari�vel que ir� indicar erro.
    int codigo = 0, erro = 0;

    system("cls");
    printf("=====================================================\n\n");
    printf("---- Busca por codigo ----\n\n");
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo);

    //percorre-se toda a lista verificando onde est� o c�digo. Ao encontrar, o "no" permanece com o endere�o da estrutura. Caso n�o encontre, fica com o valor nulo.
    while(no != NULL && no->dados.codigo != codigo){
        no = no->prox;
    }

    //Manda o "no" para impress�o.
    erro = imprime_lista(no);

    //Ajuste para exibi��o em tela. Caso n�o encontre o cliente, fun��o "imprime_lista" j� retorna para o menu, n�o sendo necess�rio ou "system("pause").
    if(erro){
        printf("\n");
        system("pause");
    }
}

//Fun��o que percorre toda a lista em busca do cliente, por meio do nome digitado pelo usu�rio.
void consulta_lista_nome(Lista *li){
    //Verifica��o de seguran�a.
    if(li == NULL){
        printf("\nNao foi possivel buscar. Lista nao criada.\n\n");
        system("pause");
        return;
    }

    //Atribui o endere�o de "li" ao "no", pois � ele quem vai percorer a lista, mantendo o "li" guardando o in�cio da lista.
    UNIDADE *no = *li;

    //Verifica��o de seguran�a.
    if(no == NULL){
        printf("\nNao foi possivel buscar, adicione clientes.\n\n");
        system("pause");
        return;
    }

    //Vari�vel que verifica se a fun��o de impress�o foi chamada.
    int n_encontrado = 0;
    //String que armazena o nome que ser� buscado.
    char pesquisa[25];

    system("cls");
    printf("=====================================================\n\n");
    printf("---- Busca por nome ----\n\n");
    printf("Digite o nome do cliente: ");
    getchar();
    gets(pesquisa);

    //While que ir� percorrer toda a lista.
    while(no != NULL){
        //Copia-se o nome da estrutura "dados" do respectivo endere�o para "busca".
        char busca[25];
        strcpy(busca, no->dados.nome);

        //Verifica-se se a string "pesquisa" encontra-se presente em algum momento na string "busca"
        if(strstr(strupr(busca), strupr(pesquisa))){
            //Caso esteja, � passado o endere�o de "no" para impress�o, bem como incrementado a vari�vel que verifica se a fun��o foi chamanda. Fora isso, o endere�o de "no" � passado a diante, para se verificar novamente.
            imprime_lista(no);
            n_encontrado++;
            no = no->prox;
        }else{
            //Caso n�o seja encontrado na string, somente passa-se o endere�o de "no" para o pr�ximo, para continuar a verifica��o at� que se chegue ao fim da lista.
            no = no->prox;
        }
    }
    //Caso o "if" n�o seja verdade nenhuma vez, a seguinte mensagem � impressa.
    if(!n_encontrado){
       printf("\nSem nomes correspondentes.\n");
    }
    printf("\n");
    system("pause");
}

//Fun��o para edi��o de dados.
void edicao_dados(Lista *li){
    //Verifica��o de seguran�a.
     if(li == NULL){
        printf("\nNao foi possivel consultar. Lista nao criada.\n\n");
        system("pause");
        return;
    }

    //Atribui o endere�o de "li" ao "no", pois � ele quem vai percorer a lista, mantendo o "li" guardando o in�cio da lista.
    UNIDADE *no = *li;

    //Verifica��o de seguran�a.
    if(no == NULL){
        printf("\nNao foi possivel buscar, adicione clientes.\n\n");
        system("pause");
        return;
    }

    //Vari�veis para pegar o c�digo do cliente, a confirma��o ou n�o da edi��o e mensagem de erro.
    int codigo = 0, escolha = 0, erro = 0;

    system("cls");
    printf("=====================================================\n\n");
    printf("---- Edicao por codigo ----\n\n");
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo);

    //percorre-se toda a lista verificando onde est� o c�digo. Ao encontrar, o "no" permanece com o endere�o da estrutura. Caso n�o encontre, fica com o valor nulo.
    while(no != NULL && no->dados.codigo != codigo){
        no = no->prox;
    }

    //Esse comando existe porque caso o c�digo informado n�o exista na lista, o "no" ter� um valor nulo, retornando erro da fun��o de imprimir, mas nessa fun��o o programa ir� prosseguir. Por isso, caso retorne erro, o "if" verifica e termina a fun��o por aqui mesmo.
    erro = imprime_lista(no);
    if(erro == 0){
        return;
    }

    //Confirma��o do usu�rio.
    printf("\n\n=====================================================\n");
    printf("\nDeseja realmente editar o cliente %d?\n\n", codigo);
    printf("[1]...Sim\n[2]...Nao");
    printf("\n\nEscolha: ");
    scanf("%d", &escolha);
    printf("\n=====================================================\n");

    //Caso ele escolha "sim", o "if" � realizado.
    if(escolha == 1){
        system("cls");
        printf("=====================================================\n\n");
        printf("---- Edicao por codigo ----\n");
        //mostra-se a estrutura para facilitar a edi��o.
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
        //Caso escolha "n�o", a fun��o acaba.
        printf("\nEdicao cancelada\n\n");
        system("pause");
    }

}

//Fun��o para remover um cliente da lista.
void remove_lista (Lista *li){
    //Verifica��o de seguran�a.
    if(li == NULL){
        printf("\nNao foi possivel buscar. Lista nao criada.\n\n");
        system("pause");
        return;
    }

    //Atribui o endere�o de "li" ao "no", pois � ele quem vai percorer a lista, mantendo o "li" guardando o in�cio da lista, al�m de usar "ant" como auxiliar na exclus�o.
    UNIDADE *ant, *no = *li;

    //Verifica��o de seguran�a.
    if(no == NULL){
        printf("\nNao foi possivel buscar, adicione clientes.\n\n");
        system("pause");
        return;
    }

    //Vari�veis para pegar o c�digo do cliente, a escolha de realment excluir ou n�o e a mensagem de erro.
    int codigo = 0, escolha = 0, erro = 0;

    system("cls");
    printf("=====================================================\n\n");
    printf("---- Exclusao ----\n\n");
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigo);

    //percorre-se toda a lista verificando onde est� o c�digo, ao encontrar, o "no" permanece com o endere�o da estrutura. Caso n�o encontre, fica com o valor nulo. Al�m disso, o "ant" vem salvando o endere�o anterior, para que posteriormente um novo endere�o seja passado para essa estrutura, pois o seguinte ser� excluido.
    while(no != NULL && no ->dados.codigo != codigo){
        ant = no;
        no = no->prox;
    }

    //Esse comando existe porque caso o c�digo informado n�o exista na lista, o "no" ter� um valor nulo, retornando erro da fun��o imprimir, mas nessa fun��o o programa ir� prosseguir. Por isso, caso retorne erro, o "if" verifica e termina a fun��o por aqui mesmo.
    erro = imprime_lista(no);
    if(erro == 0){
        return;
    }

    //Confirma��o do usu�rio.
    printf("\n\n=====================================================\n");
    printf("\nDeseja excluir o cliente %d?\n\n", codigo);
    printf("[1]...Sim\n[2]...Nao");
    printf("\n\nEscolha: ");
    scanf("%d", &escolha);
    printf("\n=====================================================\n");

    //Caso a escolha seja "sim", realiza-se o "if".
    if(escolha == 1){
        //Caso a exclus�o seja no primeiro cliente da lista, passa-se o endere�o do "no->prox" para o "li", indicando o endere�o do novo primeiro cliente.
        if(no == *li){
            *li = no->prox;
        }else{
            //Caso a exclus�o n�o seja no primeiro cliente, o "ant->prox" recebe o endere�o de "no->prox". Utiliza-se o "ant" e "no" para se ter o endere�o de exclus�o com o "no" e poder passar o novo pr�ximo endere�o para o "ant", pois caso contr�rio o endere�o "prox" de "ant" n�o pertenceria a lista, e lista acabaria ali mesmo, por mais que poderiam existir mais elementos.
            ant->prox = no->prox;
        }
        //Libera��o da mem�ria.
        free(no);
        printf("\nExclusao feita com sucesso!\n\n");
        system("pause");
    }else if(escolha == 2){
        //Caso a escolha seja "n�o", a fun��o � encerrada.
        printf("\nOperacao cancelada.\n\n");
        system("pause");
    }
}

//Fun��o de encerramento da lista, e grava��o dos dados.
void encerra_lista(Lista *li, FILE *dados){
    //Caso "li" seja diferente de nulo, realiza-se o "if".
    if(li != NULL){
        UNIDADE *no;

        //Enquanto o conte�do de "li" for diferente de nulo, realiza-se o While.
        while((*li) != NULL){
            //Atribui-se no "no" o conte�do de "li".
            no = *li;
            //Escreve no arquivo a struct "dados" do "no".
            fwrite(&(no->dados), sizeof(CLIENTES), 1, dados);
            //Passa-se o "li" para o pr�ximo endere�o.
            *li = (*li)->prox;
            //Libera a mem�ria.
            free(no);
        }
        //Ap�s salvar todos os elementos e chegar ao final, libera-se a lista.
        free(li);
    }else{
        //Caso "li" seja nulo, aparece a seguinte mensagem de erro.
        printf("\nErro.\n\n");
        system("pause");
    }
}

//Fun��o que recupera os dados.
int recupera_dados(Lista *li, FILE *dados){
    //Verifica��o de seguran�a na abertura no arquivo.
    if (dados == NULL) {
        printf("\nErro na abertura do arquivo.\n\n");
        exit(1);
    }

    //Verifica��o de seguran�a.
    if(li == NULL){
        printf("\nErro, lista nao criada.\n\n");
        system("pause");
        //Usou-se "exit" porque se a lista n�o for criada logo de in�cio o programa nem inicia. Mas caso a lista exista e por algum motivo deixe de funcionar durante o programa, o usu�rio ainda pode tentar algo.
        exit(1);
    }

    //Aloca��o de mem�ria para a estrutura clientes.
    CLIENTES *info;
    info = (CLIENTES *)malloc(sizeof(CLIENTES));

    int total_lido = 0;

    //Nesse While � lido as informa��es do arquivo "dados", e escreve as estruturas nele presentes na struct CLIENTES *info. A fun��o fread retorna 1 caso a leitura de uma estrutura aconte�a corretamente, ent�o, enquanto a leitura ocorrer, o While � mantido e a estrutura passada para "info" � mandanda...
    //para a fun��o de "insere_lista_ordenada", salvando e colocando de maneira correta todos os clientes.
    while (fread(info, sizeof(CLIENTES), 1, dados) == 1) {
        insere_lista_ordenada(li, info);
        //Incrementa a vari�vel para se ssber quantos clientes foram recuperados.
        total_lido++;
    }
    //libera��o da estrutura "info".
    free(info);
    return total_lido;
}


