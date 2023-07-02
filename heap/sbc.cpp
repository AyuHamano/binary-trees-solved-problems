#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#define N 10001
using namespace std;



class Processo {
public:
    long long int t;
    long long int c;
    Processo(){}
};
class Comp {
public:
    bool operator () (const Processo* p1, const Processo* p2) {
        return (p1->c > p2->c);
    }
};
bool sortAlg(Processo* p1, Processo* p2){
    return p1->t < p2->t;
}
class PriorityQueue
{
private:
    // vector para armazenar elementos de heap
    vector<long long int> A;
 
    // retorna o pai de `A[i]`
    // não chame esta função se `i` já for um nó raiz
    int PARENT(int i) {
        return (i - 1) / 2;
    }
 
    // retorna o filho esquerdo de `A[i]`
    int LEFT(int i) {
        return (2*i + 1);
    }
 
    // retorna o filho direito de `A[i]`
    int RIGHT(int i) {
        return (2*i + 2);
    }
 
    // Algoritmo de heapify-down recursivo.
    // O nó no índice `i` e seus dois filhos diretos
    // viola a propriedade heap
    void heapify_down(int i)
    {
        // obtém filho esquerdo e direito do nó no índice `i`
        int left = LEFT(i);
        int right = RIGHT(i);
 
        int smallest = i;
 
        // compara `A[i]` com seu filho esquerdo e direito
        // e encontrar o menor valor
        if (left < size() && A[left] < A[i]) {
            smallest = left;
        }
 
        if (right < size() && A[right] < A[smallest]) {
            smallest = right;
        }
 
        // troca com um filho de menor valor e
        // chama heapify-down no filho
        if (smallest != i)
        {
            swap(A[i], A[smallest]);
            heapify_down(smallest);
        }
    }
 
    // Algoritmo heapify-up recursivo
    void heapify_up(int i)
    {
        // verifica se o nó no índice `i` e seu pai violam a propriedade heap
        if (i && A[PARENT(i)] > A[i])
        {
            // troca os dois se a propriedade heap for violada
            swap(A[i], A[PARENT(i)]);
 
            // chama heapify-up no pai
            heapify_up(PARENT(i));
        }
    }
 
public:

    // retorna o tamanho do heap
    unsigned int size() {
        return A.size();
    }
 
    // Função para verificar se o heap está vazio ou não
    bool empty() {
        return size() == 0;
    }
 
    // insere a chave no heap
    void push(long long int key)
    {
        // insere um novo elemento no final do vector
        A.push_back(key);
 
        // obtém o índice do elemento e chama o procedimento heapify-up
        int index = size() - 1;
        heapify_up(index);
    }
 
    // Função para remover um elemento de menor prioridade (presente na raiz)
    long long int pop()
    {
        try {
            // se o heap não tiver elementos, lança uma exceção
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
            }
 
            // substitui a raiz do heap pelo último elemento
            // do vector
            long long int menor = A[0];
            A[0] = A.back();
            A.pop_back();
 
            // chama heapify-down no nó raiz
            heapify_down(0);
            return menor;
        }
        // captura e imprime a exceção
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
    }
 
    // Função para retornar um elemento com a prioridade mais baixa (presente na raiz)
    long long int top()
    {
        try {
            // se o heap não tiver elementos, lança uma exceção
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                        "index is out of range(Heap underflow)");
            }
 
            // caso contrário, retorna o elemento superior (primeiro)
            return A[0];        // ou return A[0];
        }
        // captura e imprime a exceção
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
    }
};
 



int main(int argc, const char * argv[]) {
    int n, i;
    Processo *p;
    long long int espera, qt, qc;
    long long int tempoExec;
    PriorityQueue fc, ft;
    vector<Processo*> processos;
    while(cin >> n){
        espera = 0;
        tempoExec = 0;
        processos.clear();
        for(i = 0; i < n; i++) {
            p = new Processo();
            cin >> p->t >> p->c;
            if(i == 0 || p->t < tempoExec)
                tempoExec = p->t;
            processos.push_back(p);
        }
        sort(processos.begin(), processos.end(), sortAlg);
        for(Processo* p : processos){
            if(p->t > tempoExec) {
                qt = ft.pop();
                if(qt <= tempoExec)
                    espera += tempoExec - qt;
                else
                    tempoExec = qt;
                qc = fc.pop();
                tempoExec += qc;
            }
            fc.push(p->c);
            ft.push(p->t);
        }
        while(!fc.empty()) {
            qt = ft.pop(); 
            if(qt <= tempoExec)
                espera += tempoExec - qt;
            else
                tempoExec = qt;
            qc = fc.pop();
            tempoExec += qc;
        }
        cout << espera << endl;
    }
    return 0;
}