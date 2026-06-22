#include "../../../../esami/prof/Grafo.h"
#include <iostream>
#include <vector>

using namespace std;

/**
 * Funzione f che verifica le seguenti proprietà su un Grafo orientato g:
 * 1. Il grado uscente di ogni nodo di g è minore del numero di nodi di g che hanno al più un arco entrante.
 * 2. Il numero totale di archi di g è pari.
 * 3. g non ha autoarchi (archi che vanno da un nodo a sé stesso).
 */
bool f(Grafo &g) {
    // 1. Verifica condizione O(1): numero totale di archi pari
    // Questa è la condizione più economica da verificare.
    if (g.m() % 2 != 0) {
        return false;
    }

    int n = g.n();
    
    // 2. Verifica condizione O(n): assenza di autoarchi
    // Verifichiamo prima dei cicli annidati per poter uscire subito se troviamo un autoarco.
    for (int i = 0; i < n; i++) {
        if (g(i, i)) {
            return false;
        }
    }

    // 3. Verifica condizione O(n^2): proprietà sui gradi
    // Calcoliamo i gradi entranti e uscenti per ogni nodo.
    // k = numero di nodi con in-degree <= 1
    vector<int> in_degree(n, 0);
    vector<int> out_degree(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g(i, j)) {
                out_degree[i]++;
                in_degree[j]++;
            }
        }
    }

    // Conta i nodi che hanno al più un arco entrante (in-degree <= 1)
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] <= 1) {
            k++;
        }
    }

    // Ogni nodo deve avere grado uscente < k
    for (int i = 0; i < n; i++) {
        if (out_degree[i] >= k) {
            return false;
        }
    }

    return true;
}

// Funzione di utilità per i test
void test(Grafo &g, bool expected, const string &msg) {
    bool result = f(g);
    cout << (result == expected ? "[OK] " : "[FAIL] ") << msg 
         << " | Expected: " << (expected ? "true" : "false") 
         << ", Got: " << (result ? "true" : "false") << endl;
}

int main() {
    cout << "--- Test Funzione Proprieta' Grafo ---" << endl;

    // Caso 1: Grafo vuoto (0 archi, 0 nodi)
    // Archi = 0 (pari). Autoarchi: nessuno. 
    // k = 0 (nessun nodo). Out-degree < 0? 
    // In un grafo senza nodi, il ciclo per controllare out_degree non parte, quindi true.
    Grafo g1(0);
    test(g1, true, "Grafo vuoto");

    // Caso 2: Numero archi dispari
    Grafo g2(2);
    g2(0, 1, true); // m = 1
    test(g2, false, "Archi dispari (m=1)");

    // Caso 3: Autoarco
    Grafo g3(2);
    g3(0, 0, true); // Autoarco
    g3(0, 1, true); // m = 2 (pari)
    test(g3, false, "Presenza di autoarco");

    // Caso 4: Proprietà gradi verificata
    // Grafo: 0 -> 1, 1 -> 0 (m = 2, pari)
    // in-degree: node 0: 1, node 1: 1
    // k = nodi con in-degree <= 1 = {0, 1} -> k = 2
    // out-degree: node 0: 1, node 1: 1
    // 1 < 2? Sì per entrambi.
    Grafo g4(2);
    g4(0, 1, true);
    g4(1, 0, true);
    test(g4, true, "Gradi validi (out < k)");

    // Caso 5: Proprietà gradi fallita
    // Grafo: 0 -> 1, 0 -> 2 (m = 2, pari)
    // in-degree: 0:0, 1:1, 2:1. Tutti <= 1, quindi k = 3
    // out-degree: 0:2, 1:0, 2:0.
    // 2 < 3? Sì. 0 < 3? Sì. 
    // Per farlo fallire serve k piccolo.
    // Aggiungiamo archi entranti a 1 e 2.
    // Grafo: 0->1, 0->2, 3->1, 3->2 (m=4, pari)
    // in-degree: 0:0 (<=1), 1:2 (>1), 2:2 (>1), 3:0 (<=1)
    // k = 2 (nodi 0 e 3)
    // out-degree: 0:2, 1:0, 2:0, 3:2
    // Controllo: 0: 2 < 2? NO.
    Grafo g5(4);
    g5(0, 1, true);
    g5(0, 2, true);
    g5(3, 1, true);
    g5(3, 2, true);
    test(g5, false, "Gradi non validi (out >= k)");

    return 0;
}
