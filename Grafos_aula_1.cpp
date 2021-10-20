#include <iostream>
#include <vector> // para usar o vector
#define MAX 100 // numero maximo de vertices

using namespace std;

struct no
{
	int peso; // peso da aresta
	int v; // vertice de destino
};

struct grafo
{
	vector<no> adj[MAX];
	int n_vertices; // numero de vertices
	int n_arestas; // numero de aresta
};

void cria_aresta(grafo &G, int u, int v, int peso, bool direcionado)
{
	// cria a aresta de u -> v
	no nova_aresta;
	nova_aresta.v = v; // vertice vizinho a u
	nova_aresta.peso = peso; // peso da aresta

	// No grafo G, na lista de adj. do vertice u, adiciona a nova aresta
	G.adj[u].push_back(nova_aresta);

	if(direcionado == false) // se for nao direcionado
	{
		// cria a aresta de v -> u
		cria_aresta(G, v, u, peso, true);
	}
}

void mostra_grafo(grafo G)
{

	for(int u = 0; u < G.n_vertices; u++)
	{
		cout << "Do vertice " << u << ":" << endl;
		
		for(int i = 0; i < (int)G.adj[u].size(); i++)
		{
			int v = G.adj[u][i].v;
			int peso = G.adj[u][i].peso;

			cout << "	vertice " << v << " peso " << peso << endl;
		}
	}

}

void deleta_grafo(grafo &G)
{
	for(int i = 0; i < G.n_vertices; i++)
	{
		// apaga a lista de adj. do vertice i
		G.adj[i].clear();
	}
	G.n_vertices = 0;
	G.n_arestas = 0;
}

int main()
{
	
}











