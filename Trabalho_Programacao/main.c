#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "lib.h"


void menuprincipal() {
    //criar as listas ligadas , que come�am vazias
    Cliente* clientes = NULL;
    Gestor* gestores = NULL;
    Meio* meios = NULL;
    meios = lerMeios(); //iguala-se a lista vazia � fun��o ler meios , para preencher a lista com a info que tem no ficheiro meios.txt
    clientes = lerCliente(); //iguala-se a lista vazia � fun��o ler cliente , para preencher a lista com a info que tem no ficheiro clientes.txt
    gestores = lerGestor(); //iguala-se a lista vazia � fun��o ler gestor , para preencher a lista com a info que tem no ficheiro gestores.txt
    int resposta, id, idcli, idges, carga, autonomia, idade, nif, telemovel, respostacli, respostages, idmeio, aluguer;
    char tipo[50], morada[50], password[50], nome[50], tipodemobilidade[50], localizacao[50], nomecli[50], passwordcli[50], nomeges[50], passwordges[50];
    float custo,saldo;
    // cria��o de todas as variaveis que � necessario para fazer todas as fun��es da app
    // Inicializa��o do menu com um switch para o utilizador inciar sess�o ou criar um cliente/gestor
    printf("Iniciar sessao como:\n");
    printf("1 - Cliente\n");
    printf("2 - Gestor\n");
    printf("\n");
    printf("Criar conta como:\n");
    printf("3 - Cliente\n");
    printf("4 - Gestor\n");
    printf("\n");
    printf("Opcao:");
    scanf("%d", &resposta);

    switch (resposta) {
    case 1: {
        //� pedido ao utilizador o respostivo id,nome e palavra-passe para com a fun��o verifica cliente , verificar se as credenciais est�o validas
        printf("*************** CLIENTE ***************\n");
        printf("ID: ");
        scanf("%d", &id);
        printf("Nome: ");
        getchar();
        gets(nome);
        printf("Palavra-Passe: ");
        gets(password);
        //un��o Verifica cliente, compara o id, nome e password, com o que existe na lista ligada do Cliente e verifica se � tudo igual
        if (verificaCliente(clientes, id, nome, password)) {
            printf("Sessao iniciada\n");
            printf("***************  MENU CLIENTE ***************\n");
            printf("Selecione a opcao pretendida\n");
            printf("1 - Editar Conta\n");
            printf("2 - Listar meios\n");
            printf("3 - Listar meios disponiveis para aluguer\n");
            printf("4 - Listar meios por ordem decrescente de autonomia\n");
            printf("5 - Alugar meio\n");
            printf("6 - Desalugar meio\n");
            printf("7 - Remover conta\n");
            printf("Opcao: ");
            scanf("%d", &respostacli);

            switch (respostacli) {
            case 1:
                //� chamada a fun��o editar cliente, em que pedimos ao utilizador os dados e ele insere e atualiza na mem�ria da lista
                editarCliente(clientes, id);
                //Depois de guardar na mem�ria os novos dados , guarda - se da mem�ria para o ficheiro txt , atualizando assim os novos dados
                guardarClientes(clientes);
                menuprincipal();

            case 2:
                //� chamada a fun��o listarMeios , para listar todos os meios da lista existentes na mem�ria
                listarMeios(meios);
                menuprincipal();

            case 3:
                //Lista todos os meios que est�o disponiveis para ser alugados
                MeiosParaAlugar(meios);
                menuprincipal();

            case 4:
                //lista os meios por ordem decrescente de autonomia
                listarMeiosPorAutonomia(meios);
                menuprincipal();

            case 5:
                //� pedido ao utilizador o id do meio que deseja alugar , e a fun��o alugar meios , ir� printar se deu ou n�o para alugar
                printf("ID do meio que pretende alugar: ");
                scanf("%d", &idmeio);
                AlugarMeios(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 6:
                //� pedido ao utilizador o id do meio que deseja desalugar , e a fun��o desalugar meios , ir� printar se deu ou n�o para desalugar
                printf("ID do meio que pretende desalugar: ");
                scanf("%d", &idmeio);
                DesalugarMeios(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 7:
                //O programa vai buscar o id que o cliente preenche para iniciar sess�o e elimina a sua conta
                clientes = removerCliente(clientes, id);
                guardarClientes(clientes);
                menuprincipal();

            default:
                printf("Selecione uma opcao valida !\n");
            }
            return 0;
        }
        else printf("Credenciais invalidas\n");
        break;
    }
    case 2: {
        //� pedido ao utilizador o respostivo id,nome e palavra-passe para com a fun��o verifica gestor , verificar se as credenciais est�o validas
        printf("*************** GESTOR ***************\n");
        printf("ID: ");
        scanf("%d", &id);
        printf("Nome: ");
        getchar();
        gets(nome);
        printf("Palavra-Passe: ");
        gets(password);
        //Fun��o Verifica gestor , compara o id , nome e password , com o que existe na lista ligada do Gestor e verifica se � tudo igual
        if (verificaGestor(gestores, id, nome, password)) {
            printf("Sessao iniciada\n");
            printf("***************  MENU GESTOR ***************\n");
            printf("Selecione a opcao pretendida\n");
            printf("1 - Inserir meios\n");
            printf("2 - Editar meios\n");
            printf("3 - Listar meios\n");
            printf("4 - Verificar existencia de um meio\n");
            printf("5 - Remover meio\n");
            printf("6 - Listar meios disponiveis para aluguer\n");
            printf("7 - Listar meios por ordem decrescente de autonomia\n");
            printf("8 - Alugar meio\n");
            printf("9 - Desalugar meio\n");
            printf("10 - Listar meios com a localizacao pretendida\n");
            printf("11 - Inserir cliente\n");
            printf("12 - Editar cliente\n");
            printf("13 - Listar cliente\n");
            printf("14 - Verificar existencia de um cliente\n");
            printf("15 - Remover cliente\n");
            printf("16 - Inserir gestor\n");
            printf("17 - Editar gestor\n");
            printf("18 - Listar gestores\n");
            printf("19 - Verificar existencia de um gestor\n");
            printf("20 - Remover gestor\n");
            printf("Opcao: ");
            scanf("%d", &respostages);

            switch (respostages) {
            case 1:
                //� pedido ao utilizador todos os dados necess�rios para preencher um novo meio , � inserido na lista , e depois guardado da mem�ria para o ficheiro meios.txt
                printf("Inserir novo meio:\n");
                printf("ID:");
                scanf("%d", &idmeio);
                printf("Tipo de Mobilidade: ");
                getchar();
                gets(tipodemobilidade);
                printf("Carga: ");
                scanf("%d", &carga);
                printf("Autonomia: ");
                scanf("%d", &autonomia);
                printf("Custo: ");
                scanf("%f", &custo);
                printf("Localizacao: ");
                getchar();
                gets(localizacao);
                printf("0 - Nao alugado / 1 - Alugado\n");
                printf("Aluguer: ");
                scanf("%d", &aluguer);
                meios = inserirMeio(meios, idmeio, tipodemobilidade, carga, autonomia, custo, localizacao, aluguer);
                guardarMeios(meios);
                menuprincipal();

            case 2:
                //� pedido o id que o utilizador deseja editar o meio , e ap�s isso todas as informa��es que d� para editar do meio
                printf("Editar meio:\n");
                printf("ID:");
                scanf("%d", &idmeio);
                editarMeios(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 3:
                //lista todos os meios presentes na mem�ria
                printf("Lista de meios existentes:\n");
                listarMeios(meios);
                menuprincipal();

            case 4:
                //Pede-se o id do meio, e caso o if retorne 1 == true , o meio existe , sen�o o meio n�o existe 
                printf("ID do meio que pretende verificar a sua existencia: ");
                scanf("%d", &idmeio);
                if (existeMeio(meios, idmeio)) {
                    printf("O meio com o id %d existe\n", idmeio);
                }
                else {
                    printf("O meio com o id %d nao existe\n", idmeio);
                }
                menuprincipal();

            case 5:
                //Pede-se o id do meio que quer remover , e depois � removido da mem�ria
                printf("ID do meio que pretende remover: ");
                scanf("%d", &idmeio);
                meios = removerMeio(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 6:
                //Lista os meios que estejam disponiveis para aluguer
                printf("Meios disponiveis para alugar:\n");
                MeiosParaAlugar(meios);
                menuprincipal();

            case 7:
                //lista os meios por ordem decrescente de autonomia
                printf("Lista de meios por ordem decrescente de autonomia:\n");
                listarMeiosPorAutonomia(meios);
                menuprincipal();

            case 8:
                //� pedido ao utilizador o id do meio que deseja alugar , e a fun��o alugar meios , ir� printar se deu ou n�o para alugar
                printf("ID do meio que pretende alugar: ");
                scanf("%d", &idmeio);
                AlugarMeios(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 9:
                //� pedido ao utilizador o id do meio que deseja desalugar , e a fun��o desalugar meios , ir� printar se deu ou n�o para desalugar
                printf("ID do meio que pretende desalugar: ");
                scanf("%d", &idmeio);
                DesalugarMeios(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 10:
                //pedimos um localiza��o ao utilizador , e comparamos com as que existem na lista , caso exista uma igual � que o utilizador inseriu , imprime-se esse meio
                printf("Localizacao pretendida: ");
                getchar();
                gets(localizacao);
                verificaLocalizacao(meios, localizacao);
                menuprincipal();

            case 11:
                //� pedido ao utilizador todos os dados necessarios para inserir um novo cliente, depois � chamada a fun��o para inserir na mem�ria e em seguida atualizado no ficheiro clientes.txt
                printf("Inserir cliente:\n");
                printf("ID: "),
                    scanf("%d", &idcli);
                printf("Nome: ");
                getchar();
                gets(nomecli);
                printf("Morada: ");
                gets(morada);
                printf("Idade: ");
                scanf("%d", &idade);
                printf("NIF: ");
                scanf("%d", &nif);
                printf("Telemovel: ");
                scanf("%d", &telemovel);
                printf("Saldo: ");
                scanf("%.2f", &saldo);
                printf("Password: ");
                getchar();
                gets(passwordcli);
                clientes = inserirCliente(clientes, idcli, nomecli, morada, idade, nif, telemovel, saldo, passwordcli);
                guardarClientes(clientes);
                menuprincipal();

            case 12:
                //� pedido o id do cliente , e depois altera-se na mem�ria com os dados introduzidos pelo utilizador
                printf("ID do cliente que pretende editar: ");
                scanf("%d", &idcli);
                editarCliente(clientes, idcli);
                guardarClientes(clientes);
                menuprincipal();

            case 13:
                //lista todos os clientes da struct existentes na mem�ria
                printf("Lista de clientes existentes: \n");
                listarCliente(clientes);
                menuprincipal();

            case 14:
                //Pede-se o id do cliente, e caso o if retorne 1 ou seja true , o cliente existe , sen�o o cliente n�o existe 
                printf("ID do cliente que pretende verificar a sua existencia: ");
                scanf("%d", &idcli);
                if (existeCliente(clientes, idcli)) {
                    printf("O cliente com o id %d existe\n", idcli);
                }
                else {
                    printf("O cliente com o id %d nao existe\n", idcli);
                }
                menuprincipal();

            case 15:
                //Pede-se o id do cliente que quer remover , e depois � removido da mem�ria
                printf("ID do cliente que pretende remover: ");
                scanf("%d", &idcli);
                clientes = removerCliente(clientes, idcli);
                guardarClientes(clientes);
                menuprincipal();

            case 16:
                //� pedido ao utilizador todos os dados necessarios para inserir um novo gestor, depois � chamada a fun��o para inserir na mem�ria e em seguida atualizado no ficheiro gestor.txt
                printf("Inserir gestor:\n");
                printf("ID: ");
                scanf("%d", &idges);
                printf("Nome: ");
                getchar(); // Clear the input buffer
                gets(nomeges);
                printf("NIF: ");
                scanf("%d", &nif);
                printf("Telemovel: ");
                scanf("%d", &telemovel);
                printf("Password: ");
                getchar(); // Clear the input buffer
                gets(passwordges);
                gestores = inserirGestor(gestores, idges, nomeges, nif, telemovel, passwordges);
                guardarGestores(gestores);
                menuprincipal();

            case 17:
                //� pedido o id do gestor , e depois altera-se na mem�ria com os dados introduzidos pelo utilizador
                printf("ID do gestor que pretende editar: ");
                scanf("%d", &idges);
                editarGestor(gestores, idges);
                guardarGestores(gestores);
                menuprincipal();

            case 18:
                //lista todos os gestores da struct existentes na mem�ria
                printf("Lista de gestores existentes:\n");
                listarGestor(gestores);
                menuprincipal();

            case 19:
                //Pede-se o id do gestor, e caso o if retorne 1 ou seja true , o gestor existe , sen�o o gestor n�o existe 
                printf("ID do gestor que pretende verificar a sua existencia: ");
                scanf("%d", &idges);
                if (existeGestor(gestores, idges)) {
                    printf("O gestor com o id %d existe\n", idges);
                }
                else {
                    printf("O gestor com o id %d nao existe\n", idges);
                }
                menuprincipal();

            case 20:
                //Pede-se o id do gestor que quer remover , e depois � removido da mem�ria
                printf("ID do gestor que pretende remover: ");
                scanf("%d", &idges);
                gestores = removerGestor(gestores, idges);
                guardarGestores(gestores);
                menuprincipal();

            default:
                //Caso n�o selecione nenhuma das opcoes anteriores
                printf("Selecione uma opcao valida !\n");
                menuprincipal();
            }
            return 0;

        }
        // Caso o nome/password estejam erradas
        else printf("Credenciais invalidas\n");
        break;
    }
    case 3: {
        //� pedido ao utilizador todos os dados necessarios para inserir um novo cliente, depois � chamada a fun��o para inserir na mem�ria e em seguida atualizado no ficheiro clientes.txt
        printf("*************** CLIENTE ***************\n");
        printf("ID: "),
            scanf("%d", &idcli);
        printf("Nome: ");
        getchar();
        gets(nomecli);
        printf("Morada: ");
        gets(morada);
        printf("Idade: ");
        scanf("%d", &idade);
        printf("NIF: ");
        scanf("%d", &nif);
        printf("Telemovel: ");
        scanf("%d", &telemovel);
        printf("Saldo: ");
        scanf("%.2f", &saldo);
        printf("Password: ");
        getchar();
        gets(passwordcli);
        clientes = inserirCliente(clientes, idcli, nomecli, morada, idade, nif, telemovel, saldo, passwordcli);
        guardarClientes(clientes);
        menuprincipal();
    }
    case 4: {
        //� pedido ao utilizador todos os dados necessarios para inserir um novo gestor, depois � chamada a fun��o para inserir na mem�ria e em seguida atualizado no ficheiro gestor.txt
        printf("*************** GESTOR ***************\n");
        printf("ID: ");
        scanf("%d", &idges);
        printf("Nome: ");
        getchar();
        gets(nomeges);
        printf("NIF: ");
        scanf("%d", &nif);
        printf("Telemovel: ");
        scanf("%d", &telemovel);
        printf("Password: ");
        getchar();
        gets(passwordges);
        gestores = inserirGestor(gestores, idges, nomeges, nif, telemovel, passwordges);
        guardarGestores(gestores);
        menuprincipal();
    }
    default: {
        //Caso n�o selecione nenhuma das opcoes anteriores
        printf("Selecione uma opcao valida !\n");
        menuprincipal();
    }
    }
}

int main() {

    //chamada da fun��o menu � main , para correr na consola a aplica��o
    menuprincipal();

}