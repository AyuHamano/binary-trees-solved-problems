#include <stack>
#include <queue>
#include <iostream>
#define N 1000
using namespace std;

void trocar(int *x, int *y) {
    int copy;
    copy = *y;
    *y = *x;
    *x = copy;
}

class Heap {
    int *h;
    int tamanhoHeap;
    public:
    Heap() {
        tamanhoHeap = 0;
        h = new int[N];
    }
    
    int getTamHeap() {return tamanhoHeap;}

    int pai(int i) {return (i-2)/2;}

    int esquerda(int i) {return 2*i + 1;}

    int direita(int i) {return 2*i + 1;}

    void inserir(int c) {
        tamanhoHeap++;
        int i = tamanhoHeap - 1;
        h[i] = c;

        while(i!=0 && h[pai(i)] < h[i]) {
            trocar(&h[pai(i)], &h[i]);
            i = pai(i);
        }
    }

    void maxHeapfy(int i) {
        int esq = esquerda(i);
        int dir = direita(i);
        int maior = i;
        if(esq < tamanhoHeap && h[esq] > h[i]) maior = esq;
        if(dir < tamanhoHeap && h[dir] > h[i]) maior = dir;
        if(maior != i) {
            trocar(&h[maior], &h[i]);
            maxHeapfy(maior);
        }
    }

    int extrairMaior() {
        if(tamanhoHeap == 1) {
            tamanhoHeap--;
            return h[0];
        }
        int raiz = h[0];
        h[0] = h[tamanhoHeap-1];
        tamanhoHeap--;
        maxHeapfy(0);
        return raiz;
    }
};

int main() {
    stack<int> pilha;
    queue<int> fila;
    Heap h;
    bool p=true, f=true, pri=true;
    int n, comando, vet[N];

    while(cin >> n) {
        for(int i=0; i<n; i++) {
            cin >> comando;
            cin >> vet[i];
    
            if(comando == 1) { 
                fila.push(vet[i]);
                pilha.push(vet[i]);
                h.inserir(vet[i]);
            }
            else if(comando == 2) {
                if(fila.front() != vet[i]) f = false;
                fila.pop();
                if(pilha.top() != vet[i]) p = false; 
                pilha.pop();
                if(h.extrairMaior() != vet[i]) pri = false;
            }
        }
        if((f&&p) || (f&&pri) || (pri&&p)) cout << "not sure\n";
        else if (!(f || p || pri)) cout << "impossible\n";
        else if((f) && !(p || pri)) cout << "queue\n";
        else if((p) && !(f || pri)) cout << "stack\n";
        else if((pri) && !(f || p)) cout << "priority queue\n";
        
        pri = true;
        f = true;
        p = true;
        while(!fila.empty() || !pilha.empty() || h.getTamHeap() !=0) {
            int j = h.extrairMaior();
            fila.pop();
            pilha.pop();
        }
    }
};


