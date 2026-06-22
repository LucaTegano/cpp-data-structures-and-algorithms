#include <iostream>
#include <vector>
#include "Grafo.h"

using namespace std;

bool f(const Grafo& g) {
    // --- OTTIMIZZAZIONE (BONUS) ---
    // L'esercizio richiede di evitare quando possibile verifiche computazionalmente onerose.
    // L'ordine di verifica ideale è dal più economico al più costoso:
    // 1. Controllo parità archi: O(1) grazie a g.m()
    // 2. Controllo autoarchi: O(n) iterando solo sulla diagonale
    // 3. Controllo gradi: O(n^2) richiedendo la visita della matrice

    // 1. Il numero totale di archi di g è pari
    // Utilizziamo g.m() che è O(1). Se dispari, restituiamo subito false.
    if (g.m() % 2 != 0) {
        return false;
    }

    // 2. g non ha autoarchi (archi che vanno da un nodo a sé stesso)
    // Verifichiamo solo la diagonale principale. Costo: O(n).
    for (unsigned i = 0; i < g.n(); ++i) {
        if (g(i, i)) {
            return false;
        }
    }

    // 3. Il grado uscente di ogni nodo di g è minore del numero di nodi di g che hanno al più un arco entrante
    // Questa verifica richiede il calcolo dei gradi, che su una matrice di adiacenza costa O(n^2).
    // Lo facciamo per ultimo.
    
    vector<int> grado_uscente(g.n(), 0);
    vector<int> grado_entrante(g.n(), 0);

    for (unsigned i = 0; i < g.n(); ++i) {
        for (unsigned j = 0; j < g.n(); ++j) {
            if (g(i, j)) {
                grado_uscente[i]++;
                grado_entrante[j]++;
            }
        }
    }

    // Calcoliamo la soglia: numero di nodi con al più un arco entrante (<= 1)
    int threshold_nodes = 0;
    for (unsigned i = 0; i < g.n(); ++i) {
        if (grado_entrante[i] <= 1) {
            threshold_nodes++;
        }
    }

    // Verifichiamo la condizione per ogni nodo: grado uscente < threshold
    for (unsigned i = 0; i < g.n(); ++i) {
        if (grado_uscente[i] >= threshold_nodes) {
            // Se anche solo un nodo ha grado uscente >= soglia, la condizione fallisce.
            return false;
        }
    }

    // Se tutte le condizioni sono superate
    return true;
}