/*
 * ============================================================================
 *  ESERCIZIO 8: CONST CON PUNTATORI E REFERENCE
 *               Le 4 combinazioni di const — uscite d'esame classiche
 * ============================================================================
 */

#include <iostream>
using namespace std;

int main() {

    // =====================================================================
    // LE 4 COMBINAZIONI DI CONST CON PUNTATORI
    // =====================================================================
    /*
     * SCHEMA:
     *
     *  1) int* p               → "puntatore a int"
     *     Si può modificare sia p (dove punta) sia *p (il valore puntato)
     *
     *  2) const int* p         → "puntatore a CONST int"
     *     (equivale a: int const* p)
     *     Si può modificare p (dove punta), ma NON *p (il valore è protetto)
     *     "Posso guardare attraverso il vetro, ma non toccare"
     *
     *  3) int* const p         → "puntatore COSTANTE a int"
     *     NON si può modificare p (è fisso), ma si può modificare *p
     *     "Sono inchiodato qui, ma posso modificare quello che vedo"
     *
     *  4) const int* const p   → "puntatore COSTANTE a CONST int"
     *     NON si può modificare né p né *p
     *     "Non mi muovo e non tocco niente"
     *
     * TRUCCO PER RICORDARE: leggi da DESTRA a SINISTRA!
     *   int* const p     → p è un const puntatore a int
     *   const int* p     → p è un puntatore a int costante
     *   const int* const → p è un const puntatore a int costante
     */

    int x = 10, y = 20;

    cout << "=== LE 4 COMBINAZIONI DI CONST ===" << endl;
    cout << "x=" << x << ", y=" << y << endl << endl;

    // --- Caso 1: int* (nessun const) ---
    {
        int* p = &x;
        *p = 11;     // ✅ OK: modifico il valore
        p = &y;      // ✅ OK: cambio dove punta
        cout << "1) int* p:             *p=" << *p << " (modificabile tutto)" << endl;
        x = 10; y = 20;  // reset
    }

    // --- Caso 2: const int* (puntatore a valore costante) ---
    {
        const int* p = &x;
        // *p = 11;  // ❌ ERRORE! Non si può modificare il valore puntato!
        p = &y;      // ✅ OK: il puntatore stesso si può spostare
        cout << "2) const int* p:       *p=" << *p << " (valore NON modificabile)" << endl;
    }

    // --- Caso 3: int* const (puntatore costante) ---
    {
        int* const p = &x;
        *p = 11;     // ✅ OK: il valore si può modificare
        // p = &y;   // ❌ ERRORE! Il puntatore è fisso!
        cout << "3) int* const p:       *p=" << *p << " (puntatore NON spostabile)" << endl;
        x = 10;  // reset
    }

    // --- Caso 4: const int* const (tutto costante) ---
    {
        const int* const p = &x;
        // *p = 11;  // ❌ ERRORE!
        // p = &y;   // ❌ ERRORE!
        cout << "4) const int* const p: *p=" << *p << " (NIENTE modificabile)" << endl;
    }

    // =====================================================================
    // DOMANDA 1: Quali assegnamenti sono VALIDI?
    // =====================================================================
    /*
     *  int a = 5;
     *  const int b = 10;
     *
     *  CASO A: int* p = &a;            ← ✅ OK
     *  CASO B: int* p = &b;            ← ❌ ERRORE! b è const, p no!
     *                                      "p potrebbe modificare b"
     *  CASO C: const int* p = &a;      ← ✅ OK! "prometto di non modificare a"
     *  CASO D: const int* p = &b;      ← ✅ OK! entrambi const
     *  CASO E: int* const p = &a;      ← ✅ OK (p è fisso, ma *p modificabile)
     *  CASO F: int* const p = &b;      ← ❌ ERRORE! serve const int* const
     *
     *  REGOLA: puoi AGGIUNGERE const (A→C), ma NON TOGLIERLO (B)!
     *    int* → const int*     ← OK (aggiungi protezione)
     *    const int* → int*     ← ERRORE (togli protezione)
     */
    cout << "\n=== DOMANDA 1: Conversioni const ===" << endl;
    int a = 5;
    const int b = 10;

    int* p1 = &a;                   // ✅
    // int* p2 = &b;               // ❌ discards const!
    const int* p3 = &a;            // ✅ aggiunge const
    const int* p4 = &b;            // ✅
    int* const p5 = &a;            // ✅
    // int* const p6 = &b;         // ❌ discards const!
    const int* const p7 = &b;      // ✅

    cout << "p1  (int*)          = " << *p1 << endl;
    cout << "p3  (const int*)    = " << *p3 << endl;
    cout << "p4  (const int*)    = " << *p4 << endl;
    cout << "p5  (int* const)    = " << *p5 << endl;
    cout << "p7  (const int* const) = " << *p7 << endl;

    // =====================================================================
    // DOMANDA 2: CONST REFERENCE
    // =====================================================================
    /*
     *  const int& r = x;
     *    → r è un alias READ-ONLY di x
     *    → NON si può fare r = 5; (errore!)
     *    → Ma x = 5 funziona! E poi r riflette il cambio.
     *
     *  PARTICOLARITÀ: const ref può legarsi a un RVALUE (temporaneo)!
     *    const int& r = 42;      ← ✅ OK!
     *    int& r = 42;            ← ❌ ERRORE! Non-const ref a rvalue
     *
     *    const int& r = a + b;   ← ✅ OK! Il temporaneo vive finché r esiste
     *    int& r = a + b;         ← ❌ ERRORE!
     */
    cout << "\n=== DOMANDA 2: Const reference ===" << endl;

    int val = 42;
    const int& cref = val;

    cout << "val=" << val << ", cref=" << cref << endl;
    // cref = 99;   // ❌ ERRORE! const reference!
    val = 99;
    cout << "Dopo val=99: cref=" << cref << " (riflette il cambio!)" << endl;

    // Const ref a temporaneo
    const int& temp = 3 + 4;   // ✅ OK! 7 sopravvive
    cout << "const int& temp = 3+4 → temp=" << temp << endl;

    // =====================================================================
    // DOMANDA 3: Passaggio per const reference a funzione
    // =====================================================================
    /*
     * void stampa(const int& x) { cout << x; }
     *
     * Con const int&:
     *   stampa(variabile);   ← ✅ OK
     *   stampa(42);          ← ✅ OK  (const ref si lega a rvalue!)
     *   stampa(a + b);       ← ✅ OK  (const ref si lega a temporaneo!)
     *
     * Senza const (int&):
     *   void modifica(int& x) { x++; }
     *   modifica(variabile);  ← ✅ OK
     *   modifica(42);         ← ❌ ERRORE! Non puoi passare rvalue a int&
     *   modifica(a + b);      ← ❌ ERRORE! Temporaneo non può essere modificato
     *
     * REGOLA PRATICA:
     *   Se la funzione NON modifica il parametro → usa const int&
     *   Se la funzione MODIFICA il parametro → usa int&
     */
    cout << "\n=== DOMANDA 3: const ref nelle funzioni ===" << endl;
    
    auto stampa = [](const int& x) { cout << "  Valore: " << x << endl; };
    auto modifica = [](int& x) { x *= 2; };

    int v = 5;
    stampa(v);        // ✅
    stampa(42);       // ✅ (const ref accetta rvalue!)
    stampa(v + 10);   // ✅ (const ref accetta temporanei!)

    modifica(v);      // ✅ v diventa 10
    cout << "  Dopo modifica: v=" << v << endl;
    // modifica(42);  // ❌ Cannot bind non-const lvalue reference to rvalue

    // =====================================================================
    // DOMANDA 4: QUIZ — cosa compila e cosa no?
    // =====================================================================
    cout << "\n=== DOMANDA 4: QUIZ COMPILAZIONE ===" << endl;

    int xx = 1;
    const int yy = 2;
    int* pp = &xx;
    const int* cp = &yy;

    /*
     * a) *pp = yy;          ← ✅ OK! Copia il VALORE di yy in xx
     * b) *cp = xx;          ← ❌ ERRORE! cp è const int* → *cp non modificabile
     * c) pp = cp;           ← ❌ ERRORE! const int* → int* rimuove const!
     * d) cp = pp;           ← ✅ OK! int* → const int* aggiunge const
     * e) int& r = *cp;      ← ❌ ERRORE! *cp è const, r no!
     * f) const int& r = *pp; ← ✅ OK! Aggiunge const
     * g) *pp = *cp;          ← ✅ OK! Copia il valore (sola lettura di *cp)
     */
    cout << "a) *pp = yy;           ✅ Copia valore" << endl;
    cout << "b) *cp = xx;           ❌ cp è const int*" << endl;
    cout << "c) pp = cp;            ❌ Rimuove const" << endl;
    cout << "d) cp = pp;            ✅ Aggiunge const" << endl;
    cout << "e) int& r = *cp;       ❌ Rimuove const" << endl;
    cout << "f) const int& r = *pp; ✅ Aggiunge const" << endl;
    cout << "g) *pp = *cp;          ✅ Lettura da cp OK, scrittura su pp OK" << endl;

    return 0;
}
