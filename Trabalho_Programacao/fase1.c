
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include "lib.h"

//Insere um novo meio de mobilidade 
Meio* inserirMeio(Meio* inicio, int id, char tipo[], int carga, int autonomia, float custo, char localizacao[], int aluguer)
{
	//Verifica se o meu j� existe, se j� existir retorna-se o pointer inicio sem nenhuma nova inser��o
	if (!existeMeio(inicio, id))
	{
		Meio* novo = malloc(sizeof(struct registoMeio));	//cria uma nova struct para ser inserido novos dados
		if (novo != NULL)
		{
			novo->id = id;
			strcpy(novo->tipodemobilidade, tipo);
			novo->carga = carga;
			novo->autonomia = autonomia;
			novo->custo = custo;
			strcpy(novo->localizacao, localizacao);
			novo->aluguer = aluguer;
			novo->seguinte = inicio;
			inicio = novo;	//atualiza o pointer inicio com os novos dados
		}
	}

	return inicio;
}

//Verifica se o id j� existe na lista ligada
int existeMeio(Meio* inicio, int id)
{
	while (inicio != NULL)
	{
		//Percorre a lista toda, se encontrar um id igual retorna 1, sen�o retorna 0
		if (inicio->id == id) return (1);
		inicio = inicio->seguinte;
	}

	return (0);
}

//Remove um meio de mobilidade com um determidado id da lista ligada
Meio* removerMeio(Meio* inicio, int id)
{
	Meio* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return (NULL);	//se a lista estiver vazia retorna NULL 
	else if (atual->id == id)
	{
		//se o primeiro id da lista for o pretendido para remover entra neste if
		aux = atual->seguinte;	//aux passa a ser o segundo registo da lista
		free(atual);	//liberta o espa�o de mem�ria alocado do atual
		return (aux);	// retorna o inicio da lista
	}
	else
	{
		while ((atual != NULL) && (atual->id != id))
		{
			//percorre a lista at� o id ser igual e vai atualizando os pointers
			anterior = atual;
			atual = atual->seguinte;
		}

		if (atual == NULL) return (inicio);	//se percorrer a lista toda e n�o encontrar retorna o inicio
		else
		{
			//caso encontre o registo anterior � apontado para ser o seguinte
			anterior->seguinte = atual->seguinte;
			free(atual);	//liberta o espa�o de mem�ria alocado do atual
			return (inicio);	//retorna o inicio ,j� com o registo removido
		}
	}
}

//L� as informa��es do ficheiro meios.txt e insere na lista ligada Meios
Meio* lerMeios()
{
	FILE* fp;
	int id, carga, autonomia, aluguer;
	float custo;
	char tipodemobilidade[50], localizacao[50];
	Meio* aux = NULL;
	fp = fopen("meios.txt", "r");	//Ler o ficheiro meios.txt
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			//percorre at� ao final do ficheiro
			fscanf(fp, "%d;%[^;];%d;%d;%f;%[^;];%d\n", &id, tipodemobilidade, &carga, &autonomia, &custo, localizacao, &aluguer);
			//guarda todas as informa��es da linha em variaveis
			aux = inserirMeio(aux, id, tipodemobilidade, carga, autonomia, custo, localizacao, aluguer);
			//Insere um novo meio na lista ligada
		}

		fclose(fp);	//fecha o ficheiro
	}

	return (aux);
	//retorna o pointer para o inicio da lista
}

//Lista todos os elementos da lista ligada
void listarMeios(Meio* inicio)
{
	while (inicio != NULL)
	{
		//sen�o for null percorre toda a lista
		printf("%d ; %s ; %d ; %d ; %.2f ; %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
		//imprime o registo e o pointer inicio passa para o elemento seguinte
		inicio = inicio->seguinte;
	}
}

//Lista todos os meios disponiveis para alugar
void MeiosParaAlugar(Meio* inicio)
{
	int meiosDisponiveis = 0;
	while (inicio != NULL)
	{
		//Percorre a lista toda e imprime os meios em que a variavel aluguer = 0
		if (inicio->aluguer == 0)
		{
			printf("%d ; %s ; %d ; %d ; %.2f ; %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
			meiosDisponiveis++;
		}

		inicio = inicio->seguinte;
	}

	if (meiosDisponiveis == 0)
	{
		//caso a variavel meiosDisponiveis seja = 0, significa que n�o h� meios disponiveis para alugar
		printf("Nao existem meios disponiveis para alugar\n");
	}
}

//Aluga um meio em que a variavel aluguer � igual 0
void AlugarMeios(struct registoMeio* lista, int id)
{
	struct registoMeio* atual = lista;
	FILE* fp;
	fp = fopen("registosAluguer.txt", "a");	//� aberto o ficheiro registoAluguer.txt para ser acrescentado coisas
	char data_str[50];
	setlocale(LC_TIME, "pt_PT.UTF-8");
	time_t tempo_atual = time(NULL);
	struct tm* data_hora = localtime(&tempo_atual);
	strftime(data_str, 50, "%d de %B de %Y - %H:%M:%S", data_hora);

	while (atual != NULL && atual->id != id)
	{
		//percorre a lista at� o id ser igual, sen�o igual o pointeiro passa para o elemento seguinte
		atual = atual->seguinte;
	}

	if (atual != NULL && atual->aluguer == 0)
	{
		//assim que encontra o id, verifica se a variavel aluguer � igual a 0, se for entra neste if e � alterada para 1
		atual->aluguer = 1;
		printf("O tipo de mobilidade com o id %d foi alugado com sucesso\n", id);
		if (fp != NULL)
		{
			//No ficheiro � registado que foi alugado o meio
			fprintf(fp, "%s - ", data_str);
			fprintf(fp, "O meio com id - %d foi alugado\n", id);
			fclose(fp);
		}
	}
	else if (atual != NULL && atual->aluguer == 1)
	{
		//se for encontro id mas a variavel aluguer j� estiver a 1, � imprimido uma mensagem que j� est� alugado
		printf("O tipo de mobilidade com o id %d ja esta alugado\n", id);
	}
	else if (atual != NULL && atual->aluguer == -1)
	{
		//se for encontro id mas a variavel aluguer j� estiver a 1, � imprimido uma mensagem que j� est� alugado
		printf("O tipo de mobilidade com o id %d esta indisponivel\n", id);
	}
	else
	{
		printf("O tipo de mobilidade com o id %d nao existe\n", id);
	}
}

//Desaluga um meio em que a variavel aluguer � igual a 1
void DesalugarMeios(struct registoMeio* lista, int id)
{
	struct registoMeio* atual = lista;
	FILE* fp;
	fp = fopen("registosAluguer.txt", "a");	//� aberto o ficheiro registoAluguer.txt para ser acrescentado coisas
	char data_str[50];
	setlocale(LC_TIME, "pt_PT.UTF-8");
	time_t tempo_atual = time(NULL);
	struct tm* data_hora = localtime(&tempo_atual);

	strftime(data_str, 50, "%d de %B de %Y - %H:%M:%S", data_hora);
	while (atual != NULL && atual->id != id)
	{
		atual = atual->seguinte;
	}

	if (atual != NULL && atual->aluguer == 1)
	{
		// assim que encontra o id, verifica se a variavel aluguer � igual a 1, se for entra neste if e � alterada para 0
		atual->aluguer = 0;
		if (fp != NULL)
		{
			fprintf(fp, "%s - ", data_str);
			fprintf(fp, "O meio com id - %d foi desalugado\n", id);
			fclose(fp);
		}

		printf("O tipo de mobilidade com o id %d foi desalugado com sucesso\n", id);
	}
	else if (atual != NULL && atual->aluguer == 0)
	{
		//se for encontro id mas a variavel aluguer j� estiver a 1, � imprimido uma mensagem que j� est� desalugado
		printf("O tipo de mobilidade com o id %d ja esta desalugado\n", id);
	}
	else if (atual != NULL && atual->aluguer == -1)
	{
		//se for encontro id mas a variavel aluguer j� estiver a 1, � imprimido uma mensagem que j� est� alugado
		printf("O tipo de mobilidade com o id %d esta indisponivel\n", id);
	}
	else
	{
		printf("O tipo de mobilidade com o id %d nao existe\n", id);
	}
}

//Edita o meio, alterando e atualizando os dados existentes na mem�ria
void editarMeios(struct registoMeio* lista, int id)
{
	struct registoMeio* atual = lista;
	while (atual != NULL)
	{
		//caso a lista n�o seja nula � pedido os dados para atualizar e esses dados s�o atualizados na mem�ria
		if (atual->id == id)
		{
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
void guardarMeios(Meio* inicio)
{
	FILE* fp;
	fp = fopen("meios.txt", "w");	//abrir o ficheiro para escrever por cima do que j� existe
	if (fp != NULL)
	{
		Meio* aux = inicio;
		while (aux != NULL)
		{
			//caso a lista n�o seja nula imprime no ficheiro as informa��es do primeiro elemento da lista e o pointer passa para o segundo
			fprintf(fp, "%d;%s;%d;%d;%.2f;%s;%d\n", aux->id, aux->tipodemobilidade, aux->carga, aux->autonomia, aux->custo, aux->localizacao, aux->aluguer);
			aux = aux->seguinte;
		}

		fclose(fp);
		printf("As informacoes foram guardadas no ficheiro %s\n", "meios.txt");
	}
}

//L� as informa��es do ficheiro clientes.txt e insere na lista ligada Cliente
Cliente* lerCliente()
{
	FILE* fp;
	int id, idade, contribuinte, tele;
	char nome[50], morada[50], pass[50];
	float saldo;
	Cliente* aux = NULL;
	fp = fopen("clientes.txt", "r");	//Ler o ficheiro clientes.txt
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			//percorre at� ao final do ficheiro
			fscanf(fp, "%d;%[^;];%[^;];%d;%d;%d;%f;%[^;\n]", &id, nome, morada, &idade, &contribuinte, &tele, &saldo, pass);
			//guarda todas as informa��es da linha em variaveis
			aux = inserirCliente(aux, id, nome, morada, idade, contribuinte, tele, saldo, pass);
			//Insere um novo meio na lista ligada
		}

		fclose(fp);	//fecha o ficheiro
	}

	return (aux);
	//retorna o pointer para o inicio da lista
}

//Insere um novo cliente 
Cliente* inserirCliente(Cliente* inicio, int id, char nome[], char mor[], int ida, int contribuinte, int tele, float saldo, char pass[])
{
	//Verifica se o cliente j� existe, se j� existir retorna-se o pointer inicio sem nenhuma nova inser��o
	if (!existeCliente(inicio, id))
	{
		Cliente* novo = malloc(sizeof(struct registoCliente));	//cria uma nova struct para ser inserido novos dados
		if (novo != NULL)
		{
			novo->id = id;
			strcpy(novo->nome, nome);
			strcpy(novo->morada, mor);
			novo->idade = ida;
			novo->nif = contribuinte;
			novo->telemovel = tele;
			novo->saldo = saldo;
			strcpy(novo->password, pass);
			novo->seguinte = inicio;
			return (novo);	//atualiza o pointer inicio com os novos dados

		}
	}
	else return (inicio);
}

//Verifica se as credenciais do cliente s�o v�lidas
int verificaCliente(Cliente* inicio, int id, char nome[], char password[])
{
	Cliente* atual = inicio;

	while (atual != NULL)
	{
		if (atual->id == id)
		{
			//Se a lista n�o for nula, percorre a lista at� encontrar o id e compara
			if (strcmp(atual->nome, nome) == 0)
			{
				if (strcmp(atual->password, password) == 0)
				{
					//Depois � comparada as duas strings nome e password, se for igual a 0, ou seja iguais, a fun��o retorna 1
					return 1;
				}
			}
		}

		//caso n�o tenha encontrado o id ,o pointer passa para o elemento seguinte
		atual = atual->seguinte;
	}
}

//Verifica se o id j� existe na lista ligada
int existeCliente(Cliente* inicio, int id)
{
	while (inicio != NULL)
	{
		//Percorre a lista toda, se encontrar um id igual retorna 1, sen�o retorna 0
		if (inicio->id == id) return (1);
		inicio = inicio->seguinte;
	}

	return (0);
}

//Remove um cliente com um determidado id da lista ligada
Cliente* removerCliente(Cliente* inicio, int id)
{
	Cliente* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return (NULL);	//se a lista estiver vazia retorna NULL 
	else if (atual->id == id)
	{
		//se o primeiro id da lista for o pretendido para remover entra neste if
		aux = atual->seguinte;	//aux passa a ser o segundo registo da lista
		free(atual);	//liberta o espa�o de mem�ria alocado do atual
		return (aux);	// retorna o inicio da lista
	}
	else
	{
		while ((atual != NULL) && (atual->id != id))
		{
			//percorre a lista at� o id ser igual e vai atualizando os pointers
			anterior = atual;
			atual = atual->seguinte;
		}

		if (atual == NULL) return (inicio);	//se percorrer a lista toda e n�o encontrar retorna o inicio
		else
		{
			//se percorrer a lista toda e n�o encontrar retorna o inicio
			anterior->seguinte = atual->seguinte;
			free(atual);	//liberta o espa�o de mem�ria alocado do atual
			return (inicio);	//retorna o inicio ,j� com o registo removido
		}
	}
}

//Lista todos os elementos da lista ligada
void listarCliente(Cliente* inicio)
{
	while (inicio != NULL)
	{
		//sen�o for null percorre toda a lista
		printf("%d ; %s ; %s ; %d ; %d ; %d ; %.2f ; %s\n", inicio->id, inicio->nome, inicio->morada, inicio->idade, inicio->nif, inicio->telemovel, inicio->saldo, inicio->password);
		//imprime o registo e o pointer inicio passa para o elemento seguinte
		inicio = inicio->seguinte;
	}
}

//Edita o cliente, alterando e atualizando os dados existentes na mem�ria
void editarCliente(struct registoCliente* lista, int id)
{
	struct registoCliente* atual = lista;
	while (atual != NULL)
	{
		//caso a lista n�o seja nula � pedido os dados para atualizar e esses dados s�o atualizados na mem�ria
		if (atual->id == id)
		{
			printf("Digite os novos dados para o Cliente %s:\n", atual->nome);
			printf("Nome: ");
			getchar();	// Clear the input buffer
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
			scanf("%f", &atual->saldo);
			printf("Password: ");
			getchar();
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
void guardarClientes(Cliente* inicio)
{
	FILE* arquivo = fopen("clientes.txt", "w");	//abrir o ficheiro para escrever por cima do que j� existe
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o ficheiro %s.\n", "clientes.txt");
		return;
	}

	Cliente* atual = inicio;
	while (atual != NULL)
	{
		//caso a lista n�o seja nula imprime no ficheiro as informa��es do primeiro elemento da lista e o pointer passa para o segundo
		fprintf(arquivo, "%d;%s;%s;%d;%d;%d;%f;%s\n", atual->id, atual->nome, atual->morada, atual->idade, atual->nif, atual->telemovel, atual->saldo, atual->password);
		atual = atual->seguinte;
	}

	fclose(arquivo);
	printf("As informacoes foram guardadas no ficheiro %s\n", "clientes.txt");
}

Gestor* inserirGestor(Gestor* inicio, int id, char nome[], int contribuinte, int tele, char password[])
{
	if (!existeGestor(inicio, id))
	{
		Gestor* novo = malloc(sizeof(struct registoGestor));
		if (novo != NULL)
		{
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

//L� as informa��es do ficheiro gestores.txt e insere na lista ligada Gestor
Gestor* lerGestor()
{
	FILE* fp;
	int id, contribuinte, tele;
	char nome[50], pass[50];
	Gestor* aux = NULL;
	fp = fopen("gestores.txt", "r");	//Ler o ficheiro clientes.txt
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			//percorre at� ao final do ficheiro
			fscanf(fp, "%d;%[^;];%d;%d;%[^;\n]", &id, nome, &contribuinte, &tele, pass);
			//guarda todas as informa��es da linha em variaveis
			aux = inserirGestor(aux, id, nome, contribuinte, tele, pass);
			//Insere um novo meio na lista ligada
		}

		fclose(fp);	//fecha o ficheiro
	}

	return (aux);
	//retorna o pointer para o inicio da lista
}

//Verifica se o id j� existe na lista ligada
int existeGestor(Gestor* inicio, int id)
{
	while (inicio != NULL)
	{
		//Percorre a lista toda, se encontrar um id igual retorna 1, sen�o retorn 0
		if (inicio->id == id) return (1);
		inicio = inicio->seguinte;
	}

	return (0);
}

//Remove um gestor com um determidado id da lista ligada
Gestor* removerGestor(Gestor* inicio, int id)
{
	Gestor* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return (NULL);	//se a lista estiver vazia retorna NULL 
	else if (atual->id == id)
	{
		//se o primeiro id da lista for o pretendido para remover entra neste if
		aux = atual->seguinte;	//aux passa a ser o segundo registo da lista
		free(atual);	//liberta o espa�o de mem�ria alocado do atual
		return (aux);	// retorna o inicio da lista
	}
	else
	{
		while ((atual != NULL) && (atual->id != id))
		{
			//percorre a lista at� o id ser igual e vai atualizando os pointers
			anterior = atual;
			atual = atual->seguinte;
		}

		if (atual == NULL) return (inicio);	//se percorrer a lista toda e n�o encontrar retorna o inicio
		else
		{
			//caso encontre o registo anterior � apontado para ser o seguinte
			anterior->seguinte = atual->seguinte;
			free(atual);	//liberta o espa�o de mem�ria alocado do atual
			return (inicio);	//retorna o inicio ,j� com o registo removido
		}
	}
}

//Lista todos os elementos da lista ligada
void listarGestor(Gestor* inicio)
{
	while (inicio != NULL)
	{
		//sen�o for null percorre toda a lista
		printf("%d ; %s ; %d ; %d ; %s\n", inicio->id, inicio->nome, inicio->nif, inicio->telemovel, inicio->password);
		//imprime o registo e o pointer inicio passa para o elemento seguinte
		inicio = inicio->seguinte;
	}
}

//Edita o gestor, alterando e atualizando os dados existentes na mem�ria
void editarGestor(struct registoGestor* lista, int id)
{
	struct registoGestor* atual = lista;
	while (atual != NULL)
	{
		//caso a lista n�o seja nula � pedido os dados para atualizar e esses dados s�o atualizados na mem�ria
		if (atual->id == id)
		{
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
void guardarGestores(Gestor* inicio)
{
	FILE* arquivo = fopen("gestores.txt", "w");	//abrir o ficheiro para escrever por cima do que j� existe
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o ficheiro %s.\n", "gestores.txt");
		return;
	}

	Gestor* atual = inicio;
	while (atual != NULL)
	{
		//caso a lista n�o seja nula imprime no ficheiro as informa��es do primeiro elemento da lista e o pointer passa para o segundo
		fprintf(arquivo, "%d;%s;%d;%d;%s\n", atual->id, atual->nome, atual->nif, atual->telemovel, atual->password);
		atual = atual->seguinte;
	}

	fclose(arquivo);
	printf("As informacoes foram guardadas no ficheiro %s\n", "gestores.txt");
}

//Verifica se as credenciais do gestor s�o v�lidas
int verificaGestor(Gestor* inicio, int id, char nome[], char pass[])
{
	Gestor* atual = inicio;
	while (atual != NULL)
	{
		if (atual->id == id)
		{
			//Se a lista n�o for nula, percorre a lista at� encontrar o id e compara
			if (strcmp(atual->nome, nome) == 0)
			{
				if (strcmp(atual->password, pass) == 0)
				{
					//Depois � comparada as duas strings nome e password, se for igual a 0, ou seja iguais, a fun��o retorna 1
					return 1;
				}
			}
		}

		//caso n�o tenha encontrado o id ,o pointer passa para o elemento seguinte
		atual = atual->seguinte;
	}
}

//Imprime os meios de mobilidade por ordem decrescente de autonomia
void listarMeiosPorAutonomia(Meio* inicio)
{
	Meio* ponteiro1 = NULL;	//pointer para o inicio da lista
	Meio* ponteiro2 = NULL;	// pointer para o fim da lista
	Meio* temp = NULL;
	Meio* anterior = NULL;	// pointer para o elemento anterior ao atual
	int trocas;

	do {
		//do while s� para quando trocar = 0, ou seja n�o houver mais trocas
		trocas = 0;
		ponteiro1 = inicio;

		while (ponteiro1->seguinte != ponteiro2)
		{
			//percorre a lista a toda at� que o pointer 1 chegue ao elemento anterior ao final, pointeiro 2
			if (ponteiro1->autonomia < ponteiro1->seguinte->autonomia)
			{
				//se o elemento seguinte tiver autonomia maior que o atual entra no if
				temp = ponteiro1->seguinte;	// armazena o pointer do proximo elemento da lista
				ponteiro1->seguinte = temp->seguinte;	// atualiza o pointer atual para o proximo elemento apontado para o proximo elemento do temp
				temp->seguinte = ponteiro1;	// o proximo elemento do pointer temp passa a ser o atual, trocando assim a posi��o dos dois
				if (ponteiro1 == inicio)
				{
					//verifica se o pointer 1 � o primeiro da lista 
					inicio = temp;	// o inicio da lista � apontado para pointer temporario
				}
				else
				{
					anterior->seguinte = temp;	// caso o pointer 1 n�o seja o primeiro da lista,  atualiza o pointer para o pr�ximo do elemento anterior da lista
				}

				anterior = temp;	// o elemento anterior passa a ser o pointer temporario
				trocas = 1;
			}
			else
			{
				//caso n�o haja troca o pointer 1 passa para o seguinte elemento
				ponteiro1 = ponteiro1->seguinte;
			}
		}

		ponteiro2 = ponteiro1;	//o pointer 2 ou seja ultimo, � atualizado para ser o atual que estava na compara��o
	} while (trocas);

	printf("Lista de meios de mobilidade eletrica por ordem decrescente de autonomia:\n");
	while (inicio != NULL)
	{
		printf("%d ; %s ; %d ; %d ; %.2f ; %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
		inicio = inicio->seguinte;
	}
}

//Se houver alguma localiza��o igual � do utilizador � imprimido as infos desse meio
void verificaLocalizacao(Meio* inicio, char localizacao[])
{
	printf("Meios com a mesma localizacao:\n");
	while (inicio != NULL)
	{
		//Percorre a lista e compara com cada elemento a string localiza��o com a do utilizador
		if (strcmp(inicio->localizacao, localizacao) == 0)
		{
			printf("%d ; %s ; %d ; %d ; %.2f ; %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
		}

		//depois de comparar o primeiro elemento o pointer passa para o elemento seguinte
		inicio = inicio->seguinte;
	}
}

//Cria��o do vertice na estrutura Grafo
Grafo criarVertice(Grafo* g, char vertice[])
{
	if (existeVertice(*g, vertice))
	{
		printf("O v�rtice '%s' j� existe no grafo.\n", vertice);
		return *g;
	}

	Grafo novo = malloc(sizeof(struct registoGrafo));
	if (novo != NULL)
	{
		strcpy(novo->vertice, vertice);
		novo->adjacentes = NULL;
		novo->meio = NULL;
		novo->cliente = NULL;
		novo->seguinte = *g;
		*g = novo;
	}

	return *g;
}

//Listar todos os vertices existentes
void listarVertices(Grafo g)
{
	while (g != NULL)
	{
		printf("%s\n", g->vertice);
		g = g->seguinte;
	}
}

//Remover um vertice do Grafo incluindo todas arestas a ele ligado e caso exista, do cliente e meio
void removerVertice(Grafo grafo, char vertice[])
{
	if (grafo == NULL)
	{
		return;	// Grafo vazio, n�o h� nada para remover
	}

	Grafo atual = grafo;
	Grafo anterior = NULL;

	// Procurar o v�rtice a ser removido
	while (atual != NULL)
	{
		if (strcmp(atual->vertice, vertice) == 0)
		{
			break;	// V�rtice encontrado
		}

		anterior = atual;
		atual = atual->seguinte;
	}

	if (atual == NULL)
	{
		return;	// V�rtice n�o encontrado
	}

	// Remover v�rtice dos registros de MeioGrafo e ClienteGrafo
	Meios meio = atual->meio;
	while (meio != NULL)
	{
		Meios meioAtual = meio;
		meio = meio->seguinte;
		free(meioAtual);
	}

	Clientes cliente = atual->cliente;
	while (cliente != NULL)
	{
		Clientes clienteAtual = cliente;
		cliente = cliente->seguinte;
		free(clienteAtual);
	}

	// Remover arestas que cont�m o v�rtice a ser removido
	Grafo verticeAtual = grafo;
	while (verticeAtual != NULL)
	{
		removerAresta(&verticeAtual->adjacentes, vertice);
		verticeAtual = verticeAtual->seguinte;
	}

	// Remover o v�rtice do grafo
	if (anterior == NULL)
	{
		grafo = atual->seguinte;
	}
	else
	{
		anterior->seguinte = atual->seguinte;
	}

	free(atual);
}

//Remover todas as arestas relacionadas com o vertice em quest�o
void removerAresta(Grafo g, char vertice[])
{
	// Encontrar o v�rtice na lista de v�rtices
	Grafo atual = g;
	while (atual != NULL)
	{
		if (strcmp(atual->vertice, vertice) == 0)
		{
			break;	// V�rtice encontrado
		}

		atual = atual->seguinte;
	}

	if (atual == NULL)
	{
		printf("V�rtice n�o encontrado.\n");
		return;
	}

	// Remover as arestas do v�rtice e seus adjacentes
	Adjacente adjacente = atual->adjacentes;
	while (adjacente != NULL)
	{
		Adjacente temp = adjacente;
		adjacente = adjacente->seguinte;
		free(temp);
	}

	atual->adjacentes = NULL;	// Define a lista de adjacentes do v�rtice como nula
}

//Verificar se o vertice existe
int existeVertice(Grafo g, char vertice[])
{
	while (g != NULL)
	{
		if (strcmp(g->vertice, vertice) == 0) return (1);
		else g = g->seguinte;
	}

	return (0);
}

//Cria a aresta entre vertice origem e vertice destino
void criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso)
{
	Adjacente novo;
	//Verifica se ambos os vertices existem
	if (existeVertice(g, vOrigem) && existeVertice(g, vDestino))
	{
		//Verifica se a aresta j� existe
		if (existeAresta(g, vOrigem, vDestino))
		{
			printf("O aresta j� existe no grafo.\n");
			return g;
		}

		while (strcmp(g->vertice, vOrigem) != 0)
			g = g->seguinte;

		//Cria uma nova estrutura para inserir na estrutura Adjacente
		novo = malloc(sizeof(struct registoAdjacente));
		if (novo != NULL)
		{
			//Insere o vertice de destino, peso e aponta para 
			strcpy(novo->vertice, vDestino);
			novo->peso = peso;
			novo->seguinte = g->adjacentes;
			g->adjacentes = novo;
		}
	}
}

//Verifica se a aresta j� existe
int existeAresta(Grafo g, char vOrigem[], char vDestino[])
{
	while (g != NULL)
	{
		if (strcmp(g->vertice, vOrigem) == 0)
		{
			Adjacente adj = g->adjacentes;
			while (adj != NULL)
			{
				if (strcmp(adj->vertice, vDestino) == 0)
				{
					// Aresta encontrada
					return 1;
				}

				adj = adj->seguinte;
			}
		}

		g = g->seguinte;
	}

	// Aresta n�o encontrada
	return 0;
}

// Listar os v�rtices adjacentes 
void listarAdjacentes(Grafo g, char vertice[])
{
	Adjacente aux;
	if (existeVertice(g, vertice))
	{
		while (strcmp(g->vertice, vertice) != 0) g = g->seguinte;
		aux = g->adjacentes;
		if (aux == NULL)
		{
			printf("O vertice %s n�o tem adjacentes\n", vertice);
		}
		else
		{
			while (aux != NULL)
			{
				printf("Adjacente:%s  Peso:%.2f\n", aux->vertice, aux->peso);
				aux = aux->seguinte;
			}
		}
	}
}

//Insere na estrutura MeioGrafo o id que tem vertice
int inserirMeioV2(Grafo g, struct registoMeio* lista, char geocodigo[], int codigoMeio)
{
	Grafo vertice = g;
	while ((vertice != NULL) && (strcmp(vertice->vertice, geocodigo) != 0))
		vertice = vertice->seguinte;

	if (vertice == NULL)
	{
		printf("Vertice %s nao encontrado.\n", geocodigo);
		return 0;
	}

	Meios meioAtual = vertice->meio;
	while (meioAtual != NULL)
	{
		//Verifica se na estrutura meios j� existe o id que pretendemos inserir com localiza��o
		if (meioAtual->idMeio == codigoMeio)
		{
			printf("Ja existe um registo com o ID %d no vertice %s.\n", codigoMeio, geocodigo);
			return 0;
		}

		meioAtual = meioAtual->seguinte;
	}

	struct registoMeio* meio = lista;
	while ((meio != NULL) && (meio->id != codigoMeio))
		meio = meio->seguinte;

	if (meio == NULL)
	{
		printf("Meio com o codigo %d nao encontrado.\n", codigoMeio);
		return 0;
	}

	Meios novo = malloc(sizeof(struct MeioGrafo));
	if (novo == NULL)
	{
		return 0;
	}

	//Insere o id do meio, e aponta para estrutura meios para receber informa��es desse mesmo meio
	novo->idMeio = codigoMeio;
	novo->meio = meio;
	novo->seguinte = vertice->meio;
	vertice->meio = novo;

	return 1;
}

//Atualiza o vertice do meio em quest�o
void atualizarMeio(Grafo g, int idMeio, char novoVertice[])
{
	if (existeVertice(g, novoVertice))
	{
		while (g != NULL)
		{
			if (g->meio != NULL)
			{
				Meios meio = g->meio;
				if (meio->idMeio == idMeio)
				{
					// Atualizar o v�rtice do cliente
					strcpy(g->vertice, novoVertice);
					return;
				}
			}

			g = g->seguinte;
		}

		printf("Meio com o ID %d nao encontrado.\n", idMeio);
	}
	else
	{
		printf("Vertice nao existe");
	}

	// Percorrer todos os v�rtices do grafo

}

// Listar os c�digos dos meios presente numa determinada localiza��o passada por par�metro
void listarMeiosnoGrafo(Grafo g)
{
	printf("Lista de Meios com Vertices:\n");

	while (g != NULL)
	{
		if (g->meio != NULL)
		{
			printf("Vertice: %s\n", g->vertice);

			Meios meio = g->meio;
			while (meio != NULL)
			{
				printf("Id do Meio: %d\n", meio->idMeio);
				meio = meio->seguinte;
			}

			printf("\n");
		}

		g = g->seguinte;
	}
}

// Listar os c�digos dos clientes presente numa determinada localiza��o passada por par�metro
void listarClientesnoGrafo(Grafo g)
{
	printf("Lista de Clientes com Vertices:\n");

	while (g != NULL)
	{
		if (g->cliente != NULL)
		{
			printf("Vertice: %s\n", g->vertice);

			Clientes cliente = g->cliente;
			while (cliente != NULL)
			{
				printf("Id do Cliente: %d\n", cliente->idCliente);
				cliente = cliente->seguinte;
			}

			printf("\n");
		}

		g = g->seguinte;
	}
}

//Insere na estrutura ClienteGrafo o id que tem vertice
int inserirClienteV2(Grafo g, struct registoCliente* lista, char geocodigo[], int codigoCliente)
{
	Grafo vertice = g;
	while ((vertice != NULL) && (strcmp(vertice->vertice, geocodigo) != 0))
		vertice = vertice->seguinte;

	if (vertice == NULL)
	{
		printf("Vertice %s nao encontrado.\n", geocodigo);
		return 0;
	}

	Clientes clienteExistente = vertice->cliente;
	while (clienteExistente != NULL)
	{
		if (clienteExistente->idCliente == codigoCliente)
		{
			printf("Cliente com o codigo %d ja existe para o vertice %s.\n", codigoCliente, geocodigo);
			return 0;
		}

		clienteExistente = clienteExistente->seguinte;
	}

	struct registoCliente* cliente = lista;
	while ((cliente != NULL) && (cliente->id != codigoCliente))
		cliente = cliente->seguinte;

	if (cliente == NULL)
	{
		printf("Cliente com o codigo %d nao encontrado.\n", codigoCliente);
		return 0;
	}

	Clientes novo = malloc(sizeof(struct ClienteGrafo));
	if (novo == NULL)
	{
		return 0;
	}

	novo->idCliente = codigoCliente;
	novo->cliente = cliente;
	novo->seguinte = vertice->cliente;
	vertice->cliente = novo;

	return 1;
}

//Atualiza o vertice do cliente em quest�o
void atualizarCliente(Grafo g, int idCliente, char novoVertice[])
{
	if (existeVertice(g, novoVertice))
	{
		while (g != NULL)
		{
			if (g->cliente != NULL)
			{
				Clientes cliente = g->cliente;
				if (cliente->idCliente == idCliente)
				{
					// Atualizar o v�rtice do cliente
					strcpy(g->vertice, novoVertice);
					return;
				}
			}

			g = g->seguinte;
		}

		printf("Cliente com o ID %d nao encontrado.\n", idCliente);
	}
	else
	{
		printf("Geocodigo nao existe no grafo");
	}
}

//Verifica se o vertice existe na estrutura ClientesGrafo
int existeVerticenoCliente(Grafo g, char vertice[])
{
	while (g != NULL)
	{
		if (g->cliente != NULL)
		{
			if (strcmp(g->vertice, vertice) == 0) return (1);
			else g = g->seguinte;
		}
		else
		{
			g = g->seguinte;
		}
	}

	return (0);
}

//S�o guardados todos os vertice no ficheiro vertices.txt
void guardarVertices(Grafo g)
{
	FILE* arquivo = fopen("vertices.txt", "w");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o ficheiro vertices.txt\n");
		return;
	}

	while (g != NULL)
	{
		if (g->vertice == NULL)
		{
			g->seguinte;
		}

		fprintf(arquivo, "%s\n", g->vertice);
		g = g->seguinte;
	}

	fclose(arquivo);
	printf("As informacoes foram guardadas no ficheiro %s\n", "vertices.txt");
}

//� guardado todas as arestas e peso das mesmas no ficheiro adjacentes.txt 
void guardarAdjacentes(Grafo g)
{
	FILE* arquivo = fopen("adjacentes.txt", "w");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o ficheiro adjacentes.txt\n");
		return;
	}

	while (g != NULL)
	{
		Adjacente adjacente = g->adjacentes;
		if (adjacente == NULL)
		{
			g = g->seguinte;
			continue;	// Passa para o pr�ximo v�rtice caso n�o haja adjacentes
		}

		while (adjacente != NULL)
		{
			fprintf(arquivo, "%s;%s;%.2f\n", g->vertice, adjacente->vertice, adjacente->peso);
			adjacente = adjacente->seguinte;
		}

		g = g->seguinte;
	}

	fclose(arquivo);
	printf("As informacoes foram guardadas no ficheiro adjacentes.txt\n");
}

//� guardado todos os IDs e vertice dos meios no ficheiro meiosGrafo.txt
void guardarMeioGrafo(Grafo g)
{
	FILE* arquivo = fopen("meiosGrafo.txt", "w");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o ficheiro meiosGrafo.txt\n");
		return;
	}

	while (g != NULL)
	{
		Meios meio = g->meio;
		while (meio != NULL)
		{
			if (g->vertice == NULL)
			{
				g->seguinte;
			}

			fprintf(arquivo, "%d;%s\n", meio->idMeio, g->vertice);
			meio = meio->seguinte;
		}

		g = g->seguinte;
	}

	fclose(arquivo);
	printf("As informacoes foram guardadas no ficheiro meiosGrafo.txt\n");
}

//� guardado todos os IDs e vertice dos clientes no ficheiro clientesGrafo.txt
void guardarClienteGrafo(Grafo g)
{
	FILE* arquivo = fopen("clientesGrafo.txt", "w");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o ficheiro clientesGrafo.txt\n");
		return;
	}

	while (g != NULL)
	{
		Clientes cliente = g->cliente;
		while (cliente != NULL)
		{
			if (g->vertice == NULL)
			{
				g->seguinte;
			}

			fprintf(arquivo, "%d;%s\n", cliente->idCliente, g->vertice);
			cliente = cliente->seguinte;
		}

		g = g->seguinte;
	}

	fclose(arquivo);
	printf("As informacoes foram guardadas no ficheiro clientesGrafo.txt\n");
}

//L� do ficheiro vertices.txt todos os vertices presentes no ficheiro e insere-os na estrutura
Grafo lerVertices(Grafo* g)
{
	FILE* fp = fopen("vertices.txt", "r");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro vertices.txt\n");
		return NULL;
	}

	char vertice[50];

	while (!feof(fp))
	{
		fscanf(fp, "%s\n", vertice);
		//guarda todas as informa��es da linha em variaveis
		Grafo novo = malloc(sizeof(struct registoGrafo));
		if (novo != NULL)
		{
			strcpy(novo->vertice, vertice);
			novo->adjacentes = NULL;
			novo->meio = NULL;
			novo->cliente = NULL;
			novo->seguinte = *g;
			*g = novo;
		}
	}

	fclose(fp);
	return *g;

}

//L� do ficheiro vertices.txt todas as arestas presentes no ficheiro e insere-os na estrutura
void lerAdjacentes(Grafo g)
{
	FILE* fp = fopen("adjacentes.txt", "r");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro adjacentes.txt\n");
		return;
	}

	char verticeOrigem[50];
	char verticeDestino[50];
	float peso;

	while (!feof(fp))
	{
		fscanf(fp, "%[^;];%[^;];%f\n", verticeOrigem, verticeDestino, &peso);
		//guarda todas as informa��es da linha em variaveis
		criarAresta(g, verticeOrigem, verticeDestino, peso);
	}

	fclose(fp);
}

//L� os IDs dos meios presentes no ficheiro e insere-os na estrutura meiosGrafo.txt
Grafo lerMeioGrafo(Grafo g, struct registoMeio* lista)
{
	FILE* fp = fopen("meiosGrafo.txt", "r");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro meiosGrafo.txt\n");
		return g;
	}

	// Verificar o tamanho do arquivo
	fseek(fp, 0, SEEK_END);
	long fileSize = ftell(fp);
	if (fileSize == 0)
	{
		printf("O ficheiro meiosGrafo.txt esta vazio.\n");
		fclose(fp);
		return g;
	}

	fseek(fp, 0, SEEK_SET);

	char geocodigo[50];
	int idMeio;

	while (!feof(fp))
	{
		fscanf(fp, "%d;%s\n", &idMeio, geocodigo);
		//guarda todas as informa��es da linha em variaveis
		inserirMeioV2(g, lista, geocodigo, idMeio);
	}

	fclose(fp);
	return g;
}

//L� os IDs dos meios presentes no ficheiro e insere-os na estrutura clientesGrafo.txt
Grafo lerClienteGrafo(Grafo g, struct registoCliente* lista)
{
	FILE* fp = fopen("clientesGrafo.txt", "r");
	if (fp == NULL)
	{
		printf("Erro ao abrir o ficheiro clientesGrafo.txt\n");
		return g;
	}

	// Verificar o tamanho do arquivo
	fseek(fp, 0, SEEK_END);
	long fileSize = ftell(fp);
	if (fileSize == 0)
	{
		printf("O ficheiro clientesGrafo.txt esta vazio.\n");
		fclose(fp);
		return g;
	}

	fseek(fp, 0, SEEK_SET);

	int idCliente;
	char geocodigo[50];

	while (!feof(fp))
	{
		fscanf(fp, "%d;%s\n", &idCliente, geocodigo);
		//guarda todas as informa��es da linha em variaveis
		inserirClienteV2(g, lista, geocodigo, idCliente);
	}

	fclose(fp);
	return g;
}

//Junta se todas as fun��es de ler formando o lerGrafo
Grafo lerGrafo(struct registoMeio* meio, struct registoCliente* cliente)
{
	Grafo g = NULL;

	lerVertices(&g);
	lerAdjacentes(g);
	lerMeioGrafo(g, meio);
	lerClienteGrafo(g, cliente);

	return g;
}

//Junta se todas as fun��es de ler formando o guardarGrafo
void guardarGrafo(Grafo g)
{
	guardarVertices(g);
	guardarAdjacentes(g);
	guardarMeioGrafo(g);
	guardarClienteGrafo(g);
}

//Fun��o de inserir o caminho na estrutura Caminho
void inserirCaminho(Caminho** lista, char vertice[], float distancia)
{
	Caminho* novoCaminho = (Caminho*)malloc(sizeof(Caminho));
	strcpy(novoCaminho->vertice, vertice);
	novoCaminho->distancia = distancia;
	novoCaminho->proximo = NULL;

	if (*lista == NULL)
	{
		*lista = novoCaminho;
	}
	else
	{
		Caminho* ultimo = *lista;
		while (ultimo->proximo != NULL)
		{
			ultimo = ultimo->proximo;
		}

		ultimo->proximo = novoCaminho;
	}
}

//Fun��o de remover o caminho na estrutura Caminho
void removerCaminho(Caminho** caminho)
{
	if (*caminho == NULL)
	{
		return;
	}

	Caminho* caminhoRemovido = *caminho;
	*caminho = (*caminho)->proximo;

	free(caminhoRemovido);
}

//Verifica se tem um meio presente nesse vertice
int VerificarMeio(Grafo g, char vertice[])
{
	while (g != NULL && strcmp(g->vertice, vertice) != 0)
	{
		g = g->seguinte;
	}

	if (g->meio != NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Retorna o id do meio que tenha aquele vertice
int buscarIDMeioPorVertice(Grafo g, char vertice[])
{
	while (g != NULL)
	{
		if (strcmp(g->vertice, vertice) == 0 && g->meio != NULL)
		{
			return g->meio->idMeio;	// Retorna o ID do meio encontrado
		}

		g = g->seguinte;
	}

	return -1;	// Retorna -1 se o meio n�o for encontrado
}

//Fun��o para buscar um meio pelo ID na lista de meios
Meio* buscarMeioPorID(Meio* meios, int id)
{
	Meio* meioAtual = meios;

	// Percorrer a lista de meios
	while (meioAtual != NULL)
	{
		// Verificar se o ID do meio atual corresponde ao ID buscado
		if (meioAtual->id == id)
		{
			return meioAtual;	// Retorna o ponteiro para o meio encontrado
		}

		meioAtual = meioAtual->seguinte;	// Avan�a para o pr�ximo meio na lista
	}

	return NULL;	// Retorna NULL se o meio n�o for encontrado
}

//Fun��o para buscar os caminhos mais curtos a partir de um v�rtice inicial
void buscarCaminhosMaisCurto(Grafo g, char verticeInicial[], float raio, struct registoMeio* meios, char meio[])
{
	Caminho* caminhos = NULL;
	Grafo gInicial = g;

	// Inicializar a lista de caminhos com o v�rtice inicial e dist�ncia zero
	inserirCaminho(&caminhos, verticeInicial, 0);

	// Enquanto houver caminhos na lista
	while (caminhos != NULL)
	{
		// Obter o caminho atual
		char verticeAtual[50];
		float distanciaAtual;
		strcpy(verticeAtual, caminhos->vertice);
		distanciaAtual = caminhos->distancia;

		if (distanciaAtual == 0)
		{
			if (VerificarMeio(gInicial, verticeAtual) == 1)
			{
				// Buscar o meio de mobilidade correspondente ao v�rtice adjacente
				int idMeio = buscarIDMeioPorVertice(gInicial, verticeAtual);
				if (idMeio != -1)
				{
					// Obter as informa��es do meio correspondente ao ID
					struct registoMeio* meioAtual = buscarMeioPorID(meios, idMeio);
					if (strcmp(meioAtual->tipodemobilidade, meio) == 0)
					{
						printf("Caminho encontrado: ");
						printf("%s -> ", verticeAtual);
						printf("Distancia: %.2f\n", distanciaAtual);
						// Imprimir as informa��es do meio encontrado
						printf("Informacoes do Meio (ID: %d):\n", meioAtual->id);
						printf("Tipo de Mobilidade: %s\n", meioAtual->tipodemobilidade);
						printf("Carga: %d\n", meioAtual->carga);
						printf("Autonomia: %d km\n", meioAtual->autonomia);
						printf("Custo: %.2f\n", meioAtual->custo);
						if (meioAtual->aluguer == 0)
						{
							printf("Nao alugado\n");
							printf("\n");
						}
						else if (meioAtual->aluguer == 1)
						{
							printf("Alugado\n");
							printf("\n");
						}
						else
						{
							printf("Indisponivel\n");
							printf("\n");
						}
					}
				}
			}
		}

		// Remover o caminho atual da lista
		removerCaminho(&caminhos);

		// Encontrar o v�rtice correspondente na lista de v�rtices
		Grafo vertice = gInicial;
		while (vertice != NULL && strcmp(vertice->vertice, verticeAtual) != 0)
		{
			vertice = vertice->seguinte;
		}

		// Verificar os v�rtices adjacentes
		Adjacente adjacente = vertice->adjacentes;
		while (adjacente != NULL)
		{
			// Verificar se o v�rtice adjacente n�o est� dentro do raio
			if (distanciaAtual + adjacente->peso <= raio)
			{
				// Calcular a dist�ncia acumulada para o v�rtice adjacente
				float distanciaAdjacente = distanciaAtual + adjacente->peso;

				// Verificar se o v�rtice atual tem g->meio != NULL
				if (VerificarMeio(gInicial, adjacente->vertice) == 1)
				{
					removerCaminho(&caminhos);
					inserirCaminho(&caminhos, adjacente->vertice, distanciaAdjacente);
					// Imprimir o caminho encontrado

					// Buscar o meio de mobilidade correspondente ao v�rtice adjacente
					int idMeio = buscarIDMeioPorVertice(gInicial, adjacente->vertice);
					if (idMeio != -1)
					{
						// Obter as informa��es do meio correspondente ao ID
						struct registoMeio* meioAtual = buscarMeioPorID(meios, idMeio);
						if (strcmp(meioAtual->tipodemobilidade, meio) == 0)
						{
							printf("Caminho encontrado: ");
							printf("%s -> ", adjacente->vertice);
							printf("Distancia: %.2f\n", distanciaAdjacente);
							// Imprimir as informa��es do meio encontrado
							printf("Informacoes do Meio (ID: %d):\n", meioAtual->id);
							printf("Tipo de Mobilidade: %s\n", meioAtual->tipodemobilidade);
							printf("Carga: %d\n", meioAtual->carga);
							printf("Autonomia: %d km\n", meioAtual->autonomia);
							printf("Custo: %.2f\n", meioAtual->custo);
							if (meioAtual->aluguer == 0)
							{
								printf("Nao alugado\n");
								printf("\n");
							}
							else if (meioAtual->aluguer == 1)
							{
								printf("Alugado\n");
								printf("\n");
							}
							else
							{
								printf("Indisponivel\n");
								printf("\n");
							}
						}
					}
				}
				else
				{
					inserirCaminho(&caminhos, adjacente->vertice, distanciaAdjacente);
				}
			}

			// Avan�ar para o pr�ximo v�rtice adjacente
			adjacente = adjacente->seguinte;
		}
	}

	// Liberar a mem�ria alocada pelos caminhos
	while (caminhos != NULL)
	{
		removerCaminho(&caminhos);
	}
}

//Fun��o para encontrar caminho mais curto que d� a volta toda ao grafo para que o camiao passe por todos os pontos
Camiao* encontrarCaminhoCircuitoMaisCurto(Grafo* g, char verticeInicial[], struct registoMeio* meios, struct Camiao* camiao)
{
	Camiao* MeioCamiao = NULL;
	Caminho* caminhos = NULL;
	Grafo gInicial = g;
	int totalVertices = 0;

	// Calcular o n�mero total de v�rtices no grafo
	Grafo grafoAtual = g;
	while (grafoAtual != NULL)
	{
		totalVertices++;
		grafoAtual = grafoAtual->seguinte;
	}

	// Inicializar a lista de caminhos com o v�rtice inicial e dist�ncia zero
	inserirCaminho(&caminhos, verticeInicial, 0);

	// Vetor para controlar os v�rtices visitados
	int* verticesVisitados = (int*)malloc(totalVertices * sizeof(int));
	memset(verticesVisitados, 0, totalVertices * sizeof(int));

	// Vari�vel para contar o n�mero de v�rtices visitados
	int verticesPassados = 0;

	// Enquanto houver caminhos na lista
	while (caminhos != NULL)
	{
		Caminho* caminho2 = caminhos;
		// Obter o caminho atual
		char verticeAtual[50];
		float distanciaAtual;
		while (caminho2->proximo != NULL)
		{
			caminho2 = caminho2->proximo;
		}

		strcpy(verticeAtual, caminho2->vertice);
		distanciaAtual = caminho2->distancia;

		// Encontrar o v�rtice correspondente na lista de v�rtices
		Grafo vertice = g;
		while (vertice != NULL && strcmp(vertice->vertice, verticeAtual) != 0)
		{
			vertice = vertice->seguinte;
		}

		verticesPassados++;

		// Verificar se todos os v�rtices foram visitados e se � poss�vel voltar ao v�rtice inicial
		if (verticesPassados >= totalVertices && strcmp(verticeAtual, verticeInicial) == 0)
		{
			Caminho* caminhoAtual = caminhos;
			// Imprimir o caminho encontrado
			printf("Caminho mais curto encontrado: ");
			while (caminhoAtual != NULL)
			{
				printf("\n%s -> \n", caminhoAtual->vertice);
				int idMeio = buscarIDMeioPorVertice(gInicial, caminhoAtual->vertice);

				if (idMeio != -1)
				{
					// Obter as informa��es do meio correspondente ao ID
					struct registoMeio* meioAtual = buscarMeioPorID(meios, idMeio);

					if (meioAtual != NULL)
					{
						// Verificar se o meio tem carga abaixo de 50
						if (meioAtual->carga < 50)
						{
							// Verificar se o meio j� foi recolhido
							if (camiao != NULL)
							{
								if (verificarMeioRecolhido(camiao, meioAtual->id))
								{
									printf("\nO meio %s com o id %d no local %s encontra-se com carga abaixo de 50, entao sera recolhido\n", meioAtual->tipodemobilidade, meioAtual->id, caminhoAtual->vertice);
									// Inserir o meio na estrutura MeioAbaixo50 do cami�o
									MeioCamiao = inserirMeionoCamiao(camiao, meioAtual->id, meioAtual);
									// Marcar o meio como recolhido
								}
							}
							else
							{
								printf("\nO meio %s com o id %d no local %s encontra-se com carga abaixo de 50, entao sera recolhido\n", meioAtual->tipodemobilidade, meioAtual->id, caminhoAtual->vertice);
								// Inserir o meio na estrutura MeioAbaixo50 do cami�o
								MeioCamiao = inserirMeionoCamiao(MeioCamiao, meioAtual->id, meioAtual);
							}
						}
						else
						{
							printf("\nO meio %s com o id %d no local %s tem carga acima de 50\n", meioAtual->tipodemobilidade, meioAtual->id, caminhoAtual->vertice);
						}
					}
				}

				caminhoAtual = caminhoAtual->proximo;
			}

			printf("%s\n", verticeInicial);
			printf("\nDistancia: %.2f\n", distanciaAtual);
			removerCaminho(&caminhos);
			free(verticesVisitados);
			return MeioCamiao;
			return;
		}

		// Verificar os v�rtices adjacentes
		Adjacente adjacente = vertice->adjacentes;
		while (adjacente != NULL)
		{
			// Calcular a dist�ncia acumulada para o v�rtice adjacente
			float distanciaAdjacente = distanciaAtual + adjacente->peso;

			// Inserir o caminho para o v�rtice adjacente na lista de caminhos
			inserirCaminho(&caminhos, adjacente->vertice, distanciaAdjacente);

			// Avan�ar para o pr�ximo v�rtice adjacente
			adjacente = adjacente->seguinte;
			if (adjacente != NULL)
			{
				adjacente = adjacente->seguinte;
				if (adjacente != NULL)
				{
					adjacente = adjacente->seguinte;
				}
			}
		}
	}

	printf("Nao foi possivel encontrar um caminho que percorra todos os vertices e volte ao vertice inicial.\n");
}

//Fun��o que coloca os meios a 100 de carga e disponveis para alugar retirando-os da estrutura camiao
void reporMeios(Meio* inicio, Camiao* atual)
{
	Camiao* camiao = atual;	// Ponteiro auxiliar para percorrer a lista de Cami�es
	Meio* inicioMeios = inicio;	// Ponteiro auxiliar para o in�cio da lista de Meios

	// Percorre a lista de Cami�es
	while (camiao != NULL)
	{
		Meio* meios = inicioMeios;	// Cria uma c�pia do ponteiro inicial dos Meios para percorrer a lista

		// Procura o Meio correspondente ao Cami�o pelo ID
		while (meios != NULL && meios->id != camiao->idMeio)
		{
			meios = meios->seguinte;
		}

		if (meios == NULL)
		{
			printf("Nao existe esse id\n");	// Se n�o encontrar o Meio correspondente, imprime uma mensagem de erro
		}
		else
		{
			meios->carga = 100;	// Rep�e a carga do Meio para 100
			meios->aluguer = 0;	// Define o Meio como n�o alugado
		}

		camiao = camiao->seguinte;	// Avan�a para o pr�ximo Cami�o na lista
	}

	free(atual);	// Libera a mem�ria alocada para a lista de Cami�es
}

// Fun��o que verifica se um Meio j� foi recolhido por um Cami�o
int verificarMeioRecolhido(struct Camiao* camiao, int idMeio)
{
	// Percorre a lista de Meios abaixo de 50 do Cami�o
	struct registoMeio* meioAtual = camiao->meio;
	while (meioAtual != NULL)
	{
		// Verifica se o ID do Meio coincide
		if (meioAtual->id == idMeio)
		{
			// O Meio j� foi recolhido
			return 1;
		}

		meioAtual = meioAtual->seguinte;
	}

	// O Meio n�o foi recolhido
	return 0;
}

// Fun��o para inserir um Meio num Cami�o
Camiao* inserirMeionoCamiao(Camiao* inicio, int idMeio, struct registoMeio* meio)
{
	Meio* meios = meio;
	Meio* inicioMeios = meios;

	// Verifica se o Meio j� existe no Cami�o, se j� existir retorna o ponteiro 'inicio' sem nenhuma nova inser��o
	Camiao* novo = malloc(sizeof(Camiao));	// Cria uma nova struct para inserir os novos dados
	if (novo != NULL)
	{
		if (meios == NULL)
		{
			printf("Nao existe esse id\n");
		}
		else
		{
			meios = inicioMeios;	// Reinicia a busca no in�cio dos Meios

			while (meios != NULL && meios->id != idMeio)
			{
				meios = meios->seguinte;
			}

			if (meios == NULL)
			{
				printf("Nao existe esse id\n");
			}
			else
			{
				novo->idMeio = idMeio;
				novo->meio = meios;
				meios->aluguer = -1;
				novo->seguinte = inicio;
				inicio = novo;	// Atualiza o ponteiro 'inicio' com os novos dados
			}
		}
	}

	return inicio;
}

// Fun��o para obter o v�rtice correspondente a um ID de Cliente num Grafo
char* obterVerticePorIDCliente(Grafo g, int idCliente)
{
	while (g != NULL)
	{
		Clientes clientes = g->cliente;	// Reinicia a vari�vel 'clientes' em cada itera��o
		while (clientes != NULL)
		{
			if (clientes->idCliente == idCliente)
			{
				return g->vertice;
			}

			clientes = clientes->seguinte;
		}

		g = g->seguinte;
	}

	return NULL;	// ID do cliente n�o encontrado
}

// Fun��o para guardar os dados de um Cami�o num arquivo
void guardarCamiao(Camiao* camiao)
{
	FILE* arquivo = fopen("camiao.txt", "w");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o ficheiro.\n");
		return;
	}

	if (camiao == NULL)
	{
		return;
	}

	while (camiao != NULL)
	{
		if (camiao->idMeio < 0)
		{
			return;
		}

		fprintf(arquivo, "%d\n", camiao->idMeio);
		camiao = camiao->seguinte;
	}

	fclose(arquivo);
	printf("\nAs informacoes foram guardadas no ficheiro camiao.txt.\n");
}

// Fun��o para ler os dados de um Cami�o a partir de um ficheiro
Camiao* LerCamiao(Meio* meios)
{
	FILE* fp = fopen("camiao.txt", "r");
	if (fp == NULL)
	{
		printf("Arquivo camiao.txt nao encontrado. Retornando lista de camioes vazia.\n");
		return NULL;
	}

	Camiao* camiao = NULL;
	char tipo[50];
	int idmeio;

	while (!feof(fp))
	{
		fscanf(fp, "%d\n", &idmeio);
		// Guarda todas as informa��es da linha em vari�veis
		camiao = inserirMeionoCamiao(camiao, idmeio, meios);
	}

	fclose(fp);
	return camiao;
}