/*Trova e restituisce l'indice di un "nodo madre", ovvero un nodo da cui è
 * possibile raggiungere tutti gli altri nodi del grafo tramite percorsi
 * orientati. Se non ne esiste nessuno, ritorna -1. Se lo fai iterando una BFS
 * per ogni singolo nodo, la tua soluzione è inefficiente. Spremi le meningi.*/
#include "../../../../esami/prof/Grafo.h"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Funzione ausiliaria DFS per esplorare il grafo.
 * Complessità: O(n) per nodo (scansione riga matrice).
 */
void dfs(const Grafo &g, int u, vector<bool> &visited) {
  visited[u] = true;
  for (unsigned v = 0; v < g.n(); ++v) {
    if (g(u, v) && !visited[v]) {
      dfs(g, v, visited);
    }
  }
}

/**
 * Trova un "nodo madre" nel grafo.
 * Un nodo madre è un nodo da cui sono raggiungibili tutti gli altri nodi
 * tramite percorsi orientati.
 *
 * Algoritmo:
 * 1. Si effettua una serie di DFS per coprire tutti i nodi. L'ultimo nodo che
 * avvia una DFS necessaria per visitare nuovi nodi è il candidato ideale
 * (last_v).
 * 2. Si resetta il vettore visited e si effettua una DFS partendo da last_v.
 * 3. Se tutti i nodi risultano visitati, last_v è un nodo madre. Altrimenti,
 * non ne esiste nessuno.
 *
 * Complessità Temporale: O(V^2) con matrice di adiacenza. O(V+E) con liste di
 * adiacenza. Complessità Spaziale: O(V) per il vettore dei visitati.
 */
int nodoMadre(const Grafo &g) {
  unsigned n = g.n();
  if (n == 0)
    return -1;

  vector<bool> visited(n, false);
  int last_v = 0;

  // Fase 1: Identificazione del candidato
  for (unsigned i = 0; i < n; ++i) {
    if (!visited[i]) {
      dfs(g, i, visited);
      last_v = i;
    }
  }

  // Fase 2: Verifica del candidato
  fill(visited.begin(), visited.end(), false);
  dfs(g, last_v, visited);

  for (unsigned i = 0; i < n; ++i) {
    if (!visited[i])
      return -1;
  }

  return last_v;
}

int main() {
  cout << "--- Test Nodo Madre ---" << endl;

  // Caso 1: Cammino 0 -> 1 -> 2
  Grafo g1(3);
  g1(0, 1, true);
  g1(1, 2, true);
  cout << "Test 1 (Cammino 0->1->2, atteso 0): "
       << (nodoMadre(g1) == 0 ? "OK" : "FAIL") << " (Got: " << nodoMadre(g1)
       << ")" << endl;

  // Caso 2: Grafo disconnesso
  Grafo g2(3);
  g2(0, 1, true);
  cout << "Test 2 (Disconnesso, atteso -1): "
       << (nodoMadre(g2) == -1 ? "OK" : "FAIL") << " (Got: " << nodoMadre(g2)
       << ")" << endl;

  // Caso 3: Due sorgenti 0->1, 2->1
  Grafo g3(3);
  g3(0, 1, true);
  g3(2, 1, true);
  cout << "Test 3 (Due sorgenti, atteso -1): "
       << (nodoMadre(g3) == -1 ? "OK" : "FAIL") << " (Got: " << nodoMadre(g3)
       << ")" << endl;

  // Caso 4: Ciclo 0->1->2->0
  Grafo g4(3);
  g4(0, 1, true);
  g4(1, 2, true);
  g4(2, 0, true);
  int res4 = nodoMadre(g4);
  cout << "Test 4 (Ciclo, atteso != -1): " << (res4 != -1 ? "OK" : "FAIL")
       << " (Got: " << res4 << ")" << endl;

  // Caso 5: Stella con centro 0
  Grafo g5(4);
  g5(0, 1, true);
  g5(0, 2, true);
  g5(0, 3, true);
  cout << "Test 5 (Stella centro 0, atteso 0): "
       << (nodoMadre(g5) == 0 ? "OK" : "FAIL") << " (Got: " << nodoMadre(g5)
       << ")" << endl;

  return 0;
}