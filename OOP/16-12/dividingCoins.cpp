#include<iostream>
#include <vector>
using namespace std;

/*
 * ============================================================================
 * PERCHÉ SI CHIAMA PROGRAMMAZIONE DINAMICA?
 * ============================================================================
 * 
 * La PROGRAMMAZIONE DINAMICA è una tecnica che risolve problemi complessi
 * scomponendoli in SOTTOPROBLEMI più semplici, e ha queste caratteristiche:
 * 
 * 1. SOTTOPROBLEMI SOVRAPPOSTI (Overlapping Subproblems)
 *    Lo stesso sottoproblema viene risolto più volte. Invece di ricalcolarlo,
 *    lo MEMORIZZIAMO in una tabella (array, matrice, ecc.)
 * 
 * 2. SOTTOSTRUTTURA OTTIMA (Optimal Substructure)
 *    La soluzione ottima del problema si costruisce dalle soluzioni ottime
 *    dei sottoproblemi.
 * 
 * In questo codice:
 * - L'array sommeParziali[] è la TABELLA DP (memorizzazione)
 * - sommeParziali[i] = true significa "posso ottenere la somma i?"
 * - Ogni volta che processiamo una moneta, RIUTILIZZIAMO le informazioni
 *   già calcolate (sottoproblemi sovrapposti)
 * - Costruiamo la risposta partendo da somme piccole verso somme grandi
 *   (sottostruttura ottima)
 * 
 * DIFFERENZA DA ALTRI APPROCCI:
 * - FORZA BRUTA: proverebbe tutte le 2^n combinazioni di monete → O(2^n)
 * - PROGRAMMAZIONE DINAMICA: usa la tabella per evitare ricalcoli → O(n * target)
 * 
 * È come dire: "invece di rifare gli stessi calcoli, me li scrivo e li riuso!"
 * ============================================================================
 */

int divCoins(const vector<int>& monete){
    // Calcola la somma totale di tutte le monete
    int tot = 0;
    for (int i : monete){
        tot += i;
    }
    
    // Il target è metà della somma totale
    // Se riusciamo a fare esattamente target, la differenza sarà minima (0 o 1)
    int target = tot / 2;
    
    /*
     * ECCO LA TABELLA DP!
     * sommeParziali[i] = true significa "è possibile ottenere la somma i
     *                                    usando un sottoinsieme delle monete"
     * 
     * Questa è la "memoria" della programmazione dinamica.
     * Invece di ricalcolare ogni volta se una somma è raggiungibile,
     * la calcoliamo UNA VOLTA e la memorizziamo.
     */
    vector<bool> sommeParziali(target + 1, false);
    
    // Caso base: possiamo sempre ottenere somma 0 (non prendendo nessuna moneta)
    sommeParziali[0] = true;

    /*
     * COSTRUZIONE BOTTOM-UP della tabella DP
     * 
     * Per ogni moneta m, aggiorniamo la tabella:
     * "Se potevo fare la somma i, ora posso fare anche la somma i+m"
     * 
     * IMPORTANTE: iteriamo da destra a sinistra (target verso 0) per evitare
     * di usare la stessa moneta più volte nella stessa iterazione!
     */
    for(int m : monete) {
        // Scorriamo da target-m verso 0 per non riutilizzare la stessa moneta
        for(int i = target - m; i >= 0; --i) {
            if(sommeParziali[i]) {
                // Se posso fare somma i, allora posso fare anche somma i+m
                sommeParziali[i + m] = true;
            }
        }
        // Ottimizzazione: se abbiamo già raggiunto il target, possiamo fermarci
        if(sommeParziali[target]) {
            break;
        }
    }
    
    /*
     * Cerchiamo la somma più grande ≤ target che possiamo ottenere.
     * Se troviamo somma s per un gruppo, l'altro gruppo ha somma (tot - s).
     * La differenza è: |s - (tot - s)| = |2s - tot| = tot - 2s
     */
    for(int i = target; i >= 0; --i) {
        if(sommeParziali[i]) {
            // Gruppo 1 ha somma i, Gruppo 2 ha somma (tot - i)
            // Differenza = (tot - i) - i = tot - 2*i
            return tot - 2 * i;
        }
    }
    return -1; // Non dovrebbe mai accadere
}

int main() {
    vector<int> monete;
    cout << "Inserisci le monete separate da spazio (-1 per terminare): " << endl;
    int input;
    cin >> input;
    while(input != -1) {
        monete.push_back(input);
        cin >> input;  // Corretto: era cin<<input (errore di sintassi)
    }
    int diff = divCoins(monete);
    cout << "La differenza minima è: " << diff << endl;  // Corretto: era count
    return 0;
}

/*
 * ============================================================================
 * ESEMPIO PRATICO
 * ============================================================================
 * 
 * Monete: [1, 5, 2, 8]    Totale = 16    Target = 8
 * 
 * Inizialmente:    sommeParziali = [T, F, F, F, F, F, F, F, F]
 *                                   0  1  2  3  4  5  6  7  8
 * 
 * Dopo moneta 1:   [T, T, F, F, F, F, F, F, F]  (posso fare 0 e 1)
 * Dopo moneta 5:   [T, T, F, F, F, T, T, F, F]  (anche 5 e 6)
 * Dopo moneta 2:   [T, T, T, T, F, T, T, T, T]  (anche 2,3,7,8)
 * 
 * sommeParziali[8] = true! Posso dividere in due gruppi da 8 ciascuno.
 * Differenza = 16 - 2*8 = 0 (divisione perfetta!)
 * 
 * ============================================================================
 * RIEPILOGO: PERCHÉ È PROGRAMMAZIONE DINAMICA
 * ============================================================================
 * 
 * 1. TABELLA DI MEMORIZZAZIONE: sommeParziali[] salva i risultati intermedi
 * 
 * 2. SOTTOPROBLEMI SOVRAPPOSTI: "posso fare somma 5?" viene chiesto più volte
 *    (con monete diverse), ma lo calcoliamo una volta sola
 * 
 * 3. COSTRUZIONE INCREMENTALE: partiamo da somme piccole e costruiamo
 *    verso somme più grandi, riutilizzando i risultati precedenti
 * 
 * 4. EFFICIENZA: O(n * target) invece di O(2^n) della forza bruta
 * ============================================================================
 */