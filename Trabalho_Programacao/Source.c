/*
void criarVertice(Grafo* g, char geocodigo[])
{
    Grafo novo = malloc(sizeof(struct registoGrafo));
    if (novo != NULL)
    {
        strcpy(novo->vertice, geocodigo);
        novo->meios = NULL;
        novo->clientes = NULL;
        novo->seguinte = g;
        g = novo;
    }
}

int existeVertice(Grafo g, char vertice[])
{
    while (g != NULL)
    {
        if (strcmp(g->vertice, vertice) == 0) return(1);
        else g = g->seguinte;
    }
    return(0);
}


void criarAresta(Grafo g, char vOrigem[], char vDestino[], float peso)
{
    Adjacente novo;
    if (existeVertice(g, vOrigem) && existeVertice(g, vDestino))
    {
        while (strcmp(g->vertice, vOrigem) != 0) g = g->seguinte;
        novo = malloc(sizeof(struct registoGrafo));
        if (novo != NULL)
        {
            strcpy(novo->vertice, vDestino);
            novo->peso = peso;
            novo->seguinte = g->adjacentes;
            g->adjacentes = novo;
        }
    }
}


// Listar os vértices adjacentes 
void listarAdjacentes(Grafo g, char vertice[])
{
    Adjacente aux;
    if (existeVertice(g, vertice))
    {
        while (strcmp(g->vertice, vertice) != 0) g = g->seguinte;
        aux = g->adjacentes;
        if (aux == NULL)
        {
            printf("O vertice %s não tem adjacentes\n", vertice);
        }
        else {
            while (aux != NULL)
            {
                printf("Adjacente:%s Peso:%.2f\n", aux->vertice, aux->peso);
                aux = aux->seguinte;
            }
        }
    }
}

void inserirGeocodigoMeio(Grafo g, struct registoMeio* meio, int idMeio, char geocodigo[]) {
    // Verificar se o geocódigo existe na estrutura grafo
    while (g != NULL) {
        if (strcmp(g->vertice, geocodigo) == 0) {
            // O geocódigo existe na estrutura grafo
            // Procurar o meio de transporte com o id especificado
            struct registoMeio* atual = meio;
            while (meio != NULL) {
                if (meio->id == idMeio) {
                    // Atualizar o geocódigo do meio de transporte
                    strcpy(meio->localizacao, geocodigo);
                    printf("Geocódigo inserido com sucesso!\n");
                    g->meios = meio;
                    return;
                }
                meio = meio->seguinte;
            }
            printf("Meio com id %d não encontrado!\n", idMeio);
            return;
        }
        g = g->seguinte;
    }
    printf("Geocódigo %s não encontrado\n", geocodigo);
}

// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeios(Grafo g, char geocodigo[])
{
    while ((g != NULL) && (strcmp(g->vertice, geocodigo) != 0))
        g = g->seguinte;
    if (g != NULL)
    {
        Meio* aux = g->meios;
        if (aux == NULL) printf("sem meios de transporte\n");
        else while (aux != NULL)
        {
            printf("Codigo meio: %d\n", aux->localizacao);
            aux = aux->seguinte;
        }
    }
    else printf("geocodigo inexistente\n");
}
*/