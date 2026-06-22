/*
 * ============================================================================
 *  ESERCIZIO 3: ARITMETICA DEI PUNTATORI — Trappole e insidie
 * ============================================================================
 *  Matricola esempio: {7, 0, 3, 8, 1, 5}
 */

#include <iostream>
using namespace std;

int main() {
    int* m = new int[6]{7, 0, 3, 8, 1, 5};

    // =====================================================================
    // DOMANDA 1: Cosa stampa ciascuna istruzione?
    // =====================================================================
    /*
     * RISPOSTA:
     *
     * a) *m             = m[0] = 7            (dereferenzia il primo elemento)
     * b) *(m+1)         = m[1] = 0            (secondo elemento)
     * c) *m + 1         = m[0] + 1 = 7+1 = 8  (valore + 1, NON puntatore + 1!)
     * d) (*m)++         = prima stampa 7, poi m[0] diventa 8
     *                     (post-incremento del VALORE puntato)
     * e) *(m++) sarebbe pericoloso: sposta il puntatore m!
     *
     * REGOLA: la precedenza degli operatori è CRUCIALE:
     *   *m + 1   → (*m) + 1     (dereferenzia, poi somma)
     *   *(m + 1) → prende m[1]   (somma al puntatore, poi dereferenzia)
     *   *m++     → *(m++)        (dereferenzia, poi sposta m — PERICOLOSO!)
     *   (*m)++   → incrementa il valore puntato
     *   ++*m     → ++(*m)        (pre-incrementa il valore puntato)
     */
    cout << "=== DOMANDA 1: Precedenza operatori ===" << endl;
    cout << "a) *m       = " << *m << endl;        // 7
    cout << "b) *(m+1)   = " << *(m + 1) << endl;  // 0
    cout << "c) *m + 1   = " << *m + 1 << endl;    // 8 (7+1)
    
    // Attenzione: (*m)++ modifica m[0]!
    int val = (*m)++;  // val = 7 (vecchio valore), m[0] diventa 8
    cout << "d) (*m)++   → val=" << val << ", *m ora=" << *m << endl;
    m[0] = 7;  // ripristino

    // =====================================================================
    // DOMANDA 2: Differenza tra p[i], *(p+i), e i[p]
    // =====================================================================
    /*
     * RISPOSTA: Sono TUTTE equivalenti!
     *
     * In C/C++: p[i] è definito come *(p + i)
     * E poiché l'addizione è commutativa: *(p + i) == *(i + p) == i[p]
     *
     * Quindi: m[3] == *(m+3) == 3[m] == *(3+m)
     *
     * Questa è una curiosità sintattica. In un esame potresti vedere:
     *   cout << 2[m] << endl;  → stampa m[2] = 3
     */
    cout << "\n=== DOMANDA 2: Equivalenze bizzarre ===" << endl;
    cout << "m[3]    = " << m[3] << endl;      // 8
    cout << "*(m+3)  = " << *(m + 3) << endl;  // 8
    cout << "3[m]    = " << 3[m] << endl;      // 8  ← sì, funziona!
    cout << "*(3+m)  = " << *(3 + m) << endl;  // 8

    // =====================================================================
    // DOMANDA 3: Cosa stampano queste istruzioni?
    // =====================================================================
    /*
     * ANALISI:
     *
     * int* p = m + 2;   → p punta a m[2] = 3
     * int* q = m + 5;   → q punta a m[5] = 5
     *
     * a) q - p = 3    (differenza puntatori = differenza in ELEMENTI, non bytes!)
     *                  q è 3 posizioni avanti rispetto a p
     *
     * b) *(p + (q - p) / 2)
     *    q - p = 3, 3/2 = 1 (divisione intera!)
     *    p + 1 = &m[3]
     *    *(p + 1) = m[3] = 8
     *
     * c) &m[4] - &m[1] = 3  (differenza puntatori = 3 posizioni)
     *
     * d) &m[4] < &m[1] ? → FALSE (m[4] è dopo m[1] in memoria)
     *    I puntatori nello stesso array si possono confrontare!
     */
    int* p = m + 2;
    int* q = m + 5;

    cout << "\n=== DOMANDA 3: Aritmetica differenza puntatori ===" << endl;
    cout << "a) q - p             = " << q - p << endl;              // 3
    cout << "b) *(p + (q-p)/2)    = " << *(p + (q - p) / 2) << endl; // 8
    cout << "c) &m[4] - &m[1]     = " << &m[4] - &m[1] << endl;     // 3
    cout << "d) &m[4] < &m[1]     = " << (&m[4] < &m[1]) << endl;   // 0 (false)

    // =====================================================================
    // DOMANDA 4: Cosa c'è di sbagliato?
    // =====================================================================
    /*
     * Codice: int* r = m + 3;
     *         r++;
     *         r++;
     *         r++;
     *         cout << *r << endl;
     *
     * RISPOSTA: 
     *   r = m + 3 → punta a m[3]
     *   r++ → r punta a m[4]
     *   r++ → r punta a m[5]
     *   r++ → r punta a m[6] ← FUORI DALL'ARRAY! (0-5 sono validi)
     *   *r → UNDEFINED BEHAVIOR (accesso fuori bounds)
     *
     * NOTA: spostarsi a m[6] senza dereferenziare è LECITO in C++ 
     *   (one-past-the-end), ma dereferenziare m[6] è UB!
     */
    cout << "\n=== DOMANDA 4: Fuori bounds con incremento ===" << endl;
    cout << "r = m+3, poi r++ tre volte → r punta a m[6] → OUT OF BOUNDS!" << endl;

    // =====================================================================
    // DOMANDA 5: sizeof con puntatori
    // =====================================================================
    /*
     * TRAPPOLA CLASSICA:
     *
     * sizeof(m)   = dimensione del PUNTATORE (8 byte su sistemi 64-bit)
     *               NON la dimensione dell'array!
     *
     * sizeof(*m)  = sizeof(int) = 4 byte
     *
     * Per un array STATICO:
     *   int arr[6] = {...};
     *   sizeof(arr) = 6 * 4 = 24 byte ← dimensione dell'intero array!
     *   sizeof(arr) / sizeof(arr[0]) = 24/4 = 6 ← numero di elementi
     *
     * Ma con un array DINAMICO (new[]):
     *   sizeof(m) = 8 (solo la dimensione del puntatore!)
     *   Non puoi conoscere la dimensione dell'array dal puntatore!
     */
    int arr_statico[6] = {1, 2, 3, 4, 5, 6};
    cout << "\n=== DOMANDA 5: sizeof ===" << endl;
    cout << "sizeof(m)            = " << sizeof(m) << " (puntatore!)" << endl;
    cout << "sizeof(*m)           = " << sizeof(*m) << " (un int)" << endl;
    cout << "sizeof(arr_statico)  = " << sizeof(arr_statico) << " (intero array)" << endl;
    cout << "Num elementi         = " << sizeof(arr_statico) / sizeof(arr_statico[0]) << endl;

    delete[] m;
    return 0;
}
