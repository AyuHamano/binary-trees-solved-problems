//Após algumas analises e testar uns casos,

// é possivel notar que a solução otima é escolher o dragao com menor Ti/Fi
// possiveis erros:
// usar double -> erro de precisão
// escolher o com menor tempo -> ele pode ter um Fi muito pequeno
// escolher o com maior cursto -> pode ter um tempo muito grande
// a soma dos custos é grande, pode estourar o inteiro
// esquecer de somar o tempo restante após ler todos os dragões

#include <stdio.h>
#include <stdlib.h>

#define MAX 100010

class Dragao {
    public:
    int dias, multa, chegada;
    float valor;

    Dragao (int dias, int multa, int chegada) {
        this->dias=dias;
        this->multa=multa;
        this->chegada=chegada;
        this->valor=(float)multa/(float)dias;
    }
};


class Heap {
    public:
    Dragao *a[MAX];
    int n;

    Heap () {
        this->n=0;
    }
};

Dragao *createDragao(int d, int m, int c) {
    Dragao *drag = (Dragao*)malloc(sizeof(Dragao));

    drag->dias = d;
    drag->multa = m;
    drag->chegada = c;
    drag->valor = (float)m/(float)d;

    return drag;
}

Heap *createHeap() { 
    Heap *h = (Heap*)malloc(sizeof(Heap));
    h->n = 0;

    return h;
}

void reHeapUp(Heap *h, int i) {
    Dragao *temp;

    while(i > 0 && h->a[i]->valor > h->a[(i-1)/2]->valor) {
        temp = h->a[i];
        h->a[i] = h->a[(i-1)/2];
        h->a[(i-1)/2] = temp;

        i = (i-1)/2;
    }
}

void insert(Heap *h, Dragao *d) {
    h->a[h->n] = d;

    reHeapUp(h, h->n);

    h->n++;
}

void reHeapDown(Heap *h, int i) {
    Dragao *temp;
    int j;

    while(2*i+1 < h->n) {
        j = 2*i+1;

        if(j+1 < h->n && h->a[j+1]->valor > h->a[j]->valor) j++;

        if(h->a[i]->valor > h->a[j]->valor) break;

        else {
        temp = h->a[i];
        h->a[i] = h->a[j];
        h->a[j] = temp;

        i = j;
        }
    }
}

void removeMax(Heap *h) {
    Dragao *temp;

    temp = h->a[0];
    h->a[0] = h->a[h->n-1];
    h->a[h->n-1] = temp;

    h->n--;

    reHeapDown(h, 0);
}

void printHeap(Heap *h) {
    int i;
    for(i = 0; i < h->n; i++) {
        printf("%f ", h->a[i]->valor);
    }
    printf("\n");
}

int main() {
    Heap *fila = createHeap();

    long long int dia = 0, tempo = 0;

    long long int multaTotal = 0;

    long long int d, m;
    int i;
    while(scanf("%lld %lld", &d, &m) != EOF) {

        insert(fila, createDragao(d, m, dia));

        if(tempo == 0) {
            Dragao *dg = fila->a[0];
            removeMax(fila);
            multaTotal += (dia - dg->chegada) * dg->multa;
            tempo = dg->dias;
        }
        tempo--;
        dia++;
    }

    while(fila->n != 0) {
        if(tempo == 0) {
            Dragao *dg = fila->a[0];
            removeMax(fila);
            multaTotal += (dia - dg->chegada) * dg->multa;
            tempo = dg->dias;
        }

        tempo--;
        dia++;
    }

    printf("%lld\n", multaTotal);

    return 0;
}