#include <iostream>
#include <vector>
#include <climits>
#define MAX 100

using namespace std;

struct no{
	int v;// vertice
	int peso; // peso
};

struct grafo{
	int n; // num de vertices
	int m; // num de arestas
	vector <no> adj[100]; // lista de adjacencias
};

void prim(grafo &GRAFO, int v_inicio)
{
	int custo_total = 0;
	bool na_arvore[MAX];
	int distancia[MAX];
	int pai[MAX];
	int v_atual;
	int v;
	int peso;
	int dist;

	// no inicio...
	for(int i = 0; i < GRAFO.n;i++)
	{
		na_arvore[i] = false; // ...todos estao fora da arvore geradora minima (MST)
		distancia[i] = INT_MAX;// a distancia de todos para a MST eh INFINITA
		pai[i] = -1; // ninguem tem pai
	}

	distancia[v_inicio] = 0; // distancia do vertice inicial para a arvore eh 0 (ele vai ser o primeiro a ser colocado na arvore)
	v_atual = v_inicio;

	while(na_arvore[v_atual] == false) // enquanto houver um vertice fora da arvore geradora minima
	{
		na_arvore[v_atual] = true; // adiciona o vertice atual na arvore
		custo_total = custo_total + distancia[v_atual]; // adiciona o peso da aresta que ligou o vertice a arvore(se for o primeiro, o custo sera 0)

		for(int i = 0;i < GRAFO.adj[v_atual].size();i++) // varrendo a lista de adj.s do vertice atual( para encontrar possiveis distancias menores da arvore para outros vertices)
		{
			v = GRAFO.adj[v_atual][i].v;
			peso = GRAFO.adj[v_atual][i].peso;

			if((distancia[v] > peso) && (na_arvore[v] == false))
			{

				distancia[v] = peso;
				pai[v] = v_atual;

			}

		}
		v_atual = 0;
		dist = INT_MAX;

		for(int i = 0;i < GRAFO.n;i++) // descobrindo qual o vertice esta mais proximo da arvore
		{

			if((na_arvore[i] == false) && (dist > distancia[i]))
			{
				dist = distancia[i];
				v_atual = i;

			}

		}
	}
	cout << custo_total << endl;

}

int main(){
    int M; // quantidade de caminhos
    int u; //destino
    grafo G;
    no NO;
    
    cin >> G.n; //casas no bosque
    
    cin >> M;
    
    for(int i=0;i<M;i++){
		cin >> NO.v >> u >> NO.peso;
		G.adj[u].push_back(NO);
	}
	
	
	
	return 0;
}
