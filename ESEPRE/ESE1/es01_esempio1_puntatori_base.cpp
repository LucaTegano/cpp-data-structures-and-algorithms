/*
 * ============================================================================
 *  ESERCIZIO 1 (ESEMPIO DATO): Puntatori, dereferenziazione, aritmetica
 * ============================================================================
 *  Matricola esempio: {1, 2, 3, 4, 5, 6}
 */

#include <iostream>
using namespace std;

void f(int* a) {
    int b = (*a + 3);   // b = VALORE puntato da a + 3
    int c = *(a + 3);   // c = valore nella posizione a+3 (3 posizioni avanti)
    cout << b << " " << c << endl;
}

int main() {
    int* matricola = new int[6]{1, 2, 3, 4, 5, 6};

    // =====================================================================
    // DOMANDA 1: f(matricola) è corretta? Se si, cosa stampa?
    // =====================================================================
    /*
     * RISPOSTA: SÌ, è corretta.
     *
     * matricola punta a matricola[0] = 1
     *
     * Dentro f(a):
     *   a = matricola → punta a matricola[0]
     *   
     *   b = (*a + 3)
     *       ^^^^^
     *       *a = matricola[0] = 1
     *       b = 1 + 3 = 4
     *
     *   c = *(a + 3)
     *       ^^^^^^^^
     *       a + 3 = &matricola[3]  (aritmetica puntatori: 3 posizioni avanti)
     *       *(a + 3) = matricola[3] = 4
     *
     *   STAMPA: 4 4
     *
     * ATTENZIONE alla differenza:
     *   (*a + 3)  = "prendi il valore puntato, poi aggiungi 3"     → algebra
     *   *(a + 3)  = "sposta il puntatore di 3 posizioni, poi leggi" → aritmetica ptr
     */
    cout << "Domanda 1: ";
    f(matricola);  // Stampa: 4 4

    // =====================================================================
    // DOMANDA 2: f(matricola+3) è corretta? Se si, cosa stampa?
    // =====================================================================
    /*
     * RISPOSTA: SÌ, è corretta.
     *
     * matricola + 3 punta a matricola[3] = 4
     *
     * Dentro f(a):
     *   a = matricola + 3 → punta a matricola[3]
     *
     *   b = (*a + 3)
     *       *a = matricola[3] = 4
     *       b = 4 + 3 = 7
     *
     *   c = *(a + 3)
     *       a + 3 = &matricola[6]  ← ATTENZIONE! FUORI DALL'ARRAY!
     *       Accesso a matricola[6] → UNDEFINED BEHAVIOR!
     *       L'array ha indici 0-5, l'indice 6 è FUORI BOUNDS.
     *
     *   STAMPA: 7 <valore_imprevedibile>
     *
     *   NOTA: il programma NON crasha necessariamente, ma il comportamento
     *   è indefinito. In un esame, la risposta corretta è dire che c'è
     *   un accesso fuori dai limiti dell'array.
     */
    cout << "Domanda 2: ";
    f(matricola + 3);  // Stampa: 7 <undefined behavior>

    // =====================================================================
    // DOMANDA 3: while(!matricola.empty()) matricola.pop_back() è corretta?
    // =====================================================================
    /*
     * RISPOSTA: NO, NON è corretta.
     *
     * matricola è un int* (puntatore raw), NON un std::vector!
     * 
     * .empty() e .pop_back() sono METODI di std::vector.
     * Un puntatore NON ha metodi → ERRORE DI COMPILAZIONE.
     *
     * Un int* è solo un indirizzo di memoria. Non sa quanto è grande
     * l'array, non ha metodi, non può "ridursi".
     *
     * Per usare quei metodi servirebbe:
     *   vector<int> matricola = {1, 2, 3, 4, 5, 6};
     */

    // =====================================================================
    // DOMANDA 4: Come deallocare la memoria?
    // =====================================================================
    /*
     * RISPOSTA: delete[] matricola;
     *
     * REGOLA D'ORO:
     *   - new      → delete
     *   - new[]    → delete[]
     *
     * Abbiamo usato new int[6] → quindi usiamo delete[]
     *
     * ERRORI COMUNI:
     *   - delete matricola;     ← SBAGLIATO! Manca []
     *   - free(matricola);      ← SBAGLIATO! È C, non C++
     *   - Non deallocare affatto → MEMORY LEAK
     */
    delete[] matricola;

    return 0;
}
