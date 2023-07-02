#include <iostream>
using namespace std;
#define N 100000

class Players {
    public:
    int point;

};


class DisjointSet {
    int *rank, *parent, n, *points, *victory;

    public:

    int getRafaelVictory() {
        return victory[find_set(1)];
    }

    DisjointSet(int n) {
        rank = new int[n+1];
        parent = new int[n+1];
        this->n = n;
        this->points= new int[N];
        this->victory = new int[N];
        for(int i=0; i<=n+1; i++) {victory[i] = 0;}
        make_set();
    }

    void make_set() {
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find_set(int x) {

        if (parent[x] != x) {
            parent[x] = find_set(parent[x]);
        }

        return parent[x];
    }
    
    int unionExist(int x) {
        
        if(parent[x]!=x) {
            parent[x] = find_set(parent[x]);
        }
        
        else if(parent[x] == x) {
            return parent[x];
        }
        return -1;;
    }

    void Union(int x, int y) {
        int xset = find_set(x);
        int yset = find_set(y);

        if (xset == yset) return;

        if (rank[xset] < rank[yset]) {
            parent[xset] = yset;
        }
        else if (rank[xset] > rank[yset]) {
             parent[yset] = xset;
        }

        else {
            parent[yset] = xset;
            rank[xset] = rank[xset] + 1;
        }
    }
    
    void unionPoints(int x, int y, Players players[]) {
        cout << "x"<<  unionExist(x);
        cout << "y"<< unionExist(y);
        
        if(unionExist(x) && unionExist(y)) {return;}
        
        else if(!unionExist(x) && !unionExist(y)) { 
            points[find_set(x)] += players[x].point + players[y].point;
        }
        else if(!unionExist(x) && unionExist(y)) {
            points[find_set(x)] += players[x].point;
        }
        else points[find_set(x)] += players[y].point;
        
    }

    void guildWar(int x, int y, Players players[]) {
        if(points[find_set(x)] > points[find_set(y)]) {
            victory[find_set(x)]++;
            
        }
        else if(points[find_set(x)] < points[find_set(y)]){
            victory[find_set(y)]++;
            
        }
        //cout << "\nX " << points[find_set(x)];
        //cout << "\nY " << points[find_set(y)];
        
    }
    
    
};



int main() {
    int nPlayers, actions, i, j, type, guild1, guild2;
    Players *players = new Players[N];
    cin >> nPlayers >> actions;
    DisjointSet g(nPlayers);


    while(nPlayers != 0  && actions != 0) {
        for(i=1; i<=nPlayers; i++) {
            cin >> players[i].point;
        }
        while(actions--) {
            cin >> type >> guild1 >> guild2;

            if(type == 1) {
                g.unionPoints(guild1, guild2, players);
                g.Union(guild1, guild2);
                
            }
            else if(type==2) {
                g.guildWar(guild1, guild2, players);
            }
        }
        //cout << "saiu";
        cin >> nPlayers >> actions;
    }

    cout << g.getRafaelVictory();
}