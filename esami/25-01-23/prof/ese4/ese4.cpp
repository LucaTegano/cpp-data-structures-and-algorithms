#include <iostream>
#include <algorithm>

using namespace std;

struct Soluzione{
    pair<unsigned,unsigned> pos_iniziale;
    vector<pair<unsigned,unsigned>> proibite;
    pair<unsigned,unsigned> destinazione;
    vector<pair<int,int>> mosse;

    pair<unsigned,unsigned> pos_corrente;
    vector<pair<unsigned,unsigned>>visitate;
    vector<pair<unsigned,unsigned>> soluzione;

    Soluzione(pair<unsigned,unsigned>pi,vector<pair<unsigned,unsigned>> pr,pair<unsigned,unsigned>>pos_iniziale(pi),
    proibite(pr,destinazione(d)))
    {
        mosse = {(-2,-1)}    
    }

}