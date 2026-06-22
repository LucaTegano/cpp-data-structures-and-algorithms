#include "../prof/Grafo.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// Helper function for DFS
bool dfs(const Grafo& g, unsigned u, unsigned x, vector<bool>& visited) {
    // Se u ha un arco diretto che torna a x, abbiamo trovato il cammino semplice cercato!
    if (g(u, x)) {
        return true;
    }

    visited[u] = true;
    for (unsigned v = 0; v < g.n(); ++v) {
        if (g(u, v) && !visited[v]) {
            if (dfs(g, v, x, visited)) {
                return true;
            }
        }
    }
    return false;
}

// Funzione principale dell'Esercizio 3
bool cammino_semplice_ritorno(const Grafo& g, unsigned x) {
    // 1. Controllo preliminare: se x non ha archi entranti, la condizione è automaticamente falsa.
    bool ha_archi_entranti = false;
    for (unsigned i = 0; i < g.n(); ++i) {
        if (g(i, x)) {
            ha_archi_entranti = true;
            break;
        }
    }
    if (!ha_archi_entranti) {
        return false;
    }

    // 2. Inizializziamo il vettore dei nodi visitati.
    // Impostiamo visited[x] = true fin dall'inizio per impedire che x venga usato
    // come nodo intermedio (garantendo così la semplicità del cammino).
    vector<bool> visited(g.n(), false);
    visited[x] = true;

    // 3. Avviamo la ricerca DFS a partire da tutti i vicini diretti di x (escluso x stesso).
    for (unsigned v = 0; v < g.n(); ++v) {
        if (g(x, v) && v != x) {
            if (dfs(g, v, x, visited)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    cout << "=== Avvio dei Test per l'Esercizio 3 (Cammino Semplice con Ritorno) ===" << endl;

    // --- TEST 1: Esempio della traccia ---
    // Nodi: 0, 1, 2, 3, 4
    // Cammino: 1 -> 2 -> 4 -> 1
    // Il nodo 0 non ha archi entranti.
    Grafo g1(5);
    g1(0, 1, true); // 0 -> 1
    g1(1, 2, true); // 1 -> 2
    g1(2, 4, true); // 2 -> 4
    g1(4, 1, true); // 4 -> 1 (arco di ritorno)
    g1(2, 3, true); // 2 -> 3

    // Per x=0 deve restituire false (nessun arco entrante in 0)
    cout << "Test x=0: " << (cammino_semplice_ritorno(g1, 0) ? "true" : "false") << " (Atteso: false)" << endl;
    assert(cammino_semplice_ritorno(g1, 0) == false);

    // Per x=1 deve restituire true (esiste il cammino {1,2,4} con arco (4,1))
    cout << "Test x=1: " << (cammino_semplice_ritorno(g1, 1) ? "true" : "false") << " (Atteso: true)" << endl;
    assert(cammino_semplice_ritorno(g1, 1) == true);

    // Per x=2 deve restituire true (esiste il cammino {2,4,1} con arco (1,2) ? No, l'arco di ritorno a 2 non c'è,
    // ma c'è il ciclo 2 -> 4 -> 1 -> 2 (tramite gli archi 2->4, 4->1, 1->2). Quindi sì, per x=2 è true!)
    cout << "Test x=2: " << (cammino_semplice_ritorno(g1, 2) ? "true" : "false") << " (Atteso: true)" << endl;
    assert(cammino_semplice_ritorno(g1, 2) == true);

    // Per x=3 deve restituire false (nessun arco uscente da 3, e nessun cammino che ritorna a 3)
    cout << "Test x=3: " << (cammino_semplice_ritorno(g1, 3) ? "true" : "false") << " (Atteso: false)" << endl;
    assert(cammino_semplice_ritorno(g1, 3) == false);


    // --- TEST 2: Solo un ciclo self-loop su x (non valido per "altro nodo") ---
    Grafo g2(2);
    g2(0, 0, true); // self-loop 0 -> 0
    cout << "Test x=0 con solo self-loop: " << (cammino_semplice_ritorno(g2, 0) ? "true" : "false") << " (Atteso: false)" << endl;
    assert(cammino_semplice_ritorno(g2, 0) == false);


    // --- TEST 3: Ciclo di lunghezza 2 (due nodi si puntano a vicenda) ---
    Grafo g3(2);
    g3(0, 1, true); // 0 -> 1
    g3(1, 0, true); // 1 -> 0
    cout << "Test x=0 in ciclo di 2 nodi: " << (cammino_semplice_ritorno(g3, 0) ? "true" : "false") << " (Atteso: true)" << endl;
    assert(cammino_semplice_ritorno(g3, 0) == true);

    cout << "=== Tutti i test dell'Esercizio 3 sono passati con successo! ===" << endl;
    return 0;
}
