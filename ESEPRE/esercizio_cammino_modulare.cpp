/*
 * ============================================================================
 *  ESERCIZIO 1: CAMMINO MINIMO CON VINCOLO MODULARE (DP + BFS su grafo)
 * ============================================================================
 *
 *  PROBLEMA:
 *    Dato un grafo orientato dove ogni nodo i ha un valore val[i],
 *    trovare il cammino PIÙ CORTO (in numero di archi) da s a t
 *    tale che la SOMMA dei valori dei nodi sul cammino sia
 *    divisibile per K (cioè somma % K == 0).
 *
 *    Se non esiste nessun cammino con questa proprietà → ritorna -1.
 *
 *  IDEA CHIAVE:
 *    Non basta una BFS normale! Due cammini che arrivano allo stesso nodo
 *    con la STESSA lunghezza ma DIVERSO resto (sommma % K) sono DIVERSI.
 *
 *    Quindi espandiamo lo stato: invece di visitare solo "nodo",
 *    visitiamo la coppia (nodo, resto_mod_K).
 *
 *    Stato = (nodo_corrente, somma_parziale % K)
 *    Target = (t, 0)   ← vogliamo arrivare a t con resto 0
 *
 *  COMPLESSITÀ:
 *    - Stati totali: V * K (ogni nodo × ogni possibile resto)
 *    - Per ogni stato, scanzioniamo V vicini (matrice di adiacenza)
 *    - Totale: O(V² * K)
 *
 *  CONFRONTO CON APPROCCIO NAIVE:
 *    Un approccio naive enumererebbe TUTTI i cammini da s a t (esponenziali!)
 *    e controllerebbe il vincolo su ciascuno. Questo DP è polinomiale.
 *
 * ============================================================================
 */

#include "../esami/prof/Grafo.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
 * STEP-BY-STEP dell'algoritmo:
 *
 * 1. Creiamo un array 2D visited[nodo][resto] inizializzato a false
 * 2. Creiamo un array 2D dist[nodo][resto] per la distanza minima
 * 3. Inseriamo lo stato iniziale (s, val[s] % K) nella coda BFS
 * 4. Per ogni stato (u, r) estratto dalla coda:
 *    a. Per ogni vicino j di u nel grafo:
 *       - Calcoliamo il nuovo resto: r_new = (r + val[j]) % K
 *       - Se lo stato (j, r_new) non è stato visitato:
 *         → lo segniamo visitato
 *         → dist[j][r_new] = dist[u][r] + 1
 *         → lo aggiungiamo alla coda
 *       - Se j == t e r_new == 0 → TROVATO! Ritorna la distanza
 * 5. Se la coda si svuota senza trovare (t, 0) → ritorna -1
 */

int camminoMinModulare(const Grafo& g, const vector<int>& val, 
                        unsigned s, unsigned t, int K) {
    unsigned V = g.n();
    
    // visited[nodo][resto] = true se lo stato è già stato esplorato
    vector<vector<bool>> visited(V, vector<bool>(K, false));
    // dist[nodo][resto] = distanza minima per raggiungere questo stato
    vector<vector<int>> dist(V, vector<int>(K, -1));

    // Calcolo il resto iniziale (il nodo s fa parte del cammino)
    int restoIniziale = ((val[s] % K) + K) % K;  // gestione valori negativi

    // Caso speciale: s == t
    if (s == t && restoIniziale == 0) return 0;

    // Stato iniziale
    queue<pair<unsigned, int>> coda;  // (nodo, resto)
    coda.push({s, restoIniziale});
    visited[s][restoIniziale] = true;
    dist[s][restoIniziale] = 0;

    while (!coda.empty()) {
        auto [u, r] = coda.front();
        coda.pop();

        // Esploriamo tutti i vicini di u
        for (unsigned j = 0; j < V; j++) {
            if (g(u, j)) {  // esiste arco u → j
                // Nuovo resto dopo aver aggiunto val[j]
                int nuovoResto = ((r + val[j]) % K + K) % K;

                if (!visited[j][nuovoResto]) {
                    visited[j][nuovoResto] = true;
                    dist[j][nuovoResto] = dist[u][r] + 1;

                    // Abbiamo raggiunto t con somma divisibile per K?
                    if (j == t && nuovoResto == 0) {
                        return dist[j][nuovoResto];
                    }

                    coda.push({j, nuovoResto});
                }
            }
        }
    }

    return -1;  // nessun cammino valido trovato
}


/*
 * ============================================================================
 *  VARIANTE BONUS: ricostruzione del cammino
 *
 *  Non basta sapere che esiste, vogliamo anche STAMPARE il cammino!
 *  Per farlo, salviamo il "predecessore" per ogni stato (nodo, resto).
 * ============================================================================
 */

struct Stato {
    unsigned nodo;
    int resto;
};

int camminoMinModulareConPercorso(const Grafo& g, const vector<int>& val,
                                   unsigned s, unsigned t, int K,
                                   vector<unsigned>& percorso) {
    unsigned V = g.n();
    vector<vector<bool>> visited(V, vector<bool>(K, false));
    vector<vector<int>> dist(V, vector<int>(K, -1));
    
    // Predecessore per ricostruire il cammino
    // pred[nodo][resto] = stato precedente
    vector<vector<Stato>> pred(V, vector<Stato>(K, {(unsigned)-1, -1}));

    int r0 = ((val[s] % K) + K) % K;
    if (s == t && r0 == 0) {
        percorso.push_back(s);
        return 0;
    }

    queue<pair<unsigned, int>> coda;
    coda.push({s, r0});
    visited[s][r0] = true;
    dist[s][r0] = 0;

    bool trovato = false;

    while (!coda.empty() && !trovato) {
        auto [u, r] = coda.front();
        coda.pop();

        for (unsigned j = 0; j < V; j++) {
            if (g(u, j)) {
                int nr = ((r + val[j]) % K + K) % K;
                if (!visited[j][nr]) {
                    visited[j][nr] = true;
                    dist[j][nr] = dist[u][r] + 1;
                    pred[j][nr] = {u, r};  // salva il predecessore

                    if (j == t && nr == 0) {
                        trovato = true;
                        break;
                    }
                    coda.push({j, nr});
                }
            }
        }
    }

    if (!trovato) return -1;

    // Ricostruzione del cammino (all'indietro)
    percorso.clear();
    Stato curr = {t, 0};
    while (curr.nodo != s || curr.resto != r0) {
        percorso.push_back(curr.nodo);
        curr = pred[curr.nodo][curr.resto];
    }
    percorso.push_back(s);

    // Invertiamo per avere s → ... → t
    for (int i = 0, j = percorso.size() - 1; i < j; i++, j--)
        swap(percorso[i], percorso[j]);

    return dist[t][0];
}


// ============================================================================
//                              MAIN - TEST
// ============================================================================
/*
 *  Grafo di test:
 *
 *     val: [3, 1, 4, 2, 5, 6]
 *
 *     0(3) → 1(1) → 2(4)
 *       ↓           ↓
 *     3(2) → 4(5) → 5(6)
 *
 *  K = 3: cerchiamo cammini con somma % 3 == 0
 *
 *  Cammino 0→1→2: somma = 3+1+4 = 8, 8%3 = 2 ❌
 *  Cammino 0→3→4→5: somma = 3+2+5+6 = 16, 16%3 = 1 ❌
 *  Cammino 0→1→2→5: somma = 3+1+4+6 = 14, 14%3 = 2 ❌
 *  Cammino 0→3→4: somma = 3+2+5 = 10, 10%3 = 1 ❌
 *  Aggiungiamo arco 4→2 per creare: 0→3→4→2: somma = 3+2+5+4 = 14 ❌
 *  Hmm aggiungiamo archi migliori...
 *  Arco 1→5: Cammino 0→1→5: somma = 3+1+6 = 10 ❌
 *  Arco 2→5: già presente
 *  Cammino 0→3: somma = 3+2 = 5 ❌
 *  
 *  Rendiamo i valori più comodi:
 *   val = [3, 6, 2, 1, 5, 4]
 *  Cammino 0→1: somma = 3+6 = 9, 9%3 = 0 ✅ (lunghezza 1)
 */

int main() {
    Grafo g(6);
    
    // Archi del grafo
    g(0, 1, true);  // 0 → 1
    g(0, 3, true);  // 0 → 3
    g(1, 2, true);  // 1 → 2
    g(2, 5, true);  // 2 → 5
    g(3, 4, true);  // 3 → 4
    g(4, 5, true);  // 4 → 5
    g(1, 4, true);  // 1 → 4 (arco extra per più percorsi)

    vector<int> val = {3, 6, 2, 1, 5, 4};
    int K = 3;

    cout << "=== ESERCIZIO 1: Cammino Minimo con Vincolo Modulare ===" << endl;
    cout << "Valori nodi: ";
    for (int v : val) cout << v << " ";
    cout << "\nK = " << K << " (somma cammino deve essere % " << K << " == 0)" << endl;
    cout << endl;

    // Test 1: s=0, t=1 → cammino 0→1, somma=3+6=9, 9%3=0 ✅
    {
        vector<unsigned> percorso;
        int d = camminoMinModulareConPercorso(g, val, 0, 1, K, percorso);
        cout << "Test s=0 → t=1: ";
        if (d == -1) {
            cout << "NESSUN CAMMINO VALIDO" << endl;
        } else {
            cout << "lunghezza=" << d << ", percorso: ";
            int somma = 0;
            for (unsigned i = 0; i < percorso.size(); i++) {
                if (i > 0) cout << "→";
                cout << percorso[i] << "(" << val[percorso[i]] << ")";
                somma += val[percorso[i]];
            }
            cout << " | somma=" << somma << ", " << somma << "%" << K << "=" << somma % K << endl;
        }
    }

    // Test 2: s=0, t=5 → cerchiamo cammino con somma%3==0
    {
        vector<unsigned> percorso;
        int d = camminoMinModulareConPercorso(g, val, 0, 5, K, percorso);
        cout << "Test s=0 → t=5: ";
        if (d == -1) {
            cout << "NESSUN CAMMINO VALIDO" << endl;
        } else {
            cout << "lunghezza=" << d << ", percorso: ";
            int somma = 0;
            for (unsigned i = 0; i < percorso.size(); i++) {
                if (i > 0) cout << "→";
                cout << percorso[i] << "(" << val[percorso[i]] << ")";
                somma += val[percorso[i]];
            }
            cout << " | somma=" << somma << ", " << somma << "%" << K << "=" << somma % K << endl;
        }
    }

    // Test 3: s=3, t=5 
    {
        vector<unsigned> percorso;
        int d = camminoMinModulareConPercorso(g, val, 3, 5, K, percorso);
        cout << "Test s=3 → t=5: ";
        if (d == -1) {
            cout << "NESSUN CAMMINO VALIDO" << endl;
        } else {
            cout << "lunghezza=" << d << ", percorso: ";
            int somma = 0;
            for (unsigned i = 0; i < percorso.size(); i++) {
                if (i > 0) cout << "→";
                cout << percorso[i] << "(" << val[percorso[i]] << ")";
                somma += val[percorso[i]];
            }
            cout << " | somma=" << somma << ", " << somma << "%" << K << "=" << somma % K << endl;
        }
    }

    // Test 4: nodo irraggiungibile
    {
        int d = camminoMinModulare(g, val, 5, 0, K);
        cout << "Test s=5 → t=0 (irraggiungibile): " 
             << (d == -1 ? "NESSUN CAMMINO (-1)" : to_string(d)) << endl;
    }

    // Test 5: stesso nodo
    {
        vector<unsigned> percorso;
        int d = camminoMinModulareConPercorso(g, val, 0, 0, K, percorso);
        cout << "Test s=0 → t=0 (val[0]=3, 3%3=0): ";
        if (d == -1) {
            cout << "NESSUN CAMMINO VALIDO" << endl;
        } else {
            cout << "lunghezza=" << d << ", percorso: ";
            for (unsigned i = 0; i < percorso.size(); i++) {
                if (i > 0) cout << "→";
                cout << percorso[i];
            }
            cout << endl;
        }
    }

    return 0;
}
