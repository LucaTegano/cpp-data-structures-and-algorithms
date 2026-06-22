#include "../esami/prof/Grafo.h"
#include <iostream>
#include <vector>

using namespace std;

/*
 * Backtracking: assegna ai nodi 0..n-1 un valore in [0, n-1] tale che:
 *  1) per ogni arco (i,j): v[i]%3 != v[j]%3   (vincolo cromatico mod 3)
 *  2) v[x] != x  per ogni nodo x               (vincolo anti-identità)
 *  3) somma(v) == k                             (vincolo sulla somma)
 */
bool backtrack(const Grafo &g, vector<int> &v, int nodo, int k) {
  int n = g.n();

  // Caso base: tutti i nodi assegnati, controlla la somma
  if (nodo == n) {
    int somma = 0;
    for (int x : v)
      somma += x;
    return somma == k;
  }

  // Prova ogni valore da 0 a n-1 per il nodo corrente
  for (int val = 0; val < n; val++) {
    // Vincolo 2: v[x] != x
    if (val == nodo)
      continue;

    // Vincolo 1: per ogni vicino già assegnato, val%3 != v[vicino]%3
    bool conflitto = false;
    for (int j = 0; j < n; j++) {
      if (v[j] == -1)
        continue;
      // grafo non orientato: controlliamo entrambe le direzioni
      if (g(nodo, j) || g(j, nodo)) {
        if (val % 3 == v[j] % 3) {
          conflitto = true;
          break;
        }
      }
    }
    if (conflitto)
      continue;

    // Assegna il valore e vai al nodo successivo
    v[nodo] = val;
    if (backtrack(g, v, nodo + 1, k))
      return true;
    v[nodo] = -1; // ripristina (backtrack)
  }

  return false;
}

vector<int> assegnaValori(const Grafo &g, int k) {
  int n = g.n();
  vector<int> v(n, -1);

  if (backtrack(g, v, 0, k))
    return v;

  return {}; // soluzione non trovata
}

int main() {
  // Grafo a triangolo (nodi 0,1,2) + nodo 3 isolato
  Grafo g(4);
  g(0, 1, true);
  g(1, 0, true);
  g(1, 2, true);
  g(2, 1, true);
  g(0, 2, true);
  g(2, 0, true);

  int k = 8;

  vector<int> risultato = assegnaValori(g, k);

  if (risultato.empty()) {
    cout << "IMPOSSIBILE" << endl;
  } else {
    cout << "Assegnazione trovata (somma = " << k << "):" << endl;
    int somma = 0;
    for (int i = 0; i < (int)risultato.size(); i++) {
      cout << "v[" << i << "] = " << risultato[i] << endl;
      somma += risultato[i];
    }
    cout << "Somma totale: " << somma << endl;
  }

  return 0;
}
