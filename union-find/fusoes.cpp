#include <iostream>
#include <vector>
using namespace std;
#define N 100000



class DisjointSet {
    int *rank, *parent, *points, n, *victory;

    public:

    int getRafaelVictory() {
        return victory[find_set(1)];
    }

    DisjointSet(int n) {
        rank = new int[N];
        parent = new int[N];
        points = new int[N];
        this->n = n;
        this->victory = new int[N];
        for(int i=1; i<=n; i++) {victory[i] = 0;}
        make_set();
    }

    void make_set() {
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find_set(int x) {

        if (parent[x] != x) {
            parent[x] = find_set(parent[x]);
        }

        return parent[x];
    }
    

    void Union(int x, int y) {
        int xset = find_set(x);
        int yset = find_set(y);

        if (xset == yset) return;

        if (rank[xset] < rank[yset]) {
            parent[xset] = yset;
            points[yset] += points[x];
        }
        else if (rank[xset] > rank[yset]) {
             parent[yset] = xset;
             points[xset] += points[y];
        }

        else {
            parent[yset] = xset;
            rank[xset] = rank[xset] + 1;
            points[xset] += points[y];
        }
    }
    
    void readPoints() {
        for(int i=1; i<=n; i++) {
            cin >> points[i];
        }
    }
    

    void guildWar(int x, int y) {
        if(points[find_set(x)] > points[find_set(y)]) {
            victory[find_set(x)]++;
            
        }
        else if(points[find_set(x)] < points[find_set(y)]){
            victory[find_set(y)]++;
            
        }
    }
    
};



int main() {
    int nPlayers=1, actions=1, i, j, type, guild1, guild2, b;

    while(true) {
        cin >> nPlayers >> actions;
        if(nPlayers == 0  && actions == 0) {
            break;
        }
        DisjointSet g(nPlayers);
        g.readPoints();
        while(actions--) {
            cin >> type >> guild1 >> guild2;

            if(type == 1) {
                g.Union(guild1, guild2);

            }
            else if(type==2) {
                g.guildWar(guild1, guild2);
            }
        }
        cout << g.getRafaelVictory() << "\n";
    } 
    
}