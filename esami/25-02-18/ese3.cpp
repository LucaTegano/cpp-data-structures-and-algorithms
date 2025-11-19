/*
Dato un Grafo orientato g, un nodo di partenza s, un nodo di destinazione t e un arco (i,j) del
grafo, scrivere una funzione
bool f(const Grafo&g, unsigned s, unsigned t, pair<unsigned,unsigned> edge) {
…
}
che restituisca true se e solo se, dopo aver invertito l’orientamento dell’arco (i,j), il cammino
minimo da s a t diventa più breve
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <limits>

using namespace std;

class Grafo {
public:
    unsigned n;
    vector<vector<unsigned>> adj;

    Grafo(unsigned nodes) : n(nodes), adj(nodes) {}

    void addEdge(unsigned u, unsigned v) {
        if (u < n && v < n) {
            adj[u].push_back(v);
        }
    }

    // Helper to remove an edge for the purpose of the exercise
    void removeEdge(unsigned u, unsigned v) {
        if (u < n) {
            auto& neighbors = adj[u];
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), v), neighbors.end());
        }
    }
};

int bfs(const Grafo& g, unsigned s, unsigned t) {
    if (s == t) return 0;
    
    vector<int> dist(g.n, -1);
    queue<unsigned> q;

    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        unsigned u = q.front();
        q.pop();

        for (unsigned v : g.adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                if (v == t) return dist[v];
                q.push(v);
            }
        }
    }
    return numeric_limits<int>::max(); // Not reachable
}

bool f(const Grafo& g, unsigned s, unsigned t, pair<unsigned, unsigned> edge) {
    // 1. Calculate initial distance
    int original_dist = bfs(g, s, t);

    // 2. Create a modified graph (or simulate it)
    // Since we can't easily modify 'const Grafo&', we make a copy.
    // For a large graph, this is expensive, but for this exercise it's the cleanest way
    // without modifying the original class to support temporary edge reversal efficiently.
    Grafo g_prime = g;
    
    // Reverse the edge (i, j) -> (j, i)
    unsigned i = edge.first;
    unsigned j = edge.second;
    
    g_prime.removeEdge(i, j);
    g_prime.addEdge(j, i);

    // 3. Calculate new distance
    int new_dist = bfs(g_prime, s, t);

    // 4. Compare
    return new_dist < original_dist;
}

int main() {
    // Test Case 1: Reversing creates a shortcut
    // 0 -> 1 -> 2 -> 3 (dist 3)
    // Edge (2, 0) exists. If reversed to (0, 2), path becomes 0 -> 2 -> 3 (dist 2)
    Grafo g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(2, 0); // The edge to reverse

    cout << "Test 1 (Shortcut): " << (f(g1, 0, 3, {2, 0}) ? "Passed" : "Failed") << endl;

    // Test Case 2: Reversing breaks the path
    // 0 -> 1 -> 2. Reverse (0, 1) -> (1, 0). No path to 2.
    Grafo g2(3);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    
    cout << "Test 2 (Break path): " << (!f(g2, 0, 2, {0, 1}) ? "Passed" : "Failed") << endl;

    // Test Case 3: Reversing has no effect
    // 0 -> 1 -> 2. Edge (0, 2) exists. Reverse (0, 1). Path 0->2 still exists (len 1).
    // Original path 0->2 (len 1). New path 0->2 (len 1). Not shorter.
    Grafo g3(3);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(0, 2);

    cout << "Test 3 (No effect): " << (!f(g3, 0, 2, {0, 1}) ? "Passed" : "Failed") << endl;

    return 0;
}