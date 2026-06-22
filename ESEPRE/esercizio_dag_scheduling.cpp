/*
 * ============================================================================
 *  ESERCIZIO 4: SCHEDULING SU DAG (Greedy + Ordinamento Topologico)
 * ============================================================================
 *
 *  PROBLEMA:
 *    Hai N task (nodi) con dipendenze (archi del DAG orientato).
 *    Un arco i→j significa: "task i DEVE finire PRIMA che task j inizi".
 *    Ogni task ha una durata durata[i].
 *    Hai P processori paralleli.
 *
 *    Obiettivo: assegnare i task ai processori minimizzando il MAKESPAN
 *    (tempo totale dal primo all'ultimo task completato), rispettando
 *    le dipendenze.
 *
 *    Vincolo aggiuntivo creativo: un processore può eseguire un task j
 *    solo se la somma delle durate dei task già eseguiti su quel
 *    processore è ≡ 0 (mod 3) oppure se il processore è vuoto.
 *    (Simula un vincolo hardware reale di allineamento temporale)
 *
 *  APPROCCI:
 *
 *  ┌──────────────────────────────────────────────────────────────────┐
 *  │ A) TOPOLOGICAL SORT + GREEDY (efficiente)                       │
 *  │    1. Ordine topologico: stabilisce un ordine valido dei task    │
 *  │    2. Greedy: assegna ogni task al processore che si libera       │
 *  │       prima (e che soddisfa il vincolo modulare)                 │
 *  │    Complessità: O(V + E + V*P)                                  │
 *  ├──────────────────────────────────────────────────────────────────┤
 *  │ B) CRITICAL PATH METHOD (CPM) — calcola il makespan minimo      │
 *  │    Trova il "cammino critico": il cammino più lungo nel DAG     │
 *  │    (somma delle durate). Questo è il lower bound del makespan.  │
 *  │    Con infiniti processori, il makespan = lunghezza path critico │
 *  │    Complessità: O(V + E) con DP su ordinamento topologico       │
 *  └──────────────────────────────────────────────────────────────────┘
 *
 * ============================================================================
 */

#include "../esami/prof/Grafo.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// ============================================================================
// STEP 1: ORDINAMENTO TOPOLOGICO (Algoritmo di Kahn — BFS based)
// ============================================================================
/*
 * STEP-BY-STEP:
 *   1. Calcoliamo il grado entrante (in-degree) di ogni nodo
 *   2. Mettiamo in coda tutti i nodi con in-degree = 0 (nessuna dipendenza)
 *   3. Finché la coda non è vuota:
 *      a. Estraiamo un nodo u
 *      b. Lo aggiungiamo all'ordinamento topologico
 *      c. Per ogni arco u→v, decrementiamo in-degree[v]
 *      d. Se in-degree[v] diventa 0, lo aggiungiamo alla coda
 *   4. Se l'ordinamento contiene tutti i nodi → non ci sono cicli
 *
 *   PERCHÉ FUNZIONA: un nodo viene processato solo quando tutti i suoi
 *   predecessori sono stati processati (in-degree = 0).
 */

vector<unsigned> ordinamentoTopologico(const Grafo& g) {
    unsigned V = g.n();
    vector<int> inDegree(V, 0);

    // Calcola in-degree
    for (unsigned u = 0; u < V; u++)
        for (unsigned v = 0; v < V; v++)
            if (g(u, v)) inDegree[v]++;

    // Coda con priorità: processiamo prima i nodi con durata maggiore
    // (euristica: i task più pesanti prima)
    queue<unsigned> coda;
    for (unsigned u = 0; u < V; u++)
        if (inDegree[u] == 0) coda.push(u);

    vector<unsigned> ordine;
    while (!coda.empty()) {
        unsigned u = coda.front();
        coda.pop();
        ordine.push_back(u);

        for (unsigned v = 0; v < V; v++) {
            if (g(u, v)) {
                inDegree[v]--;
                if (inDegree[v] == 0) coda.push(v);
            }
        }
    }

    return ordine;
}


// ============================================================================
// APPROCCIO A: GREEDY SCHEDULING CON VINCOLO MODULARE
// ============================================================================
/*
 * STEP-BY-STEP:
 *   1. Calcola l'ordinamento topologico
 *   2. Per ogni task nell'ordine topologico:
 *      a. Calcola il tempo minimo di inizio (max tra i finish-time dei predecessori)
 *      b. Tra tutti i processori disponibili al momento:
 *         - Scegliamo quello che si libera per primo
 *         - MA solo se la somma delle durate su quel processore è ≡ 0 (mod 3)
 *           oppure il processore è vuoto
 *      c. Assegna il task a quel processore
 *   3. Il makespan = max finish-time tra tutti i task
 */

struct ScheduleResult {
    int makespan;
    vector<int> assegnamento;       // assegnamento[task] = processore
    vector<int> startTime;          // quando inizia ogni task
    vector<int> finishTime;         // quando finisce ogni task
};

ScheduleResult greedyScheduling(const Grafo& g, const vector<int>& durata, 
                                 int P, bool vincoloModulare = false) {
    unsigned V = g.n();
    
    auto ordine = ordinamentoTopologico(g);
    
    // Per ogni processore: quando si libera e somma durate eseguite
    vector<int> processoreFine(P, 0);      // tempo di fine
    vector<int> processoreSomma(P, 0);     // somma durate assegnate

    ScheduleResult ris;
    ris.assegnamento.resize(V);
    ris.startTime.resize(V);
    ris.finishTime.resize(V, 0);

    for (unsigned task : ordine) {
        // Calcola il tempo minimo di inizio (tutti i predecessori devono aver finito)
        int minInizio = 0;
        for (unsigned pred = 0; pred < V; pred++) {
            if (g(pred, task)) {
                minInizio = max(minInizio, ris.finishTime[pred]);
            }
        }

        // Trova il miglior processore
        int migliorProc = -1;
        int migliorTempo = INT_MAX;

        for (int p = 0; p < P; p++) {
            int tempoDisponibile = max(processoreFine[p], minInizio);

            // Vincolo modulare: somma durate su questo processore deve essere %3==0
            // (oppure processore vuoto)
            if (vincoloModulare && processoreSomma[p] > 0 
                && processoreSomma[p] % 3 != 0) {
                continue;  // questo processore non è disponibile per vincolo
            }

            if (tempoDisponibile < migliorTempo) {
                migliorTempo = tempoDisponibile;
                migliorProc = p;
            }
        }

        // Se nessun processore disponibile per vincolo → usiamo il primo libero
        if (migliorProc == -1) {
            migliorTempo = INT_MAX;
            for (int p = 0; p < P; p++) {
                int tempoDisponibile = max(processoreFine[p], minInizio);
                if (tempoDisponibile < migliorTempo) {
                    migliorTempo = tempoDisponibile;
                    migliorProc = p;
                }
            }
        }

        // Assegna il task al processore
        ris.assegnamento[task] = migliorProc;
        ris.startTime[task] = migliorTempo;
        ris.finishTime[task] = migliorTempo + durata[task];
        processoreFine[migliorProc] = ris.finishTime[task];
        processoreSomma[migliorProc] += durata[task];
    }

    ris.makespan = *max_element(ris.finishTime.begin(), ris.finishTime.end());
    return ris;
}


// ============================================================================
// APPROCCIO B: CRITICAL PATH METHOD
// ============================================================================
/*
 * STEP-BY-STEP:
 *   1. Ordinamento topologico del DAG
 *   2. DP in avanti: per ogni nodo, calcola il tempo più presto di inizio
 *      ES[v] = max(ES[u] + durata[u]) per ogni u predecessore di v
 *   3. Il cammino critico = max(ES[v] + durata[v]) per ogni nodo v
 *   4. Questo è il LOWER BOUND del makespan (anche con infiniti processori)
 *
 *   NOTA: il cammino critico è il "percorso più lungo" nel DAG pesato.
 *   Anche con 1000 processori, non puoi finire prima del cammino critico!
 */

int calcolaCamminoCritico(const Grafo& g, const vector<int>& durata) {
    unsigned V = g.n();
    auto ordine = ordinamentoTopologico(g);

    // ES[v] = earliest start time per il nodo v
    vector<int> ES(V, 0);

    for (unsigned v : ordine) {
        for (unsigned u = 0; u < V; u++) {
            if (g(u, v)) {  // arco u → v
                ES[v] = max(ES[v], ES[u] + durata[u]);
            }
        }
    }

    // Il makespan minimo = max (ES[v] + durata[v])
    int critico = 0;
    for (unsigned v = 0; v < V; v++) {
        critico = max(critico, ES[v] + durata[v]);
    }

    return critico;
}


// ============================================================================
//                              MAIN - TEST
// ============================================================================
/*
 *  DAG di task:
 *
 *    0(3) → 1(2) → 3(4)
 *      ↘         ↗
 *       2(5) → 4(1) → 5(3)
 *
 *  Durate: [3, 2, 5, 4, 1, 3]
 *
 *  Dipendenze:
 *    0 → 1, 0 → 2
 *    1 → 3
 *    2 → 4
 *    4 → 3, 4 → 5
 *
 *  Cammino critico: 0→2→4→3 = 3+5+1+4 = 13
 *                   0→2→4→5 = 3+5+1+3 = 12
 *  Il cammino critico è 13.
 */

int main() {
    Grafo g(6);

    g(0, 1, true);
    g(0, 2, true);
    g(1, 3, true);
    g(2, 4, true);
    g(4, 3, true);
    g(4, 5, true);

    vector<int> durata = {3, 2, 5, 4, 1, 3};

    cout << "=== ESERCIZIO 4: Scheduling su DAG ===" << endl;
    cout << "Task (durate): ";
    for (unsigned i = 0; i < durata.size(); i++)
        cout << i << "(" << durata[i] << ") ";
    cout << endl;
    cout << "Dipendenze: 0→1, 0→2, 1→3, 2→4, 4→3, 4→5" << endl;
    cout << endl;

    // Ordinamento Topologico
    auto ordTop = ordinamentoTopologico(g);
    cout << "Ordinamento topologico: ";
    for (unsigned u : ordTop) cout << u << " ";
    cout << endl << endl;

    // Cammino Critico (Lower Bound)
    int critico = calcolaCamminoCritico(g, durata);
    cout << "Cammino Critico (lower bound): " << critico << endl << endl;

    // Test con diversi numeri di processori
    for (int P = 1; P <= 3; P++) {
        cout << "--- P = " << P << " processori ---" << endl;

        // Senza vincolo modulare
        auto ris = greedyScheduling(g, durata, P, false);
        cout << "  Greedy (senza vincolo mod):  makespan = " << ris.makespan << endl;
        cout << "    Assegnamento: ";
        for (unsigned i = 0; i < durata.size(); i++)
            cout << "task" << i << "→P" << ris.assegnamento[i] 
                 << "[" << ris.startTime[i] << "-" << ris.finishTime[i] << "] ";
        cout << endl;

        // Con vincolo modulare
        auto risM = greedyScheduling(g, durata, P, true);
        cout << "  Greedy (con vincolo %3):     makespan = " << risM.makespan << endl;
        cout << "    Assegnamento: ";
        for (unsigned i = 0; i < durata.size(); i++)
            cout << "task" << i << "→P" << risM.assegnamento[i]
                 << "[" << risM.startTime[i] << "-" << risM.finishTime[i] << "] ";
        cout << endl << endl;
    }

    return 0;
}
