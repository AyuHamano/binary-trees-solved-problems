#include <iostream>
#include <queue>
using namespace std;
#define M 10000

class Node {
    public:
     int key;
     Node *esq;
     Node *dir;

     Node (int key) {
        this->key=key;
        this->dir = nullptr;
        this->esq = nullptr;
     }
};

class Tree {
    public:
     Node *root;
     Tree () {
        this->root = nullptr;
     }

     Node* insert(Node *root, int key) {
        if(root==nullptr) {
            root = new Node(key);
            return root;
        }
        if(key < root->key) {
            insert(root->esq, key);
        }
        else if (key > root->key) {
            insert(root->dir, key);
        }
     }



};

int main() {
    int cash, client, timeCash[M], itemClient[M];
    priority_queue <pair <int, int> > row;
    cin >> cash >> client;
    for(int i=0; i<cash; i++) cin >> timeCash[i];
    for(int i=0; i<client; i++) cin >> itemClient[i];





    return 0;
}