#include "grafoPesato.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <limits>

using namespace std;

// Funzione che implementa l'approccio goloso (Nearest Neighbor)
// Sceglie sempre l'arco con peso minore tra quelli disponibili verso nodi non visitati
bool camminoGoloso(const GrafoPesato& g, int start, int end, list<int>& cammino, int& costoTotale) {
    cammino.clear();
    costoTotale = 0;
    
    int current = start;
    cammino.push_back(current);
    
    vector<bool> visitati(g.n(), false);
    visitati[current] = true;
    
    while (current != end) {
        int nextNode = -1;
        int minWeight = numeric_limits<int>::max();
        
        // Cerca il vicino non visitato con peso minimo
        for (unsigned i = 0; i < g.n(); i++) {
            // Se esiste arco verso i E non visitato
            if (g(current, i) && !visitati[i]) {
                int w = g.w(current, i);
                if (w < minWeight) {
                    minWeight = w;
                    nextNode = i;
                }
            }
        }
        
        // Se non abbiamo trovato nodi successivi validi (vicolo cieco)
        if (nextNode == -1) {
            return false;
        }
        
        // Esegui la scelta golosa
        visitati[nextNode] = true;
        cammino.push_back(nextNode);
        costoTotale += minWeight;
        current = nextNode;
    }
    
    return true;
}

void mostraCammino(const list<int>& cammino, int costo) {
    cout << "Cammino: ";
    for (int nodo : cammino) {
        cout << nodo << " ";
    }
    cout << "\nCosto totale: " << costo << endl;
}

int main() {
    // --- PARTE 1: Esempio Generico (o Input Utente) ---
    // Creiamo un esempio semplice dove il goloso funziona (o input manuale se preferito, ma qui facciamo demo)
    cout << "--- TEST 1: Grafo Semplice ---\n";
    GrafoPesato g1(4);
    // 0 -> 1 (10)
    // 1 -> 3 (10)
    // 0 -> 2 (100)
    // 2 -> 3 (100)
    g1(0, 1, true, 10);
    g1(1, 3, true, 10);
    g1(0, 2, true, 100);
    g1(2, 3, true, 100);
    
    list<int> path1;
    int cost1;
    
    cout << "Cerco cammino da 0 a 3:\n";
    if (camminoGoloso(g1, 0, 3, path1, cost1)) {
        mostraCammino(path1, cost1);
    } else {
        cout << "Nessun cammino trovato.\n";
    }
    
    cout << "\n--------------------------------------------------\n";
    
    // --- PARTE 2: Controesempio (Goloso fallisce) ---
    /*
     Definizione dell'istanza in cui l'approccio goloso NON coincide col minimo:
     Grafo con 3 nodi: 0, 1, 2. Start:0, End:2.
     
     Archi:
     0 -> 1 (peso 1)
     0 -> 2 (peso 10)
     1 -> 2 (peso 100)
     
     Il goloso è in 0. Vede vicini: 1 (peso 1) e 2 (peso 10).
     Sceglie 1 perché 1 < 10.
     Ora è in 1. Unico vicino: 2 (peso 100).
     Cammino Goloso: 0 -> 1 -> 2. Costo: 1 + 100 = 101.
     
     Cammino Minimo Reale: 0 -> 2 diretto. Costo: 10.
     */
    
    cout << "\n--- TEST 2: Controesempio (Goloso non ottimo) ---\n";
    GrafoPesato g2(3);
    g2(0, 1, true, 1);    // Scelta locale ottima (trappola)
    g2(0, 2, true, 10);   // Scelta locale peggiore, ma porta all'ottimo globale
    g2(1, 2, true, 100);  // Costo alto dal nodo trappola
    
    list<int> path2;
    int cost2;
    
    cout << "Grafo del controesempio:\n";
    cout << "Arco 0->1 peso 1\nArco 0->2 peso 10\nArco 1->2 peso 100\n";
    cout << "Start: 0, End: 2\n\n";
    
    cout << "Esecuzione Algoritmo Goloso:\n";
    if (camminoGoloso(g2, 0, 2, path2, cost2)) {
        mostraCammino(path2, cost2);
    } else {
        cout << "Nessun cammino trovato.\n";
    }
    
    cout << "\nConfronto con Cammino Minimo Reale:\n";
    cout << "Cammino ottimo: 0 2\n";
    cout << "Costo ottimo: 10\n";
    
    if (cost2 > 10) {
        cout << "\nRISULTATO: L'algoritmo goloso ha fallito nel trovare il minimo ( " << cost2 << " > 10 ).\n";
    }
    
    return 0;
}
