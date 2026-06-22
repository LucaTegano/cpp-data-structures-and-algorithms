#include "../../../../esami/prof/Grafo.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Trovare la distanza tra s e t
int distanzaGrafo(const Grafo &g, int s, int t) {
  int n = g.n();
  vector<int> dist(n, -1);
  queue<int> q;
  dist[s] = 0;
  q.push((s));
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    if (curr == t)
      return dist[t];
    for (int v = 0; v < n; v++) {
      if (g(curr, v) && dist[v] == -1) {
        dist[v] = dist[curr] + 1;
        q.push(v);
      }
    }
  }
  return -1;
}

void test(Grafo &g, int s, int t, int expected, const string &msg) {
  int result = distanzaGrafo(g, s, t);
  cout << (result == expected ? "[OK] " : "[FAIL] ") << msg << " (s=" << s
       << ", t=" << t << ") "
       << "Expected: " << expected << ", Got: " << result << endl;
}

int main() {
  cout << "--- Test Distanza Grafo ---" << endl;

  // Caso 1: Distanza da se stessi
  Grafo g1(1);
  test(g1, 0, 0, 0, "Distanza nodo-se stesso");

  // Caso 2: Arco diretto
  Grafo g2(2);
  g2(0, 1, true);
  test(g2, 0, 1, 1, "Distanza arco diretto 0->1");

  // Caso 3: Percorso a più salti
  Grafo g3(4);
  g3(0, 1, true);
  g3(1, 2, true);
  g3(2, 3, true);
  test(g3, 0, 3, 3, "Percorso 0->1->2->3 (distanza 3)");

  // Caso 4: Non raggiungibile
  Grafo g4(3);
  g4(0, 1, true);
  test(g4, 0, 2, -1, "Target non raggiungibile");

  // Caso 5: Scelta del cammino minimo (BFS)
  // 0 -> 1 -> 2
  // 0 -> 2
  Grafo g5(3);
  g5(0, 1, true);
  g5(1, 2, true);
  g5(0, 2, true);
  test(g5, 0, 2, 1, "Scelta del cammino minimo (0->2 invece di 0->1->2)");

  // Caso 6: Ciclo
  Grafo g6(3);
  g6(0, 1, true);
  g6(1, 2, true);
  g6(2, 0, true);
  test(g6, 0, 2, 2, "Ciclo 0->1->2");

  return 0;
}
