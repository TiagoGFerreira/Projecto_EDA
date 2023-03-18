#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "lib.h"


// Inserção de um novo registo
Meio* inserirMeio(Meio* inicio, int id, char tipo[], int carga, int autonomia, float custo, char localizacao[], int aluguer)
{
	if (!existeMeio(inicio, id))
	{
		Meio* novo = malloc(sizeof(struct registoMeio));
		if (novo != NULL)
		{
			novo->id = id;
			strcpy(novo->tipodemobilidade, tipo);
			novo->carga = carga;
			novo->autonomia = autonomia;
			novo->custo = custo;
			strcpy(novo->localizacao, localizacao);
			novo->aluguer = aluguer;
			//fprintf("Idade do Cliente:  %[^\t]s", ida);
			novo->seguinte = inicio;
			return(novo);
			if (inicio == NULL) // a lista está vazia
			{
				inicio = novo;
			}
			else // a lista não está vazia
			{
				Meio* atual = inicio;
				while (atual->seguinte != NULL)
				{
					atual = atual->seguinte;
				}
				atual->seguinte = novo;
			}
		}
	}
	return inicio;
}

int existeMeio(Meio* inicio, int id)
{
	while (inicio != NULL)
	{
		if (inicio->id == id) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

Meio* removerMeio(Meio* inicio, int id)
{
	Meio* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return(NULL);
	else if (atual->id == id) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (atual->id != id))
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) return(inicio);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			return(inicio);
		}
	}
}
Meio* lerMeios()
{
	FILE* fp;
	int id, carga, autonomia, aluguer;
	float custo;
	char tipodemobilidade[50] , localizacao[50];
	Meio* aux = NULL;
	fp = fopen("meios.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%d;%d;%f;%[^;];%d\n", &id, tipodemobilidade, &carga, &autonomia, &custo, localizacao, &aluguer);
			aux = inserirMeio(aux, id, tipodemobilidade, carga, autonomia, custo, localizacao, aluguer);
		}
		fclose(fp);
	}
	return(aux);
}


void listarMeios(Meio* inicio)
{
	while (inicio != NULL)
	{
		printf(" ID - %d ; Tipo de Meio - %s ; Carga - %d ; Autonomia - %d ; Custo -  %.2f ; Localizacao - %s\n ", inicio->id, inicio->tipodemobilidade,inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
		inicio = inicio->seguinte;
	}
}

void MeiosParaAlugar(Meio* inicio)
{
	int meiosDisponiveis = 0;
	while (inicio != NULL)
	{
		if (inicio->aluguer == 0)
		{
			printf("Meios Disponiveis:\n");
			printf("ID - %d ; Tipo de Meio - %s ; Carga - %d ; Autonomia - %d ;Custo -  %.2f ; Localizacao - %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
			meiosDisponiveis++;
		}
		inicio = inicio->seguinte;
	}

	if (meiosDisponiveis == 0) {
		printf("Nao existem meios disponiveis para alugar\n");
	}
}


void AlugarMeios(struct registoMeio* lista, int id) {
	struct registoMeio* atual = lista;
	FILE* fp;
	fp = fopen("registosAluguer.txt", "w");
	

		fclose(fp);
	while (atual != NULL && atual->id != id) {
		atual = atual->seguinte;
	}
	if (atual != NULL && atual->aluguer == 0)
	{
		atual->aluguer = 1;
		printf("O tipo de mobilidade com o id %d foi alugado com sucesso\n", id);
		if (fp != NULL)
		{
			fprintf(fp, "O meio com id - %d foi alugado\n", id);
		}
	}
	else if (atual != NULL && atual->aluguer == 1) {
		printf("O tipo de mobilidade com o id %d ja esta alugado\n", id);
	}
	else {
		printf("O tipo de mobilidade com o id %d nao existe\n", id);
	}
	
}

void DesalugarMeios(struct registoMeio* lista, int id) {
	struct registoMeio* atual = lista;
	FILE* fp;
	fp = fopen("registosAluguer.txt", "w");
	while (atual != NULL && atual->id != id) {
		atual = atual->seguinte;
	}
	if (atual != NULL && atual->aluguer == 1)
	{
		atual->aluguer = 0;
		if (fp != NULL)
		{
			fprintf(fp, "O meio com id - %d foi desalugado\n", id);
		}
		printf("O tipo de mobilidade com o id %d foi desalugado com sucesso\n", id);
	}
	else if(atual != NULL && atual->aluguer == 0) {
		printf("O tipo de mobilidade com o id %d ja esta desalugado\n", id);
	}
	else {
		printf("O tipo de mobilidade com o id %d nao existe\n", id);
	}
}

void editarMeios(struct registoMeio* lista, int id) {
	struct registoMeio* atual = lista;
	while (atual != NULL) {
			printf("Digite os novos dados para o ID - %d:\n", id);
			printf("Tipo de Mobilidade: ");
			getchar(); // Clear the input buffer
			gets(atual->tipodemobilidade);
			printf("Carga: ");
			scanf("%d", &atual->carga);
			printf("Autonomia: ");
			scanf("%d", &atual->autonomia);
			printf("Custo: ");
			scanf("%f", &atual->custo);
			printf("Localizacao: ");
			getchar(); // Clear the input buffer
			gets(atual->localizacao);
			printf("Dados atualizados com sucesso!\n");
			return;
		atual = atual->seguinte;
	}
	printf("O ID - %d nao foi encontrado na lista.\n", id);
}

void guardarMeios(Meio* inicio)
{
	FILE* fp;
	fp = fopen("meios.txt", "w");
	if (fp != NULL)
	{
		Meio* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "%d;%s;%d;%d;%.2f;%s;%d\n", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao, inicio->aluguer);
			aux = aux->seguinte;
		}

		fclose(fp);
		printf("As informacoes foram guardadas no ficheiro %s\n", "meios.txt");
	}
}

Cliente* lerCliente()
{
	FILE* fp;
	int id, idade, contribuinte, tele;
	char nome[50], morada[50], pass[50];
	Cliente* aux = NULL;
	fp = fopen("clientes.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%[^;];%d;%d;%d;%[^;\n]", &id, nome, morada, &idade, &contribuinte, &tele, pass);
			aux = inserirCliente(aux, id,nome,morada,idade,contribuinte,tele,pass);
		}
		fclose(fp);
	}
	return(aux);
}


Cliente* inserirCliente(Cliente* inicio, int id, char nome[], char mor[], int ida, int contribuinte, int tele, char pass[])
{

	//FILE* fp;
	//fp = fopen("cliente.txt", "w");

	if (!existeCliente(inicio, id))
	{
		Cliente* novo = malloc(sizeof(struct registoCliente));
		if (novo != NULL)
		{
		//	if (fp == NULL) {
			//	printf("Ficheiro txt não existe\n");
			//	exit(1);
			
			novo->id = id;
			strcpy(novo->nome, nome);
			//fprintf("Nome do Cliente:  %[^\t]s",nome);
			//fprintf("NIF do Cliente:  %[^\t]s", contribuinte);
			strcpy(novo->morada, mor);
			//fprintf("Morada do Cliente:  %[^\t]s", mor);
			novo->idade = ida;
			//fprintf("Morada do Cliente:  %[^\t]s", mor);
			novo->nif = contribuinte;
			//fprintf("Idade do Cliente:  %[^\t]s", ida);
			novo->telemovel = tele;
			//fprintf("Idade do Cliente:  %[^\t]s", ida);
			strcpy(novo->password, pass);
			//fprintf("Idade do Cliente:  %[^\t]s", ida);
			novo->seguinte = inicio;
			return(novo);
			
		}
	}
	else return(inicio);
}

int verificaCliente(Cliente* inicio, int id, char nome[], char password[])
{
	Cliente* atual = inicio;

	while (atual != NULL) {
		if (atual->id == id)
		{
			if (strcmp(atual->nome, nome) == 0)
			{
				if(strcmp(atual->password, password) == 0)
				{
					return 1;
				}
			}
		}
		atual = atual->seguinte;
	}	
}


int existeCliente(Cliente* inicio, int id)
{
	while (inicio != NULL)
	{
		if (inicio->id == id) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

Cliente* removerCliente(Cliente* inicio, int id)
{
	Cliente* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return(NULL);
	else if (atual->id == id) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (atual->id != id))
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) return(inicio);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			return(inicio);
		}
	}
}


void listarCliente(Cliente* inicio)
{
	while (inicio != NULL)
	{
		printf("%d ; %s ; %s ; %d ; %d ; %d ; %s\n", inicio->id , inicio->nome, inicio->morada, inicio->idade, inicio->nif,  inicio->telemovel, inicio->password);
		inicio = inicio->seguinte;
	}
}

void editarCliente(struct registoCliente* lista, int id) {
	struct registoCliente* atual = lista;
	while (atual != NULL) {
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
			getchar();
			printf("Password: ");
			gets(atual->password);
			printf("Dados atualizados com sucesso!\n");
			return;
		}
		atual = atual->seguinte;
	}
	printf("O nome %s nao foi encontrado na lista.\n", atual->nome);
}

void guardarClientes(Cliente* inicio) {
	FILE* arquivo = fopen("clientes.txt", "w");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo %s.\n", "clientes.txt");
		return;
	}

	Cliente* atual = inicio;
	while (atual != NULL) {
		fprintf(arquivo, "%d;%s;%s;%d;%d;%d;%s\n", atual->id , atual->nome, atual->morada, atual->idade, atual->nif, atual->telemovel, atual->password);
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
			return(novo);
		}
	}
	else return(inicio);
}

Gestor* lerGestor()
{
	FILE* fp;
	int id, contribuinte, tele;
	char nome[50], pass[50];
	Gestor* aux = NULL;
	fp = fopen("gestores.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d;%[^;];%d;%d;%[^;\n]", &id, nome, &contribuinte, &tele, pass);
			aux = inserirGestor(aux, id, nome, contribuinte, tele, pass);
		}
		fclose(fp);
	}
	return(aux);
}

int existeGestor(Gestor* inicio, int id)
{
	while (inicio != NULL)
	{
		if (inicio->id == id) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

Gestor* removerGestor(Gestor* inicio, int id)
{
	Gestor* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return(NULL);
	else if (atual->id == id) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (atual->id != id))
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) return(inicio);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			return(inicio);
		}
	}
}

void listarGestor(Gestor* inicio)
{
	while (inicio != NULL)
	{
		printf("%d ; %s ; %d ; %d ; %s\n", inicio->id , inicio->nome, inicio->nif, inicio->telemovel , inicio->password);
		inicio = inicio->seguinte;
	}
}

void editarGestor(struct registoGestor* lista, int id) {
	struct registoGestor* atual = lista;
	while (atual != NULL) {
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
		atual = atual->seguinte;
	}
	printf("O Gestor %s nao foi encontrado na lista.\n", atual->nome);
}

void guardarGestores(Gestor* inicio) {
	FILE* arquivo = fopen("gestores.txt", "w");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo %s.\n", "gestores.txt");
		return;
	}

	Gestor* atual = inicio;
	while (atual != NULL) {
		fprintf(arquivo, "%d;%s;%d;%d;%s\n", atual->id, atual->nome, atual->nif, atual->telemovel,  atual->password);
		atual = atual->seguinte;
	}

	fclose(arquivo);
	printf("As informacoes foram guardadas no ficheiro %s\n", "gestores.txt");
}

int verificaGestor(Gestor* inicio, int id, char nome[], char pass[]) {

	Gestor* atual = inicio;
	while (atual != NULL) {
		if (atual->id == id)
		{
			if (strcmp(atual->nome, nome) == 0)
			{
				if (strcmp(atual->password, pass) == 0)
				{
					return 1;
				}
			}
		}
		atual = atual->seguinte;
	}
}

void listarMeiosPorAutonomia(Meio* inicio) {
	Meio* ponteiro1 = NULL;
	Meio* ponteiro2 = NULL;
	Meio* temp = NULL;
	int trocas;

	do {
		trocas = 0;
		ponteiro1 = inicio;

		while (ponteiro1->seguinte != ponteiro2) {
			if (ponteiro1->autonomia < ponteiro1->seguinte->autonomia) {
				temp = ponteiro1;
				ponteiro1 = ponteiro1->seguinte;
				ponteiro1->seguinte = temp;
				trocas = 1;
			}
			else {
				ponteiro1 = ponteiro1->seguinte;
			}
		}

		ponteiro2 = ponteiro1;
	} while (trocas);

	printf("Lista de meios de mobilidade eletrica por ordem decrescente de autonomia:\n");
	while (inicio != NULL) {
		printf(" ID - %d ; Tipo de Meio - %s ; Carga - %d ; Autonomia - %d ; Custo -  %.2f ; Localizacao - %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
		inicio = inicio->seguinte;

	}
}


void verificaLocalizacao(Meio* inicio, char localizacao[])
{
	printf("Meios com a mesma localizacao:\n");
	while (inicio != NULL)
	{
		if (strcmp(inicio->localizacao, localizacao) == 0)
		{
			printf(" ID - %d ; Tipo de Meio - %s ; Carga - %d ; Autonomia - %d ; Custo -  %.2f ; Localizacao - %s\n ", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo, inicio->localizacao);
		}
		inicio = inicio->seguinte;
	}
}

void registoaluguer(Meio* inicio,int idmeio, char idaluguer[50])
{
	FILE* fp;
	fp = fopen("registosAluguer.txt", "w");
	if (fp != NULL)
	{
		Meio* aux = inicio;
		while (aux != NULL)
		{
			fprintf(fp, "O meio com id - %d foi alugudado pelo - %s\n", idmeio, idaluguer);
			aux = aux->seguinte;
		}

		fclose(fp);
		printf("As informacoes foram guardadas no ficheiro %s\n", "registosAluguer.txt");
	}
}

