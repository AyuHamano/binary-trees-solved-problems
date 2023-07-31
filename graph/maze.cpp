#include <iostream>
#include <vector>
#include <cstdio>
#define MAX 10000 
using namespace std;
 

int count=0, labirinto[MAX], adjacencia[MAX][MAX], movimentos, nodos, aresta;

 
void percorreLabirinto (int vertice) {
    labirinto[vertice] = count++;
    for (int i = 0; i < nodos; i++) {
        //se o vértice ainda não foi percorrido então soma um movimento chama a função recursivamente
        if (adjacencia[vertice][i] == 1 && labirinto[i] == -1) {
            movimentos++;
            percorreLabirinto(i);
         }
    }
}


int main() {

    int inicio, fim, N, testes,origem;
    cin >> testes;
    while (testes--) {
        movimentos=0;
        cin >> origem >> nodos >> aresta;
        //inicializando a matriz de adj
        for (int i=0; i<nodos; i++) {
            for (int j=0; j<nodos; j++) {
                adjacencia[i][j]=0;
            }
        }
        //fazendo com q a matriz seja não direcionada
        for (int i=0; i<aresta; i++) {
            cin >> inicio >> fim;
            adjacencia[inicio][fim]=1;
            adjacencia[fim][inicio]=1;
        }
        //inicializando o vetor q tem as vértices do labirinto
        for (int i = 0; i < nodos; i++) {
            labirinto[i] = -1;
        }
        percorreLabirinto (origem);
        movimentos *= 2;
        cout << movimentos << "\n";
    }
 
    return 0;
}