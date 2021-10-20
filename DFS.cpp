#include <iostream>
#include <vector>
#include <algorithm> // swap
#define MAX 100 // numero maximo de vertices
using namespace std;

struct no
{
    int v; // vertice adjacente
    int peso; // peso da aresta
};

struct grafo
{
    int n_vertices; // numero de vertices
    int n_arestas; // numero de arestas
    vector <no> adj[MAX]; // lista de adjacencias
};

// funcao para criar uma aresta no grafo
void cria_aresta(grafo &G,int u,int v,int p,bool direcionado)
{
    no nova_aresta;
    nova_aresta.v = v;
    nova_aresta.peso = p;
    G.adj[u].push_back(nova_aresta);
    if(!direcionado) // se for nao direcionado
    {
        cria_aresta(G,v,u,p,1); // cria uma aresta no sentido contrario
    }
}

// funcao para mostrar a lista de adjacencias do grafo
void mostra_grafo(grafo G)
{
    for(int i = 0; i < G.n_vertices; i++)
    {
        cout << "Vertice: " << i <<":" << endl;
        for(int j = 0; j < G.adj[i].size(); j++)
            // Aresta do vertice 'i' para o vertice G.adj[i][j].v (nao eh necessariamente o vertice j) com peso G.adj[i][j].peso
            cout << G.adj[i][j].v <<" com peso " << G.adj[i][j].peso << endl;
        cout << endl;
    }
}

void DFS_visit(grafo &G,int &time,int u,int vis[],int d[],int f[])
{
    vis[u] = 1;
    time++;
    d[u] = time;
    for(int i = 0; i < G.adj[u].size(); i++)
    {
        int v;
        v = G.adj[u][i].v;
        if(!vis[v])
        {
			DFS_visit(G,time,v,vis,d,f);
        }
    }
    time++;
    f[u] = time;
}

void DFS(grafo &G)
{
    int vis[G.n_vertices]; // 0 = nao visitado // 1 = visitado e sendo processado // 2 = visitado e processado
    int d[G.n_vertices]; // marca o momento que o vertice eh descoberto
    int f[G.n_vertices]; // marca o final do processamento do vetice
    int topologic[G.n_vertices]; // vetor utilizado na ordenação topologica
    int time;

    for(int i = 0; i < G.n_vertices; i++)
    {
        vis[i] = 0;	// nenhum vertice foi visitado
        topologic[i] = i;
    }
    time  = 0;

    for(int i = 0; i < G.n_vertices; i++)
    {
        if(!vis[i])
            DFS_visit(G,time,i,vis,d,f);	
    }
    
    // ordenacao topologica
    for(int i = 0;i < G.n_vertices;i++)
		for(int j = i+1;j < G.n_vertices;j++)
			if(f[topologic[i]]  < f[topologic[j]])
			{
				swap(topologic[i],topologic[j]);
			}
			
	for(int i = 0;i < G.n_vertices;i++)	
	{
		if(i != G.n_vertices-1) // se nao for o ultimo
			cout << topologic[i] << " -> "; // mostra com seta na frente
		else // se for o ultimo
			cout << topologic[i] << endl; // coloca uma quebra de linha
	}	
}

int main()
{
    grafo G;
    int u; // vertice de origem
    int v; // vertice de destino
    
    cout << "Entre com o numero de vertices:" << endl;
    cin >> G.n_vertices;
    cout << "Entre com o numero de arestas:" << endl;
    cin >> G.n_arestas;
    
    for(int i = 0; i < G.n_arestas; i++)
    {
        cout << "Entre com o vertice de origem:" <<endl;
        cin >> u;
        cout << "Entre com o vertice de destino:" << endl;
        cin >> v;
        cria_aresta(G,u,v,1,true); // direcionado, pois para um grafo conter ordenacao topologica, ele deve ser uma grafo direcionado aciclico
    }
    mostra_grafo(G);
    DFS(G);
    return 0;
}
