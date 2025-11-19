/*
Scrivere una funzione f che, preso in input un Grafo orientato g, restituisca true se e solo se
risultano verificate tutte le seguenti proprietà:
• Il grado uscente di ogni nodo di g è minore del numero di nodi di g che hanno al più un arco
entrante
• Il numero totale di archi di g è pari
• g non ha autoarchi (archi che vanno da un nodo a sé stesso)
La classe Grafo dispone dei seguenti metodi pubblici (dove g è un’istanza della classe Grafo):
• g.n() che restituisce il numero di nodi del Grafo
• g.m() che restituisce il numero di archi del Grafo
• g(i,j) che restituisce true se esiste un arco dal nodo i al nodo j e false altrimenti
Nota: Verrà assegnato un piccolo bonus a chi svolgerà l’esercizio in modo da ‘evitare’, quando possibile, di verificare le condizioni
computazionalmente più onerose (la complessità dei 3 metodi pubblici della classe Grafo è O(1)).
*/
#include <iostream>
#include <vector>

// Use namespace std as requested
using namespace std;

/**
 * @brief A mock Grafo class for testing purposes.
 *
 * This class simulates the interface described in the problem statement.
 * It uses an adjacency matrix to store the graph structure.
 * The methods n(), m(), and operator() all have O(1) complexity.
 */
class Grafo
{
private:
    int num_nodes;
    int num_edges;
    vector<vector<bool>> adj_matrix;

public:
    // Constructor to create a graph with a specific number of nodes
    Grafo(int nodes) : num_nodes(nodes), num_edges(0)
    {
        adj_matrix.resize(num_nodes, vector<bool>(num_nodes, false));
    }

    // Add an edge from node u to node v
    void add_edge(int u, int v)
    {
        if (u >= 0 && u < num_nodes && v >= 0 && v < num_nodes)
        {
            if (!adj_matrix[u][v])
            {
                adj_matrix[u][v] = true;
                num_edges++;
            }
        }
    }

    // Returns the number of nodes, O(1)
    int n() const
    {
        return num_nodes;
    }

    // Returns the number of edges, O(1)
    int m() const
    {
        return num_edges;
    }

    // Returns true if an edge exists from u to v, O(1)
    bool operator()(int u, int v) const
    {
        if (u >= 0 && u < num_nodes && v >= 0 && v < num_nodes)
        {
            return adj_matrix[u][v];
        }
        return false;
    }
};

/**
 * @brief Checks if a given graph satisfies a set of properties.
 *
 * The properties are checked in order of increasing computational cost
 * to allow for early exit, as suggested by the problem's bonus note.
 *
 * @param g The input graph to check.
 * @return true if all properties are met, false otherwise.
 */
bool f(const Grafo &g)
{
    int n = g.n();
    int m = g.m();

    // Property 2: Total number of edges must be even.
    // This is the cheapest check (O(1)), so we do it first.
    if (m % 2 != 0)
    {
        return false;
    }

    // To check the other two properties, we need to compute the degrees of the nodes.
    // We can do this and check for self-loops in a single O(n^2) pass.
    vector<int> in_degrees(n, 0);
    vector<int> out_degrees(n, 0);

    for (int i = 0; i < n; ++i)
    {
        // Property 3: No self-loops.
        // This check is performed on the diagonal of the adjacency matrix representation.
        // If a self-loop is found, we can exit early.
        if (g(i, i))
        {
            return false;
        }

        // Calculate in-degrees and out-degrees for all nodes.
        for (int j = 0; j < n; ++j)
        {
            if (g(i, j))
            {
                out_degrees[i]++;
                in_degrees[j]++;
            }
        }
    }

    // Property 1: Out-degree of every node is less than the number of nodes
    // with at most one incoming edge. This is the most expensive check.

    // First, count the number of nodes with in-degree 0 or 1.
    int low_in_degree_nodes_count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (in_degrees[i] <= 1)
        {
            low_in_degree_nodes_count++;
        }
    }

    // Finally, check if the out-degree of any node violates the property.
    for (int i = 0; i < n; ++i)
    {
        if (out_degrees[i] >= low_in_degree_nodes_count)
        {
            return false;
        }
    }

    // If all checks have passed, the graph satisfies all properties.
    return true;
}

int main()
{
    cout << "--- Test Case 1: Should return true ---" << endl;
    Grafo g1(4);
    g1.add_edge(0, 1);
    g1.add_edge(1, 2);
    // Edges: 2 (even)
    // Self-loops: 0
    // In-degrees: {0:0, 1:1, 2:1, 3:0}. Nodes with in-degree <= 1: 4
    // Out-degrees: {0:1, 1:1, 2:0, 3:0}. All out-degrees < 4.
    cout << "Graph g1 satisfies all properties: " << (f(g1) ? "true" : "false") << endl;
    cout << endl;

    cout << "--- Test Case 2: Should return false (odd number of edges) ---" << endl;
    Grafo g2(3);
    g2.add_edge(0, 1);
    cout << "Graph g2 has odd edges: " << (f(g2) ? "true" : "false") << endl;
    cout << endl;

    cout << "--- Test Case 3: Should return false (has a self-loop) ---" << endl;
    Grafo g3(3);
    g3.add_edge(0, 1);
    g3.add_edge(1, 1); // Self-loop
    cout << "Graph g3 has a self-loop: " << (f(g3) ? "true" : "false") << endl;
    cout << endl;

    cout << "--- Test Case 4: Should return false (degree condition violated) ---" << endl;
    Grafo g4(3);
    g4.add_edge(0, 1);
    g4.add_edge(0, 2);
    // Edges: 2 (even)
    // Self-loops: 0
    // In-degrees: {0:0, 1:1, 2:1}. Nodes with in-degree <= 1: 3
    // Out-degrees: {0:2, 1:0, 2:0}.
    // Node 0 has out-degree 2. The number of nodes with low in-degree is 3. 2 < 3 is true.
    // Let's make it fail.
    g4.add_edge(1, 0);
    g4.add_edge(2, 0);
    // Edges: 4 (even)
    // In-degrees: {0:2, 1:1, 2:1}. Nodes with in-degree <= 1: 2 (nodes 1, 2)
    // Out-degrees: {0:2, 1:1, 2:1}.
    // Node 0 has out-degree 2. low_in_degree_nodes_count is 2.
    // The condition is out_degree < low_in_degree_nodes_count.
    // For node 0, 2 < 2 is false. So f(g4) should be false.
    cout << "Graph g4 violates degree condition: " << (f(g4) ? "true" : "false") << endl;
    cout << endl;

    return 0;
}