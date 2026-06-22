#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Soluzione {
    // istanza
    pair<unsigned, unsigned> pos_iniziale;
    vector<pair<unsigned, unsigned> > proibite;  // celle su cui non si puo' andare
    pair<unsigned, unsigned> destinazione;
    vector<pair<int, int>> mosse;
    pair<unsigned, unsigned> pos_corrente;    // cella su cui si trova al momento il cavallo

    // soluzione
    vector<pair<unsigned, unsigned>> soluzione;  // sequenza di mosse per arrivare a destinazione

    Soluzione(pair<unsigned, unsigned> pi, vector<pair<unsigned, unsigned>> pr, pair<unsigned, unsigned> d): 
        pos_iniziale(pi), proibite(pr), destinazione(d) {
            mosse = {
                {-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1}
            };
            soluzione = {};
            pos_corrente = pos_iniziale;
        }
};


bool canAdd(pair<int, int> mossa, const Soluzione& sol) {
    /*
    posso fare questa mossa se:
    1. non atterro fuori dalla scacchiera
    2. non atterro su una proibita
    3. non ho già visitato questa cella
    */ 

    // calcolo dove andrei ad atterrare facendo la mossa
    pair<unsigned, unsigned> pos_atterraggio = {
        sol.pos_corrente.first + mossa.first, 
        sol.pos_corrente.second + mossa.second
    };

    // NB: modello la scacchiera come una matrice 8x8, con indici di riga e colonna che vanno entrambi da 0 a 7

    // condizione 1
    // NB: non serve controllare esplicitamente che pos_atterraggio < 0 poichè questo controllo
    // è implicito -> quando sottraggo un unsigned maggiore ad uno minore, questo va in overflow 
    // -> diventa un numero molto grande (quindi, sicuramente > 7)
    if (pos_atterraggio.first > 7 || pos_atterraggio.second > 7) 
        return false;
    
    // condizione 2
    if (find(sol.proibite.begin(), sol.proibite.end(), pos_atterraggio) != sol.proibite.end())
        return false;

    // condizione 3
    if (find(sol.soluzione.begin(), sol.soluzione.end(), pos_atterraggio) != sol.soluzione.end())
        return false;

    return true;
    
}


void add(pair<int, int> mossa, Soluzione& sol) {
    // aggiorno pos corrente
    sol.pos_corrente.first += mossa.first;
    sol.pos_corrente.second += mossa.second;

    // aggiungo questa nuova cella a soluzione 
    sol.soluzione.push_back(sol.pos_corrente);
}


void remove(Soluzione& sol) {
    sol.soluzione.pop_back();
    
    // rimetto il cavallo alla posizione precedente (torno indieto dall'ultima mossa)
    if (sol.soluzione.empty())
        sol.pos_corrente = sol.pos_iniziale;
    else
        sol.pos_corrente = sol.soluzione.back();
}


bool isComplete(const Soluzione& sol) {
    return sol.pos_corrente == sol.destinazione;
}


bool solve(Soluzione& sol) {
    int index_mossa = 0;
    while (index_mossa < sol.mosse.size()) {
        if (canAdd(sol.mosse[index_mossa], sol)) {
            add(sol.mosse[index_mossa], sol);
            if (isComplete(sol))
                return true;
            if (solve(sol))
                return true;
            remove(sol);
            index_mossa++;            
        }
        else index_mossa++;
    }
    return false;
}


int main() {
    // istanza di esempio
    pair<unsigned, unsigned> pos_iniziale = {0, 0};
    pair<unsigned, unsigned> destinazione = {4, 5};
    vector<pair<unsigned, unsigned>> proibite = {
        {4, 2}, {3, 1}
    };

    Soluzione sol = Soluzione(pos_iniziale, proibite, destinazione);
   
    bool esito = solve(sol);

    if (esito) 
        for (pair<unsigned, unsigned> mossa : sol.soluzione)
            cout << mossa.first << ", " << mossa.second << endl;
    else cout << "IMPOSSIBILE" << endl;

    return 0;
}