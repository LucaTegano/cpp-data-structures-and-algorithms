/*
 * ============================================================================
 *  ESERCIZIO 5: CICLO HAMILTONIANO CON VINCOLI MODULARI (Backtracking)
 * ============================================================================
 *
 *  PROBLEMA:
 *    Dato un grafo orientato con N nodi, ogni nodo ha un valore val[i].
 *    Trovare un CICLO HAMILTONIANO (percorso che visita TUTTI i nodi
 *    esattamente una volta e ritorna al nodo di partenza) tale che:
 *
 *    VINCOLO: Per ogni 3 nodi CONSECUTIVI nel ciclo (a,b,c),
 *             la somma val[a] + val[b] + val[c] deve essere PARI.
 *
 *    Se esistono più cicli validi, trovare quello con la SOMMA TOTALE
 *    dei valori più piccola (o semplicemente un ciclo qualsiasi valido).
 *
 *  NOTA TEORICA:
 *    Il problema del ciclo Hamiltoniano è NP-Completo (uno dei 21 problemi
 *    originali di Karp). Non c'è algoritmo polinomiale conosciuto.
 *    Il backtracking è l'approccio standard per istanze piccole.
 *
 *  APPROCCI:
 *
 *  ┌──────────────────────────────────────────────────────────────────┐
 *  │ A) BACKTRACKING SEMPLICE                                        │
 *  │    Prova tutti i percorsi possibili. Worst case: O(N!)          │
 *  ├──────────────────────────────────────────────────────────────────┤
 *  │ B) BACKTRACKING CON PRUNING                                     │
 *  │    Pruning 1: verifica il vincolo di parità già a ogni step     │
 *  │    Pruning 2: controlla che dal nodo corrente sia possibile     │
 *  │              raggiungere TUTTI i nodi non ancora visitati       │
 *  │    Pruning 3: se non c'è arco verso un non-visitato → skip     │
 *  ├──────────────────────────────────────────────────────────────────┤
 *  │ C) DP CON BITMASK (Bellman-Held-Karp style)                    │
 *  │    dp[mask][v] = true se possiamo visitare esattamente i nodi   │
 *  │    in 'mask' con il percorso che termina in v                   │
 *  │    Complessità: O(2^N * N²) — meglio di N! ma comunque esponenz│
 *  │    Con il vincolo modulare: stato = (mask, nodo_corrente,       │
 *  │    nodo_precedente) per poter controllare le triplette          │
 *  └──────────────────────────────────────────────────────────────────┘
 *
 * ============================================================================
 */

#include "../esami/prof/Grafo.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ============================================================================
//  APPROCCIO A) BACKTRACKING SEMPLICE
// ============================================================================
/*
 * STEP-BY-STEP:
 *   1. Scegliamo un nodo di partenza (per convenzione, il nodo 0)
 *   2. Manteniamo un array visited[] e il percorso corrente path[]
 *   3. Ad ogni passo, proviamo ad aggiungere un nodo non visitato
 *      che sia raggiungibile dal nodo corrente
 *   4. Se abbiamo visitato tutti i nodi:
 *      → Controlliamo se esiste un arco di ritorno al nodo 0
 *      → Controlliamo il vincolo di parità su TUTTE le triplette
 *        (inclusa la "chiusura" del ciclo)
 *   5. Se tutti i vincoli sono soddisfatti → ciclo trovato!
 *
 *   DIFETTO: controlla la parità solo alla fine → spreca tempo
 */

class HamiltonSemplice {
    const Grafo& g;
    const vector<int>& val;
    unsigned N;

    vector<unsigned> path;
    vector<bool> visited;
    bool trovato;

    // Controlla il vincolo: ogni tripletta consecutiva ha somma pari
    bool vincoloPariValido() {
        if (path.size() < 3) return true;

        // Controlliamo tutte le triplette nel ciclo
        for (unsigned i = 0; i < path.size(); i++) {
            unsigned a = path[i];
            unsigned b = path[(i + 1) % path.size()];
            unsigned c = path[(i + 2) % path.size()];
            int somma = val[a] + val[b] + val[c];
            if (somma % 2 != 0) return false;  // somma dispari → invalido
        }
        return true;
    }

    void backtrack() {
        if (trovato) return;

        if (path.size() == N) {
            // Tutti i nodi visitati → controlliamo arco di ritorno
            unsigned ultimo = path.back();
            unsigned primo = path.front();
            if (g(ultimo, primo) && vincoloPariValido()) {
                trovato = true;
            }
            return;
        }

        unsigned corrente = path.back();
        for (unsigned j = 0; j < N; j++) {
            if (!visited[j] && g(corrente, j)) {
                visited[j] = true;
                path.push_back(j);
                backtrack();
                if (trovato) return;
                path.pop_back();
                visited[j] = false;
            }
        }
    }

public:
    HamiltonSemplice(const Grafo& g, const vector<int>& val)
        : g(g), val(val), N(g.n()), trovato(false) {}

    bool risolvi(vector<unsigned>& risultato) {
        visited.assign(N, false);
        path.clear();
        trovato = false;

        // Partiamo dal nodo 0
        visited[0] = true;
        path.push_back(0);
        backtrack();

        if (trovato) {
            risultato = path;
            return true;
        }
        return false;
    }
};


// ============================================================================
//  APPROCCIO B) BACKTRACKING CON PRUNING
// ============================================================================
/*
 * STEP-BY-STEP:
 *   Uguale al semplice MA con PRUNING INCREMENTALE:
 *
 *   PRUNING 1 (parità incrementale):
 *     Ogni volta che aggiungiamo un nodo, controlliamo SUBITO l'ultima
 *     tripletta (se abbiamo almeno 3 nodi nel path).
 *     Se la tripletta non è pari → tagliamo subito, senza esplorare oltre.
 *
 *   PRUNING 2 (raggiungibilità):
 *     Se esiste un nodo non visitato che NON è raggiungibile da NESSUNO
 *     dei nodi non visitati → il ciclo è impossibile → taglia.
 *
 *   PRUNING 3 (chiusura anticipata):
 *     Quando manca solo 1 nodo, controlliamo subito se:
 *     - Esiste arco ultimo→primo (per chiudere il ciclo)
 *     - Le ultime triplette (inclusa la chiusura) sono pari
 */

class HamiltonPruning {
    const Grafo& g;
    const vector<int>& val;
    unsigned N;

    vector<unsigned> path;
    vector<bool> visited;
    bool trovato;

    // *** PRUNING 1: Controlla SOLO l'ultima tripletta ***
    bool ultimaTriplettaOK() {
        unsigned sz = path.size();
        if (sz < 3) return true;  // non abbiamo ancora 3 nodi

        unsigned a = path[sz - 3];
        unsigned b = path[sz - 2];
        unsigned c = path[sz - 1];
        int somma = val[a] + val[b] + val[c];
        return somma % 2 == 0;
    }

    // *** PRUNING per chiusura: controlla le triplette che includono l'arco di chiusura ***
    bool chiusuraOK() {
        unsigned sz = path.size();
        if (sz < 3) return true;

        // Tripletta (..., ultimo, primo, secondo)
        unsigned a1 = path[sz - 2], b1 = path[sz - 1], c1 = path[0];
        if ((val[a1] + val[b1] + val[c1]) % 2 != 0) return false;

        // Tripletta (ultimo, primo, secondo)
        unsigned a2 = path[sz - 1], b2 = path[0], c2 = path[1];
        if ((val[a2] + val[b2] + val[c2]) % 2 != 0) return false;

        return true;
    }

    // *** PRUNING 2: Tutti i nodi non visitati sono raggiungibili? ***
    bool tuttiRaggiungibili() {
        for (unsigned j = 0; j < N; j++) {
            if (visited[j]) continue;
            // j deve essere raggiungibile da almeno un nodo non visitato o dal corrente
            bool raggiungibile = g(path.back(), j);
            if (!raggiungibile) {
                for (unsigned k = 0; k < N && !raggiungibile; k++) {
                    if (!visited[k] && k != j && g(k, j))
                        raggiungibile = true;
                }
            }
            if (!raggiungibile) return false;
        }
        return true;
    }

    void backtrack() {
        if (trovato) return;

        // *** PRUNING 1: controlla l'ultima tripletta ***
        if (!ultimaTriplettaOK()) return;

        if (path.size() == N) {
            unsigned ultimo = path.back();
            if (g(ultimo, path[0]) && chiusuraOK()) {
                trovato = true;
            }
            return;
        }

        // *** PRUNING 2: tutti i nodi rimanenti sono raggiungibili? ***
        if (path.size() >= 3 && !tuttiRaggiungibili()) return;

        unsigned corrente = path.back();
        for (unsigned j = 0; j < N; j++) {
            if (!visited[j] && g(corrente, j)) {
                visited[j] = true;
                path.push_back(j);
                backtrack();
                if (trovato) return;
                path.pop_back();
                visited[j] = false;
            }
        }
    }

public:
    HamiltonPruning(const Grafo& g, const vector<int>& val)
        : g(g), val(val), N(g.n()), trovato(false) {}

    bool risolvi(vector<unsigned>& risultato) {
        visited.assign(N, false);
        path.clear();
        trovato = false;

        visited[0] = true;
        path.push_back(0);
        backtrack();

        if (trovato) {
            risultato = path;
            return true;
        }
        return false;
    }
};


// ============================================================================
//  APPROCCIO C) DP CON BITMASK (Held-Karp style)
// ============================================================================
/*
 * STEP-BY-STEP:
 *   Stato: dp[mask][v][prev] = true se:
 *     - Abbiamo visitato esattamente i nodi nella bitmask 'mask'
 *     - L'ultimo nodo visitato è 'v'
 *     - Il penultimo nodo visitato è 'prev' (serve per il vincolo triplette)
 *
 *   Transizione: per ogni vicino w di v non in mask:
 *     - Se val[prev] + val[v] + val[w] è pari:
 *       → dp[mask | (1<<w)][w][v] = true
 *
 *   Risposta: dp[(1<<N)-1][v][prev] dove g(v, 0) è true
 *     e la chiusura (..., v, 0, ...) rispetta il vincolo
 *
 *   Complessità: O(2^N * N³) — meglio di N! ma servono grafi piccoli (N≤15-18)
 *
 *   NOTA: lo stato ha 3 dimensioni → memoria: O(2^N * N²). Per N=15 è ~7GB,
 *   quindi in pratica usiamo N ≤ 12-13. Per il test usiamo N piccolo.
 */

bool hamiltonDP(const Grafo& g, const vector<int>& val, vector<unsigned>& risultato) {
    unsigned N = g.n();
    if (N > 15) {
        cout << "  (DP bitmask impraticabile per N > 15)" << endl;
        return false;
    }

    unsigned FULL = (1u << N) - 1;

    // dp[mask][v][prev] = true se raggiungibile
    // Per risparmiare memoria, usiamo vector<vector<vector<bool>>>
    vector<vector<vector<bool>>> dp(1u << N,
        vector<vector<bool>>(N, vector<bool>(N, false)));

    // Predecessore per ricostruzione
    struct Pred { unsigned mask; unsigned v; unsigned prev; };
    vector<vector<vector<Pred>>> pred(1u << N,
        vector<vector<Pred>>(N, vector<Pred>(N, {0, (unsigned)-1, 0})));

    // Stato iniziale: partiamo dal nodo 0, proviamo tutti i secondi nodi
    for (unsigned j = 1; j < N; j++) {
        if (g(0, j)) {
            unsigned mask = (1u << 0) | (1u << j);
            dp[mask][j][0] = true;
        }
    }

    // Espandiamo
    for (unsigned mask = 0; mask <= FULL; mask++) {
        for (unsigned v = 0; v < N; v++) {
            if (!(mask & (1u << v))) continue;
            for (unsigned prev = 0; prev < N; prev++) {
                if (prev == v || !(mask & (1u << prev))) continue;
                if (!dp[mask][v][prev]) continue;

                // Proviamo ad aggiungere un nuovo nodo w
                for (unsigned w = 0; w < N; w++) {
                    if (mask & (1u << w)) continue;  // già visitato
                    if (!g(v, w)) continue;           // no arco

                    // *** VINCOLO TRIPLETTE: val[prev]+val[v]+val[w] pari ***
                    int somma = val[prev] + val[v] + val[w];
                    if (somma % 2 != 0) continue;

                    unsigned newMask = mask | (1u << w);
                    if (!dp[newMask][w][v]) {
                        dp[newMask][w][v] = true;
                        pred[newMask][w][v] = {mask, v, prev};
                    }
                }
            }
        }
    }

    // Controlliamo se esiste un ciclo hamiltoniano valido
    for (unsigned v = 0; v < N; v++) {
        if (!g(v, 0)) continue;  // deve tornare a 0
        for (unsigned prev = 0; prev < N; prev++) {
            if (!dp[FULL][v][prev]) continue;

            // Controlliamo le triplette di chiusura
            // Tripletta: (prev, v, 0)
            if ((val[prev] + val[v] + val[0]) % 2 != 0) continue;

            // Tripletta: (v, 0, path[1]) — serve il secondo nodo del path
            // Per semplicità, ricostruiamo il path e controlliamo alla fine
            risultato.clear();
            unsigned cmask = FULL, cv = v, cprev = prev;
            while (cmask != ((1u << 0) | (1u << cv))) {
                risultato.push_back(cv);
                auto& p = pred[cmask][cv][cprev];
                cmask = p.mask;
                unsigned newV = p.v;
                cprev = p.prev;
                cv = newV;
            }
            risultato.push_back(cv);
            risultato.push_back(0);

            // Invertiamo
            reverse(risultato.begin(), risultato.end());

            // Verifica completa chiusura
            bool valido = true;
            for (unsigned i = 0; i < risultato.size() && valido; i++) {
                unsigned a = risultato[i];
                unsigned b = risultato[(i + 1) % N];
                unsigned c = risultato[(i + 2) % N];
                if ((val[a] + val[b] + val[c]) % 2 != 0) valido = false;
            }

            if (valido) return true;
        }
    }

    return false;
}


// ============================================================================
//                              MAIN - TEST
// ============================================================================
void stampaRisultato(const vector<unsigned>& path, const vector<int>& val) {
    if (path.empty()) {
        cout << "NESSUN CICLO TROVATO" << endl;
        return;
    }

    cout << "Ciclo: ";
    int somma = 0;
    for (unsigned i = 0; i < path.size(); i++) {
        if (i > 0) cout << "→";
        cout << path[i] << "(" << val[path[i]] << ")";
        somma += val[path[i]];
    }
    cout << "→" << path[0] << " | somma=" << somma << endl;

    // Verifica triplette
    cout << "  Triplette: ";
    bool valido = true;
    unsigned N = path.size();
    for (unsigned i = 0; i < N; i++) {
        unsigned a = path[i], b = path[(i+1)%N], c = path[(i+2)%N];
        int s = val[a] + val[b] + val[c];
        cout << "(" << a << "," << b << "," << c << ")=" << s;
        if (s % 2 == 0) cout << "✓ ";
        else { cout << "✗ "; valido = false; }
    }
    cout << (valido ? " → VALIDO" : " → INVALIDO") << endl;
}

int main() {
    /*
     *  Grafo completo (orientato) con 5 nodi per avere cicli hamiltoniani
     *
     *  Val = [2, 4, 6, 8, 10]  (tutti pari → qualsiasi tripletta ha somma pari)
     */

    cout << "=== ESERCIZIO 5: Ciclo Hamiltoniano con Vincolo Modulare ===" << endl;
    cout << endl;

    // --- Test 1: Valori tutti pari (facile) ---
    {
        Grafo g(5);
        // Grafo completo orientato
        for (unsigned i = 0; i < 5; i++)
            for (unsigned j = 0; j < 5; j++)
                if (i != j) g(i, j, true);

        vector<int> val = {2, 4, 6, 8, 10};
        cout << "--- Test 1: Valori tutti pari (dovrebbe trovare ciclo) ---" << endl;
        cout << "Val: ";
        for (int v : val) cout << v << " ";
        cout << endl;

        vector<unsigned> ris;
        
        HamiltonSemplice hs(g, val);
        if (hs.risolvi(ris)) {
            cout << "A) Backtracking semplice:  ";
            stampaRisultato(ris, val);
        } else cout << "A) Backtracking semplice:  NESSUN CICLO" << endl;

        HamiltonPruning hp(g, val);
        if (hp.risolvi(ris)) {
            cout << "B) Backtracking pruning:   ";
            stampaRisultato(ris, val);
        } else cout << "B) Backtracking pruning:   NESSUN CICLO" << endl;

        if (hamiltonDP(g, val, ris)) {
            cout << "C) DP bitmask:             ";
            stampaRisultato(ris, val);
        } else cout << "C) DP bitmask:             NESSUN CICLO" << endl;

        cout << endl;
    }

    // --- Test 2: Valori misti (più difficile) ---
    {
        Grafo g(5);
        for (unsigned i = 0; i < 5; i++)
            for (unsigned j = 0; j < 5; j++)
                if (i != j) g(i, j, true);

        // val = [1, 3, 5, 7, 9] — tutti dispari
        // somma di 3 dispari = dispari → NESSUN CICLO POSSIBILE!
        vector<int> val = {1, 3, 5, 7, 9};
        cout << "--- Test 2: Valori tutti dispari (impossibile) ---" << endl;
        cout << "Val: ";
        for (int v : val) cout << v << " ";
        cout << "(3 dispari → somma dispari → vincolo impossibile)" << endl;

        vector<unsigned> ris;

        HamiltonSemplice hs(g, val);
        if (hs.risolvi(ris)) {
            cout << "A) Backtracking semplice:  ";
            stampaRisultato(ris, val);
        } else cout << "A) Backtracking semplice:  NESSUN CICLO ✓" << endl;

        HamiltonPruning hp(g, val);
        if (hp.risolvi(ris)) {
            cout << "B) Backtracking pruning:   ";
            stampaRisultato(ris, val);
        } else cout << "B) Backtracking pruning:   NESSUN CICLO ✓" << endl;

        if (hamiltonDP(g, val, ris)) {
            cout << "C) DP bitmask:             ";
            stampaRisultato(ris, val);
        } else cout << "C) DP bitmask:             NESSUN CICLO ✓" << endl;

        cout << endl;
    }

    // --- Test 3: Mix pari/dispari ---
    {
        Grafo g(6);
        for (unsigned i = 0; i < 6; i++)
            for (unsigned j = 0; j < 6; j++)
                if (i != j) g(i, j, true);

        // val = [2, 1, 4, 3, 6, 5]
        // Tripletta (2,1,4)=7 dispari! Non va.
        // Serve un ordine dove ogni 3 consecutivi abbiano somma pari.
        // Es: (2,4,6,1,3,5) → (2+4+6)=12✓, (4+6+1)=11✗ no
        // Es: (2,4,6,2,4,6)... deve essere un permutazione
        // (1,3,6,2,4,5) → nodo 0=val2, nodo3=val3...
        // Proviamo con l'algoritmo!
        vector<int> val = {2, 1, 4, 3, 6, 5};
        cout << "--- Test 3: Valori misti (6 nodi) ---" << endl;
        cout << "Val: ";
        for (int v : val) cout << v << " ";
        cout << endl;

        vector<unsigned> ris;

        HamiltonPruning hp(g, val);
        if (hp.risolvi(ris)) {
            cout << "B) Backtracking pruning:   ";
            stampaRisultato(ris, val);
        } else cout << "B) Backtracking pruning:   NESSUN CICLO" << endl;

        if (hamiltonDP(g, val, ris)) {
            cout << "C) DP bitmask:             ";
            stampaRisultato(ris, val);
        } else cout << "C) DP bitmask:             NESSUN CICLO" << endl;

        cout << endl;
    }

    // --- Test 4: Grafo sparso (non completo) ---
    {
        Grafo g(5);
        g(0, 1, true); g(1, 2, true); g(2, 3, true);
        g(3, 4, true); g(4, 0, true);  // ciclo semplice
        g(0, 2, true); g(2, 4, true); g(4, 1, true);
        g(1, 3, true); g(3, 0, true);  // archi extra

        vector<int> val = {2, 4, 6, 8, 2};
        cout << "--- Test 4: Grafo sparso (tutti pari, dovrebbe funzionare) ---" << endl;
        cout << "Val: ";
        for (int v : val) cout << v << " ";
        cout << endl;

        vector<unsigned> ris;

        HamiltonPruning hp(g, val);
        if (hp.risolvi(ris)) {
            cout << "B) Backtracking pruning:   ";
            stampaRisultato(ris, val);
        } else cout << "B) Backtracking pruning:   NESSUN CICLO" << endl;
    }

    return 0;
}
