#include <stdio.h>
// Remover um meio a partir do seu código

typedef struct registoMeio {
	int id; // código do meio de mobilidade elétrica
	char tipodemobilidade[50];
	int carga;
	int autonomia;
	float custo;
	char localizacao[50];
	int aluguer;
	struct registoMeio* seguinte; // endereço de memória para uma struct registo
}
Meio;

typedef struct registoCliente {
	int id;
	char nome[50];
	char morada[50];
	int idade;
	int nif;
	int telemovel;
	char password[50];
	struct registoCliente* seguinte;
	struct registoMeio* aluguer; // endereço de memória para uma struct registo
}
Cliente;

typedef struct registoGestor {
	int id;
	char nome[50];
	int nif;
	int telemovel;
	char password[50];
	struct registoGestor* seguinte; // endereço de memória para uma struct registo
}
Gestor;

// Inserção de um novo registo
Meio* inserirMeio(Meio* inicio, int id, char tipo[], int carga, int autonomia, float custo, char localizacao[], int aluguer);

// listar na consola o conteúdo da lista ligada
void listarMeios(Meio* inicio);

// Determinar existência do 'codigo' na lista ligada 'inicio'
int existeMeio(Meio* inicio, int id);

// Remover um meio a partir do seu código
Meio* removerMeio(Meio* inicio, int id);

Meio* lerMeios();

void MeiosParaAlugar(Meio* inicio);

void AlugarMeios(struct registoMeio* lista, int id);

void DesalugarMeios(struct registoMeio* lista, int id);

void editarMeios(struct registoMeio* lista, int id);

void guardarMeios(Meio* inicio);

Cliente* lerCliente();

Cliente* inserirCliente(Cliente* inicio, int id, char nome[], char mor[], int ida, int nif, int tele, char pass[]);

void listarCliente(Cliente* inicio);

int existeCliente(Cliente* inicio, int id);

int verificaCliente(Cliente* inicio, int id, char nome[], char password[]);

Cliente* removerCliente(Cliente* inicio, int id);

void editarCliente(struct registoCliente* lista, int id);

void guardarClientes(Cliente* inicio);

Gestor* inserirGestor(Gestor* inicio, int id, char nome[], int contribuinte, int tele, char password[]);

Gestor* lerGestor();

void listarGestor(Gestor* inicio);

int existeGestor(Gestor* inicio, int id);

Gestor* removerGestor(Gestor* inicio, int id);

void editarGestor(struct registoGestor* lista, int id);

void guardarGestores(Gestor* inicio);

int verificaGestor(Gestor* inicio, int id, char nome[], char password[]);

void listarMeiosPorAutonomia(Meio* inicio);

void verificaLocalizacao(Meio* inicio, char localizacao[]);