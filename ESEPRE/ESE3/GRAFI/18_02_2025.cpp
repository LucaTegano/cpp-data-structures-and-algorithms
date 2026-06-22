#include "../../../esami/prof/Grafo.h"
#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// Funzione BFS per calcolare la distanza minima da 's' a 't'
unsigned BFS(const Grafo &g, unsigned s, unsigned t) {
  if (s == t)
    return 0;

  unsigned n = g.n();
  vector<unsigned> dist(n, UINT_MAX);
  vector<bool> visited(n, false);
  queue<unsigned> q;

  visited[s] = true;
  dist[s] = 0;
  q.push(s);

  while (!q.empty()) {
    unsigned u = q.front();
    q.pop();

    if (u == t)
      return dist[t];

    for (unsigned v = 0; v < n; ++v) {
      // Se esiste arco u->v e non visitato
      if (g(u, v) && !visited[v]) {
        visited[v] = true;
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }

  return UINT_MAX; // Non raggiungibile
}

// Funzione richiesta
bool f(const Grafo &g, unsigned s, unsigned t, pair<unsigned, unsigned> edge) {
  unsigned i = edge.first;
  unsigned j = edge.second;

  // 1. Calcola distanza originale
  unsigned distOriginal = BFS(g, s, t);

  // 2. Clona il grafo e inverti l'arco
  // Nota: Grafo ha il costruttore di copia di default che fa deep copy dei
  // vector
  Grafo gMod = g;

  // Rimuovi arco i->j (se esiste) e aggiungi j->i
  // La traccia dice "dato un arco (i,j) del grafo", quindi assumiamo esista.
  // g(i, j) restituisce true.
  gMod(i, j, false); // Rimuovi i->j
  gMod(j, i, true);  // Aggiungi j->i

  // 3. Calcola nuova distanza
  unsigned distNew = BFS(gMod, s, t);

  // 4. Restituisci true se la nuova è strettamente minore
  return distNew < distOriginal;
}

// ============================================================
// MAIN DI TEST
// ============================================================
int main() {
  // Grafo di esempio:
  // 0 -> 1 -> 2 -> 3
  // Arco da invertire: (1, 2) -> diventa (2, 1).
  // Percorso originale: 0->1->2->3 (lun 3).
  // Nuovo grafo: 0->1, 2->1, 2->3. Path 0->3 interrotto?
  // Proviamo un caso dove accorcia.
  // 0 -> 1 -> 2
  // 0 -> 2 (diretto)
  // Se invertiamo (0,2) in (2,0), non cambia nulla per 0->1->2.
  // Caso utile:
  // s=0, t=2.
  // 0 -> 1
  // 1 -> 2
  // Invertiamo (1,2) in (2,1). Path 0->1->2 rotto. Dist diventa INF.

  // Caso Accorciante:
  // s=0, t=2.
  // Grafo:
  // 0->1 (lungo)
  // 1->2
  // Ma esiste un arco 2->0 ? No.
  // Immagina:
  // 0 -> 1
  // 2 -> 1 (arco esistente)
  // Arco da invertire: (2,1) in (1,2).
  // Se invertiamo (2,1), diventa 0->1->2. Distanza 2.
  // Prima era irraggiungibile?
  // Proviamo:

  Grafo g(3);
  g(0, 1, true); // 0->1
  g(2, 1, true); // 2->1

  // Vogliamo andare da 0 a 2.
  // Originale: 0->1. 2->1. Nessun cammino 0->2. Dist = INF.
  // Invertiamo arco (2,1) -> diventa (1,2).
  // Nuovo: 0->1->2. Dist = 2.
  // 2 < INF -> True.

  pair<unsigned, unsigned> arco = {2, 1};

  cout << "Test: Invertire arco (2,1) migliora il cammino 0->2?" << endl;
  if (f(g, 0, 2, arco)) {
    cout << "Sì! Il cammino diventa più breve." << endl;
  } else {
    cout << "No." << endl;
  }

  return 0;
}
