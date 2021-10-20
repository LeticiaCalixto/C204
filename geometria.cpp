#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

struct ponto
{
	int x;
	int y; 	
};
typedef ponto vetor;

struct reta
{
	ponto A;
	ponto B;   	
};
typedef reta segmento;

vetor cria_vetor(ponto A,ponto B)
{
	vetor AB;
	AB.x = B.x - A.x;
	AB.y = B.y - A.y;
	return AB;
}

int vetorial(vetor A,vetor B)
{
	int v;
	v = A.x*B.y - A.y*B.x;
	return v;
}

int escalar(vetor A,vetor B)
{
	int e;
	e = A.x*B.x + A.y*B.y;
	return e;
}

float area_triangulo(ponto A,ponto B,ponto C)
{
	vetor AB;
	vetor AC;
	float area;
	AB = cria_vetor(A,B);
	AC = cria_vetor(A,C);
	area = fabs(vetorial(AB,AC)) / 2;
	return area;
}

/*
Posicao de C em relacao ao segmento AB
1 -> esquerda
-1 -> direita
0 -> colinear
*/
int sentido(ponto A,ponto B, ponto C)
{
	vetor AB;
	vetor AC;
	int vet;
	AB = cria_vetor(A,B);
	AC = cria_vetor(A,C);
	vet = vetorial(AB,AC);
	if(vet > 0)
		return 1;
	else if(vet < 0)
		return -1;
	else
		return 0;
}

/*
Verifica se o ponto P esta dentro do triangulo ABC
1 -> dentro
-1 -> fora
0 -> na linha
*/
int dentro_triangulo(ponto A,ponto B, ponto C,ponto P)
{
	int s1,s2,s3;
	s1 = sentido(A,B,P);
	s2 = sentido(B,C,P);
	s3 = sentido(C,A,P);
	if(s1 == s2 && s2 == s3)
		return 1; 
	else if(s1*s3 == -1 || s1*s2 == -1 || s2*s3 == -1)
		return -1;
	else
		return 0;
}

bool ponto_segmento(segmento S,ponto P)
{
	if(sentido(S.A,S.B,P) != 0)
		return false;
	else if(P.x > S.A.x && P.x < S.B.x)
		return true;
	else if(P.x < S.A.x && P.x > S.B.x)
		return true;
	else if(P.y < S.A.y && P.y > S.B.y)
		return true;
	else if(P.y > S.A.y && P.y < S.B.y)
		return true;
	else
		return false;
}


//Os pontos devem estar ordenados radialmente
//O poligono deve ser convexo
float area_poligono(ponto v[],int n)
{
	float area = 0;
	for(int i = 0;i < n-2;i++)
	{
		area = area + area_triangulo(v[0],v[i+1],v[i+2]);
	}
	return area;
}

//Calcular a distancia do ponto A ao ponto B
double dist( ponto A, ponto B ){
	vetor AB = cria_vetor(A, B);
	return hypot(AB.x, AB.y);
}


//Encontra os pontos que fazem parte do fecho convexo 
//(que seria o perimetro no caso)
void fechoConvexo(ponto *P, int &n){
	ponto fecho[n+1];
	int t, i;

	for(i=1;i<n;i++){
		if(P[i].y < P[0].y || (P[i].y == P[0].y && P[i].x < P[0].x)){
			swap(P[i], P[0]);
		}
	}

	for(i=1;i<n;i++){
		for(int j=i+1;j<n;j++){
			if( sentido(P[0], P[i], P[j]) == -1 ){
				swap(P[i], P[j]); // Troca o valor das variaveis
			}
			else if( sentido(P[0], P[i], P[j]) == 0 && dist(P[0], P[i]) > dist(P[0], P[j]) ){
				swap(P[i], P[j]); // Troca o valor das variaveis
			}
		}
	}

	P[n++] = P[0];

	fecho[0] = P[0];
	fecho[1] = P[1];
	t = 2;
	i = 2;

	while(i< n){
		if(t<2 || sentido(fecho[t-2],fecho[t-1],P[i])==1){
			fecho[t] = P[i];
			t++;
			i++;
		}
		else{
			t--;
		}
	}
	n = t;
	for(int i=0;i<t;i++){
		P[i] = fecho[i];
	}
}

int main()
{
	int N;
	double metros = 0.00;
	ponto P[1000];

	cin >> N;
	
	for(int i=0;i<N;i++){
		cin >> P[i].x >> P[i].y;
	}
	
	fechoConvexo(P,N);

	//calcula a distancia total do perimetro (distancia entre os pontos do fecho)
	for(int i=0;i<N-1;i++){
		metros += dist(P[i], P[i+1]);
	}
	
	cout << fixed << setprecision(2) << metros << " m" << endl;

	return 0;
}





