#include "grafo.hpp"
#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

struct Soluzione {
    /* ISTANZA */
    Grafo g;
    unsigned nodoPartenza;
    /***********/

    /* SOLUZIONE */
    vector<unsigned> ciclo;
    /*************/

    Soluzione(Grafo &g_i, unsigned nodoPartenza) : g(g_i), nodoPartenza(nodoPartenza) {
        ciclo.push_back(nodoPartenza);
    }
};


//rimuovo l'ultimo nodo dal ciclo corrente
void remove(Soluzione &soluzione) {
    soluzione.ciclo.pop_back();
}

//controllo se ho raggiunto la dimensione richiesta e contemporaneamente posso chiudere il ciclo
bool isComplete(Soluzione &soluzione) {
    return soluzione.ciclo.size() == soluzione.g.n() && soluzione.g(soluzione.ciclo.back(), soluzione.ciclo.front());
}

//aggiungo un nodo al ciclo corrente
void add(int nodo, Soluzione &soluzione) {
    soluzione.ciclo.push_back(nodo);
}

//aggiungo il nodo al ciclo corrente
bool canAdd(int nodo, Soluzione &soluzione) {
    if (soluzione.ciclo.empty()) return true; //posso aggiungere il nodo se è il primo elemento del ciclo

    //posso aggiungere il nodo se non lo ho visitato ed esiste un arco che lo raggiunge partendo dall'ultimo nodo aggiunto
    return (find(soluzione.ciclo.begin(), soluzione.ciclo.end(), nodo) == soluzione.ciclo.end() && soluzione.
            g(soluzione.ciclo.back(), nodo));
}

bool solve(Soluzione &soluzione) {
    int nodo = 0;
    while (nodo < soluzione.g.n()) {
        if (canAdd(nodo, soluzione)) {
            add(nodo, soluzione);

            //se la lista ha la dimensione g.n() ed esiste un arco dall'ultimo elemento al primo allora restituisco true
            if (isComplete(soluzione))
                return true;

            if (solve(soluzione))
                return true;

            remove(soluzione);

            nodo++;
        } else
            nodo++;
    }

    return false;
}

int main() {
    // // CASO 1: Successo Standard
    // // Ciclo: 0 -> 1 -> 2 -> 0
    // cout << "--- Test 1: Ciclo Semplice (Partenza 0) ---" << endl;
    // Grafo g1(3);
    // g1(0, 1, true);
    // g1(1, 2, true);
    // g1(2, 0, true);
    // Soluzione soluzione(g1, 0);
    // // Output atteso: 0 1 2

    // // CASO 2: Fallimento (Vicolo cieco)
    // // 0 -> 1 -> 2 (nessun ritorno a 0)
    // cout << "\n--- Test 2: Vicolo Cieco (Partenza 0) ---" << endl;
    // Grafo g2(3);
    // g2(0, 1, true);
    // g2(1, 2, true);
    // Soluzione soluzione(g2, 0);
    // // Output atteso: Impossibile

    // // CASO 3: Fallimento (Grafo sconnesso)
    // // 0 -> 1 -> 0 (ciclo su 2 nodi), ma il nodo 2 è isolato.
    // // Partendo da 0 non posso visitare il 2.
    // cout << "\n--- Test 3: Nodo Isolato (Partenza 0) ---" << endl;
    // Grafo g3(3);
    // g3(0, 1, true);
    // g3(1, 0, true);
    // // Il nodo 2 esiste ma non ha archi
    // Soluzione soluzione(g3, 0);
    // // Output atteso: Impossibile
    //
    // CASO 4: Successo con scelta (Bivio)
    // 0 può andare a 1 o 2.
    // Se va a 2 -> 3 -> 0 (taglia fuori l'1 -> NO)
    // Se va a 1 -> 2 -> 3 -> 0 (TUTTI -> OK)
    cout << "\n--- Test 4: Bivio con scelta obbligata (Partenza 0) ---" << endl;
    Grafo g4(4);
    g4(0, 1, true); // Strada giusta
    g4(0, 2, true); // Scorciatoia (strada sbagliata per Hamilton)
    g4(1, 2, true);
    g4(2, 3, true);
    g4(3, 0, true);
    Soluzione soluzione(g4, 0);
    // Output atteso: 0 1 2 3 (o 0 2 3 se l'ordine dei vicini fosse inverso, ma qui 0->2 taglia l'1, quindi deve backtrackare)
    if (solve(soluzione)) {
        cout << "SOLUZIONE: " << endl;
        for (auto nodo:soluzione.ciclo)
            cout << nodo << " ";
    } else {
        cout << "Impossibile";
    }
}
