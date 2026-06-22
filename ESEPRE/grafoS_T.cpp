/*
 * ============================================================================
 *  PROBLEMA: Dati due nodi s e t in un grafo ORIENTATO, verificare se esiste
 *            un percorso da s→t E da t→s. Se entrambi esistono → true.
 *
 *  In un grafo orientato, che esista s→t NON implica che esista t→s!
 *  Quindi servono DUE visite separate (o un approccio ottimizzato).
 *
 *  APPROCCI (dal meno ottimizzato al più ottimizzato):
 *
 *  ┌──────────────────────────────────────────────────────────────────────┐
 *  │ 1) DFS RICORSIVA (semplice, meno ottimizzata)                      │
 *  │    - Due DFS ricorsive: una da s, una da t                         │
 *  │    - Pro: codice molto breve e leggibile                           │
 *  │    - Contro: rischia stack overflow su grafi grandi                 │
 *  │    - Complessità: O(V + E) per ogni DFS → totale O(V + E)         │
 *  │                   (ma costante nascosta più alta per la ricorsione) │
 *  ├──────────────────────────────────────────────────────────────────────┤
 *  │ 2) DFS ITERATIVA (con stack esplicito)                             │
 *  │    - Stessa logica della DFS ma usa uno std::stack                 │
 *  │    - Pro: niente rischio stack overflow                            │
 *  │    - Contro: un po' più verbosa                                    │
 *  │    - Complessità: O(V + E) per ogni DFS → totale O(V + E)         │
 *  ├──────────────────────────────────────────────────────────────────────┤
 *  │ 3) BFS (con coda)                                                  │
 *  │    - Due BFS: una da s, una da t                                   │
 *  │    - Pro: trova il percorso più corto (in numero di archi)         │
 *  │    - Contro: usa più memoria di DFS (la coda può essere grande)   │
 *  │    - Complessità: O(V + E) per ogni BFS → totale O(V + E)         │
 *  ├──────────────────────────────────────────────────────────────────────┤
 *  │ 4) BFS/DFS OTTIMIZZATA (early termination)                         │
 *  │    - Si ferma appena trova t (non visita tutto il grafo)           │
 *  │    - Pro: nel caso medio molto più veloce                          │
 *  │    - Complessità: worst case O(V + E), best case O(1)             │
 *  ├──────────────────────────────────────────────────────────────────────┤
 *  │ 5) BFS BIDIREZIONALE (la più ottimizzata)                          │
 *  │    - Partenza contemporanea da s e da t                            │
 *  │    - Si incontrano "a metà strada"                                 │
 *  │    - Pro: esplora molti meno nodi                                  │
 *  │    - Complessità: circa O(V + E) ma con costante molto ridotta    │
 *  └──────────────────────────────────────────────────────────────────────┘
 *
 *  NOTA: Tutti hanno complessità teorica O(V + E), con la matrice di
 *  adiacenza diventa O(V²) perché scorrere i vicini di un nodo costa O(V).
 * ============================================================================
 */

#include "../esami/prof/Grafo.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// ============================================================================
// 1) DFS RICORSIVA — Approccio base, meno ottimizzato
// ============================================================================
/*
 * STEP-BY-STEP:
 *   1. Partiamo dal nodo 'corrente', lo segniamo come visitato
 *   2. Scorriamo TUTTI i vicini j di 'corrente'
 *   3. Se j non è stato visitato, chiamiamo ricorsivamente dfs su j
 *   4. Alla fine, visited[j] == true per tutti i nodi raggiungibili
 *
 *   Per il nostro problema:
 *   - Facciamo DFS da s → se visited[t] == true, allora s→t esiste
 *   - Facciamo DFS da t → se visited[s] == true, allora t→s esiste
 *   - Se entrambe → return true
 *
 *   DIFETTO: visita TUTTO il grafo anche se trova t subito.
 *            Inoltre, la ricorsione può causare stack overflow.
 */

void dfsRicorsiva(const Grafo& g, unsigned corrente, vector<bool>& visited) {
    visited[corrente] = true;
    for (unsigned j = 0; j < g.n(); j++) {
        if (g(corrente, j) && !visited[j]) {
            dfsRicorsiva(g, j, visited);
        }
    }
}

bool raggiungiDFS_Ricorsiva(const Grafo& g, unsigned s, unsigned t) {
    // DFS da s: verifico se raggiungo t
    vector<bool> visitedDaS(g.n(), false);
    dfsRicorsiva(g, s, visitedDaS);
    if (!visitedDaS[t]) return false;  // s non raggiunge t → inutile continuare

    // DFS da t: verifico se raggiungo s
    vector<bool> visitedDaT(g.n(), false);
    dfsRicorsiva(g, t, visitedDaT);
    return visitedDaT[s];  // true solo se t raggiunge s
}


// ============================================================================
// 2) DFS ITERATIVA — Niente ricorsione, usa stack esplicito
// ============================================================================
/*
 * STEP-BY-STEP:
 *   1. Mettiamo il nodo di partenza nello stack e lo segniamo visitato
 *   2. Finché lo stack non è vuoto:
 *      a. Estraiamo il nodo in cima (top + pop)
 *      b. Scorriamo tutti i vicini j
 *      c. Se j non è visitato, lo segniamo e lo puschiamo nello stack
 *   3. Alla fine, visited[j] == true per tutti i nodi raggiungibili
 *
 *   VANTAGGIO rispetto alla ricorsiva: niente stack overflow.
 *   DIFETTO: come la ricorsiva, visita tutto il grafo raggiungibile.
 */

bool dfsIterativa(const Grafo& g, unsigned start, unsigned target) {
    vector<bool> visited(g.n(), false);
    stack<unsigned> pila;

    pila.push(start);
    visited[start] = true;

    while (!pila.empty()) {
        unsigned corrente = pila.top();
        pila.pop();

        // Scorriamo tutti i possibili vicini
        for (unsigned j = 0; j < g.n(); j++) {
            if (g(corrente, j) && !visited[j]) {
                visited[j] = true;
                pila.push(j);
            }
        }
    }

    return visited[target];
}

bool raggiungiDFS_Iterativa(const Grafo& g, unsigned s, unsigned t) {
    // Prima verifica: s → t
    if (!dfsIterativa(g, s, t)) return false;
    // Seconda verifica: t → s
    return dfsIterativa(g, t, s);
}


// ============================================================================
// 3) BFS — Visita in ampiezza con coda
// ============================================================================
/*
 * STEP-BY-STEP:
 *   1. Mettiamo il nodo di partenza nella coda e lo segniamo visitato
 *   2. Finché la coda non è vuota:
 *      a. Estraiamo il primo nodo dalla coda (front + pop)
 *      b. Scorriamo tutti i vicini j
 *      c. Se j non è visitato, lo segniamo e lo aggiungiamo alla coda
 *   3. Alla fine, visited[j] == true per tutti i nodi raggiungibili
 *
 *   DIFFERENZA con DFS: BFS esplora livello per livello (prima tutti
 *   i nodi a distanza 1, poi distanza 2, ecc.). DFS va "in profondità".
 *
 *   VANTAGGIO: se servisse anche la DISTANZA minima, BFS la trova.
 *   DIFETTO: usa più memoria (la coda contiene tutto il "fronte" corrente).
 */

bool bfs(const Grafo& g, unsigned start, unsigned target) {
    vector<bool> visited(g.n(), false);
    queue<unsigned> coda;

    coda.push(start);
    visited[start] = true;

    while (!coda.empty()) {
        unsigned corrente = coda.front();
        coda.pop();

        for (unsigned j = 0; j < g.n(); j++) {
            if (g(corrente, j) && !visited[j]) {
                visited[j] = true;
                coda.push(j);
            }
        }
    }

    return visited[target];
}

bool raggiungiBFS(const Grafo& g, unsigned s, unsigned t) {
    if (!bfs(g, s, t)) return false;
    return bfs(g, t, s);
}


// ============================================================================
// 4) DFS/BFS CON EARLY TERMINATION — Ottimizzata
// ============================================================================
/*
 * STEP-BY-STEP:
 *   Uguale a BFS/DFS MA:
 *   - Appena troviamo il nodo target, ci fermiamo SUBITO (return true)
 *   - Non visitiamo il resto del grafo inutilmente!
 *
 *   VANTAGGIO: nel caso medio, molto più veloce.
 *   Worst case: target è l'ultimo nodo visitato → stessa complessità.
 *   Best case: target è un vicino diretto → O(V) per scorrere la riga.
 *
 *   Usiamo BFS qui, ma si può fare lo stesso con DFS iterativa.
 */

bool bfsEarlyStop(const Grafo& g, unsigned start, unsigned target) {
    if (start == target) return true;  // caso banale

    vector<bool> visited(g.n(), false);
    queue<unsigned> coda;

    coda.push(start);
    visited[start] = true;

    while (!coda.empty()) {
        unsigned corrente = coda.front();
        coda.pop();

        for (unsigned j = 0; j < g.n(); j++) {
            if (g(corrente, j) && !visited[j]) {
                if (j == target) return true;  // *** TROVATO! STOP! ***
                visited[j] = true;
                coda.push(j);
            }
        }
    }

    return false;  // target non raggiungibile
}

bool raggiungiOttimizzato(const Grafo& g, unsigned s, unsigned t) {
    if (!bfsEarlyStop(g, s, t)) return false;
    return bfsEarlyStop(g, t, s);
}


// ============================================================================
// 5) BFS BIDIREZIONALE — La più ottimizzata
// ============================================================================
/*
 * STEP-BY-STEP (per UN singolo percorso s→t):
 *   1. Partiamo contemporaneamente da s (in avanti) e da t (all'indietro)
 *   2. Ad ogni passo, espandiamo il "fronte" più piccolo
 *   3. Se i due fronti si incontrano → percorso trovato!
 *
 *   NOTA: "all'indietro da t" vuol dire seguire gli archi AL CONTRARIO.
 *         Nel grafo orientato, se esiste arco (a,b), dal lato di t 
 *         seguiamo l'arco da b verso a (arco inverso).
 *
 *   VANTAGGIO: esplora molti meno nodi rispetto a BFS unidirezionale.
 *   Immagina un albero: BFS visita tutti i nodi fino alla profondità d.
 *   BFS bidirezionale visita nodi fino a profondità d/2 da entrambi i lati.
 *   Il numero di nodi cresce esponenzialmente → enorme risparmio.
 *
 *   DIFETTO: più complesso da implementare, e in un grafo orientato
 *            richiede di conoscere anche gli archi entranti (trasposto).
 */

bool bfsBidirezionaleSinglePath(const Grafo& g, unsigned s, unsigned t) {
    if (s == t) return true;

    vector<bool> visitedS(g.n(), false);  // visitati partendo da s
    vector<bool> visitedT(g.n(), false);  // visitati partendo da t (all'indietro)
    queue<unsigned> codaS, codaT;

    codaS.push(s);
    visitedS[s] = true;
    codaT.push(t);
    visitedT[t] = true;

    while (!codaS.empty() && !codaT.empty()) {
        // Espandiamo un livello dal lato S (in avanti: arco i→j)
        {
            int size = codaS.size();
            for (int i = 0; i < size; i++) {
                unsigned corrente = codaS.front();
                codaS.pop();
                for (unsigned j = 0; j < g.n(); j++) {
                    if (g(corrente, j) && !visitedS[j]) {
                        if (visitedT[j]) return true;  // INCONTRO!
                        visitedS[j] = true;
                        codaS.push(j);
                    }
                }
            }
        }

        // Espandiamo un livello dal lato T (all'indietro: arco j→corrente)
        {
            int size = codaT.size();
            for (int i = 0; i < size; i++) {
                unsigned corrente = codaT.front();
                codaT.pop();
                for (unsigned j = 0; j < g.n(); j++) {
                    // ATTENZIONE: qui cerchiamo archi ENTRANTI in corrente
                    // cioè archi (j, corrente), non (corrente, j)!
                    if (g(j, corrente) && !visitedT[j]) {
                        if (visitedS[j]) return true;  // INCONTRO!
                        visitedT[j] = true;
                        codaT.push(j);
                    }
                }
            }
        }
    }

    return false;
}

bool raggiungiBidirezionale(const Grafo& g, unsigned s, unsigned t) {
    // Verifica s→t con BFS bidirezionale
    if (!bfsBidirezionaleSinglePath(g, s, t)) return false;
    // Verifica t→s con BFS bidirezionale (invertendo s e t)
    return bfsBidirezionaleSinglePath(g, t, s);
}


// ============================================================================
//                              MAIN - TEST
// ============================================================================
/*
 *  Grafo di test (orientato):
 *
 *    0 → 1 → 2
 *    ↑       ↓
 *    4 ← 3 ← 2
 *
 *  Archi: 0→1, 1→2, 2→3, 3→4, 4→0
 *  Questo è un ciclo: da qualsiasi coppia (s,t) si può andare e tornare.
 *
 *  Aggiungiamo un nodo 5 isolato per testare il caso false.
 */

int main() {
    Grafo g(6);  // 6 nodi: 0,1,2,3,4,5

    // Creiamo il ciclo: 0 → 1 → 2 → 3 → 4 → 0
    g(0, 1, true);
    g(1, 2, true);
    g(2, 3, true);
    g(3, 4, true);
    g(4, 0, true);
    // Nodo 5 è isolato (nessun arco)

    unsigned s, t;
    cout << "=== Verifica percorso bidirezionale nel grafo orientato ===" << endl;
    cout << "Grafo: 0->1->2->3->4->0 (ciclo), nodo 5 isolato" << endl;
    cout << endl;

    // ---- Test 1: nodi nel ciclo (dovrebbe essere TRUE) ----
    s = 0; t = 3;
    cout << "--- Test s=" << s << ", t=" << t << " (entrambi nel ciclo) ---" << endl;
    cout << "1) DFS Ricorsiva:       " << (raggiungiDFS_Ricorsiva(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "2) DFS Iterativa:       " << (raggiungiDFS_Iterativa(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "3) BFS:                 " << (raggiungiBFS(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "4) BFS Early Stop:      " << (raggiungiOttimizzato(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "5) BFS Bidirezionale:   " << (raggiungiBidirezionale(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << endl;

    // ---- Test 2: un nodo isolato (dovrebbe essere FALSE) ----
    s = 0; t = 5;
    cout << "--- Test s=" << s << ", t=" << t << " (5 è isolato) ---" << endl;
    cout << "1) DFS Ricorsiva:       " << (raggiungiDFS_Ricorsiva(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "2) DFS Iterativa:       " << (raggiungiDFS_Iterativa(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "3) BFS:                 " << (raggiungiBFS(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "4) BFS Early Stop:      " << (raggiungiOttimizzato(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "5) BFS Bidirezionale:   " << (raggiungiBidirezionale(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << endl;

    // ---- Test 3: arco solo in una direzione (dovrebbe essere FALSE) ----
    // Aggiungiamo 5→0 ma NON 0→5, quindi da 0 non si arriva a 5
    g(5, 0, true);
    s = 0; t = 5;
    cout << "--- Test s=" << s << ", t=" << t << " (arco solo 5->0, manca 0->5) ---" << endl;
    cout << "1) DFS Ricorsiva:       " << (raggiungiDFS_Ricorsiva(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "2) DFS Iterativa:       " << (raggiungiDFS_Iterativa(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "3) BFS:                 " << (raggiungiBFS(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "4) BFS Early Stop:      " << (raggiungiOttimizzato(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "5) BFS Bidirezionale:   " << (raggiungiBidirezionale(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << endl;

    // ---- Test 4: aggiungiamo arco anche 0→5 (ora dovrebbe essere TRUE) ----
    g(0, 5, true);
    s = 0; t = 5;
    cout << "--- Test s=" << s << ", t=" << t << " (archi 5->0 e 0->5, bidirezionale) ---" << endl;
    cout << "1) DFS Ricorsiva:       " << (raggiungiDFS_Ricorsiva(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "2) DFS Iterativa:       " << (raggiungiDFS_Iterativa(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "3) BFS:                 " << (raggiungiBFS(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "4) BFS Early Stop:      " << (raggiungiOttimizzato(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "5) BFS Bidirezionale:   " << (raggiungiBidirezionale(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << endl;

    // ---- Test 5: stesso nodo (s == t, dovrebbe essere TRUE) ----
    s = 2; t = 2;
    cout << "--- Test s=" << s << ", t=" << t << " (stesso nodo) ---" << endl;
    cout << "1) DFS Ricorsiva:       " << (raggiungiDFS_Ricorsiva(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "2) DFS Iterativa:       " << (raggiungiDFS_Iterativa(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "3) BFS:                 " << (raggiungiBFS(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "4) BFS Early Stop:      " << (raggiungiOttimizzato(g, s, t) ? "TRUE" : "FALSE") << endl;
    cout << "5) BFS Bidirezionale:   " << (raggiungiBidirezionale(g, s, t) ? "TRUE" : "FALSE") << endl;

    return 0;
}