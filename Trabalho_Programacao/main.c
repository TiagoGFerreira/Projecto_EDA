#include <stdio.h>
#include "lib.h"
#define _CRT_SECURE_NO_WARNINGS

int main()
{
    char tipo, morada, password, nome;
    int id, carga, autonomia, idade, nif, telemovel;
    float custo;

    int resposta , respostaCLI , respostaGES;
	Meio* meios = NULL; // Lista ligada vazia 
	Cliente* clientes = NULL;
    Gestor* gestores = NULL;

    /*
    printf("***************  MENU ***************");
    printf("Selecione o tipo de utilizador\n");
    printf("1 - Cliente\n");
    printf("2 - Gestor\n");
    scanf("%d", &resposta);


    switch (resposta) {
    case 1: {
        printf("***************  MENU ***************");
        printf("Escolha o que deseja fazer\n");
        printf("1 - Criar utilizador\n");
        printf("2 - Alugar meio de mobilidadade\n");
        printf("3 - Vizualizar meios de mobilidade ja alugados\n");
        printf("4 - Verificar existencia de alguer por id\n");
        printf("5 - Remover sua conta\n");
        scanf("%d", &respostaCLI);
        switch (respostaCLI) {
        case 1: {
            printf("Nome:\n");
            scanf("%s", &nome);
            printf("Morada:\n");
            scanf("%s", &morada);
            printf("Idade:\n");
            scanf("%d", &idade);
            printf("NIF:\n");
            scanf("%d", &nif);
            printf("Telemovel:\n");
            scanf("%d", &telemovel);
            printf("Password:\n");
            scanf("%s", &password);
            clientes = inserirCliente(clientes, nome, morada, idade, nif, telemovel, password);
            break;
        }
        case 2: {
            char tipo, morada, password;
            int id, carga, autonomia;
            float custo;
            printf("ID:\n");
            scanf("%d", &id);
            printf("Tipo de Mobilidade:\n");
            scanf("%s", &tipo);
            printf("Carga:\n");
            scanf("%d", &carga);
            printf("Autonomia:\n");
            scanf("%d", &autonomia);
            printf("Custo:\n");
            scanf("%.2f", &custo);
            meios = inserirMeio(meios, id, tipo, carga, autonomia, custo);
            break;
        }
        case 3: {
            listarMeios(meios);
            break;
        }
        case 4: {
            int id;
            printf("Digite o ID do aluguer:\n");
            scanf("%d", &id);
            if (existeMeio(meios, id)) {
                printf("O aluguer numero %d existe\n",id);
            }
            else {
                printf("O aluguer numero %d nao existe\n",id);
            }
            break;
        }
        case 5: {
            Cliente* removerCliente(Cliente * inicio, char nome);
        }
        default:
            printf("Selecione uma opcao valida !\n");
        }
        return 0;
        break;
    }
    case 2: {
        printf("***************  MENU ***************");
        printf("Escolha o que deseja fazer\n");
        printf("1 - Cliente\n");
        printf("2 - Gestor\n");
        scanf("%d", &resposta);
        break;
    }
    case 3: {
        break;
    }
    default:
        printf("Selecione uma opcao valida !\n");
    }
    return 0;

    */
    meios = inserirMeio(meios, 1, "trotinete", 67, 87, 31.31);
    meios = inserirMeio(meios, 2, "bicicleta", 100, 47, 14);
	listarMeios(meios);
    listarMeiosPorAutonomia(meios);
    //guardarMeios(meios);

    //editarMeios(meios, 1);
    
    //clientes = inserirCliente(clientes, "Tiago", "Rua das Flores", 18, 253793866, 938710984, "1234");
    //editarCliente(clientes, "Tiago");
    //listarCliente(clientes);


    // gestores = inserirGestor(gestores, "Tiago Ferreira", "253793866", "1234");
     //listarGestor(gestores);
    //editarGestor(gestores, "Tiago Ferreira");
   // listarGestor(gestores);


    //meios = removerMeio(meios, 1);
    //if (existeMeio(meios, 1)) printf("Meio 4 existe\n");
    //else printf("Meio 4 nao existe\n");



    
	//clientes = inserirCliente(clientes, "Tiago","Rua Senhora da Guia",18, 253793866, 938710984, "tiago4567");
    //guardarClientes(clientes);
    //listarCliente(clientes);

    //gestores = inserirGestor(gestores, "Diogo", 253793866, "tiago4567");
    //guardarGestores(gestores);
    //listarGestor(gestores);

	//listarCliente(clientes);
	//return(0);
    
}
    