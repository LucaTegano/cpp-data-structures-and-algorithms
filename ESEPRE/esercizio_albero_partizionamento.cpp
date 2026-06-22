/*
 * ============================================================================
 *  ESERCIZIO 3: PARTIZIONAMENTO ALBERO IN SOTTALBERI (DP su Albero)
 * ============================================================================
 *
 *  PROBLEMA:
 *    Dato un albero (grafo non orientato connesso aciclico) con N nodi,
 *    ogni nodo ha un peso val[i]. Vuoi TAGLIARE esattamente K archi
 *    per ottenere K+1 sottoalberi.
 *
 *    Obiettivo: scegliere i K archi da tagliare per MASSIMIZZARE la
 *    somma del sottoalbero più piccolo (max-min).
 *
 *    Esempio: se tagli 2 archi ottieni 3 sottalberi con somme [5, 8, 3].
 *    Il valore è min(5,8,3) = 3. Vuoi massimizzare questo valore.
 *
 *  APPROCCI:
 *
 *  ┌──────────────────────────────────────────────────────────────────┐
 *  │ A) BINARY SEARCH + GREEDY (ottimizzato)                         │
 *  │    Binary search sulla risposta: "è possibile che ogni           │
 *  │    sottoalbero abbia somma >= X?"                                │
 *  │    Per ogni X candidato: DFS greedy che taglia un arco           │
 *  │    appena un sottoalbero raggiunge somma >= X                    │
 *  │    Complessità: O(N * log(SommaMax))                            │
 *  ├──────────────────────────────────────────────────────────────────┤
 *  │ B) DP SU ALBERO (completa ma più lenta)                         │
 *  │    dp[v][k] = massima somma-minima tagliando k archi nel         │
 *  │    sottoalbero radicato in v                                     │
 *  │    Complessità: O(N * K²)                                       │
 *  └──────────────────────────────────────────────────────────────────┘
 *
 *  Usiamo il grafo come albero (non orientato = archi in entrambe le dir.)
 *
 * ============================================================================
 */

#include "../esami/prof/Grafo.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// ============================================================================
//  APPROCCIO A: BINARY SEARCH + DFS GREEDY
// ============================================================================
/*
 * IDEA CHIAVE:
 *   Facciamo binary search sulla risposta X (la somma minima di un sottoalbero).
 *   Per un dato X, la domanda diventa:
 *     "Posso tagliare almeno K archi in modo che ogni pezzo abbia somma >= X?"
 *
 * STEP-BY-STEP:
 *   1. DFS: per ogni nodo calcoliamo la "somma del sottoalbero"
 *   2. Se la somma di un sottoalbero >= X, lo "stacchiamo" (contiamo un taglio)
 *      e restituiamo 0 al genitore (il sottoalbero è autonomo)
 *   3. Se il numero di tagli >= K, allora X è una risposta valida
 *   4. Binary search: troviamo il massimo X valido
 *
 * PERCHÉ FUNZIONA:
 *   - Proprietà di monotonia: se posso con soglia X, posso anche con soglia X-1
 *   - Greedy è ottimale: staccare appena possibile non peggiora mai la soluzione
 */

class AlberoPartizioneBS {
    const Grafo& g;
    const vector<int>& val;
    unsigned N;
    int tagli;

    // DFS: ritorna la somma del sottoalbero radicato in 'u'
    // Se la somma >= soglia, "taglia" l'arco verso il genitore
    int dfs(unsigned u, int parent, int soglia) {
        int somma = val[u];

        for (unsigned v = 0; v < N; v++) {
            if ((g(u, v) || g(v, u)) && (int)v != parent) {
                somma += dfs(v, u, soglia);
            }
        }

        // Se il sottoalbero ha somma sufficiente → lo stacchiamo
        if (somma >= soglia) {
            tagli++;
            return 0;  // il genitore non vede questa somma
        }

        return somma;
    }

    // Verifica: è possibile ottenere K+1 pezzi tutti con somma >= soglia?
    bool possibile(int soglia, int K, unsigned radice) {
        tagli = 0;
        dfs(radice, -1, soglia);
        // tagli include anche la radice stessa se la usa somma >= soglia
        // ci servono K tagli per ottenere K+1 pezzi
        // ma la radice non viene "tagliata" → serve tagli >= K+1
        return tagli >= K + 1;
    }

public:
    AlberoPartizioneBS(const Grafo& g, const vector<int>& val)
        : g(g), val(val), N(g.n()), tagli(0) {}

    int risolvi(int K, unsigned radice = 0) {
        // Calcola somma totale per il limite superiore
        int sommaTotal = 0;
        for (unsigned i = 0; i < N; i++) sommaTotal += val[i];

        // Binary search sulla risposta
        int lo = 0, hi = sommaTotal, risposta = 0;

        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (possibile(mid, K, radice)) {
                risposta = mid;  // X = mid è valido, proviamo più alto
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return risposta;
    }
};


// ============================================================================
//  APPROCCIO B: DP SU ALBERO
// ============================================================================
/*
 * STEP-BY-STEP:
 *   dp[v][k] = somma del sottoalbero di v DOPO aver tagliato k archi
 *              all'interno del sottoalbero di v.
 *              (I pezzi staccati devono tutti avere somma >= del minimo globale)
 *
 *   Transizione: per ogni figlio c di v:
 *     - Non tagliare l'arco v-c: dp[v][k] include dp[c][k'] per vari k'
 *     - Taglia l'arco v-c: il sottoalbero di c diventa indipendente
 *       dp[v][k] = dp[v senza c][k-1], e registriamo dp[c][k'] come pezzo
 *
 *   Questo è un "knapsack su albero" — ogni figlio offre opzioni.
 *
 *   NOTA: per semplicità, qui implementiamo una versione che calcola
 *   le somme dei sottoalberi e poi prova tutte le combinazioni di K tagli.
 */

class AlberoPartizioneDP {
    const Grafo& g;
    const vector<int>& val;
    unsigned N;

    // sottalberoSomma[v] = somma di tutti i nodi nel sottoalbero di v
    vector<int> subtreeSum;
    vector<vector<unsigned>> figli;  // lista figli per ogni nodo

    void calcolaSottoalbero(unsigned u, int parent) {
        subtreeSum[u] = val[u];
        for (unsigned v = 0; v < N; v++) {
            if ((g(u, v) || g(v, u)) && (int)v != parent) {
                figli[u].push_back(v);
                calcolaSottoalbero(v, u);
                subtreeSum[u] += subtreeSum[v];
            }
        }
    }

    // Enumera tutte le combinazioni di K archi da tagliare (backtracking)
    // archi[] contiene tutte le coppie (genitore, figlio)
    int migliorMinimo;
    vector<pair<unsigned, unsigned>> tuttiArchi;

    void enumera(int idx, int tagli, int K, vector<bool>& tagliato) {
        if (tagli == K) {
            // Calcola le somme dei pezzi risultanti
            // Per ogni nodo, se l'arco verso il genitore è tagliato,
            // il suo sottoalbero è un pezzo autonomo
            // La radice è sempre un pezzo
            vector<int> pezzi;
            for (unsigned i = 0; i < tuttiArchi.size(); i++) {
                if (tagliato[i]) {
                    // Il sottoalbero del figlio è un pezzo
                    pezzi.push_back(subtreeSum[tuttiArchi[i].second]);
                }
            }
            // La radice ha somma = subtreeSum[radice] - somma dei pezzi staccati
            int sommaRadice = subtreeSum[0];
            for (int p : pezzi) sommaRadice -= p;
            pezzi.push_back(sommaRadice);

            int minimo = *min_element(pezzi.begin(), pezzi.end());
            migliorMinimo = max(migliorMinimo, minimo);
            return;
        }

        if (idx >= (int)tuttiArchi.size()) return;

        // Rimangono abbastanza archi?
        if ((int)tuttiArchi.size() - idx < K - tagli) return;

        // Taglia l'arco idx
        tagliato[idx] = true;
        enumera(idx + 1, tagli + 1, K, tagliato);
        tagliato[idx] = false;

        // Non tagliare l'arco idx
        enumera(idx + 1, tagli, K, tagliato);
    }

public:
    AlberoPartizioneDP(const Grafo& g, const vector<int>& val)
        : g(g), val(val), N(g.n()), migliorMinimo(INT_MIN) {
        subtreeSum.resize(N, 0);
        figli.resize(N);
    }

    int risolvi(int K, unsigned radice = 0) {
        // Passo 1: calcola sottoalberi e archi
        calcolaSottoalbero(radice, -1);

        tuttiArchi.clear();
        for (unsigned u = 0; u < N; u++)
            for (unsigned c : figli[u])
                tuttiArchi.push_back({u, c});

        // Passo 2: enumera tutte le combinazioni di K tagli
        migliorMinimo = INT_MIN;
        vector<bool> tagliato(tuttiArchi.size(), false);
        enumera(0, 0, K, tagliato);

        return migliorMinimo;
    }
};


// ============================================================================
//                              MAIN - TEST
// ============================================================================
/*
 *  Albero di test (8 nodi, 7 archi):
 *
 *              0(10)
 *             / \
 *          1(5)  2(8)
 *          /    / \
 *       3(3) 4(7) 5(2)
 *       /          \
 *    6(4)          7(6)
 *
 *  Val = [10, 5, 8, 3, 7, 2, 4, 6]
 *  Somma totale = 45
 *
 *  Con K=2 tagli → 3 pezzi:
 *    Tagliamo arco 0-1 e arco 2-5:
 *    Pezzo 1: {0, 2, 4} = 10+8+7 = 25
 *    Pezzo 2: {1, 3, 6} = 5+3+4 = 12
 *    Pezzo 3: {5, 7} = 2+6 = 8
 *    Min = 8
 *
 *    Oppure tagliamo 0-2 e 1-3:
 *    Pezzo 1: {0, 1} = 10+5 = 15
 *    Pezzo 2: {2, 4, 5, 7} = 8+7+2+6 = 23
 *    Pezzo 3: {3, 6} = 3+4 = 7
 *    Min = 7
 *
 *    Il primo partizionamento è migliore (min=8 > 7).
 */

int main() {
    Grafo g(8);

    // Costruiamo l'albero (archi bidirezionali)
    g(0, 1, true); g(1, 0, true);
    g(0, 2, true); g(2, 0, true);
    g(1, 3, true); g(3, 1, true);
    g(2, 4, true); g(4, 2, true);
    g(2, 5, true); g(5, 2, true);
    g(3, 6, true); g(6, 3, true);
    g(5, 7, true); g(7, 5, true);

    vector<int> val = {10, 5, 8, 3, 7, 2, 4, 6};
    int sommaTotal = 0;
    for (int v : val) sommaTotal += v;

    cout << "=== ESERCIZIO 3: Partizionamento Albero in Sottoalberi ===" << endl;
    cout << "Valori: ";
    for (int v : val) cout << v << " ";
    cout << "\nSomma totale: " << sommaTotal << endl;
    cout << "Albero:" << endl;
    cout << "          0(10)" << endl;
    cout << "         / \\" << endl;
    cout << "      1(5)  2(8)" << endl;
    cout << "      /    / \\" << endl;
    cout << "   3(3) 4(7) 5(2)" << endl;
    cout << "   /          \\" << endl;
    cout << "6(4)          7(6)" << endl;
    cout << endl;

    // Test con diversi valori di K
    for (int K = 1; K <= 3; K++) {
        cout << "--- K = " << K << " (tagli " << K << " archi → " << K + 1 << " pezzi) ---" << endl;

        AlberoPartizioneBS solverBS(g, val);
        int risBS = solverBS.risolvi(K);
        cout << "  Binary Search + Greedy:  min sottoalbero >= " << risBS << endl;

        AlberoPartizioneDP solverDP(g, val);
        int risDP = solverDP.risolvi(K);
        cout << "  DP esaustivo:            min sottoalbero >= " << risDP << endl;

        cout << endl;
    }

    return 0;
}
