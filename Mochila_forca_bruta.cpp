#include <iostream>
#include <algorithm>
using namespace std;

struct item
{
	int peso;
	int valor;
};

int mochila_fb(item v[],int n,int cap,int i)
{
	if(i == n) return 0; // se ja analizou todos os itens, nao consigo mais nada de valor
	else if(cap == 0) return 0; // se a capacidade for 0, nao consigo mais nada de valor
	else
	{
		int pegar;
		int nao_pegar;
		pegar = 0; // inicializar a opção pegar
		if(cap >= v[i].peso) // Se houver capacidade disponivel
		{						
			pegar = mochila_fb(v,n,cap-v[i].peso,i+1) + v[i].valor; //diminui a capacidade, vai para o proximo item e soma o valor do item atual
		}
		nao_pegar = mochila_fb(v,n,cap,i+1); // opção não pegar, mantem a capacidade e vai para o proximo item
		return max(pegar,nao_pegar); // retorna o maior entre as opções pegar e não pegar
	}
}

int main()
{
	item v[100]; // vetor para armazenar os itens
	int capacidade; // capacidade maxima da mochila
	int n; // quantidade de itens
	cout <<"Entre com a quantidade de itens:";
	cin >> n;
	cout <<"Entre com a capacidade maxima da mochila:";
	cin >> capacidade;
	
	for(int i = 0;i < n;i++) // Entrada dos pesos e valores de cada item
	{
		cout << "Entre com o peso do item " << i << endl;
		cin >> v[i].peso;
		cout << "Entre com o valor do item " << i << endl;
		cin >> v[i].valor;
	}
	
	cout << mochila_fb(v,n,capacidade,0) << endl; // começa com a capacidade maxima da mochila disponivel e a partir do item 0
	return 0;	
}












