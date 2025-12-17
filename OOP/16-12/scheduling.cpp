#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * PROBLEMA: Scheduling di Attività con Peso (Weighted Job Scheduling)
 * 
 * Abbiamo n attività, ognuna con:
 * - tempo di inizio (start)
 * - tempo di fine (end)  
 * - valore/peso (value)
 * 
 * Due attività sono COMPATIBILI se i loro intervalli NON si sovrappongono.
 * Obiettivo: trovare il sottoinsieme di attività compatibili con valore MASSIMO.
 * 
 * STRATEGIA (Programmazione Dinamica):
 * 1. Ordiniamo le attività per tempo di FINE crescente
 * 2. Per ogni attività i, calcoliamo dp[i] = massimo valore ottenibile
 *    considerando le attività da 0 a i, dove l'attività i è INCLUSA
 * 3. Per ogni attività i abbiamo due scelte:
 *    - NON includere l'attività i: il valore rimane dp[i-1]
 *    - INCLUDERE l'attività i: value[i] + dp[j], dove j è l'ultima attività
 *      compatibile con i (cioè che finisce PRIMA che i inizi)
 */

// Struttura per rappresentare un'attività
struct Attivita {
    int start;   // tempo di inizio
    int end;     // tempo di fine
    int value;   // valore dell'attività
    int id;      // identificatore originale (per tracciare quale attività)
};

// Funzione per confrontare attività per tempo di fine (per ordinamento)
bool confrontaPerFine(const Attivita& a, const Attivita& b) {
    return a.end < b.end;
}

/*
 * Ricerca binaria per trovare l'ultima attività compatibile con l'attività i.
 * Un'attività j è compatibile con i se: end[j] <= start[i]
 * (j finisce prima o quando i inizia)
 * 
 * Restituisce l'indice dell'ultima attività compatibile, oppure -1 se non esiste.
 */
int trovaUltimaCompatibile(const vector<Attivita>& attivita, int i) {
    int low = 0;
    int high = i - 1;
    int risultato = -1;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        
        // Se l'attività mid finisce prima o quando l'attività i inizia
        if (attivita[mid].end <= attivita[i].start) {
            risultato = mid;  // mid è una candidata valida
            low = mid + 1;    // cerchiamo una più recente a destra
        } else {
            high = mid - 1;   // mid non è compatibile, cerchiamo a sinistra
        }
    }
    
    return risultato;
}

/*
 * Funzione principale per calcolare il massimo valore ottenibile
 * da un sottoinsieme di attività compatibili.
 */
int schedulingMassimo(vector<Attivita>& attivita) {
    int n = attivita.size();
    if (n == 0) return 0;
    
    // PASSO 1: Ordina le attività per tempo di fine crescente
    // Questo è fondamentale per la programmazione dinamica!
    sort(attivita.begin(), attivita.end(), confrontaPerFine);
    
    cout << "\n=== ATTIVITA' ORDINATE PER TEMPO DI FINE ===" << endl;
    for (int i = 0; i < n; i++) {
        cout << "a" << attivita[i].id << ": [" << attivita[i].start 
             << ", " << attivita[i].end << "] valore=" << attivita[i].value << endl;
    }
    
    // PASSO 2: Crea array dp dove dp[i] = massimo valore considerando attività 0..i
    vector<int> dp(n);
    
    // Caso base: considerando solo la prima attività, il massimo è il suo valore
    dp[0] = attivita[0].value;
    
    cout << "\n=== CALCOLO DP STEP BY STEP ===" << endl;
    cout << "dp[0] = " << dp[0] << " (solo attività a" << attivita[0].id << ")" << endl;
    
    // PASSO 3: Riempi la tabella dp
    for (int i = 1; i < n; i++) {
        // Opzione 1: NON includere l'attività i
        int valoreEscludi = dp[i - 1];
        
        // Opzione 2: INCLUDERE l'attività i
        int valoreIncludi = attivita[i].value;
        
        // Trova l'ultima attività compatibile con i
        int j = trovaUltimaCompatibile(attivita, i);
        
        // Se esiste un'attività compatibile, aggiungi il suo dp
        if (j != -1) {
            valoreIncludi += dp[j];
        }
        
        // Prendi il massimo tra includere e non includere
        dp[i] = max(valoreEscludi, valoreIncludi);
        
        // Stampa spiegazione
        cout << "\nAttività a" << attivita[i].id << " [" << attivita[i].start 
             << ", " << attivita[i].end << "] valore=" << attivita[i].value << endl;
        cout << "  Ultima compatibile: ";
        if (j != -1) {
            cout << "a" << attivita[j].id << " (finisce a " << attivita[j].end << ")" << endl;
        } else {
            cout << "nessuna" << endl;
        }
        cout << "  Opzione ESCLUDI: dp[" << i-1 << "] = " << valoreEscludi << endl;
        cout << "  Opzione INCLUDI: " << attivita[i].value;
        if (j != -1) {
            cout << " + dp[" << j << "](" << dp[j] << ") = " << valoreIncludi;
        }
        cout << endl;
        cout << "  dp[" << i << "] = max(" << valoreEscludi << ", " << valoreIncludi 
             << ") = " << dp[i] << endl;
    }
    
    // Il risultato è l'ultimo elemento di dp
    return dp[n - 1];
}

int main() {
    /*
     * ESEMPIO dal problema:
     * a0: 1, 4, 1    (inizia a 1, finisce a 4, vale 1)
     * a1: 3, 5, 2
     * a2: 0, 6, 3
     * a3: 4, 7, 4
     * a4: 3, 8, 5
     * a5: 5, 9, 6
     * a6: 6, 10, 7
     * a7: 7, 11, 8
     * 
     * Risposta attesa: 13 (attività 0, 3, 7: 1+4+8=13)
     */
    
    vector<Attivita> attivita = {
        {1, 4, 1, 0},   // a0: start=1, end=4, value=1
        {3, 5, 2, 1},   // a1
        {0, 6, 3, 2},   // a2
        {4, 7, 4, 3},   // a3
        {3, 8, 5, 4},   // a4
        {5, 9, 6, 5},   // a5
        {6, 10, 7, 6},  // a6
        {7, 11, 8, 7}   // a7
    };
    
    cout << "=== INPUT: ATTIVITA' ORIGINALI ===" << endl;
    for (int i = 0; i < attivita.size(); i++) {
        cout << "a" << i << ": [" << attivita[i].start << ", " 
             << attivita[i].end << "] valore=" << attivita[i].value << endl;
    }
    
    int risultato = schedulingMassimo(attivita);
    
    cout << "\n=== RISULTATO FINALE ===" << endl;
    cout << "Massimo valore ottenibile: " << risultato << endl;
    
    return 0;
}

/*
 * ============================================================================
 * SPIEGAZIONE STEP BY STEP DELL'ESEMPIO
 * ============================================================================
 * 
 * INPUT ORIGINALE:
 * a0: [1, 4] v=1    a1: [3, 5] v=2    a2: [0, 6] v=3    a3: [4, 7] v=4
 * a4: [3, 8] v=5    a5: [5, 9] v=6    a6: [6, 10] v=7   a7: [7, 11] v=8
 * 
 * PASSO 1 - ORDINAMENTO per tempo di fine:
 * Indice 0: a0 [1,4]  v=1   (finisce prima)
 * Indice 1: a1 [3,5]  v=2
 * Indice 2: a2 [0,6]  v=3
 * Indice 3: a3 [4,7]  v=4
 * Indice 4: a4 [3,8]  v=5
 * Indice 5: a5 [5,9]  v=6
 * Indice 6: a6 [6,10] v=7
 * Indice 7: a7 [7,11] v=8   (finisce per ultimo)
 * 
 * PASSO 2 - CALCOLO DP:
 * 
 * dp[0] = 1 (solo a0)
 * 
 * dp[1] (a1 [3,5] v=2):
 *   - Ultima compatibile: nessuna (a0 finisce a 4 > 3)
 *   - ESCLUDI: dp[0] = 1
 *   - INCLUDI: 2
 *   - dp[1] = max(1, 2) = 2
 * 
 * dp[2] (a2 [0,6] v=3):
 *   - Ultima compatibile: nessuna (inizia a 0, nessuno finisce prima!)
 *   - ESCLUDI: dp[1] = 2
 *   - INCLUDI: 3
 *   - dp[2] = max(2, 3) = 3
 * 
 * dp[3] (a3 [4,7] v=4):
 *   - Ultima compatibile: a0 (finisce a 4 <= 4)
 *   - ESCLUDI: dp[2] = 3
 *   - INCLUDI: 4 + dp[0] = 4 + 1 = 5
 *   - dp[3] = max(3, 5) = 5
 * 
 * dp[4] (a4 [3,8] v=5):
 *   - Ultima compatibile: nessuna (inizia a 3, ma a0 finisce a 4 > 3)
 *   - ESCLUDI: dp[3] = 5
 *   - INCLUDI: 5
 *   - dp[4] = max(5, 5) = 5
 * 
 * dp[5] (a5 [5,9] v=6):
 *   - Ultima compatibile: a1 (finisce a 5 <= 5)
 *   - ESCLUDI: dp[4] = 5
 *   - INCLUDI: 6 + dp[1] = 6 + 2 = 8
 *   - dp[5] = max(5, 8) = 8
 * 
 * dp[6] (a6 [6,10] v=7):
 *   - Ultima compatibile: a2 (finisce a 6 <= 6)
 *   - ESCLUDI: dp[5] = 8
 *   - INCLUDI: 7 + dp[2] = 7 + 3 = 10
 *   - dp[6] = max(8, 10) = 10
 * 
 * dp[7] (a7 [7,11] v=8):
 *   - Ultima compatibile: a3 (finisce a 7 <= 7)
 *   - ESCLUDI: dp[6] = 10
 *   - INCLUDI: 8 + dp[3] = 8 + 5 = 13
 *   - dp[7] = max(10, 13) = 13
 * 
 * RISULTATO: dp[7] = 13
 * 
 * Questo corrisponde a selezionare:
 * - a0 [1,4] valore=1
 * - a3 [4,7] valore=4 (inizia quando a0 finisce)
 * - a7 [7,11] valore=8 (inizia quando a3 finisce)
 * 
 * Totale: 1 + 4 + 8 = 13
 * 
 * ============================================================================
 * COMPLESSITÀ
 * ============================================================================
 * - Tempo: O(n log n) per l'ordinamento + O(n log n) per le ricerche binarie
 *   = O(n log n) totale
 * - Spazio: O(n) per l'array dp
 */
