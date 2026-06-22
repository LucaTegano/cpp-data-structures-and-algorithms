#include "../esami/prof/Grafo.h"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

#include <queue>

// Funzione che restituisce tutte le coppie di nodi tra di loro sovrapponibili.
// Due nodi x e y sono sovrapponibili se hanno esattamente gli stessi archi entranti
// ed esattamente gli stessi archi uscenti.
vector<pair<int, int>> nodi_sovrapponibili(const Grafo& g) {
    int n = g.n();
    vector<pair<int, int>> ris;
    vector<bool> visited(n, false);

    // Ciclo esterno per gestire eventuali componenti disconnesse o nodi non raggiungibili
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            queue<int> q;
            visited[i] = true;
            q.push(i);

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                // Confronta il nodo u estratto con tutti i nodi v > u
                for (int v = u + 1; v < n; ++v) {
                    bool sovrapponibili = true;
                    for (int k = 0; k < n; ++k) {
                        if (g(u, k) != g(v, k) || g(k, u) != g(k, v)) {
                            sovrapponibili = false;
                            break;
                        }
                    }
                    if (sovrapponibili) {
                        ris.push_back({u, v});
                    }
                }

                // BFS classica: esplorazione dei vicini di u
                for (int v = 0; v < n; ++v) {
                    if (g(u, v) && !visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }

    return ris;
}

int main() {
    // Creiamo il grafo dell'esempio:
    // Nodi: 0, 1, 2, 3
    // Archi entranti in 1 e 2: entrambi da 0 (0->1 e 0->2)
    // Archi uscenti da 1 e 2: entrambi verso 3 (1->3 e 2->3)
    // Quindi i nodi 1 e 2 devono essere sovrapponibili.
    Grafo g(4);
    g(0, 1, true); // 0 -> 1
    g(0, 2, true); // 0 -> 2
    g(1, 3, true); // 1 -> 3
    g(2, 3, true); // 2 -> 3

    vector<pair<int, int>> ris = nodi_sovrapponibili(g);

    cout << "Coppie di nodi sovrapponibili trovate:" << endl;
    for (const auto& p : ris) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }

    return 0;
}
