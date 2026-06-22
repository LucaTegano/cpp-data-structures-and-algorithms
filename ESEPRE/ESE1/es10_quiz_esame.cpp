/*
 * ============================================================================
 *  ESERCIZIO 10: QUIZ D'ESAME COMPLETO — MIX AVANZATO
 *                Stile esame universitario completo con tutte le trappole
 * ============================================================================
 *  Matricola esempio: {3, 1, 4, 1, 5, 9}
 */

#include <iostream>
using namespace std;

// ----------- Funzioni del quiz -----------

void alpha(int* a, int& b) {
    *a = b + 1;
    b = *a + 1;
    a = &b;      // cambia la copia locale di a, non l'originale!
    *a = 0;      // ora a punta a b → b = 0
}

int* beta(int* arr, int n) {
    int* max = arr;
    for (int i = 1; i < n; i++)
        if (arr[i] > *max)
            max = &arr[i];  // max punta all'elemento maggiore
    return max;             // ✅ OK: arr è nell'heap, il puntatore è valido
}

void gamma(int** p, int* q) {
    *p = q;      // fa puntare *p (il puntatore originale) a dove punta q
}

int& delta(int* arr, int i) {
    return arr[i];  // ✅ reference a elemento di array (heap → valido)
}

void epsilon(int*& p) {
    p++;  // sposta il PUNTATORE ORIGINALE di una posizione!!!
}

int main() {
    int* m = new int[6]{3, 1, 4, 1, 5, 9};
    //                  0  1  2  3  4  5

    cout << "=== QUIZ D'ESAME: Traccia ogni modifica step by step ===" << endl;
    cout << "Matricola: {3, 1, 4, 1, 5, 9}" << endl << endl;

    // =====================================================================
    // DOMANDA 1: alpha(m+2, m[4]) — Cosa stampa m[2], m[4]?
    // =====================================================================
    /*
     * alpha(int* a, int& b):
     *   a = m+2 → punta a m[2] = 4
     *   b è reference a m[4] = 5
     *
     *   *a = b + 1    → m[2] = 5 + 1 = 6
     *   b = *a + 1    → m[4] = 6 + 1 = 7
     *   a = &b        → a (COPIA LOCALE!) ora punta a m[4]
     *                    m non cambia, solo la variabile locale a
     *   *a = 0        → m[4] = 0 (perché a ora punta a b = m[4])
     *
     *   Stato: m = {3, 1, 6, 1, 0, 9}
     */
    cout << "--- DOMANDA 1: alpha(m+2, m[4]) ---" << endl;
    alpha(m + 2, m[4]);
    cout << "m[2]=" << m[2] << " (atteso: 6)" << endl;
    cout << "m[4]=" << m[4] << " (atteso: 0)" << endl;
    cout << "Tutto m: ";
    for (int i=0; i<6; i++) cout << m[i] << " ";
    cout << endl << endl;

    // Reset
    m[0]=3; m[1]=1; m[2]=4; m[3]=1; m[4]=5; m[5]=9;

    // =====================================================================
    // DOMANDA 2: beta — cosa restituisce?
    // =====================================================================
    /*
     * beta(m, 6) scorre l'array e restituisce un puntatore al MAX.
     *
     * m = {3, 1, 4, 1, 5, 9}
     * Max = 9 all'indice 5
     * Restituisce &m[5]
     *
     * È corretto perché m è nell'heap (allocato con new).
     * Se fosse un array locale dentro beta → DANGLING!
     *
     * *beta(m, 6) = 9
     * beta(m, 6) - m = 5  (indice dell'elemento massimo)
     */
    cout << "--- DOMANDA 2: beta(m, 6) ---" << endl;
    int* maxP = beta(m, 6);
    cout << "*maxP = " << *maxP << " (atteso: 9)" << endl;
    cout << "Indice del max: " << (maxP - m) << " (atteso: 5)" << endl;

    // Modifica tramite il puntatore restituito
    *maxP = 0;
    cout << "Dopo *maxP=0: m[5]=" << m[5] << endl;
    m[5] = 9;  // reset
    cout << endl;

    // =====================================================================
    // DOMANDA 3: gamma — doppio puntatore che reindirizza
    // =====================================================================
    /*
     * int* ptr = m;          → ptr punta a m[0]
     * gamma(&ptr, m + 3);    → *(&ptr) = m+3 → ptr = m+3!
     *                           ptr ora punta a m[3]
     *
     * cout << *ptr → m[3] = 1
     *
     * ATTENZIONE: m non è stato modificato!
     * Solo ptr è stato spostato, m è invariato.
     */
    cout << "--- DOMANDA 3: gamma(&ptr, m+3) ---" << endl;
    int* ptr = m;
    cout << "Prima:  *ptr=" << *ptr << " (ptr punta a m[0]=3)" << endl;
    gamma(&ptr, m + 3);
    cout << "Dopo:   *ptr=" << *ptr << " (ptr punta a m[3]=1)" << endl;
    cout << endl;

    // =====================================================================
    // DOMANDA 4: delta — reference a elemento dell'array
    // =====================================================================
    /*
     * delta(m, 2) ritorna un int& a m[2]
     *
     * delta(m, 2) = 99  → m[2] = 99
     *
     * delta(m, delta(m, 3)) = ?
     *   Primo: delta(m, 3) → reference a m[3] = 1 → letto come int = 1
     *   Poi: delta(m, 1) → reference a m[1]
     *   delta(m, delta(m, 3)) = 77 → m[1] = 77
     */
    cout << "--- DOMANDA 4: delta (reference a array) ---" << endl;
    delta(m, 2) = 99;
    cout << "Dopo delta(m,2)=99: m[2]=" << m[2] << " (atteso: 99)" << endl;
    
    m[2] = 4;  // reset

    delta(m, m[3]) = 77;  // m[3]=1, quindi delta(m,1) = 77 → m[1]=77
    cout << "Dopo delta(m, m[3])=77: m[1]=" << m[1] << " (atteso: 77)" << endl;
    m[1] = 1;  // reset
    cout << endl;

    // =====================================================================
    // DOMANDA 5: epsilon — la trappola di int*&
    // =====================================================================
    /*
     * epsilon(int*& p) { p++; }
     *
     * ⚠️ ATTENZIONE: modifica il PUNTATORE ORIGINALE!
     *
     * Dopo epsilon(m):
     *   m ora punta a m[1] (era m[0])!
     *   m non punta più all'inizio dell'array!
     *   m[0] ora è il VECCHIO m[1]!
     *
     * PERICOLO: non puoi più fare delete[] m perché m non punta
     *   all'inizio del blocco allocato!
     *   delete[] m → UNDEFINED BEHAVIOR!
     *
     * Soluzione: salvare il puntatore originale PRIMA di epsilon.
     */
    cout << "--- DOMANDA 5: epsilon(m) — TRAPPOLA int*& ---" << endl;
    int* originale = m;  // salvo l'inizio dell'array!
    
    cout << "Prima: m[0]=" << m[0] << " (punta a inizio)" << endl;
    epsilon(m);
    cout << "Dopo:  m[0]=" << m[0] << " (m spostato! era m[1]=1)" << endl;
    epsilon(m);
    cout << "Dopo:  m[0]=" << m[0] << " (spostato ancora! era m[2]=4)" << endl;

    // Per deallocare DEVO usare il puntatore originale!
    // delete[] m;         ← ⚠️ CRASH! m non è più l'inizio!
    cout << endl;

    m = originale;  // ripristino per sicurezza

    // =====================================================================
    // DOMANDA 6: QUIZ MISTO FINALE — Cosa stampa?
    // =====================================================================
    cout << "--- DOMANDA 6: QUIZ FINALE ---" << endl;

    int* a = new int[4]{10, 20, 30, 40};
    int* b = a + 1;
    int& r = a[2];
    int** pp = &b;

    /*
     * STEP-BY-STEP:
     *   a = [10, 20, 30, 40]
     *   b → a[1] = 20
     *   r è alias di a[2] = 30
     *   pp → b (pp è puntatore al puntatore b)
     *
     * Riga 1: *b = r;
     *   b punta a a[1], r = a[2] = 30
     *   a[1] = 30
     *   a = [10, 30, 30, 40]
     *
     * Riga 2: r = **pp + 5;
     *   **pp = *b (pp→b→a[1]) = 30
     *   r = 30 + 5 = 35
     *   r è alias di a[2] → a[2] = 35
     *   a = [10, 30, 35, 40]
     *
     * Riga 3: (*pp)++;
     *   *pp = b (il puntatore b stesso)
     *   b++ → b ora punta a a[2]
     *   a invariato = [10, 30, 35, 40]
     *   b → a[2] = 35
     *
     * Riga 4: **pp = 0;
     *   **pp = *b = a[2] = 0
     *   a = [10, 30, 0, 40]
     *   ⚠️ Ma r è alias di a[2]! Ora r = 0
     */
    *b = r;         // a[1] = 30
    r = **pp + 5;   // a[2] = 35
    (*pp)++;        // b sposta a a[2]
    **pp = 0;       // a[2] = 0

    cout << "a[0]=" << a[0] << " (atteso: 10)" << endl;
    cout << "a[1]=" << a[1] << " (atteso: 30)" << endl;
    cout << "a[2]=" << a[2] << " (atteso: 0)" << endl;
    cout << "a[3]=" << a[3] << " (atteso: 40)" << endl;
    cout << "r   =" << r << " (atteso: 0, alias di a[2])" << endl;
    cout << "*b  =" << *b << " (atteso: 0, b punta a a[2])" << endl;

    delete[] a;
    delete[] originale;  // dealloca l'array della matricola

    return 0;
}
