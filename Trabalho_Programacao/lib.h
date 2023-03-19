#include <stdio.h>


//struct registoMeio , armazena as informações do meio de mobilidade
typedef struct registoMeio {
	int id;
	char tipodemobilidade[50];
	int carga;
	int autonomia;
	float custo;
	char localizacao[50];
	int aluguer;
	struct registoMeio* seguinte; // endereço de memória da struct registoMeio ,criando assim uma lista ligada onde cada elemento na lista contém um ponteiro para o próximo elemento
}
Meio;

//struct registoCliente , armazena as informações do Cliente
typedef struct registoCliente {
	int id;
	char nome[50];
	char morada[50];
	int idade;
	int nif;
	int telemovel;
	float saldo;
	char password[50];
	struct registoCliente* seguinte; // endereço de memória da struct registoCliente ,criando assim uma lista ligada onde cada elemento na lista contém um ponteiro para o próximo elemento
}
Cliente;

//struct registoGestor , armazena as informações do Gestor
typedef struct registoGestor {
	int id;
	char nome[50];
	int nif;
	int telemovel;
	char password[50];
	struct registoGestor* seguinte; // endereço de memória da struct registoGestor ,criando assim uma lista ligada onde cada elemento na lista contém um ponteiro para o próximo elemento
}
Gestor;

// Inserção de um novo registo
Meio* inserirMeio(Meio* inicio, int id, char tipo[], int carga, int autonomia, float custo, char localizacao[], int aluguer);

// Printar o conteúdo da lista ligada
void listarMeios(Meio* inicio);

// Determinar existência do id na lista ligada 'inicio'
int existeMeio(Meio* inicio, int id);

// Remover um meio a partir do seu id
Meio* removerMeio(Meio* inicio, int id);

//guardar a informação do ficheiro meios.txt como variaveis e inserir na lista ligada 
Meio* lerMeios();

//Lista todos os meios em que a variavel aluguer encontra-se a 0 , ou seja disponiveis para alugar
void MeiosParaAlugar(Meio* inicio);

//muda a variavel aluguer da lista ligada para 1 do id inserido , mudando o seu estado para alugado
void AlugarMeios(struct registoMeio* lista, int id);

//muda a variavel aluguer da lista ligada para 0 do id inserido , mudando o seu estado para alugado
void DesalugarMeios(struct registoMeio* lista, int id);

//pede novamente as informações e atualizas na memória
void editarMeios(struct registoMeio* lista, int id);

//Guarda todas as informações da lista ligada no ficheiro meios.txt
void guardarMeios(Meio* inicio);

//guardar a informação do ficheiro clientes.txt como variaveis e inserir na lista ligada 
Cliente* lerCliente();

//Inserção de um novo registo
Cliente* inserirCliente(Cliente* inicio, int id, char nome[], char mor[], int ida, int nif, int tele, float saldo, char pass[]);

// Printar o conteúdo da lista ligada
void listarCliente(Cliente* inicio);

// Determinar existência do id na lista ligada 'inicio'
int existeCliente(Cliente* inicio, int id);

//vai verificar se o id inserido existe na lista ligada , e compara a string nome e password com as existe na struct desse id
int verificaCliente(Cliente* inicio, int id, char nome[], char password[]);

// Remover um cliente a partir do seu id
Cliente* removerCliente(Cliente* inicio, int id);

//pede novamente as informações e atualizas na memória
void editarCliente(struct registoCliente* lista, int id);

//Guarda todas as informações da lista ligada no ficheiro clientes.txt
void guardarClientes(Cliente* inicio);

//Inserção de um novo registo
Gestor* inserirGestor(Gestor* inicio, int id, char nome[], int contribuinte, int tele, char password[]);

//guardar a informação do ficheiro clientes.txt como variaveis e inserir na lista ligada 
Gestor* lerGestor();

// Printar o conteúdo da lista ligada
void listarGestor(Gestor* inicio);

// Determinar existência do id na lista ligada 'inicio'
int existeGestor(Gestor* inicio, int id);

// Remover um gestor a partir do seu id
Gestor* removerGestor(Gestor* inicio, int id);

//pede novamente as informações e atualizas na memória
void editarGestor(struct registoGestor* lista, int id);

//Guarda todas as informações da lista ligada no ficheiro gestores.txt
void guardarGestores(Gestor* inicio);

//vai verificar se o id inserido existe na lista ligada , e compara a string nome e password com as existe na struct desse id
int verificaGestor(Gestor* inicio, int id, char nome[], char password[]);

//lista os meios por ordem decrescente de autonomia
void listarMeiosPorAutonomia(Meio* inicio);

//compara a localização inserida com as existentes na lista e se houver iguais imprimes as informações desse meio
void verificaLocalizacao(Meio* inicio, char localizacao[]);