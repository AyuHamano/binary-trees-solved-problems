#include <stack>
#include <queue>
#include <iostream>
#define N 10000
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

    int pai(int i) {return i/2;}

    int esquerda(int i) {return 2*i;}
 
    int direita(int i) {return 2*i + 1;}

    void inserir(int c) {
        tamanhoHeap++;
        h[tamanhoHeap] = c;
        heapify_up(tamanhoHeap);
    }

    void heapify_down(int i) {
        int esq = esquerda(i);
        int dir = direita(i);
        int maior = i;
        if(esq < tamanhoHeap && h[esq] > h[maior]) maior = esq;
        if(dir < tamanhoHeap && h[dir] > h[maior]) maior = dir;
        if(maior != i) {
            trocar(&h[maior], &h[i]);
            heapify_down(maior);
        }
    }

    void heapify_up(int v) {
        if(v == 1) return;

        int p = v-1;
        if(h[v] > h[p]){
            trocar(&h[v], &h[p]);
            heapify_up(p);
        }
    
    }

    void maxHeapify(int i)
{
    int l = esquerda(i);
    int r = direita(i);
    int maior = i;
    if (l <= tamanhoHeap && h[l] > h[maior])
        maior = l;
    if (r <= tamanhoHeap && h[r] > h[maior])
        maior = r;
    if (maior != i)
    {
        trocar(&h[i], &h[maior]);
        maxHeapify(maior);
    }
}

    int extrairMaior() {
        if(tamanhoHeap == 1) {
            tamanhoHeap--;
            return h[1];
        }
        int raiz = h[1];
        h[1] = h[tamanhoHeap];
        tamanhoHeap--;
        maxHeapify(1);
        return raiz;
    }
    void imprime() {
        for(int i=1; i<=tamanhoHeap; i++) {
            cout << "  "<< h[i];
        }
    }
};

int main() {
    stack<int> pilha;
    queue<int> fila;
    Heap h;
    bool p=true, f=true, pri=true;
    int n, comando, vet[N];

    while(cin >> n) {
        for(int i=1; i<=n; i++) {
            cin >> comando;
            cin >> vet[i];
    
            if(comando == 1) { 
                fila.push(vet[i]);
                pilha.push(vet[i]);
                h.inserir(vet[i]);
            }
            if(comando == 2) {
                if(fila.front() != vet[i]) f = false;
                if(pilha.top() != vet[i]) p = false; 
                fila.pop();
                pilha.pop();
                int maior = h.extrairMaior();
                //cout << "maior ->" << maior;
                if(maior != vet[i]) pri = false;
            }
            
        }
        if((f&&p) || (f&&pri) || (pri&&p)) cout << "not sure\n";
        else if (!(f || p || pri)) cout << "impossible\n";
        else if(f) cout << "queue\n";
        else if(p) cout << "stack\n";
        else if(pri) cout << "priority queue\n";
        
        
        pri = true;
        f = true;
        p = true;
        while(!fila.empty() && !pilha.empty() && h.getTamHeap() !=0) {
            int j = h.extrairMaior();
            fila.pop();
            pilha.pop();
        }
    }
};


