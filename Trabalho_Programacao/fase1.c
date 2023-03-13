#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "lib.h"


Meio* inserirMeio(Meio* inicio, int id, char tip[], int car, int aut , float cus)
{
	if (!existeMeio(inicio, id))
	{
		Meio* novo = malloc(sizeof(struct registoMeio));
		if (novo != NULL)
		{
			novo->id = id;
			strcpy(novo->tipodemobilidade, tip);
			novo->carga = car;
			novo->autonomia = aut;
			novo->custo = cus;
			novo->seguinte = inicio;
			return(novo);
		}
	}
	else return(inicio);

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

	if (atual == NULL) return(NULL); // lista ligada vazia
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

void listarMeios(Meio* inicio)
{
	while (inicio != NULL)
	{
		printf("%d %s %d %d %.2f\n", inicio->id, inicio->tipodemobilidade,inicio->carga, inicio->autonomia, inicio->custo);
		inicio = inicio->seguinte;
	}
}

void editarMeios(struct registoMeio* lista, int id) {
	struct registoMeio* atual = lista;
	while (atual != NULL) {
			printf("Digite os novos dados para o ID - %d:\n", id);
			printf("Tipo de Mobilidade: ");
			scanf("%s", atual->tipodemobilidade);
			printf("Carga: ");
			scanf("%d", &atual->carga);
			printf("Autonomia: ");
			scanf("%d", &atual->autonomia);
			printf("Custo: ");
			scanf("%f", &atual->custo);
			printf("Dados atualizados com sucesso!\n");
			return;
		atual = atual->seguinte;
	}
	printf("O ID - %d nao foi encontrado na lista.\n", id);
}

void guardarMeios(Meio* inicio) {
	FILE* arquivo = fopen("meios.txt", "w");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo %s.\n", "meios.txt");
		return;
	}

	Meio* atual = inicio;
	while (atual != NULL) {
		fprintf(arquivo, "ID - %d , Tipo de Mobilidade - %s , Carga -  %d , Autonomia - %d , Custo - %.2f\n", atual->id, atual->tipodemobilidade, atual->carga, atual->autonomia, atual->custo);
		atual = atual->seguinte;
	}

	fclose(arquivo);
	printf("As informacoes foram guardadas no ficheiro %s\n", "meios.txt");
}

Cliente* inserirCliente(Cliente* inicio, char nome[], char mor[], int ida, int contribuinte, int tele, char pass[])
{

	//FILE* fp;
	//fp = fopen("cliente.txt", "w");

	if (!existeCliente(inicio, nome))
	{
		Cliente* novo = malloc(sizeof(struct registoCliente));
		if (novo != NULL)
		{
		//	if (fp == NULL) {
			//	printf("Ficheiro txt não existe\n");
			//	exit(1);
			

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

int existeCliente(Cliente* inicio, char nome[])
{
	while (inicio != NULL)
	{
		if (inicio->nome == nome) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

Cliente* removerCliente(Cliente* inicio, char nome[])
{
	Cliente* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return(NULL); // lista ligada vazia
	else if (atual->nome == nome) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (nome != nome))
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
		printf("%s %s %d %d %d %s\n", inicio->nome, inicio->morada, inicio->idade, inicio->nif,  inicio->telemovel, inicio->password);
		inicio = inicio->seguinte;
	}
}

void editarCliente(struct registoCliente* lista, char nome[]) {
	struct registoCliente* atual = lista;
	while (atual != NULL) {
		if (strcmp(atual->nome, nome) == 0) {
			printf("Digite os novos dados para o Cliente %s:\n", nome);
			printf("Morada: ");
			scanf("%s", atual->morada);
			printf("Idade: ");
			scanf("%d", &atual->idade);
			printf("NIF: ");
			scanf("%d", &atual->nif);
			printf("Telemovel: ");
			scanf("%d", &atual->telemovel);
			printf("Password: ");
			scanf("%s", &atual->password);
			printf("Dados atualizados com sucesso!\n");
			return;
		}
		atual = atual->seguinte;
	}
	printf("O nome %s nao foi encontrado na lista.\n", nome);
}

void guardarClientes(Cliente* inicio) {
	FILE* arquivo = fopen("clientes.txt", "w");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo %s.\n", "clientes.txt");
		return;
	}

	Cliente* atual = inicio;
	while (atual != NULL) {
		fprintf(arquivo, "Nome - %s , Morada - %s , Idade -  %d , NIF - %d , Telemovel - %d, Password - %s\n", atual->nome, atual->morada, atual->idade, atual->nif, atual->telemovel, atual->password);
		atual = atual->seguinte;
	}

	fclose(arquivo);
	printf("As informacoes foram guardadas no ficheiro %s\n", "clientes.txt");
}

Gestor* inserirGestor(Gestor* inicio, char nome[], int contribuinte, char pass[])
{
	if (!existeGestor(inicio, nome))
	{
		Gestor* novo = malloc(sizeof(struct registoGestor));
		if (novo != NULL)
		{
			strcpy(novo->nome, nome);
			novo->nif = contribuinte;
			strcpy(novo->password, pass);
			novo->seguinte = inicio;
			return(novo);
		}
	}
	else return(inicio);
}


int existeGestor(Gestor* inicio, char nome[])
{
	while (inicio != NULL)
	{
		if (inicio->nome == nome) return(1);
		inicio = inicio->seguinte;
	}
	return(0);
}

Gestor* removerGestor(Gestor* inicio, char nome[])
{
	Gestor* anterior = inicio, * atual = inicio, * aux;

	if (atual == NULL) return(NULL); // lista ligada vazia
	else if (atual->nome == nome) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		return(aux);
	}
	else
	{
		while ((atual != NULL) && (nome != nome))
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
		printf("%s %d %s\n", inicio->nome, inicio->nif, inicio->password);
		inicio = inicio->seguinte;
	}
}

void editarGestor(struct registoGestor* lista, char nome[]) {
	struct registoGestor* atual = lista;
	while (atual != NULL) {
		if (strcmp(atual->nome, nome) == 0) {
			printf("Digite os novos dados para o Gestor %s:\n", nome);
			printf("NIF: ");
			scanf("%d", &atual->nif);
			printf("Password: ");
			scanf("%s", &atual->password);
			printf("Dados atualizados com sucesso!\n");
			return;
		}
		atual = atual->seguinte;
	}
	printf("O Gestor %s nao foi encontrado na lista.\n", nome);
}

void guardarGestores(Gestor* inicio) {
	FILE* arquivo = fopen("gestores.txt", "w");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo %s.\n", "gestores.txt");
		return;
	}

	Gestor* atual = inicio;
	while (atual != NULL) {
		fprintf(arquivo, "Nome - %s , NIF - %d , Password -  %s\n", atual->nome, atual->nif, atual->password);
		atual = atual->seguinte;
	}

	fclose(arquivo);
	printf("As informacoes foram guardadas no ficheiro %s\n", "gestores.txt");
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

	printf("Lista de meios de mobilidade elétrica por ordem decrescente de autonomia:\n");
	while (inicio != NULL) {
		printf("%d %s %d %d %.2f\n", inicio->id, inicio->tipodemobilidade, inicio->carga, inicio->autonomia, inicio->custo);
		inicio = inicio->seguinte;

	}
}
