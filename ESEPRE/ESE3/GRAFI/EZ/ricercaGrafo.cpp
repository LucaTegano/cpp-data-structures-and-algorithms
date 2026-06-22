#include "../../../../esami/prof/Grafo.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Verificare se esiste un percorso da s a t
bool ricercaGrafo(Grafo &g, int s, int t) {
  int n = g.n();
  vector<bool> visitati(n, false);
  queue<int> q;
  visitati[s] = true;
  q.push(s);
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    if (curr == t)
      return true;
    for (int v = 0; v < n; v++) {
      if (g(curr, v) && !visitati[v]) {
        visitati[v] = true;
        q.push((v));
      }
    }
  }
  return false;
}

void test(Grafo &g, int s, int t, bool expected, const string &msg) {
    bool result = ricercaGrafo(g, s, t);
    cout << (result == expected ? "[OK] " : "[FAIL] ") << msg 
         << " (s=" << s << ", t=" << t << ") "
         << "Expected: " << (expected ? "true" : "false") 
         << ", Got: " << (result ? "true" : "false") << endl;
}

int main() {
    cout << "--- Test Ricerca Grafo ---" << endl;

    // Caso 1: Grafo con un solo nodo
    Grafo g1(1);
    test(g1, 0, 0, true, "Sorgente coincide con target (1 nodo)");

    // Caso 2: Percorso diretto
    Grafo g2(2);
    g2(0, 1, true);
    test(g2, 0, 1, true, "Percorso diretto 0->1");
    test(g2, 1, 0, false, "Percorso inverso inesistente 1->0");

    // Caso 3: Percorso a più salti
    Grafo g3(4);
    g3(0, 1, true);
    g3(1, 2, true);
    g3(2, 3, true);
    test(g3, 0, 3, true, "Percorso a piu' salti 0->1->2->3");
    test(g3, 3, 0, false, "Percorso inverso inesistente 3->0");

    // Caso 4: Componenti disconnesse
    Grafo g4(4);
    g4(0, 1, true);
    g4(2, 3, true);
    test(g4, 0, 3, false, "Nodi in componenti disconnesse");

    // Caso 5: Cicli
    Grafo g5(3);
    g5(0, 1, true);
    g5(1, 2, true);
    g5(2, 0, true);
    test(g5, 2, 1, true, "Ciclo 2->0->1");

    // Caso 6: Grafo a diamante
    Grafo g6(4);
    g6(0, 1, true);
    g6(0, 2, true);
    g6(1, 3, true);
    g6(2, 3, true);
    test(g6, 0, 3, true, "Grafo a diamante 0->(1,2)->3");

    // Caso 7: Nessun arco
    Grafo g7(5);
    test(g7, 0, 4, false, "Nessun arco presente");

    return 0;
}
