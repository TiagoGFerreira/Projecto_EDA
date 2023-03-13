#include <stdio.h>
// Remover um meio a partir do seu código

typedef struct registoMeio
{int id; // código do meio de mobilidade elétrica
char tipodemobilidade[50];
int carga;
int autonomia;
float custo;
 struct registoMeio* seguinte; // endereço de memória para uma struct registo
} Meio;

typedef struct registoCliente
{
	char nome[50];
	char morada[50];
	int idade;
	int nif;
	int telemovel;
	char password[50];
	struct registoCliente* seguinte; // endereço de memória para uma struct registo
} Cliente;

typedef struct registoGestor
{
	char nome[50];
	int nif;
	char password[50];
	struct registoGestor* seguinte; // endereço de memória para uma struct registo
} Gestor;


// Inserção de um novo registo
Meio* inserirMeio(Meio* inicio, int id, char tip[], int car, int aut, float cus);

// listar na consola o conteúdo da lista ligada
void listarMeios(Meio* inicio); 


// Determinar existência do 'codigo' na lista ligada 'inicio'
int existeMeio(Meio* inicio, int codigo); 

// Remover um meio a partir do seu código
Meio* removerMeio(Meio* inicio, int cod); 

void editarMeios(struct registoMeio* lista, int id);

void guardarMeios(Meio* inicio);

Cliente* inserirCliente(Cliente* inicio, char nome[], char mor[], int ida, int nif, int tele, char pass[]);

void listarCliente(Cliente* inicio);

int existeCliente(Cliente* inicio, char nome[]);

Cliente* removerCliente(Cliente* inicio, char nome[]);

void editarCliente(struct registoCliente* lista, char nome[]);

void guardarClientes(Cliente* inicio);

Gestor* inserirGestor(Gestor* inicio, char nome[], int contribuinte, char pass[]);

void listarGestor(Gestor* inicio);

int existeGestor(Gestor* inicio, char nome[]);

Gestor* removerGestor(Gestor* inicio, char nome[]);

void editarGestor(struct registoGestor* lista, char nome[]);

void guardarGestores(Gestor* inicio);

void listarMeiosPorAutonomia(Meio* inicio);