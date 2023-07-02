#include <iostream>
#include <queue>
#define N 600
using namespace std;

class No
{
private:
	No *esq, *dir;
	int chave;

public:
	No(int chave)
	{
		this->chave = chave;
		esq = NULL;
		dir = NULL;
	}

	int getChave()
	{
		return chave;
	}
	
	// funções getters e setters

	No* getEsq()
	{
		return esq;
	}

	No* getDir()
	{
		return dir;
	}

	void setEsq(No *no)
	{
		esq = no;
	}

	void setDir(No *no)
	{
		dir = no;
	}
};

class Arvore
{
private:
	No *raiz;

public:
	Arvore()
	{
		raiz = NULL;
	}
	void inicializar() {
	    raiz = NULL;
	}

	void inserir(int chave)
	{
		if(raiz == NULL) // verifica se a árvore está vazia
			raiz = new No(chave); // cria um novo nó
		else
			inserirAux(raiz, chave);
	}

	void inserirAux(No *no, int chave)
	{
		// se for menor, então insere à esquerda
		if(chave < no->getChave())
		{
			// verifica se a esquerda é nulo
			if(no->getEsq() == NULL)
			{
				No *novo_no = new No(chave);
				no->setEsq(novo_no); // seta o novo_no à esquerda
			}
			else
			{
				// senão, continua percorrendo recursivamente
				inserirAux(no->getEsq(), chave);
			}
		}
		// se for maior, então insere à direita
		else if(chave > no->getChave())
		{
			// verifica se a direita é nulo
			if(no->getDir() == NULL)
			{
				No *novo_no = new No(chave);
				no->setDir(novo_no); // seta o novo_no à direita
			}
			else
			{
				// senão, continua percorrendo recursivamente
				inserirAux(no->getDir(), chave);
			}
		}
		// se for igual, não vai inserir
		// não pode existir 2 chaves iguais
	}

	No* getRaiz()
	{
		return raiz;
	}

	void BFS_Tree () {
		queue <No*> Q;
		No *no =raiz;
		cout << no->getChave();
		do {
			
			if ( (no-> getEsq()) != NULL) {
				Q.push(no->getEsq());
				//no = no->getEsq();
			}

			if (no-> getDir() != NULL) {
				Q.push(no->getDir());
				//no = no->getDir();
			}
			
			if(Q.empty()) break;
			
			no = Q.front();

			cout << " " << no->getChave();

			Q.pop();
			
		} while (1) ;
	}
};

int main()
{
	Arvore arv;
	queue<int> arvore;
	int casos, tamVetor, i, j=1, vetor[N];
	
	cin >> casos;
	
	 do {
	    cin >> tamVetor;
	    for(i=0; i<tamVetor; i++) {
	        cin >> vetor[i];
	        arv.inserir(vetor[i]);
	    }
	    cout << "Case " << j << ":\n";
	    arv.BFS_Tree();
	    std::cout << "\n\n";
	    arv.inicializar();
	    j++;
	}  while(j <= casos);

	return 0;
}

