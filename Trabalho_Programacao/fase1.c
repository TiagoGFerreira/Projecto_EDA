#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "lib.h"


//Insere um novo meio de mobilidade 
Meio* inserirMeio(Meio* inicio, int id, char tipo[], int carga, int autonomia, float custo, char localizacao[], int aluguer) {
    //Verifica se o meu já existe , se já existir retorna-se o pointer inicio sem nenhuma nova inserção
    if (!existeMeio(inicio, id)) {
        Meio* novo = malloc(sizeof(struct registoMeio)); //cria uma nova struct para ser inserido novos dados
        if (novo != NULL) {
            novo->id = id;
            strcpy(novo->tipodemobilidade, tipo);
            novo->carga = carga;
            novo->autonomia = autonomia;
            novo->custo = custo;
            strcpy(novo->localizacao, localizacao);
            novo->aluguer = aluguer;
            novo->seguinte = inicio;
            inicio = novo; //atualiza o pointer inicio com os novos dados
        }
    }
    return inicio;
}

//Verifica se o id já existe na lista ligada
int existeMeio(Meio* inicio, int id) {
    while (inicio != NULL) {
        //Percorre a lista toda , se encontrar um id igual retorna 1 , senão retorna 0
        if (inicio->id == id) return (1);
        inicio = inicio->seguinte;
    }
    return (0);
}

//Remove um meio de mobilidade com um determidado id da lista ligada
Meio* removerMeio(Meio* inicio, int id) {
    Meio* anterior = inicio, * atual = inicio, * aux;

    if (atual == NULL) return (NULL); //se a lista estiver vazia retorna NULL 
    else if (atual->id == id) {
        //se o primeiro id da lista for o pretendido para remover entra neste if
        aux = atual->seguinte; //aux passa a ser o segundo registo da lista
        free(atual); //liberta o espaço de memória alocado do atual
        return (aux); // retorna o inicio da lista
    }
    else {
        while ((atual != NULL) && (atual->id != id)) {
            //percorre a lista até o id ser igual e vai atualizando os pointers
            anterior = atual;
            atual = atual->seguinte;
        }
        if (atual == NULL) return (inicio); //se percorrer a lista toda e não encontrar retorna o inicio
        else {
            //caso encontre o registo anterior é apontado para ser o seguinte
            anterior->seguinte = atual->seguinte;
            free(atual); //liberta o espaço de memória alocado do atual
            return (inicio); //retorna o inicio ,já com o registo removido
        }
    }
}

//Lê as informações do ficheiro meios.txt e insere na lista ligada Meios
Meio* lerMeios() {
    FILE* fp;
    int id, carga, autonomia, aluguer;
    float custo;
    char tipodemobilidade[50], localizacao[50];
    Meio* aux = NULL;
    fp = fopen("meios.txt", "r"); //Ler o ficheiro meios.txt
    if (fp != NULL) {
        while (!feof(fp)) {
            //percorre até ao final do ficheiro
            fscanf(fp, "%d;%[^;];%d;%d;%f;%[^;];%d\n", &id, tipodemobilidade, &carga, &autonomia, &custo, localizacao, &aluguer);
            //guarda todas as informações da linha em variaveis
            aux = inserirMeio(aux, id, tipodemobilidade, carga, autonomia, custo, localizacao, aluguer);
            //Insere um novo meio na lista ligada
        }
        fclose(fp); //fecha o ficheiro
    }
    return (aux);
    //retorna o pointer para o inicio da lista
}

//Lista todos os elementos da lista ligada
void listarMeios(Meio* inicio) {
    while (inicio != NULL) {
        //senão for null percorre toda a lista
        printf("%d ; %s ; %d ; %d ; %.2f ; %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
        //imprime o registo e o pointer inicio passa para o elemento seguinte
        inicio = inicio->seguinte;
    }
}

//Lista todos os meios disponiveis para alugar
void MeiosParaAlugar(Meio* inicio) {
    int meiosDisponiveis = 0;
    while (inicio != NULL) {
        //Percorre a lista toda e imprime os meios em que a variavel aluguer = 0
        printf("Meios Disponiveis:\n");
        if (inicio->aluguer == 0) {
            printf("%d ; %s ; %d ; %d ; %.2f ; %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
            meiosDisponiveis++;
        }
        inicio = inicio->seguinte;
    }

    if (meiosDisponiveis == 0) {
        //caso a variavel meiosDisponiveis seja = 0 , significa que não há meios disponiveis para alugar
        printf("Nao existem meios disponiveis para alugar\n");
    }
}

//Aluga um meio em que a variavel aluguer é igual 0
void AlugarMeios(struct registoMeio* lista, int id) {
    struct registoMeio* atual = lista;
    FILE* fp;
    fp = fopen("registosAluguer.txt", "a"); //é aberto o ficheiro registoAluguer.txt para ser acrescentado coisas

    while (atual != NULL && atual->id != id) {
        //percorre a lista até o id ser igual , senão igual o pointeiro passa para o elemento seguinte
        atual = atual->seguinte;
    }
    if (atual != NULL && atual->aluguer == 0) {
        //assim que encontra o id , verifica se a variavel aluguer é igual a 0 , se for entra neste if e é alterada para 1
        atual->aluguer = 1;
        printf("O tipo de mobilidade com o id %d foi alugado com sucesso\n", id);
        if (fp != NULL) {
            //No ficheiro é registado que foi alugado o meio
            fprintf(fp, "O meio com id - %d foi alugado\n", id);
            fclose(fp);
        }
    }
    else if (atual != NULL && atual->aluguer == 1) {
        //se for encontro id mas a variavel aluguer já estiver a 1 , é imprimido uma mensagem que já está alugado
        printf("O tipo de mobilidade com o id %d ja esta alugado\n", id);
    }
    else {
        printf("O tipo de mobilidade com o id %d nao existe\n", id);
    }

}

//Desaluga um meio em que a variavel aluguer é igual a 1
void DesalugarMeios(struct registoMeio* lista, int id) {
    struct registoMeio* atual = lista;
    FILE* fp;
    fp = fopen("registosAluguer.txt", "a"); //é aberto o ficheiro registoAluguer.txt para ser acrescentado coisas
    while (atual != NULL && atual->id != id) {
        atual = atual->seguinte;
    }
    if (atual != NULL && atual->aluguer == 1) {
        // assim que encontra o id, verifica se a variavel aluguer é igual a 1, se for entra neste if e é alterada para 0
        atual->aluguer = 0;
        if (fp != NULL) {
            fprintf(fp, "O meio com id - %d foi desalugado\n", id);
            fclose(fp);

        }
        printf("O tipo de mobilidade com o id %d foi desalugado com sucesso\n", id);
    }
    else if (atual != NULL && atual->aluguer == 0) {
        //se for encontro id mas a variavel aluguer já estiver a 1 , é imprimido uma mensagem que já está desalugado
        printf("O tipo de mobilidade com o id %d ja esta desalugado\n", id);
    }
    else {
        printf("O tipo de mobilidade com o id %d nao existe\n", id);
    }
}

//Edita o meio , alterando e atualizando os dados existentes na memória
void editarMeios(struct registoMeio* lista, int id) {
    struct registoMeio* atual = lista;
    while (atual != NULL) {
        //caso a lista não seja nula é pedido os dados para atualizar e esses dados são atualizados na memória
        if (atual->id == id) {
            printf("Digite os novos dados para o ID - %d:\n", id);
            printf("Tipo de Mobilidade: ");
            getchar();
            gets(atual->tipodemobilidade);
            printf("Carga: ");
            scanf("%d", &atual->carga);
            printf("Autonomia: ");
            scanf("%d", &atual->autonomia);
            printf("Custo: ");
            scanf("%f", &atual->custo);
            printf("Localizacao: ");
            getchar();
            gets(atual->localizacao);
            printf("Dados atualizados com sucesso!\n");
            return;
        }
        //o pointer de inicio vai ser igual ao pointer do elemento seguinte
        atual = atual->seguinte;
    }
    printf("O ID - %d nao foi encontrado na lista.\n", id);
}

//Guarda todos os elementos da lista ligada no ficheiro meios.txt
void guardarMeios(Meio* inicio) {
    FILE* fp;
    fp = fopen("meios.txt", "w"); //abrir o ficheiro para escrever por cima do que já existe
    if (fp != NULL) {
        Meio* aux = inicio;
        while (aux != NULL) {
            //caso a lista não seja nula imprime no ficheiro as informações do primeiro elemento da lista e o pointer passa para o segundo
            fprintf(fp, "%d;%s;%d;%d;%.2f;%s;%d\n", aux->id, aux->tipodemobilidade, aux->carga, aux->autonomia, aux->custo, aux->localizacao, aux->aluguer);
            aux = aux->seguinte;
        }

        fclose(fp);
        printf("As informacoes foram guardadas no ficheiro %s\n", "meios.txt");
    }
}

//Lê as informações do ficheiro clientes.txt e insere na lista ligada Cliente
Cliente* lerCliente() {
    FILE* fp;
    int id, idade, contribuinte, tele;
    char nome[50], morada[50], pass[50];
    float saldo;
    Cliente* aux = NULL;
    fp = fopen("clientes.txt", "r"); //Ler o ficheiro clientes.txt
    if (fp != NULL) {
        while (!feof(fp)) {
            //percorre até ao final do ficheiro
            fscanf(fp, "%d;%[^;];%[^;];%d;%d;%d;%f;%[^;\n]", &id, nome, morada, &idade, &contribuinte, &tele, &saldo, pass);
            //guarda todas as informações da linha em variaveis
            aux = inserirCliente(aux, id, nome, morada, idade, contribuinte, tele, saldo, pass);
            //Insere um novo meio na lista ligada
        }
        fclose(fp); //fecha o ficheiro
    }
    return (aux);
    //retorna o pointer para o inicio da lista
}

//Insere um novo cliente 
Cliente* inserirCliente(Cliente* inicio, int id, char nome[], char mor[], int ida, int contribuinte, int tele, float saldo, char pass[]) {
    //Verifica se o cliente já existe , se já existir retorna-se o pointer inicio sem nenhuma nova inserção
    if (!existeCliente(inicio, id)) {
        Cliente* novo = malloc(sizeof(struct registoCliente)); //cria uma nova struct para ser inserido novos dados
        if (novo != NULL) {
            novo->id = id;
            strcpy(novo->nome, nome);
            strcpy(novo->morada, mor);
            novo->idade = ida;
            novo->nif = contribuinte;
            novo->telemovel = tele;
            novo->saldo = saldo;
            strcpy(novo->password, pass);
            novo->seguinte = inicio;
            return (novo); //atualiza o pointer inicio com os novos dados

        }
    }
    else return (inicio);
}

//Verifica se as credenciais do cliente são válidas
int verificaCliente(Cliente* inicio, int id, char nome[], char password[]) {
    Cliente* atual = inicio;

    while (atual != NULL) {
        if (atual->id == id) {
            //Se a lista não for nula , percorre a lista até encontrar o id e compara
            if (strcmp(atual->nome, nome) == 0) {
                if (strcmp(atual->password, password) == 0) {
                    //Depois é comparada as duas strings nome e password , se for igual a 0 , ou seja iguais , a função retorna 1
                    return 1;
                }
            }
        }
        //caso não tenha encontrado o id ,o pointer passa para o elemento seguinte
        atual = atual->seguinte;
    }
}

//Verifica se o id já existe na lista ligada
int existeCliente(Cliente* inicio, int id) {
    while (inicio != NULL) {
        //Percorre a lista toda , se encontrar um id igual retorna 1 , senão retorna 0
        if (inicio->id == id) return (1);
        inicio = inicio->seguinte;
    }
    return (0);
}

//Remove um cliente com um determidado id da lista ligada
Cliente* removerCliente(Cliente* inicio, int id) {
    Cliente* anterior = inicio, * atual = inicio, * aux;

    if (atual == NULL) return (NULL); //se a lista estiver vazia retorna NULL 
    else if (atual->id == id) {
        //se o primeiro id da lista for o pretendido para remover entra neste if
        aux = atual->seguinte; //aux passa a ser o segundo registo da lista
        free(atual); //liberta o espaço de memória alocado do atual
        return (aux); // retorna o inicio da lista
    }
    else {
        while ((atual != NULL) && (atual->id != id)) {
            //percorre a lista até o id ser igual e vai atualizando os pointers
            anterior = atual;
            atual = atual->seguinte;
        }
        if (atual == NULL) return (inicio); //se percorrer a lista toda e não encontrar retorna o inicio
        else {
            //se percorrer a lista toda e não encontrar retorna o inicio
            anterior->seguinte = atual->seguinte;
            free(atual); //liberta o espaço de memória alocado do atual
            return (inicio); //retorna o inicio ,já com o registo removido
        }
    }
}

//Lista todos os elementos da lista ligada
void listarCliente(Cliente* inicio) {
    while (inicio != NULL) {
        //senão for null percorre toda a lista
        printf("%d ; %s ; %s ; %d ; %d ; %d ; %.2f ; %s\n", inicio->id, inicio->nome, inicio->morada, inicio->idade, inicio->nif, inicio->telemovel, inicio->saldo, inicio->password);
        //imprime o registo e o pointer inicio passa para o elemento seguinte
        inicio = inicio->seguinte;
    }
}

//Edita o cliente , alterando e atualizando os dados existentes na memória
void editarCliente(struct registoCliente* lista, int id) {
    struct registoCliente* atual = lista;
    while (atual != NULL) {
        //caso a lista não seja nula é pedido os dados para atualizar e esses dados são atualizados na memória
        if (atual->id == id) {
            printf("Digite os novos dados para o Cliente %s:\n", atual->nome);
            printf("Nome: ");
            getchar(); // Clear the input buffer
            gets(atual->nome);
            printf("Morada: ");
            gets(atual->morada);
            printf("Idade: ");
            scanf("%d", &atual->idade);
            printf("NIF: ");
            scanf("%d", &atual->nif);
            printf("Telemovel: ");
            scanf("%d", &atual->telemovel);
            printf("Saldo: ");
            scanf("%.2f", &atual->saldo);
            getchar();
            printf("Password: ");
            gets(atual->password);
            printf("Dados atualizados com sucesso!\n");
            return;
        }
        //o pointer de inicio vai ser igual ao pointer do elemento seguinte
        atual = atual->seguinte;
    }
    printf("O nome %s nao foi encontrado na lista.\n", atual->nome);
}

//Guarda todos os elementos da lista ligada no ficheiro clientes.txt
void guardarClientes(Cliente* inicio) {
    FILE* arquivo = fopen("clientes.txt", "w"); //abrir o ficheiro para escrever por cima do que já existe
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", "clientes.txt");
        return;
    }

    Cliente* atual = inicio;
    while (atual != NULL) {
        //caso a lista não seja nula imprime no ficheiro as informações do primeiro elemento da lista e o pointer passa para o segundo
        fprintf(arquivo, "%d;%s;%s;%d;%d;%d;%.2f;%s\n", atual->id, atual->nome, atual->morada, atual->idade, atual->nif, atual->telemovel, atual->saldo, atual->password);
        atual = atual->seguinte;
    }

    fclose(arquivo);
    printf("As informacoes foram guardadas no ficheiro %s\n", "clientes.txt");
}

Gestor* inserirGestor(Gestor* inicio, int id, char nome[], int contribuinte, int tele, char password[]) {
    if (!existeGestor(inicio, id)) {
        Gestor* novo = malloc(sizeof(struct registoGestor));
        if (novo != NULL) {
            novo->id = id;
            strcpy(novo->nome, nome);
            novo->nif = contribuinte;
            novo->telemovel = tele;
            strcpy(novo->password, password);
            novo->seguinte = inicio;
            return (novo);
        }
    }
    else return (inicio);
}

//Lê as informações do ficheiro gestores.txt e insere na lista ligada Gestor
Gestor* lerGestor() {
    FILE* fp;
    int id, contribuinte, tele;
    char nome[50], pass[50];
    Gestor* aux = NULL;
    fp = fopen("gestores.txt", "r"); //Ler o ficheiro clientes.txt
    if (fp != NULL) {
        while (!feof(fp)) {
            //percorre até ao final do ficheiro
            fscanf(fp, "%d;%[^;];%d;%d;%[^;\n]", &id, nome, &contribuinte, &tele, pass);
            //guarda todas as informações da linha em variaveis
            aux = inserirGestor(aux, id, nome, contribuinte, tele, pass);
            //Insere um novo meio na lista ligada
        }
        fclose(fp); //fecha o ficheiro
    }
    return (aux);
    //retorna o pointer para o inicio da lista
}

//Verifica se o id já existe na lista ligada
int existeGestor(Gestor* inicio, int id) {
    while (inicio != NULL) {
        //Percorre a lista toda , se encontrar um id igual retorna 1 , senão retorn 0
        if (inicio->id == id) return (1);
        inicio = inicio->seguinte;
    }
    return (0);
}

//Remove um gestor com um determidado id da lista ligada
Gestor* removerGestor(Gestor* inicio, int id) {
    Gestor* anterior = inicio, * atual = inicio, * aux;

    if (atual == NULL) return (NULL); //se a lista estiver vazia retorna NULL 
    else if (atual->id == id) {
        //se o primeiro id da lista for o pretendido para remover entra neste if
        aux = atual->seguinte; //aux passa a ser o segundo registo da lista
        free(atual); //liberta o espaço de memória alocado do atual
        return (aux); // retorna o inicio da lista
    }
    else {
        while ((atual != NULL) && (atual->id != id)) {
            //percorre a lista até o id ser igual e vai atualizando os pointers
            anterior = atual;
            atual = atual->seguinte;
        }
        if (atual == NULL) return (inicio); //se percorrer a lista toda e não encontrar retorna o inicio
        else {
            //caso encontre o registo anterior é apontado para ser o seguinte
            anterior->seguinte = atual->seguinte;
            free(atual); //liberta o espaço de memória alocado do atual
            return (inicio); //retorna o inicio ,já com o registo removido
        }
    }
}

//Lista todos os elementos da lista ligada
void listarGestor(Gestor* inicio) {
    while (inicio != NULL) {
        //senão for null percorre toda a lista
        printf("%d ; %s ; %d ; %d ; %s\n", inicio->id, inicio->nome, inicio->nif, inicio->telemovel, inicio->password);
        //imprime o registo e o pointer inicio passa para o elemento seguinte
        inicio = inicio->seguinte;
    }
}

//Edita o gestor , alterando e atualizando os dados existentes na memória
void editarGestor(struct registoGestor* lista, int id) {
    struct registoGestor* atual = lista;
    while (atual != NULL) {
        //caso a lista não seja nula é pedido os dados para atualizar e esses dados são atualizados na memória
        if (atual->id == id) {
            printf("Digite os novos dados para o Gestor %s:\n", atual->nome);
            printf("Nome: ");
            getchar();
            gets(atual->nome);;
            printf("Telemovel: ");
            scanf("%d", &atual->telemovel);
            printf("NIF: ");
            scanf("%d", &atual->nif);
            printf("Password: ");
            getchar();
            gets(atual->password);
            printf("Dados atualizados com sucesso!\n");
            return;
        }
        //o pointer de inicio vai ser igual ao pointer do elemento seguinte
        atual = atual->seguinte;
    }
    printf("O Gestor %s nao foi encontrado na lista.\n", atual->nome);
}

//Guarda todos os elementos da lista ligada no ficheiro gestores.txt
void guardarGestores(Gestor* inicio) {
    FILE* arquivo = fopen("gestores.txt", "w"); //abrir o ficheiro para escrever por cima do que já existe
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", "gestores.txt");
        return;
    }

    Gestor* atual = inicio;
    while (atual != NULL) {
        //caso a lista não seja nula imprime no ficheiro as informações do primeiro elemento da lista e o pointer passa para o segundo
        fprintf(arquivo, "%d;%s;%d;%d;%s\n", atual->id, atual->nome, atual->nif, atual->telemovel, atual->password);
        atual = atual->seguinte;
    }

    fclose(arquivo);
    printf("As informacoes foram guardadas no ficheiro %s\n", "gestores.txt");
}

//Verifica se as credenciais do gestor são válidas
int verificaGestor(Gestor* inicio, int id, char nome[], char pass[]) {

    Gestor* atual = inicio;
    while (atual != NULL) {
        if (atual->id == id) {
            //Se a lista não for nula , percorre a lista até encontrar o id e compara
            if (strcmp(atual->nome, nome) == 0) {
                if (strcmp(atual->password, pass) == 0) {
                    //Depois é comparada as duas strings nome e password , se for igual a 0 , ou seja iguais , a função retorna 1
                    return 1;
                }
            }
        }
        //caso não tenha encontrado o id ,o pointer passa para o elemento seguinte
        atual = atual->seguinte;
    }
}

//Imprime os meios de mobilidade por ordem decrescente de autonomia
void listarMeiosPorAutonomia(Meio* inicio) {
    Meio* ponteiro1 = NULL; //pointer para o inicio da lista
    Meio* ponteiro2 = NULL; // pointer para o fim da lista
    Meio* temp = NULL;
    Meio* anterior = NULL; // pointer para o elemento anterior ao atual
    int trocas;

    do {
        //do while só para quando trocar = 0 , ou seja não houver mais trocas
        trocas = 0;
        ponteiro1 = inicio;

        while (ponteiro1->seguinte != ponteiro2) {
            //percorre a lista a toda até que o pointer 1 chegue ao elemento anterior ao final , pointeiro 2
            if (ponteiro1->autonomia < ponteiro1->seguinte->autonomia) {
                //se o elemento seguinte tiver autonomia maior que o atual entra no if
                temp = ponteiro1->seguinte; // armazena o pointer do proximo elemento da lista
                ponteiro1->seguinte = temp->seguinte; // atualiza o pointer atual para o proximo elemento apontado para o proximo elemento do temp
                temp->seguinte = ponteiro1; // o proximo elemento do pointer temp passa a ser o atual , trocando assim a posição dos dois
                if (ponteiro1 == inicio) {
                    //verifica se o pointer 1 é o primeiro da lista 
                    inicio = temp; // o inicio da lista é apontado para pointer temporario
                }
                else {
                    anterior->seguinte = temp; // caso o pointer 1 não seja o primeiro da lista ,  atualiza o pointer para o próximo do elemento anterior da lista
                }
                anterior = temp; // o elemento anterior passa a ser o pointer temporario
                trocas = 1;
            }
            else {
                //caso não haja troca o pointer 1 passa para o seguinte elemento
                ponteiro1 = ponteiro1->seguinte;
            }
        }

        ponteiro2 = ponteiro1; //o pointer 2 ou seja ultimo , é atualizado para ser o atual que estava na comparação
    } while (trocas);

    printf("Lista de meios de mobilidade eletrica por ordem decrescente de autonomia:\n");
    while (inicio != NULL) {
        printf("%d ; %s ; %d ; %d ; %.2f ; %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
        inicio = inicio->seguinte;

    }
}

//Se houver alguma localização igual á do utilizador é imprimido as infos desse meio
void verificaLocalizacao(Meio* inicio, char localizacao[]) {
    printf("Meios com a mesma localizacao:\n");
    while (inicio != NULL) {
        //Percorre a lista e compara com cada elemento a string localização com a do utilizador
        if (strcmp(inicio->localizacao, localizacao) == 0) {
            printf("%d ; %s ; %d ; %d ; %.2f ; %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
        }
        //depois de comparar o primeiro elemento o pointer passa para o elemento seguinte
        inicio = inicio->seguinte;
    }
}