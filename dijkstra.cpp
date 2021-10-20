#include <iostream>
#include <vector>
#include <climits>
#include <stack>

using namespace std;
#define MAX 100

struct no
{
	int v; // vertice adjacente
	int peso; // peso da aresta
};

struct grafo
{
	int n_vertices; // numero de vertices
	int n_arestas; // numero de arestas
	vector <no> adj[MAX];
};

void cria_aresta(grafo &G,int u,int v,int peso,bool direcionado)
{
	no nova_aresta;
	nova_aresta.v = v;
	nova_aresta.peso = peso;
	G.adj[u].push_back(nova_aresta);
	if(!direcionado)
	{
		cria_aresta(G,v,u,peso,true);
	}
}

// recuepera o caminho para ir do inicio ao fim
void mostra_caminho(int pai[],int v_fim)
{
	stack <int> pilha;
	int aux;
	
	aux = v_fim;
	
	while(aux != -1)
	{
		pilha.push(aux);
		aux = pai[aux];
	}
	
	while(!pilha.empty())
	{
		cout << pilha.top() << " ";
		pilha.pop();
	}
	cout << endl;
	
}

// Retorna o custo total do menor caminho entre v_ini e v_fim
int dijkstra(grafo G,int v_ini,int v_fim)
{
	int distancia[G.n_vertices];
	int pai[G.n_vertices];
	int vis[G.n_vertices];
	int u;
	int dist;
	for(int i = 0;i < G.n_vertices;i++)
	{
		vis[i] = 0; // nao visitou
		pai[i] = -1; // nao tem pai ainda
		distancia[i] = INT_MAX; // distancia infinita para o vertice inicial
	}
	distancia[v_ini] = 0;
	u = v_ini;
	while(!vis[u])
	{
		vis[u] = 1; // visitei o vertice 'u'
		// atualiza qual a menor
		for(int i = 0; i < G.adj[u].size();i++)
		{
			int v = G.adj[u][i].v;
			int custo = G.adj[u][i].peso;
			if(distancia[v] > distancia[u] + custo)
			{
				distancia[v] = distancia[u] + custo;
				pai[v] = u;
			}
		}
		
		u = 0;
		dist = INT_MAX;
		
		//Procura o vertice mais perto que ainda nao visitei
		for(int i = 0; i < G.n_vertices; i++)
		{
			if(!vis[i] && dist > distancia[i])
			{
				u = i;
				dist = distancia[i];
			}
		}
	}
	
	mostra_caminho(pai,v_fim); 
	
	return distancia[v_fim];
}

int main(){
	int T; //caso de teste
	int u; //origem
	int c; //distancia
	int custo;
	int ini, fim;
	grafo G;
	no NO;

	cin >> T;
	
	for(int i=0;i<T;i++){
		cin >> G.n_vertices;
		cin >> G.n_arestas;

		for(int j=0; j<G.n_arestas;j++){
			cin >> u >> NO.v >> c;
			cria_aresta(G, u, NO.v, c, true);
		}

		cin >> ini >> fim;
		
		cout << "Caso#" << i << endl;
		
		custo = dijkstra(G, ini, fim);
		
		cout << custo << endl;
	}
	
	return 0;
}