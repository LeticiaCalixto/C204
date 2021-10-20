#include <iostream>
#include <cmath> // fabs() = (valor ABSoluto) modulo de numero float
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct ponto
{
	int x; // poderia ser float, dependendo do caso
	int y; // poderia ser float, dependendo do caso
};

typedef ponto vetor;

float vetorial(vetor A,vetor B)
{
	return (A.x*B.y - B.x*A.y);
}
vetor cria_vetor(ponto A,ponto B)
{
	vetor AB;
	AB.x = B.x-A.x;
	AB.y = B.y-A.y;
	return AB;
}

/*
1 -> anti-horario
0 -> colineares
-1 -> horario
*/
int sentido(ponto A,ponto B,ponto C)
{
	vetor AB,AC;
	float resultado;
	AB = cria_vetor(A,B);
	AC = cria_vetor(A,C);
	resultado = vetorial(AB,AC);
	if(resultado > 0)
		return 1;
	else if(resultado < 0)
		return -1;
	else
		return 0;
}

bool cmp(ponto a,ponto b)
{
	float angA = atan2(a.y,a.x);
	float angB = atan2(b.y,b.x);
	if(angA == angB){
		float distA = hypot(a.x,a.y);
		float distB = hypot(b.x,b.y);
		return distA > distB;
	}
	else
		return angA < angB;
}

ponto next_to_top(stack <ponto> pilha)
{
	pilha.pop();
	return pilha.top();
}

stack <ponto> Graham_scan(vector <ponto> pontos)
{
	stack <ponto> pilha;
	ponto pivot;
	pivot = pontos[0];
	
	//Encontrando o pivo
	for(int i = 1;i < pontos.size();i++)
	{
		if(pontos[i].y < pivot.y || pontos[i].y == pivot.y && pontos[i].x < pivot.x)
		{
			pivot = pontos[i];
		}
	}
	for(int i = 0;i < pontos.size();i++)
	{
		if(pivot.x == pontos[i].x && pivot.y == pontos[i].y)
		{
			swap(pontos[i],pontos[0]);
		}
	}
	
	// Fazendo a ordenacao
	for(int i = 0;i < pontos.size();i++)
	{
		pontos[i].x = pontos[i].x - pivot.x;
		pontos[i].y = pontos[i].y - pivot.y;
	}
	
	sort(pontos.begin()+1,pontos.end(),cmp);
	
	for(int i = 0;i < pontos.size();i++)
	{
		pontos[i].x = pontos[i].x + pivot.x;
		pontos[i].y = pontos[i].y + pivot.y;
	}
	
	// Inserindo os 3 primeiros pontos na pilha
	pilha.push(pontos[0]);
	pilha.push(pontos[1]);
	pilha.push(pontos[2]);
	int i = 3;
	while(i < pontos.size())
	{
		if(sentido(next_to_top(pilha),pilha.top(),pontos[i]) == 1)// se fez curva pra esquerda
		{
			pilha.push(pontos[i]); // insere na pilha
			i++; // vai pro proximo ponto
		}
		else  //se fez curva pra direita
		{
			pilha.pop(); // remove o topo da pilha
		}
	}
	return pilha;
}


int main()
{
	vector <ponto> pontos;
	stack <ponto> pilha;
	ponto aux;
	
	int n; // quantidade de pontos
	cout << "Entre com o numero de pontos: ";
	cin >> n;
	for(int i = 0;i < n;i++)
	{
		cin >> aux.x >> aux.y;
		pontos.push_back(aux);
	}
	pilha = Graham_scan(pontos);
	
	cout << "Pontos que fazem parte do fecho convexo:" << endl;
	
	while(!pilha.empty())
	{
		cout << pilha.top().x << " " <<pilha.top().y << endl;
		pilha.pop();
	}
	
	return 0;
}


























