#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "lib.h"


void menuprincipal() {
    Cliente* clientes = NULL;
    Gestor* gestores = NULL;
    Meio* meios = NULL;
    meios = lerMeios();
    clientes = lerCliente();
    gestores = lerGestor();
    int resposta, id, idcli, idges, carga, autonomia, idade, nif, telemovel, respostacli, respostages, idmeio, aluguer;
    char tipo[50], morada[50], password[50], nome[50], tipodemobilidade[50], localizacao[50], nomecli[50], passwordcli[50], nomeges[50], passwordges[50];
    float custo;
    printf("***************  MENU ***************\n");
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
        printf("*************** CLIENTE ***************\n");
        printf("ID: ");
        scanf("%d", &id);
        printf("Nome: ");
        getchar(); // Clear the input buffer
        gets(nome);
        printf("Palavra-Passe: ");
        //scanf("%s", password);
        gets(password);
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
                editarCliente(clientes, id);
                guardarClientes(clientes);
                menuprincipal();

            case 2:
                listarMeios(meios);
                menuprincipal();

            case 3:
                MeiosParaAlugar(meios);
                menuprincipal();

            case 4:
                listarMeiosPorAutonomia(meios);
                menuprincipal();

            case 5:
                printf("ID do meio que pretende alugar: ");
                scanf("%d", &idmeio);
                AlugarMeios(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 6:
                printf("ID do meio que pretende desalugar: ");
                scanf("%d", &idmeio);
                DesalugarMeios(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 7:
                removerCliente(clientes, id);
                guardarClientes(clientes);
                menuprincipal();

            default:
                printf("Selecione uma opcao valida !\n");
            }
            return 0;
        }
        else printf("Credenciais invalidas\n");
        return 0;
        break;
    }
    case 2: {
        printf("*************** GESTOR ***************\n");
        printf("ID: ");
        scanf("%d", &id);
        printf("Nome: ");
        getchar(); // Clear the input buffer
        gets(nome);
        printf("Palavra-Passe: ");
        //scanf("%s", password); 
        gets(password);
        if (verificaGestor(gestores, id, nome, password)) {
            printf("Sessao iniciada\n");
            printf("***************  MENU GESTOR ***************\n");
            printf("Selecione a opcao pretendida\n");
            printf("1 - Inserir meios\n");
            printf("2 - Editar meios\n");
            printf("3 - Listar meios\n");
            printf("4 - Verificar existencia de um meio\n");
            printf("5 - Remover meios\n");
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
                printf("Editar meio:\n");
                printf("ID:");
                scanf("%d", &idmeio);
                editarMeios(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 3:
                printf("Lista de meios existentes:\n");
                listarMeios(meios);
                menuprincipal();

            case 4:
                printf("ID do meio que pretende verificar a sua existencia: \n");
                scanf("%d", &idmeio);
                if (existeMeio(meios, idmeio)) {
                    printf("O meio com o id %d existe\n", idmeio);
                }
                else {
                    printf("O meio com o id %d nao existe\n", idmeio);
                }
                menuprincipal();

            case 5:
                printf("ID do meio que pretende remover: ");
                scanf("%d", &idmeio);
                meios = removerMeio(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 6:
                printf("Meios disponiveis para alugar:\n");
                MeiosParaAlugar(meios);
                menuprincipal();

            case 7:
                printf("Lista de meios por ordem decrescente de autonomia:\n");
                listarMeiosPorAutonomia(meios);
                menuprincipal();

            case 8:
                printf("ID do meio que pretende alugar: ");
                scanf("%d", &idmeio);
                AlugarMeios(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 9:
                printf("ID do meio que pretende desalugar: ");
                scanf("%d", &idmeio);
                DesalugarMeios(meios, idmeio);
                guardarMeios(meios);
                menuprincipal();

            case 10:
                printf("Localizacao pretendida: ");
                getchar();
                gets(localizacao);
                verificaLocalizacao(meios, localizacao);
                menuprincipal();

            case 11:
                printf("Inserir cliente:\n");
                printf("ID: "),
                    scanf("%d", &idcli);
                printf("Nome: ");
                getchar(); // Clear the input buffer
                gets(nomecli);
                printf("Morada: "); // Clear the input buffer
                gets(morada);
                printf("Idade: ");
                scanf("%d", &idade);
                printf("NIF: ");
                scanf("%d", &nif);
                printf("Telemovel: ");
                scanf("%d", &telemovel);
                printf("Password: ");
                getchar(); // Clear the input buffer
                gets(passwordcli);
                clientes = inserirCliente(clientes, idcli, nomecli, morada, idade, nif, telemovel, passwordcli);
                guardarClientes(clientes);
                menuprincipal();

            case 12:
                printf("ID do cliente que pretende editar: ");
                scanf("%d", &idcli);
                editarCliente(clientes, idcli);
                guardarClientes(clientes);
                menuprincipal();

            case 13:
                printf("Lista de clientes existentes: \n");
                listarCliente(clientes);
                menuprincipal();

            case 14:
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
                printf("ID do cliente que pretende remover: ");
                scanf("%d", &idcli);
                removerCliente(clientes, idcli);
                guardarClientes(clientes);
                menuprincipal();

            case 16:
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
                printf("ID do gestor que pretende editar: ");
                scanf("%d", &idges);
                editarGestor(gestores, idges);
                guardarGestores(gestores);
                menuprincipal();

            case 18:
                printf("Lista de gestores existentes:\n");
                listarGestor(gestores);
                menuprincipal();

            case 19:
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
                printf("ID do gestor que pretende remover: ");
                scanf("%d", &idges);
                removerGestor(gestores, idges);
                guardarGestores(gestores);
                menuprincipal();

            default:
                printf("Selecione uma opcao valida !\n");
            }
            return 0;

        }
        else printf("Credenciais invalidas\n");
        break;
    }
    case 3: {
        printf("*************** CLIENTE ***************\n");
        printf("ID: "),
            scanf("%d", &id);
        printf("Nome: ");
        getchar(); // Clear the input buffer
        gets(nome);
        printf("Morada: ");
        getchar(); // Clear the input buffer
        gets(morada);
        printf("Idade: ");
        scanf("%d", &idade);
        printf("NIF: ");
        scanf("%d", &nif);
        printf("Telemovel: ");
        scanf("%d", &telemovel);
        printf("Password: ");
        getchar(); // Clear the input buffer
        gets(password);
        clientes = inserirCliente(clientes, id, nome, morada, idade, nif, telemovel, password);
        guardarClientes(clientes);
        menuprincipal();
    }
    case 4: {
        printf("*************** GESTOR ***************\n");
        printf("ID: ");
        scanf("%d", &id);
        printf("Nome: ");
        getchar(); // Clear the input buffer
        gets(nome);
        printf("NIF: ");
        scanf("%d", &nif);
        printf("Telemovel: ");
        scanf("%d", &telemovel);
        printf("Password: ");
        getchar(); // Clear the input buffer
        gets(password);
        gestores = inserirGestor(gestores, id, nome, nif, telemovel, password);
        guardarGestores(gestores);
        menuprincipal();
    }
    default: {
        printf("Selecione uma opcao valida !\n");
        menuprincipal();
    }
    }
}

/*
void menucliente()
{
    printf("***************  MENU CLIENTE ***************\n");
    printf("Selecione a opcao pretendida\n");
    printf("1 - Editar Conta\n");
    printf("2 - Listar meios\n");
    printf("3 - Listar meios disponiveis para aluguer\n");
    printf("4 - Listar meios por ordem decrescente de autonomia\n");
    printf("5 - Alugar meio\n");
    printf("6 - Desalugar meio\n");
    printf("7 - Remover conta\n");
    scanf("%d", &respostacli);

    switch (respostacli) {
    case 1:
        editarCliente(clientes, nome);
        break;

    case 2:
        listarMeios(meios);
        break;

    case 3:
        MeiosParaAlugar(meios);
        break;

    case 4:
        listarMeiosPorAutonomia(meios);
        break;

    case 5:
        AlugarMeios(meios);
        break;

    case 6:
        DesalugarMeios(meios);
        break;

    case 7:
        removerCliente(clientes, id);
        break;

    default:
        printf("Opção inválida.\n");
    }
    return 0;
}
*/

int main() {
    Cliente* clientes = NULL;
    Gestor* gestores = NULL;
    Meio* meios = NULL;

    int idmeio, carga, autonomia, aluguer;
    float custo;
    char tipodemobilidade[50],  localizacao[50];

    menuprincipal();
    
    

    //meios = lerMeios();
    //inserirMeio(meios, 4, "tipodemobilidade", 45, 50, 60.1, "localizacao", 0);
    //listarMeios(meios);
    //clientes = lerCliente();
    //clientes = inserirCliente(clientes, 1, "Tiago", "Rua das Flores", 18, 253793866, 938710984, "1234");
    //clientes = inserirCliente(clientes, 2, "Ferreira", "Rua das Flores", 18, 253793866, 938710984, "1234");
    //listarCliente(clientes);

    /*
    gestores = inserirGestor(gestores, 9, "tiago", 222, 222, "passs");
    gestores = inserirGestor(gestores, 19, "tiago", 222, 222, "passs");
    listarGestor(gestores);
    removerGestor(gestores, 9);
    listarGestor(gestores);

   
    listarMeios(meios);
    removerMeio(meios, 1);
    guardarMeios(meios);
    listarMeios(meios);
     //guardarClientes(clientes);
    //lerCliente();
    */
    //meios = inserirMeio(meios, 1, "tipodemobilidade", 45, 50, 60.1, "localizacao", 0);
    //listarMeios(meios);
    //guardarMeios(meios);
    //clientes = inserirCliente(clientes, 1, "Tiago", "Rua das Flores", 18, 253793866, 938710984, "1234");
    //clientes = inserirCliente(clientes, 2, "Ferreira", "Rua das Flores", 18, 253793866, 938710984, "1234");
    //listarCliente(clientes);
    //menuprincipal();

}