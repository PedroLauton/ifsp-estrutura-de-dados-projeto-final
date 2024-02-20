#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "projetoFinal.h"

/*Projeto realizado pelos alunos:

  Pedro Henrique Ramos Lauton - GU3046222;
  Caio Dib Laronga � GU3042294.

*/

int main()
{
    //Cria��o de vari�veis para a escolha do usu�rio e quantidade de clientes recuperados.
    int escolha = 0, total_lido = 0;

    //Cria��o da vari�vel de abertura do arquivo "Clientes.bin".
    FILE *dados;
    dados = fopen("Clientes.bin", "rb");

    //Cria��o da lista din�mica.
    Lista *li;
    li = criaLista();

    //Verifica��o da abertura do arquivo.
    if(dados == NULL){
        //Caso seja nulo, ou seja, o arquivo nao exisite ou nao pode ser aberto, a seguinte mensagem � exibida, indicando que n�o houve como recuperar os dados.
        printf("=======================\n");
        printf("\nSem registros de dados.\n\n");
        printf("=======================\n\n");
        system("pause");
    }else{
        /*Caso a abertura aconte�a, � chamado a fun��o "recupera_dados" passando como argumento o arquivo FILE, bem como o ponteiro de "li".
        Essa fun��o retorna quantos clientes foram recuperados para a vari�vel "total_lido", que exibi logo em seguinda.*/
        total_lido = recupera_dados(li, dados);
        fclose(dados);
        printf("============================================\n");
        printf("\nQuantidade total de clientes recuperados: %d\n\n", total_lido);
        printf("============================================\n\n");
        system("pause");
    }

    do{
        //Exibi��o do menu. Utilizou-se o la�o de repeti��o "do while" para manter o usu�rio sempre preso no menu, ao menos que ele decida sair por vontade pr�pria.
        system("cls");
        printf("============================================\n\n");
        printf("----- Menu - ACME S.A. -----\n");
        printf("\n[1]... Incluir cliente");
        printf("\n[2]... Relatorio total");
        printf("\n[3]... Relatorio individual (Identificador)");
        printf("\n[4]... Relatorio (Nome)");
        printf("\n[5]... Edicao de dados (Identificador)");
        printf("\n[6]... Excluir cliente (Identificador)");
        printf("\n[7]... Encerrar");
        printf("\n\n============================================\n");
        printf("\nEscolha: ");

        /*Esta fun��o verifica se a escolha do usu�rio est� no intervalo v�lido (1 a 7).
        Se a escolha n�o estiver dentro desse intervalo, o usu�rio entra em um loop (while),
        exibindo uma mensagem de erro e solicitando uma nova escolha at� que um valor v�lido seja inserido.*/
        while (1) {
            if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 7) {
                printf("\n============================================\n");
                printf("\nEscolha inconsistente, tente novamente.\n\n");
                system("pause");
                while (getchar() != '\n');
                system("cls");
                printf("============================================\n\n");
                printf("----- Menu - ACME S.A. -----\n");
                printf("\n[1]... Incluir cliente");
                printf("\n[2]... Relatorio total");
                printf("\n[3]... Relatorio individual (Identificador)");
                printf("\n[4]... Relatorio (Nome)");
                printf("\n[5]... Edicao de dados (Identificador)");
                printf("\n[6]... Excluir cliente (Identificador)");
                printf("\n[7]... Encerrar");
                printf("\n\n============================================\n");
                printf("\nEscolha: ");
                continue;
            }
            break;
        }

        printf("\n============================================\n");

        //Switch direcionando o cliente para a funcionalidade escolhida com base no valor digitado.
        switch(escolha){
            case 1:
                inserir_clientes(li);
                break;

            case 2:
                imprime_lista_total(li);
                break;

            case 3:
                consulta_lista_identificador(li);
                break;

            case 4:
                consulta_lista_nome(li);
                break;

            case 5:
                edicao_dados(li);
                break;

            case 6:
                remove_lista(li);
                break;

            case 7:
                //No encerramento do programa, foi mudado a abertura do arquivo para escrita, podendo assim salvar os dados dessa sess�o.
                dados = fopen("Clientes.bin", "wb");
                encerra_lista(li, dados);
                fclose(dados);
                break;

            default:
                printf("\nErro.\n\n");
                break;
        }
    }while(escolha != 7);
    return 0;
}
