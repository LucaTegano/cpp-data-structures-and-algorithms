/*
 * ============================================================================
 *  ESERCIZIO 2: MASSIMO INSIEME INDIPENDENTE CON VINCOLO (Backtracking)
 * ============================================================================
 *
 *  PROBLEMA:
 *    Dato un grafo (orientato, ma consideriamo adiacenza "in entrambe le
 *    direzioni" per l'indipendenza), ogni nodo ha un valore val[i].
 *    Trovare il più grande INSIEME INDIPENDENTE di nodi tale che:
 *      1) Nessuna coppia di nodi nell'insieme sia collegata da un arco
 *      2) La somma dei valori dei nodi nell'insieme sia ≡ 0 (mod K)
 *
 *    Un insieme indipendente è un sottoinsieme di nodi dove NESSUNO
 *    è adiacente a un altro. È un problema NP-Hard in generale!
 *
 *  APPROCCI:
 *
 *  ┌──────────────────────────────────────────────────────────────────┐
 *  │ A) BRUTE FORCE — Enumera tutti i 2^V sottoinsiemi              │
 *  │    Per ogni sottoinsieme verifica indipendenza e somma%K==0     │
 *  │    Complessità: O(2^V * V²) — impraticabile per V > 25        │
 *  ├──────────────────────────────────────────────────────────────────┤
 *  │ B) BACKTRACKING CON PRUNING — Molto più veloce in pratica      │
 *  │    Esplora l'albero delle decisioni con potatura intelligente   │
 *  │    Pruning 1: se un nodo è adiacente a uno già scelto → skip   │
 *  │    Pruning 2: se anche aggiungendo TUTTI i nodi rimanenti      │
 *  │              non si batte il record corrente → taglia           │
 *  │    Pruning 3: se la somma parziale rende impossibile il %K     │
 *  │              con i nodi rimanenti → taglia                      │
 *  └──────────────────────────────────────────────────────────────────┘
 *
 * ============================================================================
 */

#include "../esami/prof/Grafo.h"
#include <iostream>
#include <vector>
using namespace std;

// ============================================================================
// Helper: verifica se il nodo 'v' è indipendente da tutti i nodi nel set
// ============================================================================
bool isIndipendente(const Grafo& g, unsigned v, const vector<unsigned>& insieme) {
    for (unsigned u : insieme) {
        // Consideriamo adiacenza in entrambe le direzioni
        if (g(v, u) || g(u, v)) return false;
    }
    return true;
}


// ============================================================================
// APPROCCIO A) BRUTE FORCE — Enumera tutti i sottoinsiemi con bitmask
// ============================================================================
/*
 * STEP-BY-STEP:
 *   1. Iteriamo su tutti i 2^V sottoinsiemi (usando una bitmask)
 *   2. Per ogni sottoinsieme:
 *      a. Verifichiamo che sia un insieme indipendente
 *      b. Calcoliamo la somma dei valori
 *      c. Controlliamo somma % K == 0
 *      d. Se è più grande del migliore trovato finora → aggiorniamo
 *   3. Alla fine restituiamo il miglior insieme trovato
 *
 *   DIFETTO: esponenziale, proibitivo per grafi con più di ~25 nodi
 */

vector<unsigned> maxInsiemeBruteForce(const Grafo& g, const vector<int>& val, int K) {
    unsigned V = g.n();
    vector<unsigned> migliore;
    int miglioreSomma = 0;

    // Iteriamo su tutti i 2^V sottoinsiemi
    for (unsigned mask = 1; mask < (1u << V); mask++) {
        vector<unsigned> corrente;
        int somma = 0;

        // Estraiamo i nodi dal bitmask
        for (unsigned i = 0; i < V; i++) {
            if (mask & (1u << i)) {
                corrente.push_back(i);
                somma += val[i];
            }
        }

        // Se non è più grande del migliore, skip
        if (corrente.size() <= migliore.size()) continue;

        // Verifica indipendenza: nessuna coppia adiacente
        bool indipendente = true;
        for (unsigned i = 0; i < corrente.size() && indipendente; i++)
            for (unsigned j = i + 1; j < corrente.size() && indipendente; j++)
                if (g(corrente[i], corrente[j]) || g(corrente[j], corrente[i]))
                    indipendente = false;

        // Verifica vincolo modulare
        if (indipendente && ((somma % K + K) % K == 0)) {
            migliore = corrente;
            miglioreSomma = somma;
        }
    }

    return migliore;
}


// ============================================================================
// APPROCCIO B) BACKTRACKING CON PRUNING
// ============================================================================
/*
 * STEP-BY-STEP:
 *   Per ogni nodo i (da 0 a V-1) decidiamo: lo INCLUDIAMO o lo ESCLUDIAMO?
 *
 *   1. Base case: se abbiamo considerato tutti i nodi
 *      → Se somma % K == 0 e l'insieme è più grande del record → aggiorna
 *
 *   2. PRUNING BOUND: se (nodi_correnti + nodi_rimanenti) ≤ record → taglia
 *      → anche nel caso migliore non batteremo il record
 *
 *   3. Prova ad INCLUDERE il nodo i:
 *      → Solo se è indipendente da tutti i nodi già scelti
 *      → Aggiungi i all'insieme, ricorri con i+1
 *      → Rimuovi i (backtrack)
 *
 *   4. Prova ad ESCLUDERE il nodo i:
 *      → Ricorri con i+1 senza aggiungere nulla
 */

class MaxInsiemeBacktracking {
    const Grafo& g;
    const vector<int>& val;
    int K;
    unsigned V;

    vector<unsigned> corrente;   // insieme corrente
    vector<unsigned> migliore;   // miglior insieme trovato
    int sommaCorrente;
    int miglioreSomma;

    void backtrack(unsigned idx) {
        // Base case: abbiamo considerato tutti i nodi
        if (idx == V) {
            int resto = ((sommaCorrente % K) + K) % K;
            if (resto == 0 && corrente.size() > migliore.size()) {
                migliore = corrente;
                miglioreSomma = sommaCorrente;
            }
            return;
        }

        // *** PRUNING 1: Upper Bound ***
        // Se anche aggiungendo TUTTI i nodi rimanenti non superiamo il record → taglia
        unsigned nodiRimanenti = V - idx;
        if (corrente.size() + nodiRimanenti <= migliore.size()) {
            return;  // impossibile battere il record
        }

        // OPZIONE 1: INCLUDI il nodo idx (se possibile)
        if (isIndipendente(g, idx, corrente)) {
            corrente.push_back(idx);
            sommaCorrente += val[idx];

            backtrack(idx + 1);

            // *** BACKTRACK: rimuovi il nodo ***
            corrente.pop_back();
            sommaCorrente -= val[idx];
        }

        // OPZIONE 2: ESCLUDI il nodo idx
        backtrack(idx + 1);
    }

public:
    MaxInsiemeBacktracking(const Grafo& g, const vector<int>& val, int K)
        : g(g), val(val), K(K), V(g.n()), sommaCorrente(0), miglioreSomma(0) {}

    vector<unsigned> risolvi() {
        corrente.clear();
        migliore.clear();
        sommaCorrente = 0;
        miglioreSomma = 0;

        backtrack(0);
        return migliore;
    }

    int getSomma() const { return miglioreSomma; }
};


// ============================================================================
//  APPROCCIO C) BACKTRACKING CON PRUNING AVANZATO (pruning modulare)
// ============================================================================
/*
 *  Aggiungiamo un pruning più raffinato:
 *
 *  PRUNING MODULARE:
 *    Calcoliamo se con i nodi rimanenti È POSSIBILE raggiungere
 *    un resto % K == 0. Se tutti i nodi rimanenti hanno lo stesso
 *    resto e la combinazione non può dare 0, tagliamo.
 *
 *    In pratica: per ogni valore residuo, contiamo quanti nodi
 *    rimanenti lo hanno. Se nessuna combinazione può portare a 0 → taglia.
 *    (Questo è un mini-DP sui resti dei nodi rimanenti)
 */

class MaxInsiemeAvanzato {
    const Grafo& g;
    const vector<int>& val;
    int K;
    unsigned V;

    vector<unsigned> corrente;
    vector<unsigned> migliore;
    int sommaCorrente;

    // Verifica se è possibile ottenere resto desiderato aggiungendo
    // un sottoinsieme dei nodi da idx a V-1 (solo quelli indipendenti)
    bool restoPossibile(unsigned idx, int restoAttuale) {
        // Mini-DP: possiamo raggiungere resto 0 partendo da restoAttuale?
        vector<bool> raggiungibile(K, false);
        raggiungibile[restoAttuale] = true;

        for (unsigned i = idx; i < V; i++) {
            if (!isIndipendente(g, i, corrente)) continue;
            int valResto = ((val[i] % K) + K) % K;

            // Scorriamo al contrario per non usare lo stesso nodo due volte
            vector<bool> nuovoRaggiungibile = raggiungibile;
            for (int r = 0; r < K; r++) {
                if (raggiungibile[r]) {
                    int nr = (r + valResto) % K;
                    nuovoRaggiungibile[nr] = true;
                }
            }
            raggiungibile = nuovoRaggiungibile;
        }

        return raggiungibile[0];
    }

    void backtrack(unsigned idx) {
        if (idx == V) {
            int resto = ((sommaCorrente % K) + K) % K;
            if (resto == 0 && corrente.size() > migliore.size()) {
                migliore = corrente;
            }
            return;
        }

        // Pruning bound
        unsigned nodiRimanenti = V - idx;
        if (corrente.size() + nodiRimanenti <= migliore.size()) return;

        // *** PRUNING MODULARE: è possibile raggiungere somma%K==0? ***
        int restoAttuale = ((sommaCorrente % K) + K) % K;
        if (!restoPossibile(idx, restoAttuale)) return;

        // Includi idx
        if (isIndipendente(g, idx, corrente)) {
            corrente.push_back(idx);
            sommaCorrente += val[idx];
            backtrack(idx + 1);
            corrente.pop_back();
            sommaCorrente -= val[idx];
        }

        // Escludi idx
        backtrack(idx + 1);
    }

public:
    MaxInsiemeAvanzato(const Grafo& g, const vector<int>& val, int K)
        : g(g), val(val), K(K), V(g.n()), sommaCorrente(0) {}

    vector<unsigned> risolvi() {
        corrente.clear();
        migliore.clear();
        sommaCorrente = 0;
        backtrack(0);
        return migliore;
    }
};


// ============================================================================
//                              MAIN - TEST
// ============================================================================
void stampaInsieme(const vector<unsigned>& ins, const vector<int>& val) {
    int somma = 0;
    cout << "{ ";
    for (unsigned i = 0; i < ins.size(); i++) {
        if (i > 0) cout << ", ";
        cout << ins[i] << "(val=" << val[ins[i]] << ")";
        somma += val[ins[i]];
    }
    cout << " } → dimensione=" << ins.size() << ", somma=" << somma;
    cout << ", somma%3=" << ((somma % 3 + 3) % 3) << endl;
}

int main() {
    /*
     *  Grafo di test:
     *
     *     0 — 1     (archi: 0→1, 1→0)
     *     |   |
     *     3 — 2     (archi: 0→3, 3→0, 1→2, 2→1, 2→3, 3→2)
     *         |
     *         4     (archi: 2→4, 4→2)
     *     5 (isolato)
     *
     *  Val = [3, 5, 1, 2, 6, 3]
     *  K = 3
     *
     *  Insiemi indipendenti possibili:
     *  {0, 2, 5}: somma = 3+1+3 = 7, 7%3 = 1 ❌
     *  {0, 4, 5}: somma = 3+6+3 = 12, 12%3 = 0 ✅ dimensione 3
     *  {1, 3, 4, 5}: 1-3 adiacenti? 1→3 no, 3→1 no. 3-4? 3→4 no, 4→3 no. OK!
     *     somma = 5+2+6+3 = 16, 16%3 = 1 ❌
     *  {1, 3, 5}: somma = 5+2+3 = 10, 10%3 = 1 ❌
     *  {0, 4}: somma = 3+6 = 9, 9%3 = 0 ✅ dimensione 2
     *  {0, 4, 5}: ✅ dimensione 3 → MIGLIORE
     */

    Grafo g(6);

    // Grafo non orientato simulato (archi in entrambe le direzioni)
    g(0, 1, true); g(1, 0, true);
    g(0, 3, true); g(3, 0, true);
    g(1, 2, true); g(2, 1, true);
    g(2, 3, true); g(3, 2, true);
    g(2, 4, true); g(4, 2, true);
    // Nodo 5 isolato

    vector<int> val = {3, 5, 1, 2, 6, 3};
    int K = 3;

    cout << "=== ESERCIZIO 2: Massimo Insieme Indipendente con Vincolo Modulare ===" << endl;
    cout << "Valori: ";
    for (int v : val) cout << v << " ";
    cout << "\nK = " << K << endl;
    cout << "Archi: 0-1, 0-3, 1-2, 2-3, 2-4, nodo 5 isolato" << endl;
    cout << endl;

    // A) Brute Force
    cout << "A) BRUTE FORCE:" << endl;
    auto risBF = maxInsiemeBruteForce(g, val, K);
    cout << "   ";
    stampaInsieme(risBF, val);

    // B) Backtracking con pruning
    cout << "\nB) BACKTRACKING CON PRUNING:" << endl;
    MaxInsiemeBacktracking solverBT(g, val, K);
    auto risBT = solverBT.risolvi();
    cout << "   ";
    stampaInsieme(risBT, val);

    // C) Backtracking avanzato
    cout << "\nC) BACKTRACKING AVANZATO (pruning modulare):" << endl;
    MaxInsiemeAvanzato solverAV(g, val, K);
    auto risAV = solverAV.risolvi();
    cout << "   ";
    stampaInsieme(risAV, val);

    cout << "\n--- Verifica: tutti gli approcci trovano la stessa dimensione ---" << endl;
    cout << "BF=" << risBF.size() << "  BT=" << risBT.size() 
         << "  AV=" << risAV.size() << endl;

    return 0;
}
