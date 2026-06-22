#include "../../../../esami/prof/Grafo.h"
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * Calcola la lunghezza del cammino minimo tra due nodi s e t in un grafo non pesato.
 * Utilizza l'algoritmo BFS (Breadth-First Search).
 * 
 * @param g Il grafo in input
 * @param s Il nodo sorgente
 * @param t Il nodo destinazione
 * @return La distanza minima (numero di archi), oppure -1 se t non è raggiungibile da s.
 */
int minpath(const Grafo &g, int s, int t) {
    int n = g.n();
    // Vettore delle distanze, inizializzato a -1 (non visitato)
    vector<int> dist(n, -1);
    // Coda per la BFS
    queue<int> q;

    // Controllo validità indici
    if (s < 0 || s >= n || t < 0 || t >= n) return -1;

    // Nodo di partenza
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        // Se abbiamo raggiunto la destinazione, restituiamo la distanza
        if (curr == t) {
            return dist[t];
        }

        // Esploriamo i vicini del nodo corrente
        for (int v = 0; v < n; v++) {
            // Se esiste l'arco (curr, v) e v non è stato visitato
            if (g(curr, v) && dist[v] == -1) {
                dist[v] = dist[curr] + 1;
                q.push(v);
            }
        }
    }

    // Se la coda è vuota e non abbiamo raggiunto t, non esiste un cammino
    return -1;
}

// Funzione ausiliaria per la DFS ricorsiva con backtracking
void minpathDFS_rec(const Grafo &g, int curr, int t, int d_corrente, int &d_minima, vector<bool> &visitato) {
    // Se abbiamo raggiunto la destinazione
    if (curr == t) {
        if (d_corrente < d_minima) {
            d_minima = d_corrente; // Aggiorniamo il minimo trovato finora
        }
        return;
    }

    // Ottimizzazione (Pruning): se il cammino attuale è già peggiore o uguale al minimo trovato, inutile continuare
    if (d_corrente >= d_minima) return;

    visitato[curr] = true; // Marca come visitato per il cammino attuale

    for (int v = 0; v < g.n(); v++) {
        // Se esiste l'arco e v non è nel cammino corrente
        if (g(curr, v) && !visitato[v]) {
            minpathDFS_rec(g, v, t, d_corrente + 1, d_minima, visitato);
        }
    }

    visitato[curr] = false; // BACKTRACKING: fondamentale per esplorare altri cammini che potrebbero passare di qui
}

/**
 * Calcola la distanza minima usando la DFS.
 * NOTA: Molto inefficiente rispetto alla BFS (complessità potenzialmente esponenziale).
 */
int minpathDFS(const Grafo &g, int s, int t) {
    int n = g.n();
    if (s < 0 || s >= n || t < 0 || t >= n) return -1;

    int d_minima = 1e9; // Valore sentinella (infinito)
    vector<bool> visitato(n, false);

    minpathDFS_rec(g, s, t, 0, d_minima, visitato);

    return (d_minima == 1e9) ? -1 : d_minima;
}

int main() {
    // Esempio di utilizzo
    Grafo g(5);
    g(0, 1, true);
    g(1, 2, true);
    g(2, 3, true);
    g(0, 4, true);
    g(4, 3, true);

    int s = 0, t = 3;
    cout << "BFS - Distanza minima tra " << s << " e " << t << ": " << minpath(g, s, t) << endl;
    cout << "DFS - Distanza minima tra " << s << " e " << t << ": " << minpathDFS(g, s, t) << endl;

    return 0;
}
