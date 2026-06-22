/*
 * ============================================================================
 *  ESERCIZIO 4: REFERENCE — Swap, passaggio per valore/ref/puntatore
 * ============================================================================
 *  Matricola esempio: {9, 4, 2, 7, 6, 1}
 */

#include <iostream>
using namespace std;

// --- Funzione A: passaggio per VALORE (copia) ---
void swapValore(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    // a e b sono COPIE locali → le modifiche NON si propagano!
}

// --- Funzione B: passaggio per REFERENCE ---
void swapReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
    // a e b sono ALIAS degli originali → le modifiche SI propagano!
}

// --- Funzione C: passaggio per PUNTATORE ---
void swapPuntatore(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    // dereferenziamo i puntatori → modifica gli originali
}

// --- Funzione D: TRAPPOLA! Scambia i puntatori, non i valori ---
void swapPuntatoreErrato(int* a, int* b) {
    int* temp = a;
    a = b;
    b = temp;
    // Scambia le COPIE LOCALI dei puntatori → NON modifica gli originali!
}

// --- Funzione E: Modifica con side-effect nascosto ---
int& maxRef(int& a, int& b) {
    return (a > b) ? a : b;
}

// --- Funzione F: Reference a elemento di array ---
void raddoppiaIndex(int* arr, int& idx) {
    arr[idx] *= 2;
    idx++;  // ATTENZIONE: modifica anche l'indice!
}

int main() {
    int* m = new int[6]{9, 4, 2, 7, 6, 1};

    // =====================================================================
    // DOMANDA 1: Quale swap funziona?
    // =====================================================================
    /*
     * RISPOSTA:
     *
     * swapValore(m[0], m[1]):
     *   a = 9 (copia), b = 4 (copia)
     *   Scambia le copie locali → m[0] e m[1] NON cambiano!
     *   m = {9, 4, 2, 7, 6, 1} → INVARIATO      ❌ NON funziona
     *
     * swapReference(m[0], m[1]):
     *   a è alias di m[0], b è alias di m[1]
     *   Scambia gli originali → m[0]=4, m[1]=9
     *   m = {4, 9, 2, 7, 6, 1}                   ✅ Funziona
     *
     * swapPuntatore(&m[2], &m[3]):
     *   a = &m[2], b = &m[3]
     *   *a e *b modificano gli originali
     *   m = {4, 9, 7, 2, 6, 1}                   ✅ Funziona
     *
     * swapPuntatoreErrato(&m[4], &m[5]):
     *   Scambia le copie dei puntatori, non i valori!
     *   m = {4, 9, 7, 2, 6, 1} → INVARIATO       ❌ NON funziona
     */
    cout << "=== DOMANDA 1: Quale swap funziona? ===" << endl;
    
    cout << "Prima: ";
    for (int i = 0; i < 6; i++) cout << m[i] << " ";
    cout << endl;

    swapValore(m[0], m[1]);
    cout << "Dopo swapValore(m[0],m[1]):          ";
    for (int i = 0; i < 6; i++) cout << m[i] << " ";
    cout << " (INVARIATO)" << endl;

    swapReference(m[0], m[1]);
    cout << "Dopo swapReference(m[0],m[1]):       ";
    for (int i = 0; i < 6; i++) cout << m[i] << " ";
    cout << " (SCAMBIATO!)" << endl;

    swapPuntatore(&m[2], &m[3]);
    cout << "Dopo swapPuntatore(&m[2],&m[3]):     ";
    for (int i = 0; i < 6; i++) cout << m[i] << " ";
    cout << " (SCAMBIATO!)" << endl;

    swapPuntatoreErrato(&m[4], &m[5]);
    cout << "Dopo swapPuntatoreErrato(&m[4],&m[5]): ";
    for (int i = 0; i < 6; i++) cout << m[i] << " ";
    cout << " (INVARIATO)" << endl;

    // Reset
    m[0]=9; m[1]=4; m[2]=2; m[3]=7; m[4]=6; m[5]=1;

    // =====================================================================
    // DOMANDA 2: maxRef restituisce un reference — cosa succede?
    // =====================================================================
    /*
     * RISPOSTA:
     *
     * maxRef(m[0], m[1]) ritorna un REFERENCE a m[0] (perché 9 > 4)
     *
     * maxRef(m[0], m[1]) = 0;
     *   → Assegna 0 al reference restituito → m[0] = 0!
     *
     * Dopo: m = {0, 4, 2, 7, 6, 1}
     *
     * CONCETTO: una funzione che ritorna int& permette di ASSEGNARE
     *           attraverso la chiamata di funzione!
     */
    cout << "\n=== DOMANDA 2: Reference come lvalue ===" << endl;
    cout << "Prima:  m[0]=" << m[0] << ", m[1]=" << m[1] << endl;
    maxRef(m[0], m[1]) = 0;  // modifica il maggiore tra m[0] e m[1]
    cout << "Dopo maxRef(m[0],m[1])=0:  m[0]=" << m[0] << ", m[1]=" << m[1] << endl;
    // Stampa: m[0]=0, m[1]=4
    m[0] = 9;  // ripristino

    // =====================================================================
    // DOMANDA 3: Reference + indice — effetto collaterale
    // =====================================================================
    /*
     * RISPOSTA:
     *
     * int idx = 1;
     * raddoppiaIndex(m, idx):
     *   arr[idx] *= 2 → m[1] *= 2 → m[1] = 4*2 = 8
     *   idx++          → idx = 2 ← MODIFICATO perché passato per ref!
     *
     * raddoppiaIndex(m, idx):  (ora idx = 2)
     *   arr[idx] *= 2 → m[2] *= 2 → m[2] = 2*2 = 4
     *   idx++          → idx = 3
     *
     * Chiama due volte con lo stesso idx, ma modifica posizioni DIVERSE!
     * Questo è un side-effect subdolo del passaggio per reference.
     *
     * Risultato: m = {9, 8, 4, 7, 6, 1}, idx = 3
     */
    cout << "\n=== DOMANDA 3: Side-effect con reference ===" << endl;
    int idx = 1;
    cout << "Prima: m[1]=" << m[1] << ", m[2]=" << m[2] << ", idx=" << idx << endl;
    raddoppiaIndex(m, idx);
    cout << "Dopo 1a chiamata: m[1]=" << m[1] << ", idx=" << idx << endl;
    raddoppiaIndex(m, idx);
    cout << "Dopo 2a chiamata: m[2]=" << m[2] << ", idx=" << idx << endl;
    // m[1]=8, m[2]=4, idx=3

    // =====================================================================
    // DOMANDA 4: Cosa NON si può fare con i reference?
    // =====================================================================
    /*
     * REGOLE dei reference:
     *
     * 1) Un reference DEVE essere inizializzato alla dichiarazione
     *    int& r;           ← ERRORE! Reference senza inizializzazione
     *
     * 2) Un reference NON può essere ri-assegnato a un altro oggetto
     *    int a = 5, b = 10;
     *    int& r = a;       ← r è alias di a
     *    r = b;            ← NON ri-assegna r! Copia il VALORE di b in a!
     *                         Dopo: a = 10, r è ancora alias di a
     *
     * 3) Non esistono "reference a NULL"
     *    int& r = nullptr;  ← ERRORE!
     *
     * 4) Non esistono array di reference
     *    int& arr[3];       ← ERRORE!
     *
     * 5) Non esistono puntatori a reference (ma reference a puntatori sì!)
     *    int&* p;           ← ERRORE!
     *    int*& p = ...;     ← OK! Reference a puntatore
     */
    cout << "\n=== DOMANDA 4: Ri-assegnazione reference ===" << endl;
    int a = 5, b = 10;
    int& r = a;
    cout << "a=" << a << ", b=" << b << ", r=" << r << endl;
    r = b;  // COPIA il valore di b in a, NON ri-assegna r!
    cout << "Dopo r=b: a=" << a << ", b=" << b << ", r=" << r << endl;
    // a=10, b=10, r=10 (r è ancora alias di a, e a ora vale 10!)
    b = 99;
    cout << "Dopo b=99: a=" << a << ", r=" << r << " (r NON segue b!)" << endl;
    // a=10, r=10 → conferma che r è alias di a, non di b

    delete[] m;
    return 0;
}
