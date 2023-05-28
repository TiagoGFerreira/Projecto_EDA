#include <stdio.h>

//Esta estrutura Camiao representa o camiao que passa por todos os vertices do grafo e armazena o id do meio , a estrutura meio e um apontador para o elemento seguinte
typedef struct Camiao
{
	int idMeio;
	struct registoMeio* meio;
	struct Camiao* seguinte;
}

Camiao;

//Esta estrutura MeioGrafo representa os meios que tem vertice , guardando o id do meio , a estrutura meio e um apontador para o elemento seguinte
typedef struct MeioGrafo
{
	int idMeio;
	struct registoMeio* meio;
	struct MeioGrafo* seguinte;
}*Meios;

//Esta estrutura ClienteGrafo representa os clientes que tem vertice , guardando o id do cliente , a estrutura cliente e um apontador para o elemento seguinte
typedef struct ClienteGrafo
{
	int idCliente;
	struct registoCliente* cliente;
	struct ClienteGrafo* seguinte;
}*Clientes;

//Esta estrutura reprsente os adjacentes dos vertices , guardando o vertice de destino , o peso da aresta e um apontador do adjacente seguinte
typedef struct registoAdjacente
{
	char vertice[50];	// geoc�digo what3words
	float peso;
	struct registoAdjacente* seguinte;
}*Adjacente;

//Esta estrutura represente os vertices do grafo , guardando o vertice , um apontador para a estrutura Adjacente , ClienteGrafo e MeioGrafo e um apontador para o proximo vertice
typedef struct registoGrafo
{
	char vertice[50];	// geoc�digo what3words
	Adjacente adjacentes;
	Clientes cliente;
	Meios meio;
	// neste geoc�digo
	struct registoGrafo* seguinte;
}*Grafo;

//Estrutura Caminho que guarda cada caminho que o vertice passa para encontrar o caminho mais curto , guardando o vertice , a distancia e o proximo elemento
typedef struct Caminho
{
	char vertice[50];
	float distancia;
	struct Caminho* proximo;
}

Caminho;

//struct registoMeio, armazena as informa��es do meio de mobilidade
typedef struct registoMeio
{
	int id;
	char tipodemobilidade[50];
	int carga;
	int autonomia;
	float custo;
	char localizacao[50];
	int aluguer;
	struct registoMeio* seguinte;	// endere�o de mem�ria da struct registoMeio ,criando assim uma lista ligada onde cada elemento na lista cont�m um ponteiro para o pr�ximo elemento
}

Meio;

//struct registoCliente, armazena as informa��es do Cliente
typedef struct registoCliente
{
	int id;
	char nome[50];
	char morada[50];
	int idade;
	int nif;
	int telemovel;
	float saldo;
	char password[50];
	char localizacao[50];
	struct registoCliente* seguinte;	// endere�o de mem�ria da struct registoCliente ,criando assim uma lista ligada onde cada elemento na lista cont�m um ponteiro para o pr�ximo elemento
}

Cliente;

//struct registoGestor, armazena as informa��es do Gestor
typedef struct registoGestor
{
	int id;
	char nome[50];
	int nif;
	int telemovel;
	char password[50];
	struct registoGestor* seguinte;	// endere�o de mem�ria da struct registoGestor ,criando assim uma lista ligada onde cada elemento na lista cont�m um ponteiro para o pr�ximo elemento
}

Gestor;

// Inser��o de um novo registo de meio de mobilidade na lista ligada
Meio* inserirMeio(Meio* inicio, int id, char tipo[], int carga, int autonomia, float custo, char localizacao[], int aluguer);

// Printar o conte�do da lista ligada de meios de mobilidade
void listarMeios(Meio* inicio);

// Verificar se um meio de mobilidade com o ID especificado existe na lista ligada
int existeMeio(Meio* inicio, int id);

// Remover um meio de mobilidade da lista ligada a partir do ID especificado
Meio* removerMeio(Meio* inicio, int id);

// Ler as informa��es dos meios de mobilidade a partir do arquivo "meios.txt" e criar a lista ligada
Meio* lerMeios();

// Listar todos os meios de mobilidade dispon�veis para aluguel (aluguer = 0)
void MeiosParaAlugar(Meio* inicio);

// Alterar a vari�vel "aluguer" de um meio de mobilidade para 1, indicando que est� alugado
void AlugarMeios(struct registoMeio* lista, int id);

// Alterar a vari�vel "aluguer" de um meio de mobilidade para 0, indicando que est� dispon�vel para aluguel
void DesalugarMeios(struct registoMeio* lista, int id);

// Pedir novamente as informa��es do meio de mobilidade com o ID especificado e atualizar na mem�ria
void editarMeios(struct registoMeio* lista, int id);

// Guardar todas as informa��es da lista ligada de meios de mobilidade no arquivo "meios.txt"
void guardarMeios(Meio* inicio);

// Ler as informa��es dos clientes a partir do arquivo "clientes.txt" e criar a lista ligada
Cliente* lerCliente();

// Inser��o de um novo registo de cliente na lista ligada
Cliente* inserirCliente(Cliente* inicio, int id, char nome[], char mor[], int ida, int nif, int tele, float saldo, char pass[]);

// Printar o conte�do da lista ligada de clientes
void listarCliente(Cliente* inicio);

// Verificar se um cliente com o ID especificado existe na lista ligada
int existeCliente(Cliente* inicio, int id);

// Verificar se o ID, nome e senha fornecidos correspondem a um cliente na lista ligada
int verificaCliente(Cliente* inicio, int id, char nome[], char password[]);

// Remover um cliente da lista ligada a partir do ID especificado
Cliente* removerCliente(Cliente* inicio, int id);

// Pedir novamente as informa��es do cliente com o ID especificado e atualizar na mem�ria
void editarCliente(struct registoCliente* lista, int id);

// Guardar todas as informa��es da lista ligada de clientes no arquivo "clientes.txt"
void guardarClientes(Cliente* inicio);

// Inser��o de um novo registo de gestor na lista ligada
Gestor* inserirGestor(Gestor* inicio, int id, char nome[], int contribuinte, int tele, char password[]);

// Ler as informa��es dos gestores a partir do arquivo "gestores.txt" e criar a lista ligada
Gestor* lerGestor();

// Printar o conte�do da lista ligada de gestores
void listarGestor(Gestor* inicio);

// Verificar se um gestor com o ID especificado existe na lista ligada
int existeGestor(Gestor* inicio, int id);

// Remover um gestor da lista ligada a partir do ID especificado
Gestor* removerGestor(Gestor* inicio, int id);

// Pedir novamente as informa��es do gestor com o ID especificado e atualizar na mem�ria
void editarGestor(struct registoGestor* lista, int id);

// Guardar todas as informa��es da lista ligada de gestores no arquivo "gestores.txt"
void guardarGestores(Gestor* inicio);

// Listar os meios de mobilidade por ordem decrescente de autonomia
void listarMeiosPorAutonomia(Meio* inicio);

// Verificar se a localiza��o especificada existe na lista de meios de mobilidade e imprimir suas informa��es
void verificaLocalizacao(Meio* inicio, char localizacao[]);

// Criar um novo v�rtice no grafo
Grafo criarVertice(Grafo* g, char vertice[]);

// Verificar se um v�rtice j� existe no grafo
int existeVertice(Grafo g, char vertice[]);

// Remover um v�rtice do grafo
void removerVertice(Grafo grafo, char vertice[]);

// Remover uma aresta do grafo
void removerAresta(Grafo g, char vertice[]);

// Listar todos os v�rtices do grafo
void listarVertices(Grafo g);

// Criar uma aresta entre dois v�rtices no grafo com um peso especificado
void criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso);

// Verificar se uma aresta existe entre dois v�rtices no grafo
int existeAresta(Grafo g, char vOrigem[], char vDestino[]);

// Listar os v�rtices adjacentes a um v�rtice espec�fico no grafo
void listarAdjacentes(Grafo g, char vertice[]);

// Inserir um novo meio de mobilidade no grafo com base em um v�rtice existente
int inserirMeioV2(Grafo g, struct registoMeio* lista, char geocodigo[], int codigoMeio);

// Listar os meios de mobilidade presentes no grafo
void listarMeiosnoGrafo(Grafo g);

// Inserir um novo cliente no grafo com base em um v�rtice existente
int inserirClienteV2(Grafo g, struct registoCliente* lista, char geocodigo[], int codigoCliente);

// Listar os clientes presentes no grafo
void listarClientesnoGrafo(Grafo g);

// Guardar os v�rtices do grafo no arquivo "vertices.txt"
void guardarVertices(Grafo g);

// Guardar as informa��es de adjac�ncia do grafo no arquivo "adjacentes.txt"
void guardarAdjacentes(Grafo g);

// Guardar as informa��es dos meios de mobilidade no grafo no arquivo "meiografo.txt"
void guardarMeioGrafo(Grafo g);

// Guardar as informa��es dos clientes no grafo no arquivo "clientegrafo.txt"
void guardarClienteGrafo(Grafo g);

// Guardar todas as informa��es do grafo nos arquivos correspondentes
void guardarGrafo(Grafo g);

// Ler os v�rtices do grafo a partir do arquivo "vertices.txt"
Grafo lerVertices(Grafo* g);

// Ler as informa��es de adjac�ncia do grafo a partir do arquivo "adjacentes.txt"
void lerAdjacentes(Grafo g);

// Ler as informa��es dos meios de mobilidade do grafo a partir do arquivo "meiografo.txt"
Grafo lerMeioGrafo(Grafo g, struct registoMeio* lista);

// Ler as informa��es dos clientes do grafo a partir do arquivo "clientegrafo.txt"
Grafo lerClienteGrafo(Grafo g, struct registoCliente* lista);

// Ler todas as informa��es do grafo a partir dos arquivos correspondentes
Grafo lerGrafo(struct registoMeio* meio, struct registoCliente* cliente);

// Verificar se um v�rtice existe na lista de clientes no grafo
int existeVerticenoCliente(Grafo g, char vertice[]);

// Atualizar o v�rtice de um cliente no grafo com base no ID do cliente
void atualizarCliente(Grafo g, int idCliente, char novoVertice[]);

// Atualizar o v�rtice de um meio de mobilidade no grafo com base no ID do meio
void atualizarMeio(Grafo g, int idMeio, char novoVertice[]);

// Buscar os caminhos mais curtos a partir de um v�rtice inicial dentro de um determinado raio usando determinados meios de mobilidade
void buscarCaminhosMaisCurto(Grafo g, char verticeInicial[], float raio, struct registoMeio* meios, char meio[]);

// Remover todos os caminhos da estrutura de dados Caminho
void removerCaminho(Caminho** caminhos);

// Inserir um novo caminho na estrutura de dados Caminho
void inserirCaminho(Caminho** caminhos, char vertice[], float distancia);

// Verificar se um meio de mobilidade est� dispon�vel no v�rtice especificado
int VerificarMeio(Grafo g, char vertice[]);

// Buscar o ID do meio de mobilidade com base no v�rtice especificado
int buscarIDMeioPorVertice(Grafo g, char vertice[]);

// Buscar um meio de mobilidade pelo seu ID na lista de meios de mobilidade
Meio* buscarMeioPorID(struct registoMeio* meios, int id);

// Repor os meios de mobilidade dispon�veis no grafo com base na lista ligada de meios de mobilidade
void reporMeios(Meio* inicio, Camiao* atual);

// Verificar se um meio de mobilidade est� recolhido em um cami�o espec�fico com base no ID do meio
int verificarMeioRecolhido(struct Camiao* camiao, int idMeio);

// Encontrar o caminho mais curto para percorrer um circuito que retorna ao v�rtice inicial, levando em conta os meios de mobilidade dispon�veis
Camiao* encontrarCaminhoCircuitoMaisCurto(Grafo* g, char verticeInicial[], struct registoMeio* meios, struct Camiao* camiao);

// Inserir um meio de mobilidade em um cami�o
Camiao* inserirMeionoCamiao(Camiao* inicio, int idMeio, struct registoMeio* meio);

// Obter o v�rtice correspondente ao ID do cliente no grafo
char* obterVerticePorIDCliente(Grafo g, int idCliente);

// Guardar as informa��es do cami�o na estrutura de dados
void guardarCamiao(Camiao* camiao);

//L� as informa��es dentro do ficheiro camiao e insere na estrutura
Camiao* LerCamiao(Meio* meios);
