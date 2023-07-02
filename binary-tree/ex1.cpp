#include <iostream>
#include <string>

#define N 600
using namespace std;


class No
{
private:
	No *esq, *dir;
	int chave;
	char letra;

public:
	No(int chave)
	{
		this->chave = chave;
		//this->letra = vetor[chave];
		esq = NULL;
		dir = NULL;
	}

	int getChave() {
		return chave;
	}

	char getLetra() {
		return letra;
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

	void postOrdem(No* no, string inorder)
	{
		if(no != NULL)
		{
			postOrdem(no->getEsq(), inorder);
			postOrdem(no->getDir(), inorder);
			cout << inorder[no->getChave()];
		}
	}
};

int main() {
	Arvore arv;
	int casos, tamVetor, k=1;
	string preOrd, inOrd;
	
	cin >> casos;
	getchar();
	do {
        
        cin >> tamVetor;
        getchar(); 
		getline(cin, preOrd, ' ');
		
        getline(cin, inOrd);
        

	    for(int i = 0; i < tamVetor; i++){
			for(int j = 0; j < tamVetor; j++) {
				
                if(inOrd[j] == preOrd[i])  {
                    arv.inserir(j); 
				}
			}
		}
		arv.postOrdem(arv.getRaiz(), inOrd);
		std::cout << '\n';
		arv.inicializar();
		k++;
        
		  
	} while ( k <= casos);

	return 0;
}