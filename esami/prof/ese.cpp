#include "Grafo.h"
#include <vector>

using namespace std;


bool f(const Grafo& g) {
    vector<int> grado_uscente(g.n());
    vector<int> grado_entrante(g.n());

    int count_archi=0;

    for (int i=0; i<g.n(); ++i)
        for (int j=0; j<g.n(); ++j) {
            if (g(i, j)) {  
                if (i==j) return false; // CODIZIONE 3: g NON ha autoarchi
                grado_entrante[j]++;    // punto 1
                grado_uscente[i]++;     // punto 1
                count_archi++;          // punto 2
            }
        }
    

    // CONDIZIONE 2. Il numero totale di archi di g è pari
    if (count_archi%2!=0)
        return false;


    // CONDIZIONE 1. il grado uscente di ogni nodo di g è minore del numero di nodi di g che hanno al più un arco entrante
    // conto nodi con al più un arco entrante
    int count_max_uno_entrante=0;
    for (int i=0; i<g.n(); ++i)
        if (grado_entrante[i]<=1)
            count_max_uno_entrante++;
    // controllo che non esista nodo con grado uscente > # nodi con max 1 entrante
    for (int i=0; i<g.n(); ++i)
        if (grado_uscente[i] > count_max_uno_entrante)
            return false;


    return true;      
}

//mia spiegazione cond 3
    // 2. g non ha autoarchi
    // Verifichiamo solo la diagonale principale. Costo: O(n).
    for (unsigned i = 0; i < g.n(); ++i) {
        if (g(i, i)) return false;
    }

// --- CONDIZIONE 1 e 2: Conteggio Archi e Gradi ---
// Questo doppio ciclo annidato scorre tutta la matrice di adiacenza (O(n^2)).
// È necessario farlo perché dobbiamo calcolare i gradi di tutti i nodi e contare il numero totale di archi.
// Se avessimo controllato gli autoarchi prima (come nell'ottimizzazione sopra), qui non servirebbe ricontrollare i==j.

// 1. Itera su tutte le possibili coppie (i, j)
int count_archi = 0;
for (int i = 0; i < g.n(); ++i) {
    for (int j = 0; j < g.n(); ++j) {
        // 2. Se esiste un arco da i a j:
        if (g(i, j)) {  
            grado_entrante[j]++;    // Incrementa il grado entrante del nodo destinazione j
            grado_uscente[i]++;     // Incrementa il grado uscente del nodo sorgente i
            count_archi++;          // Conta l'arco per verificare poi la parità totale
        }
    }
}